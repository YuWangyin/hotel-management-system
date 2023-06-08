#include "modiftroomprice.h"
#include "ui_modiftroomprice.h"
#include "app/myhelper.h"


#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>

ModiftRoomPrice::ModiftRoomPrice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModiftRoomPrice)
{
    ui->setupUi(this);
    this->initForm();

}

ModiftRoomPrice::~ModiftRoomPrice()
{
    delete ui;
}

void ModiftRoomPrice::initForm()
{
    //初始化表格列名和列宽
    ColumnNames[0] = tr("坑位类型编号");
    ColumnNames[1] = tr("坑位名称");
    ColumnNames[2] = tr("坑位价格");

    ColumnWidths[0] = 100;
    ColumnWidths[1] = 120;
    ColumnWidths[2] = 120;

    //在表格中显示数据库roomtype表中的内容
    MyBindTable("roomtype",ui->tableView,ColumnNames,ColumnWidths);

    //showRoomInfo()函数功能：获取鼠标点击房间的值，并显示在相应的界面上
    this->connect(ui->tableView,SIGNAL(clicked(QModelIndex)),SLOT(showRoomInfo()));

    //初始化
    ui->lineEditNo->setEnabled(false);
    ui->lineEditName->setEnabled(false);
    ui->lineEditPrice->setEnabled(false);

    ui->pbnSave->setEnabled(false);
    ui->pbnCancel->setEnabled(false);


}

//在表格中显示数据库roomtype表中的内容
void ModiftRoomPrice::MyBindTable(QString tableName, QTableView *tableView, QString columnNames[], int columnWidths[])
{
    QueryModel = new QSqlQueryModel(this);

    TableView = tableView;
    QString sql = "SELECT * FROM " + tableName;
    QueryModel->setQuery(sql);
    TableView->setModel(QueryModel);

    //依次设置列标题、列宽等
    for (int i = 0;i<TableView->model()->columnCount();i++)
    {
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);     //设置列标题
        TableView->setColumnWidth(i,columnWidths[i]);                   //设置列宽
    }

    TableView->horizontalHeader()->setHighlightSections(false);         //点击表头时不对表头光亮
    TableView->setSelectionMode(QAbstractItemView::ContiguousSelection);//选中模式为多行选中
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);     //选中整行
    TableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");
}


void ModiftRoomPrice::on_pbnModify_clicked()
{
    //控件内容可以进行输入
    ui->lineEditNo->setEnabled(true);
    ui->lineEditName->setEnabled(true);
    ui->lineEditPrice->setEnabled(true);

    ui->pbnModify->setEnabled(false);//修改按钮不可用
    //ui->pbnAdd->setEnabled(false);

    ui->pbnSave->setEnabled(true);
    ui->pbnCancel->setEnabled(true);
}

void ModiftRoomPrice::on_pbnSave_clicked()
{
	//获取控件中输入的值
    QString roomtypeNo = ui->lineEditNo->text();
    QString roomtypeName = ui->lineEditName->text();
    QString roomtypePrice = ui->lineEditPrice->text();
	//如果控件中有空字段，则弹出提示信息
    if(roomtypeNo.isEmpty() &&roomtypeName.isEmpty() && roomtypePrice.isEmpty())
    {
        myHelper::ShowMessageBoxInfo(tr("必须填满所有字段！"));
    }
    else
    {
        //QSqlQuery query;

//        bool ok = query.prepare("INSERT INTO roomtype (Id, Typename,TypePrice)"
//                                "VALUES (:Id,:Typename,:TypePrice)");
//        query.bindValue(":Id",roomtypeNo);
//        query.bindValue(":Typename",roomtypeName);
//        query.bindValue(":TypePrice",roomtypePrice);
//        query.setForwardOnly(true);
//        query.exec();
			//生成SQL语句并执行
            QSqlQuery query;
            QString sql = "update roomtype set TypePrice = '"+roomtypePrice+"' where RoomTypeId='"+roomtypeNo+"';";
            qDebug() <<sql;
            qDebug() << query.exec(sql);
            qDebug() <<"update ok!";
            myHelper::ShowMessageBoxInfo(tr("保存坑位信息成功!"));//弹出提示信息
            myHelper::MyLoginBlog("log","修改坑位价格",+"坑位价格改为"+roomtypePrice,"监督官");//写入日志文件

    }

        //在表格中显示数据库roomtype表中的内容
    MyBindTable("roomtype",ui->tableView,ColumnNames,ColumnWidths);
}
//当“取消”按钮被点击时，禁用文本框和按钮
void ModiftRoomPrice::on_pbnCancel_clicked()
{
    ui->lineEditNo->setEnabled(false);
    ui->lineEditName->setEnabled(false);
    ui->lineEditPrice->setEnabled(false);

    ui->pbnModify->setEnabled(true);

    ui->pbnCancel->setEnabled(false);
    ui->pbnSave->setEnabled(false);
}

/*
 *函数功能：获取鼠标点击坑位的值，并显示在相应的界面上
*/
void ModiftRoomPrice::showRoomInfo()
{
    ui->pbnModify->setEnabled(true);
    QSqlQueryModel userMode(ui->tableView);
    QString sql = "SELECT *FROM roomtype;";
    qDebug() <<sql;
    userMode.setQuery(QString(sql));
    int Row = ui->tableView->currentIndex().row();
    QSqlRecord record = userMode.record(Row);
    ui->lineEditNo->setText(record.value(0).toString());
    ui->lineEditName->setText(record.value(1).toString());
    ui->lineEditPrice->setText(record.value(2).toString());
}

void ModiftRoomPrice::on_tableView_activated(const QModelIndex &index)
{

}
