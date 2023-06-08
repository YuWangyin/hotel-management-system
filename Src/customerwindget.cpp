//用户使用的所有界面，以及窗口大小和拖拽的功能实现
#include "customerwindget.h"
#include "ui_customerwindget.h"
#include "app/iconhelper.h"
#include "app/myhelper.h"
#include "app/myapp.h"

#include "logindialog.h"
#include "ui_logindialog.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDate>

CustomerWindget::CustomerWindget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerWindget)
{
    ui->setupUi(this);
    this->InitForm();
}

CustomerWindget::~CustomerWindget()
{
    delete ui;
}

void CustomerWindget::InitForm()
{
    //ui->letNo->setEnabled(false);//用户编号不允许修改

    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    this->setMinimumSize(1000,600);
    location = this->geometry();
    max = false;
    mousePressed = false;
    //安装事件监听器,让标题栏识别鼠标双击
    ui->lab_Title->installEventFilter(this);

    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf096), 10);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Min, QChar(0xf068), 10);
    IconHelper::Instance()->SetIcon(ui->btnMenu, QChar(0xf0c9), 10);
    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf015), 12);

    //初始化表格列名和列宽，用于下面函数的TableView控件中显示坑位列名
    ColumnNames[0] = tr("坑位编号");
    ColumnNames[1] = tr("坑位类型");
    ColumnNames[2] = tr("坑位价格");
    ColumnNames[3] = tr("坑位状态");

    ColumnWidths[0] = 80;
    ColumnWidths[1] = 120;
    ColumnWidths[2] = 120;
    ColumnWidths[3] = 120;

    //顾客信息显示字段初始化，用于下面函数的TableView控件中显示顾客列名
    CustomeColumnNames[0] = "编号";
    CustomeColumnNames[1] = "姓名";
    CustomeColumnNames[2] = "性别";
    CustomeColumnNames[3] = "密码";
    CustomeColumnNames[4] = "电话";
    CustomeColumnNames[5] = "地址";
    CustomeColumnNames[6] = "注册日期";
    CustomeColumnNames[7] = "备注";


    CustomeColumnWidths[0] = 50;
    CustomeColumnWidths[1] = 90;
    CustomeColumnWidths[2] = 100;
    CustomeColumnWidths[3] = 80;
    CustomeColumnWidths[4] = 150;
    CustomeColumnWidths[5] = 200;
    CustomeColumnWidths[6] = 200;
    CustomeColumnWidths[7] = 200;

   //卫生间的坑位信息，函数在下面，控件ui->tableViewRoomInfo
    BindRoomInfo("Room",ui->tableViewRoomInfo,ColumnNames,ColumnWidths);

    ui->dateRfrom->setDate(QDate::currentDate());
    //ui->dateRto->setDate(QDate::currentDate());
    ui->dateCustomeIn->setDate(QDate::currentDate());

    roompicture = new RoomPicDialog();      //坑位房间欣赏界面

    ui->stackedWidget->addWidget(roompicture);

    this->connect(ui->tableViewCustomeInfo,SIGNAL(clicked(QModelIndex)),SLOT(showCustomInfo()));

    ui->pbnmodify->setEnabled(true);
    ui->pbuModifyOk->setEnabled(false);
    ui->pbnCancle->setEnabled(false);


}

/*
 *函数功能：将坑位信息绑定到控件tableview上
*/
void CustomerWindget::BindRoomInfo(QString tableName, QTableView *tableView, QString columnNames[], int columnWidths[])
{
    QueryModel = new QSqlQueryModel(this);
    TableView = tableView;
    QString sql = "SELECT RoomNo,Typename,TypePrice,RoomState FROM " + tableName+
            ",RoomType where room.RoomTypeId = roomtype.RoomTypeId and Roomstate ='空';";
    QueryModel->setQuery(sql);
    TableView->setModel(QueryModel);

    //用setHeaderData()依次设置TableView控件的列标题、列宽等
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
 *函数功能：将组员信息绑定到tableview上
*/
void CustomerWindget::BindCustomeInfo(QString tableName, QTableView *tableView, QString columnNames[], int columnWidths[])
{
    customModel = new QSqlQueryModel(this);

    //QString customename = GetCutrrentUserName("Customelogblog");
    QString customename = Myapp::CurrentUserName;
    qDebug() <<"当前用户名:"<<customename;
    QString sql = "SELECT * FROM " + tableName+
            " where CustomerName ='"+customename+"';";
    qDebug() <<sql;
    QueryModel->setQuery(sql);
    tableView->setModel(QueryModel);

    //依次设置列标题、列宽等
    for (int i = 0;i<tableView->model()->columnCount();i++)
    {
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);     //设置Qt TableView列标题
        tableView->setColumnWidth(i,columnWidths[i]);                   //设置列宽
    }

    tableView->horizontalHeader()->setHighlightSections(false);         //点击表头时不对表头光亮
    tableView->setSelectionMode(QAbstractItemView::ContiguousSelection);//选中模式为多行选中
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);     //选中整行
    tableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");
}

/*
 *函数功能：获取当前登录用户名
*/
QString CustomerWindget::GetCutrrentUserName(QString tablename)
{
    QString sql ="select CustomeName from "+tablename+";";// 构造 SQL 查询语句
    QSqlQuery query;
    query.exec(sql);// 执行 SQL 查询语句
	// 将查询结果移动到第一条记录并输出第一条记录的值
    query.next();
    qDebug() << query.value(0).toString();
    return query.value(0).toString();// 返回第一条记录的值
}

bool CustomerWindget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick) {// 判断是否双击了鼠标左键
        this->on_btnMenu_Max_clicked();// 调用 on_btnMenu_Max_clicked() 函数，最大化窗口
        return true;
    }
    return QObject::eventFilter(obj, event);// 将事件传递给下一个对象处理
}

void CustomerWindget::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton) && !max) {// 如果鼠标左键被按下且窗口没有被最大化
        this->move(e->globalPos() - mousePoint);// 移动窗口到当前鼠标位置减去上一次鼠标位置的差
        e->accept();
    }
}

void CustomerWindget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {// 如果按下了鼠标左键
        mousePressed = true; // 标记鼠标左键已经被按下
        mousePoint = e->globalPos() - this->pos();// 记录当前鼠标位置
        e->accept();
    }
}

void CustomerWindget::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;// 标记鼠标左键已经释放
}

void CustomerWindget::on_btnMenu_Max_clicked()
{
    if (max)// 如果窗口已经被最大化
    {
		// 还原窗口大小和位置
        this->setGeometry(location);
        IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf096), 10);// 更改最大化图标为正常图标
        ui->btnMenu_Max->setToolTip("最大化");// 设置提示信息为最大化
    }
    else
    {
        location = this->geometry();// 记录当前窗口大小和位置
        this->setGeometry(qApp->desktop()->availableGeometry()); //设置窗口大小为屏幕可用大小
        IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf079), 10);// 更改正常图标为最大化图标
        ui->btnMenu_Max->setToolTip("还原");// 设置提示信息为还原
    }
    max = !max;// 标记窗口状态已经改变
}

void CustomerWindget::on_btnMenu_Min_clicked()
{
    this->showMinimized();//最小化窗口按钮按下后，调用showMinimized()函数来实现最小化窗口。
}

void CustomerWindget::on_btnMenu_Close_clicked()
{
	//关闭窗口按钮按下后，关闭当前窗口。
    LoginDialog* logindialog = new LoginDialog();
    logindialog->show();

    this->close();

}

void CustomerWindget::on_punroom_clicked()
{
	//坑位按钮按下后，将stackedWidget的当前页面切换为索引0，即坑位信息界面，并调用BindRoomInfo()函数加载坑位信息。
    ui->stackedWidget->setCurrentIndex(0);
    BindRoomInfo("Room",ui->tableViewRoomInfo,ColumnNames,ColumnWidths);
}

//组员端左边的个人信息按钮按下后：
void CustomerWindget::on_pbnGuest_clicked()
{
	//个人信息按钮按下后，调用BindCustomeInfo()函数加载当前用户的信息，并将stackedWidget的当前页面切换为索引1，即个人信息界面。
    BindCustomeInfo("Customer",ui->tableViewCustomeInfo,CustomeColumnNames,CustomeColumnWidths);

    ui->stackedWidget->setCurrentIndex(1); //stackedWidget（2）是个人信息界面
}


/*
 *函数功能：确认预订那个坑位
*/
void CustomerWindget::on_pbnROK_clicked()
{
    QString roomphone = ui->letphones->text();
    QString roomId = ui->letNo->text();    //坑位编号
    QString roomType = ui->comboBoxRoomType->currentText();  //坑位类型
    QString roomPrice = ui->letprice->text();  //价格
    //QString roomstate = ui->letstate->text();
    //QString dateto = ui->dateRto->text();
    QString datefrom = ui->dateRfrom->text();  //预定时间

    QString currentdatetime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm");
    //QString currentdatetime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");

    //流水号
    QString serialNumber = "2021"+currentdatetime;

    //选了不在线支付的选项
    if(ui->radioButtonNo->isChecked())
    {
        //到店支付，即给现金
        if(roomId.isEmpty()||roomPrice.isEmpty())
        {
            myHelper::ShowMessageBoxError(tr("必须填满带*的字段"));
        }
        else
        {
            QString roomTypeId = "";
            if(roomType == "(1)低调奢华有内涵")
            {
                roomTypeId ="1";
            }
            else if(roomType == "(2)杰哥之家")
            {
                roomTypeId = "2";
            }
            else if(roomType == "(3)比奇堡三剑客")
            {
                roomTypeId = "3";
            }
            else
            {
                roomTypeId = "4";
            }
            qDebug() <<roomTypeId;
            QString customerName = GetCutrrentUserName("customelogblog");
            QSqlQuery query;
//            bool ok = query.prepare("INSERT INTO book(Id,roomno,bookName,roomtypeId,"
//                                    "booktimefrom,booktimeto,bookremark)"
//                                    "VALUES (:Id,:roomno,:bookName,:roomtypeId,:booktimefrom,:booktimeto,:bookremark)");
//            query.bindValue(":Id",serialNumber);
//            query.bindValue(":roomno",roomId);
//            query.bindValue(":bookName",customerName);
//            query.bindValue(":roomtypeId",roomTypeId);
//            //query.bindValue(":booktimefrom",dateto);
//            query.bindValue(":booktimeto",datefrom);
//            query.bindValue(":bookremark"," ");
//            query.setForwardOnly(true);
//            query.exec();

            QString sqlsql = "INSERT INTO book (Id,roomno,BookName,roomtypeid,BookTimeFrom,Price,phone) VALUES ('"+serialNumber+"', '"+roomId+"', '"+customerName+"', '"+roomTypeId+"', '"+currentdatetime+"', '"+roomPrice+"', '"+roomphone+"')";
            qDebug() <<sqlsql;
            qDebug()<<query.exec("INSERT INTO book (Id,roomno,BookName,roomtypeid,BookTimeFrom,Price,phone) VALUES ('"+serialNumber+"', '"+roomId+"', '"+customerName+"', '"+roomTypeId+"', '"+currentdatetime+"', '"+roomPrice+"', '"+roomphone+"')");
            qDebug() <<"update!";

            QString sql = "update room set RoomState = '满' where RoomNo='"+roomId+"';";
            qDebug() <<sql;
            query.exec(sql);
            qDebug() <<"update ok!";

//            if(ok)
//            {
                myHelper::ShowMessageBoxInfo(QString("预订成功!坑位号:"+serialNumber));
                qDebug() <<"组员预订成功!";
//            }
        }

    }
    else if(ui->radioButtonOk->isChecked())
    {
        //在线支付
        myHelper::ShowMessageBoxInfo(tr("请扫描旁边二维码"));
    }
    else
    {
        //其他
        myHelper::ShowMessageBoxInfo(tr("请选择支付方式"));
    }

}

void CustomerWindget::on_comboBoxRoomType_activated(const QString &arg1)
{
    if(arg1 == "(1)低调奢华有内涵")
    {
        ui->letprice->setText("100");
    }
    else if(arg1 == "(2)杰哥之家")
    {
        ui->letprice->setText("150");
    }
    else if(arg1 == "(3)比奇堡三剑客")
    {
        ui->letprice->setText("200");
    }
    else if(arg1 == "(4)米奇妙妙屋")
    {
        ui->letprice->setText("50");
    }
}


void CustomerWindget::on_pbnroomPicture_clicked()
{
	// 当名为 pbnroomPicture 的按钮被点击时，将当前的 stackedWidget 索引设置为 2
    ui->stackedWidget->setCurrentIndex(2);
}

/*
 *修改自己信息
*/
void CustomerWindget::on_pbnmodify_clicked()
{
//    ui->letusename->clear();
//    ui->letsex->clear();
//    ui->letpossword->clear();
//    ui->letphone->clear();
//    ui->letaddress->clear();
//    ui->letGnote->clear();

//    ui->pbnmodify->setEnabled(false);

    ui->pbnmodify->setEnabled(false);// 禁用 pbnmodify 按钮
	// 启用 pbuModifyOk 和 pbnCancle 按钮
    ui->pbuModifyOk->setEnabled(true);
    ui->pbnCancle->setEnabled(true);
}

/*
 *函数功能：确认修改，进行写库
*/
void CustomerWindget::on_pbuModifyOk_clicked()
{
	// 获取文本框中的值
    QString customeName = ui->letusename->text();
    QString customeSex = ui->letsex->text();
    QString customePwd = ui->letpossword->text();
    QString customePhone = ui->letphone->text();
    QString customedate = ui->dateCustomeIn->text();
    QString customeAddress = ui->letaddress->text();
    QString customeRemark = ui->letGnote->text();

    if(customeName.isEmpty() ||customePhone.isEmpty()// 判断必填字段是否为空
            ||customePwd.isEmpty()||customeAddress.isEmpty())
    {
        myHelper::ShowMessageBoxError(tr("必须填满带*字段"));// 显示错误信息提示框
    }
    else
    {
        QString currentUseName = Myapp::CurrentUserName;    //获取当前登录名
        QSqlQuery query; // 构造 SQL 语句并执行更新
        QString sql ="update customer set CustomerSex ='"+customeSex
                +"', CustomerPassword='"+customePwd+"',CustomerPhone='"+customePhone
                +"', CustomerData ='"+customedate+"', CustomerAddress='"+customeAddress
                +"', CustomerRemark ='"+customeRemark+"' where CustomerName = '"+currentUseName+"';";
        qDebug() <<sql;
        qDebug() << query.exec(sql);
        myHelper::ShowMessageBoxInfo(tr("修改成功")); // 显示信息提示框
        myHelper::MyLoginBlog("log","修改信息","组员","监督官"); // 记录日志
        qDebug() <<"update customer info success!";
    }
}

/*
 *函数功能：取消操作
*/
void CustomerWindget::on_pbnCancle_clicked()
{
    ui->pbnmodify->setEnabled(true);// 启用 pbnmodify 按钮
	// 禁用 pbuModifyOk 和 pbnCancle 按钮
    ui->pbuModifyOk->setEnabled(false);
    ui->pbnCancle->setEnabled(false);

}


/*
 *当鼠标点击显示组员信息到对应控件中
*/
void CustomerWindget::showCustomInfo()
{
	// 获取当前用户名
    QString customerName = GetCutrrentUserName("customelogblog");
	// 创建 QSqlQueryModel 对象 userMode 并绑定到 tableViewCustomeInfo 控件
    QSqlQueryModel userMode(ui->tableViewCustomeInfo);
    QString sql = "SELECT *FROM customer where CustomerName = '"+customerName+"'";// 根据当前用户名查询 customer 表中对应的记录
    qDebug() <<sql;
    userMode.setQuery(QString(sql));
    int Row = ui->tableViewCustomeInfo->currentIndex().row();// 获取当前选中行的行号
    QSqlRecord record = userMode.record(Row);// 获取该行对应的 QSqlRecord 对象 record
	// 在对应的 QLineEdit 控件中显示该记录的各个字段值
    ui->letusename->setText(record.value(1).toString());
    ui->letsex->setText(record.value(2).toString());
    ui->letpossword->setText(record.value(3).toString());
    ui->letphone->setText(record.value(4).toString());
    ui->letaddress->setText(record.value(5).toString());
    //ui->dateCustomeIn->setDate(QDate::addDays(record.value(6).toInt()));
    ui->letGnote->setText(record.value(7).toString());
}

void CustomerWindget::on_tableViewCustomeInfo_activated(const QModelIndex &index)
{

}
