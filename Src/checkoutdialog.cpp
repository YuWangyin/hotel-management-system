//预定了，就需要组员去拉屎打卡。等组员打卡完坑位，更新入数据库
#include "checkoutdialog.h"
#include "ui_checkoutdialog.h"

#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>
#include "app/myhelper.h"

#include "app/iconhelper.h"
#include "app/myapp.h"
#include <QDate>

CheckOutDialog::CheckOutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckOutDialog)
{
    ui->setupUi(this);
    this->InitForm();
}

CheckOutDialog::~CheckOutDialog()
{
    delete ui;
}

void CheckOutDialog::InitForm()
{
    ColumnNames[0] = tr("订单编号");//设置表格列名
    ColumnNames[1] = tr("坑位编号");
    ColumnNames[2] = tr("组员姓名");
    ColumnNames[3] = tr("坑位类型");
    ColumnNames[4] = tr("预定时间");
    ColumnNames[5] = tr("价格");
    ColumnNames[6] = tr("电话");
    ColumnNames[7] = tr("备注");

    ColumnWidths[0] = 70;//设置表格列宽
    ColumnWidths[1] = 100;
    ColumnWidths[2] = 80;
    ColumnWidths[3] = 100;
    ColumnWidths[4] = 100;
    ColumnWidths[5] = 200;
    ColumnWidths[6] = 160;
    ColumnWidths[7] = 200;

    //将数据库中的一张表中的内容显示到tableView控件上
    BindCustomInfo("book",ui->tableView,ColumnNames,ColumnWidths);



    //showCustomerInfo()将点击的tableView列表内容放到各个格子中
    this->connect(ui->tableView,SIGNAL(clicked(QModelIndex)),SLOT(showCustomerInfo()));

}

void CheckOutDialog::BindCustomInfo(QString tableName, QTableView *tableView, QString columnNames[], int columnWidths[])
{
    QueryModel = new QSqlQueryModel(this);
    QString sql = "SELECT *FROM " + tableName+";";//查询语句
    qDebug() <<sql;
    QueryModel->setQuery(sql);
    tableView->setModel(QueryModel);

    //依次设置列标题、列宽等
    for (int i = 0;i<tableView->model()->columnCount();i++)
    {
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);     //设置列标题
        tableView->setColumnWidth(i,columnWidths[i]);                   //设置列宽
    }

    tableView->horizontalHeader()->setHighlightSections(false);         //点击表头时不对表头光亮
    tableView->setSelectionMode(QAbstractItemView::ContiguousSelection);//选中模式为多行选中
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);     //选中整行
    tableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");
}

/*
 *函数功能:当点击tableView显示当前表格中组员的信息到控件上
*/
void CheckOutDialog::showCustomerInfo()
{
    QSqlQueryModel userMode(ui->tableView);
    QString sql = "SELECT *FROM book;";//定义一个SQL语句查询
    qDebug() <<sql;
    userMode.setQuery(QString(sql));
    int Row = ui->tableView->currentIndex().row();//获取当前选中行的行号
    QSqlRecord record = userMode.record(Row);//获取选中行的记录
//    ui->CustomerNo->setText(record.value(0).toString());

	//将选中行的不同字段值赋值到不同的控件上，显示组员的信息
    ui->lineEdit_no->setText(record.value(1).toString());
    ui->lineEdit_name->setText(record.value(2).toString());
//    ui->CustomerRePwd->setText(record.value(3).toString());
//    ui->CustomerPhone->setText(record.value(4).toString());
//    ui->CustomerAddress->setText(record.value(5).toString());
//    ui->ledCustomDate->setText(record.value(6).toString());
//    ui->CustomerRemark->setText(record.value(7).toString());
}
/*

函数功能：当点击“查找”按钮时，将组员退出坑位的信息写入数据库
*/
void CheckOutDialog::on_button_find_clicked()
{
    //组员拉完屎打完了卡，在数据库的room中将坑位编号置“蹲坑打卡成功”
    //在数据库的outbook中添加组员打卡完坑位的那一条记录
    QSqlQueryModel userMode(ui->tableView);
    QString sql = "SELECT *FROM book;";//定义一个SQL语句查询
    qDebug() <<sql;
    userMode.setQuery(QString(sql));
    int Row = ui->tableView->currentIndex().row();
    QSqlRecord record = userMode.record(Row);

	//将选中行的不同字段值赋值到不同的变量中，方便后面操作
    QString currentdatetime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm");
    QString serialNumber = record.value(0).toString();
    QString roomId = record.value(1).toString();    //坑位编号
    QString customerName = record.value(2).toString();
    QString roomTypeId = record.value(3).toString();
    //QString currentdatetime = record.value(4).toString();
    QString roomPrice = record.value(5).toString();
    QString roomphone = record.value(6).toString();

    QSqlQuery query;//创建一个QSqlQuery对象query，用于执行SQL语句
	//更新表中的坑位信息
    QString sqlsqlsql = "update room set RoomState = '空' where RoomNo='"+roomId+"';";
    qDebug() <<sqlsqlsql;
    query.exec(sqlsqlsql);
    qDebug() <<"update ok!";


    QString sqlsql = "INSERT INTO outbook (Id,roomno,BookName,roomtypeid,BookTimeFrom,Price,phone) VALUES ('"+serialNumber+"', '"+roomId+"', '"+customerName+"', '"+roomTypeId+"', '"+currentdatetime+"', '"+roomPrice+"', '"+roomphone+"')";
    qDebug() <<sqlsql;
    qDebug()<<query.exec("INSERT INTO outbook (Id,roomno,BookName,roomtypeid,BookTimeFrom,Price,phone) VALUES ('"+serialNumber+"', '"+roomId+"', '"+customerName+"', '"+roomTypeId+"', '"+currentdatetime+"', '"+roomPrice+"', '"+roomphone+"')");//执行SQL语句
    qDebug() <<"update!";


    //组员离开坑位，从数据库的book表中删除组员蹲坑的那一条记录，表示组员已经打卡完坑位
    QString no = ui->lineEdit_no->text();
    //QSqlQuery query;
    sql = "delete from room where roomno = '"+no+"'";
    qDebug() <<sql;
    qDebug()<<query.exec("delete from book where roomno = '"+no+"'");
    qDebug() <<"update ok!";


    //将删除后的表的内容显示在tableView中
    BindCustomInfo("book",ui->tableView,ColumnNames,ColumnWidths);

    myHelper::ShowMessageBoxInfo("蹲坑成功");


}

void CheckOutDialog::on_push_find_clicked()
{
    InitForm();

}

void CheckOutDialog::on_tableView_activated(const QModelIndex &index)
{

}
