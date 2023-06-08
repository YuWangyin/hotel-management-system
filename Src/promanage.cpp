﻿//显示坑位信息的界面
#include "promanage.h"
#include "ui_promanage.h"
#include <QDateTime>
#include "app/Connection.h"


ProManage::ProManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProManage)
{
    ui->setupUi(this);
    this->initForm();
}

ProManage::~ProManage()
{
    delete ui;
}

void ProManage::initForm()
{
    //mythread.SetCurrentTime(ui->Datetimelabel);
    /***************创建一个定时器，用来显示系统当前的时间*************/
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(showtimeslot()));
    timer->start(1000);// 每隔1秒触发一次timeout()信号

    QueryModel = new QSqlQueryModel(this);
    //初始化表格列名和列宽
    ColumnNames[0] = tr("坑位编号");
    ColumnNames[1] = tr("坑位类型");
    ColumnNames[2] = tr("坑位价格");
    ColumnNames[3] = tr("坑位状态");
    ColumnNames[4] = tr("备注");

    ColumnWidths[0] = 80;
    ColumnWidths[1] = 120;
    ColumnWidths[2] = 120;
    ColumnWidths[3] = 120;
    ColumnWidths[4] = 200;

    //mysql = new MysqlApi(this);//实例化数据库操作对象，以备以后调用
    //mysql->SetControl(ui->tableView,ui->labInfo,ui->btnFirst,ui->btnPre,ui->btnNext,ui->btnLast);
    //mysql->BindData("Room","RoomId","dec",10,ColumnNames,ColumnWidths);
    BindHotelInfo("Room",ui->tableView,ColumnNames,ColumnWidths);

    this->connect(ui->tableView,SIGNAL(clicked(QModelIndex)),SLOT(showCurrentRoomNo()));
}

/*
 *函数功能：实现数据绑定
 *输入参数：数据表名，tableview名，列名，列宽度
 *输出参数：无
 *返回值：无
*/
void ProManage::MyBindTable(QString tableName, QTableView *tableView, QString columnNames[], int columnWidths[])
{
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

/*
 *函数功能：将坑位信息显示在tableview中
 *说明：显示坑位信息时用到两张表，需要关联操作
*/
void ProManage::BindHotelInfo(QString tableName, QTableView *tableView, QString columnNames[], int columnWidths[])
{
    TableView = tableView;
    QString sql = "SELECT RoomNo,Typename,TypePrice,RoomState,RoomRemark FROM " + tableName+
            ",RoomType where room.RoomTypeId=roomtype.RoomTypeId;";
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

/*
 *函数功能：带条件  绑定数据
 *输入参数：表名，排序的列名，排序方式(升序或降序)，条件，列名，类宽
 *说明：调用时输入对应的参数
*/
void ProManage::BindDataSelect(QString tableName,QTableView *tableView, QString orderColumn, QString orderType, QString where, QString columnNames[], int columnWidths[])
{
    TableView = tableView;
    QString sql = "SELECT RoomNo,Typename,TypePrice,RoomState,RoomRemark FROM " + tableName+
            ",RoomType where room.RoomTypeId=roomtype.RoomTypeId"+" "+where+" order by "+orderColumn+" "+orderType+";";
    qDebug() <<sql;
    QueryModel->setQuery(sql);
    TableView->setModel(QueryModel);

    //依次设置列标题、列宽等
    for (int i=0;i<TableView->model()->columnCount();i++){
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);//设置列标题
        TableView->setColumnWidth(i,columnWidths[i]);//设置列宽
    }


    TableView->horizontalHeader()->setHighlightSections(false);//点击表头时不对表头光亮
    TableView->setSelectionMode(QAbstractItemView::SingleSelection);//选中模式为单行选中
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);//选中整行
    TableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");
}

/*
 *函数功能：显示系统时间
*/
void ProManage::showtimeslot()
{
    ui->Datetimelabel->setText(QDateTime::currentDateTime().toString(tr("yyyy-MM-dd\ndddd HH:mm")));
}

/*
 *函数功能：显示当前坑位编号
*/
void ProManage::showCurrentRoomNo()
{
    QSqlQueryModel userMode(ui->tableView);
    QString sql = "SELECT RoomNo,Typename,TypePrice,RoomState,RoomRemark FROM Room,RoomType where "
            "room.RoomTypeId = roomtype.RoomTypeId";
    qDebug() <<sql;
    userMode.setQuery(QString(sql));
    int Row = ui->tableView->currentIndex().row();
    QSqlRecord record = userMode.record(Row);
    ui->labelRoomNo->setText(record.value(0).toString());
}

/*
 *函数功能：当坑位类型改变时，相应的输出也改变
 *说明：
*/
void ProManage::on_comboBoxRoomType_activated(const QString &arg1)
{
    qDebug() <<"显示"<<arg1<<"信息";
    QString sql = "and Typename='"+arg1+"'";
    if(arg1 == "所有类型坑位")
    {
        sql = "";
    }

    BindDataSelect("Room",ui->tableView,"RoomNo","asc",sql,ColumnNames,ColumnWidths);
}


/*
 *函数功能：当坑位状态变化时，改变相应的输出
*/
void ProManage::on_comboBoxRoomStatus_activated(const QString &arg1)
{
    qDebug() <<"显示"<<arg1<<"房间信息";
    //QString sql = "and RoomState='"+sql+"'";
    QString sql = " ";
    if(arg1 == "不限状态")
    {
        sql +="";
    }
    else if(arg1 == "限空坑位")
    {
        sql +=" and RoomState = '空'";
    }
    else if(arg1 == "限满坑位")
    {
        sql +=" and RoomState = '满'";
    }
    else if(arg1 == "限维修坑位")
    {
        sql +=" and RoomState = '维修'";
    }
    BindDataSelect("Room",ui->tableView,"RoomNo","asc",sql,ColumnNames,ColumnWidths);
}

void ProManage::on_tableView_activated(const QModelIndex &index)
{

}