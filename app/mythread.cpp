#include "mythread.h"
#include <QDateTime>

Mythread::Mythread(QObject *parent) :
    QThread(parent)
{
    /***************创建一个定时器，用来显示系统当前的时间功能，并且每秒钟更新一次*************/
    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(showTimesslot));// 当定时器超时时，调用showTimesslot()函数
    timer->start(1000);// 启动定时器，时间间隔为1000ms
}

void Mythread::run()
{
    showTimesslot();// 在线程中运行showTimesslot()函数
}

void Mythread::SetCurrentTime(QLabel *label)
{
    curlabel = label;// 将传入的QLabel对象赋值给成员变量curlabel
}

void Mythread::showTimesslot()
{
    curlabel->setText(QDateTime::currentDateTime().toString(tr("yyyy-MM-dd\ndddd HH:mm")));// 设置curlabel的文本内容为当前日期和时间
    sleep(1);// 休眠1秒，以等待下一次定时器超时
}
