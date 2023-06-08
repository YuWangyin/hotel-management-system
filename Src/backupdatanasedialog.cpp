/***************************************************************
 *文件名称：数据库备份文件
 *简要描述：提供用户备份数据库功能
******************************************************************/
#include "backupdatanasedialog.h"
#include "ui_backupdatanasedialog.h"


#include "app/myhelper.h"
#include "app/myapp.h"
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

BackupDatanaseDialog::BackupDatanaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BackupDatanaseDialog)//初始化界面
{
    ui->setupUi(this);//设置UI界面
    this->InitForm();//初始化窗体
}

BackupDatanaseDialog::~BackupDatanaseDialog()//析构函数
{
    delete ui;//退出UI界面
}

void BackupDatanaseDialog::InitForm()//初始化窗体
{
    ui->labelBackInfo->setText(tr(" "));//初始化备份提示信息
    ui->pbnOk->setToolTip(tr("确认备份")); //设置确认备份的提示信息

    ui->progressBar->setRange(0,5000 - 1); //设置备份进度条的范围
    ui->progressBar->setValue(0); //设置备份进度条的初始值为0
}

/*
 *函数功能：备份数据库
*/
void BackupDatanaseDialog::on_pbnOk_clicked()//点击“确认备份”按钮
{
    QString pathname = ui->lineEdit->text();//获取备份文件的路径名
    QString Cmd = QString("mysqldump.exe --add-drop-table -u%1 -p%2 hotel").arg("root","123456");//设置备份命令
    QString Path = QString("%1").arg(pathname);//设置备份文件的路径
    QProcess *poc=new QProcess;//创建QProcess对象
    poc->setStandardOutputFile(Path);//设置输出文件
    poc->start(Cmd);//执行备份命令

    for(int i = 0;i<5000;i++)//循环5000次
    {
        ui->labelBackInfo->setText(tr("正在备份……"));//设置进度条的值
        for(int j = 0;j<2000;j++)
        {
            ui->progressBar->setValue(i);
        }
        ui->labelBackInfo->setText(tr("备份完成"));//显示备份完成的提示信息

        ui->pbnOk->setToolTip(tr("已经备份完成"));//设置备份完成的提示信息
    }

    QString currentname = Myapp::CurrentUserName;//获取当前用户名
    qDebug() <<"备份数据库:"<<currentname;//打印日志信息
    myHelper::MyLoginBlog("log","备份数据库","备份全部数据","监督官");//写入日志

}

/*
*获取当前要备份数据库的目录
*函数功能：当用户点击“浏览”按钮时，弹出对话框选择备份数据库的目录。
*/
void BackupDatanaseDialog::on_pbnSearch_clicked()//点击“浏览”按钮
{
    QString defaultname = "back_punchsystem.sql";
    //选择路径
    QString filename = QFileDialog::getSaveFileName(this,tr("保存数据库"),"",
                                                    tr("*sql;; *txt;;"));
    if(filename.isEmpty())//如果未选择路径，则使用默认路径。
    {
        filename = defaultname;
    }
    ui->lineEdit->setText(filename);

}
/*
*函数功能：当用户输入备份数据库的目录时，重置进度条的值，并清空备份按钮的工具提示。
*/
void BackupDatanaseDialog::on_lineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    ui->progressBar->setValue(0);
    ui->pbnOk->setToolTip(tr(""));
}
