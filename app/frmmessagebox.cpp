﻿#include "frmmessagebox.h"
#include "ui_frmmessagebox.h"
#include "iconhelper.h"
#include "myhelper.h"

frmMessageBox::frmMessageBox(QWidget *parent) :// 构造函数
    QDialog(parent),
    ui(new Ui::frmMessageBox)
{
    ui->setupUi(this);// 初始化UI

    this->mousePressed = false;// 鼠标未按下
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置窗体关闭时自动释放内存
    this->setAttribute(Qt::WA_DeleteOnClose);
    //设置图形字体
    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf015), 12);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);
    //关联关闭按钮
    connect(ui->btnMenu_Close, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
    //窗体居中显示

}
// 析构函数
frmMessageBox::~frmMessageBox()
{
    delete ui;
}
// 设置消息框信息
void frmMessageBox::SetMessage(const QString &msg, int type)
{
    //提示消息框
    if (type == 0)
    {
        ui->labIcoMain->setStyleSheet("border-image: url(:/image/info.png);");
        ui->btnCancel->setVisible(false);   //取消按钮不可见
        ui->lab_Title->setText(tr("提示"));
    }
    //询问消息框
    else if (type == 1)
    {
        ui->labIcoMain->setStyleSheet("border-image: url(:/image/question.png);");
        ui->lab_Title->setText(tr("询问"));
    }
    //错误消息框
    else if (type == 2)
    {
        ui->labIcoMain->setStyleSheet("border-image: url(:/image/error.png);");
        ui->btnCancel->setVisible(false);
        ui->lab_Title->setText(tr("错误"));
    }
// 设置消息内容
    ui->labInfo->setText(msg);
}
// 确认按钮点击事件
void frmMessageBox::on_btnOk_clicked()
{
    done(1);
    this->close();
}
// 鼠标移动事件
void frmMessageBox::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton)) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}
// 鼠标按下事件
void frmMessageBox::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}
// 鼠标释放事件
void frmMessageBox::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}
