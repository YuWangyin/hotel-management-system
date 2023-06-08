﻿//用户预定坑位的功能，并把信息同步到数据库
#include "checkcutomdialog.h"
#include "ui_checkcutomdialog.h"
#include "app/myhelper.h"



#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QDate>

#include "checkoutdialog.h"



CheckCutomDialog::CheckCutomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckCutomDialog)
{
    ui->setupUi(this);//初始化ui
    this->InitForm();//初始化界面

}

CheckCutomDialog::~CheckCutomDialog()
{
    delete ui;//释放ui
}

void CheckCutomDialog::InitForm()
{
    ui->lineEditCustomOrderId->setEnabled(false);//将lineEditCustomOrderId设置为禁用状态


    //正则表达式，对输入的内容进行限制，电话号码11位,身份证18位,房间号4位，坑位类型编号1位
    QRegExp rxPhone("\\d{11}$");//创建11位数字的正则表达式对象rxPhone 手机号
    //QRegExp rxIdcard("\\d{18}$");
    //QRegExp rxRoomID("\\d{4}$");
    QRegExp rxRoomTypeId("\\d{1}$");//创建1位数字的正则表达式对象rxRoomTypeId 坑位ID

    QRegExpValidator *regPhone = new QRegExpValidator(rxPhone,this);//创建电话号码正则表达式的验证器regPhone
    //QRegExpValidator *regIdcard = new QRegExpValidator(rxIdcard,this);
    //QRegExpValidator *regRoomId = new QRegExpValidator(rxRoomID,this);
    QRegExpValidator *regRoomTypeId = new QRegExpValidator(rxRoomTypeId,this);//创建房间类型编号正则表达式的验证器regRoomTypeId

    ui->lineEditCustomPhone->setValidator(regPhone);//设置lineEditCustomPhone的验证器为regPhone
    //ui->lineEditCustomIcard->setValidator(regIdcard);
    //ui->lineEditRoomId->setValidator(regRoomId);
    ui->lineEditroomTypeId->setValidator(regRoomTypeId);//设置lineEditroomTypeId的验证器为regRoomTypeId
}

void CheckCutomDialog::on_pbnCheckOk_clicked()
{
    QString roomId = ui->lineEditRoomId->text();//获取lineEditRoomId的文本
    QString roomTypeId = ui->lineEditroomTypeId->text();//获取lineEditroomTypeId的文本
    QString customerName = ui->lineEditCustomName->text();//获取lineEditCustomName的文本
    QString roomphone = ui->lineEditCustomPhone->text();//获取lineEditCustomPhone的文本
    QString roomPrice = ui->lineEditCustomCash->text();//获取lineEditCustomCash的文本
    //QString roomCustomOrderId = ui->lineEditCustomOrderId->text();
    QString Remark = ui->lineEditRemark->text();//获取lineEditRemark的文本
    QString currentdatetime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm");//获取当前日期时间
    QString serialNumber = "2021"+currentdatetime;//创建坑位订单编号



    QSqlQuery query;
	//检查输入是否为空，如果为空则提示错误信息，否则执行以下代码块
    if(roomId.isEmpty() || roomTypeId.isEmpty()
            || customerName.isEmpty() || roomPrice.isEmpty())
    {
        myHelper::ShowMessageBoxInfo(tr("必须填满带*字段"));//显示提示框
    }
    else//构造SQL语句，将预订信息插入数据库中
    {
        QString sqlsql = "INSERT INTO book (Id,roomno,BookName,roomtypeid,BookTimeFrom,Price,phone,BookRemark) VALUES ('"+serialNumber+"', '"+roomId+"', '"+customerName+"', '"+roomTypeId+"', '"+currentdatetime+"', '"+roomPrice+"', '"+roomphone+"', '"+Remark+"')";
        qDebug() <<sqlsql;//执行SQL语句，并打印执行结果
        qDebug()<<query.exec("INSERT INTO book (Id,roomno,BookName,roomtypeid,BookTimeFrom,Price,phone,BookRemark) VALUES ('"+serialNumber+"', '"+roomId+"', '"+customerName+"', '"+roomTypeId+"', '"+currentdatetime+"', '"+roomPrice+"', '"+roomphone+"', '"+Remark+"')");
        qDebug() <<"update!";

        QString sql = "update room set RoomState = '满' where RoomNo='"+roomId+"';";//构造SQL语句，更新坑位状态为满
        qDebug() <<sql;
        query.exec(sql);//执行SQL语句，并打印执行结果
        qDebug() <<"update ok!";



        myHelper::ShowMessageBoxInfo(tr("预定坑位成功!"));//显示预定成功提示框

        //this->UpdateRoomeTableInfo("Room","满",roomId);
        myHelper::MyLoginBlog("log","组员登记","组员预定坑位","监督官");//记录操作日志

    }


}


/*
 *函数功能：更新坑位状态
 *输入参数
*/
void CheckCutomDialog::UpdateRoomeTableInfo(QString tablename, QString updatename,QString roomNo)
{
    QString sql = "update "+tablename+" set RoomState = '"+updatename+"' where RoomNo ='"+roomNo+"';"; // 构造 SQL 语句，更新指定ID的坑位状态
    qDebug() <<sql;// 打印 SQL 语句，方便调试和查错
    QSqlQuery query;
    query.exec(sql);// 执行 SQL 语句，更新数据库中对应的记录
    qDebug() <<"update roomstate success";// 打印成功信息
}



void CheckCutomDialog::on_lineEditroomTypeId_cursorPositionChanged(int arg1, int arg2)
{

}
