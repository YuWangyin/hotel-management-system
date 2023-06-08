//登陆界面的功能实现，以及界面拖拽缩小
#include "logindialog.h"
#include "ui_logindialog.h"
#include "app/iconhelper.h"
#include "app/myapp.h"



//
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->InitForm();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::InitForm()
{
    total = 0;
    this->setWindowFlags(Qt::FramelessWindowHint);// 设置窗口无边框
    ui->txtUserPwd->setFocus();

    customewidget = new CustomerWindget;// 创建 CustomerWindget 窗口，并将其赋值给 customewidget


    //mysql->BindData("StaffName","Staff",ui->txtUserName);
    location = this->geometry();// 获取窗口位置
    mousePressed = false;// 鼠标按下标志位初始化为 false
    //安装事件监听器,让标题栏识别鼠标双击
    ui->lab_Title->installEventFilter(this);// 安装事件监听器,让标题栏识别鼠标双击
	// 设置窗口图标
    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);
    IconHelper::Instance()->SetIcon(ui->btnMenu_Min, QChar(0xf068), 10);
    IconHelper::Instance()->SetIcon(ui->btnMenu, QChar(0xf0c9), 10);
    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf015), 12);
    //ui->labCompany->setText(tr("欢迎登录，组员可自行注册使用"));
    //ui->radioButtonAdmin->setCheckable(true);
	// 设置控件提示信息
    ui->btnLogin->setToolTip(tr("登录"));
    ui->btnresgister->setToolTip(tr("注册"));
    ui->radioButtonAdmin->setToolTip(tr("监督官"));
    ui->radioButtonCustomer->setToolTip(tr("组员"));
}

/*
 *函数功能：保存当前用户名和类型
 *输入参数：数据表名，用户名，用户类型，用户密码
 *说明：在插入时总会先判断，若有数值，进行删除在插入
*/
void LoginDialog::WriteCurrentUser(QString tablename, QString username, QString usertype, QString userpwd)
{
    if(FindTableIsEmpty("currentuser") != 0)// 如果表不为空，先删除表内容
    {
        //deldete table
        this->DeleteTableContent("currentuser");
        qDebug() <<"deltet table ok";// 输出删除表内容成功的信息
    }
    else// 如果表为空
    {
        QSqlQuery query;
        QString sql = "insert into "+tablename+" values(:UserName,:UserType,:UserPwd)";
        qDebug() <<sql;
        query.prepare(sql);
        query.bindValue(":UserName",username);
        query.bindValue(":UserType",usertype);
        query.bindValue(":UserPwd",userpwd);
        query.setForwardOnly(true);
        query.exec();
        qDebug() <<"insert into table ok";// 输出插入表内容成功的信息
    }
}

/*
 *函数功能：检查某个表是否空表
 *输入参数：表名称
 *返回值：表中的字段值，根据返回值可以判断是否为空
*/
int LoginDialog::FindTableIsEmpty(QString tablename)
{
    int value = 0;
    QString sql = "select count(*) from "+tablename+";";// 统计表中记录条数
    qDebug() <<sql;
    QSqlQuery query;
    query.exec(sql);
    if(query.next())// 如果查询到结果
    {
        value = query.value(0).toInt();// 取出结果，转换为整型
        qDebug() <<"in "<<value;
    }
    qDebug()<<"out "<<value;
    return value;
}

/*
 *函数功能：删除表中的内容
 *
*/
void LoginDialog::DeleteTableContent(QString tablename)
{
    QString sql ="delete from "+tablename+";";// 构造SQL删除语句
    qDebug() <<sql;
    QSqlQuery query;
    query.exec(sql);// 执行SQL删除语句
}

void LoginDialog::on_btnLogin_clicked()
{
	// 获取用户名和密码
    QString UserName = ui->txtUserName->text().trimmed();
    QString UserPwd = ui->txtUserPwd->text().trimmed();
    ui->txtUserPwd->setFocus();
    //监督官登录
    if(ui->radioButtonAdmin->isChecked())
    {
		// 检查用户名和密码是否为空
        if(UserPwd.isEmpty()&&UserName.isEmpty())
        {
            myHelper::ShowMessageBoxError(tr("用户名或密码不能为空,请重新输入!"));
        }
        else
        {
			// 新建 QSqlTableModel 并设置表名
            QSqlTableModel model;
            model.setTable("Staff"); //选好表
            model.setFilter(QObject::tr("StaffName = '%1' and StaffPassword ='%2'")
                            .arg(UserName).arg(UserPwd));  //将刚才输入的用户名和密码和数据库staff表中的所有行做对比
            model.select(); //选取整个表的所有行              //setFilter这个函数是对整个结果集进行查询。为了使用变量，我们使用了QObject类的tr()函数。

            if(model.rowCount() == 1)// 判断结果集中的行数是否为1
            {
				// 设置当前用户信息并将其写入配置文件
                Myapp::LastLoginter = ui->txtUserName->text();
                Myapp::CurrentUserName = Myapp::LastLoginter;
                Myapp::CurrentUserPwd = ui->txtUserPwd->text();
                Myapp::CurrentUserType = tr("监督官");
                Myapp::WriteConfig();           //写进配置文件
				// 将登录信息写入系统日志
                myHelper::MyLoginBlog("log","登录","登录系统","监督官");     //写入系统日志
                qDebug() <<UserName<<""<<UserPwd;
                //创建主界面并显示，关闭登录界面
                mainwidget = new Widget;
                mainwidget->show();
                this->close();
            }
            else
            {
				// 密码错误
                myHelper::ShowMessageBoxError(tr("密码错误，请重新输入!"));
				// 清空密码输入框并将焦点设置到密码输入框
                ui->txtUserPwd->clear();
                ui->txtUserPwd->setFocus();
            }
        }
    }
    else if(ui->radioButtonCustomer->isChecked())
    {
        //组员登录
        if(UserPwd.isEmpty()&&UserName.isEmpty())// 检查用户名和密码是否为空
        {
            myHelper::ShowMessageBoxError(tr("用户名或密码不能为空,请重新输入!"));
        }
        else
        {
			// 新建 QSqlQuery 并构建查询语句
            QSqlQuery query;
            QString sql = "select customerPassword from customer where CustomerName='"+UserName+"';";
            qDebug() <<sql;
            qDebug() <<query.exec(sql);  //执行了上面的sql语句
            if(query.exec(sql))
            {
                qDebug() <<sql;
                qDebug() <<"ok+++++++++++++++++++++++";
                qDebug() <<sql;
            }
            query.next();// 获取查询结果中的密码
            QString customePwd = query.value(0).toString();
            if(customePwd == UserPwd)// 检查密码是否正确
            {
				// 设置当前用户信息并将其写入配置文件
                Myapp::LastLoginter = ui->txtUserName->text();
                Myapp::CurrentUserName = Myapp::LastLoginter;
                Myapp::CurrentUserPwd = ui->txtUserPwd->text();
                Myapp::CurrentUserType = tr("一般用户");
                Myapp::WriteConfig();           //写进配置文件
                //写到数据库中的log表中
                myHelper::MyLoginBlog("log","登录系统","组员",ui->txtUserName->text());     //写入系统日志
                //写到数据库中的customelogblog表中，表示当前登录的组员
                myHelper::customeMyLoginBlog("customelogblog", ui->txtUserName->text());
                customewidget->show();
                this->close();
            }
			// 如果密码错误，连续输错三次会弹出警告并退出程序，否则弹出错误提示并清空密码输入框
            else 
            {
                total++;
                myHelper::ShowMessageBoxError(tr("密码错误，请重新输入!"));
                ui->txtUserPwd->clear();
                ui->txtUserPwd->setFocus();

                if(total == 3)
                {
                    myHelper::ShowMessageBoxError(tr("系统检测您已连续三次输错密码，若忘记密码请联系监督官！"));
                    qApp->quit();
                }
            }

        }
    }
    else// 如果未选择登录身份，弹出错误提示
    {
        myHelper::ShowMessageBoxError(tr("请选择登录身份后在登录!"));
    }

}
//检测用户是否按下了回车键，如果按下则调用登录按钮的单击事件
bool LoginDialog::eventFilter(QObject *obj, QEvent *event)
{
    //用户按下回车键,触发登录信号.
    if (event->type() == QEvent::KeyPress)// 检测事件是否为按键事件
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);// 将事件转换为键盘事件
		// 检测按下的键是否为回车键
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key()==Qt::Key_Enter)
        {
            this->on_btnLogin_clicked();// 调用登录按钮的单击事件
            return true;
        }
    }
    return QObject::eventFilter(obj,event);
}
//鼠标移动事件，用于实现窗口拖动
void LoginDialog::mouseMoveEvent(QMouseEvent *e)
{
    if(mousePressed && (e->buttons()) && Qt::LeftButton)
    {
        this->move(e->globalPos() - mousePoint);// 移动窗口
        e->accept();
    }
}
//鼠标按下事件，用于实现窗口拖动
void LoginDialog::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
		// 记录鼠标按下位置和窗口位置
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

//鼠标释放事件，用于实现窗口拖动
void LoginDialog::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;// 鼠标释放
}
//最小化按钮的单击事件，用于最小化窗口
void LoginDialog::on_btnMenu_Min_clicked()
{
    this->showMinimized();
}
//关闭按钮的单击事件，用于关闭窗口
void LoginDialog::on_btnMenu_Close_clicked()
{
    this->close();
}
//注册按钮的单击事件，用于打开注册对话框
void LoginDialog::on_btnresgister_clicked()
{
    registerdialog = new RegisterDialog();
    registerdialog->exec();
}
//组员用户身份单选按钮的单击事件，暂时被注释掉了
void LoginDialog::on_radioButtonCustomer_clicked()
{
//    ui->txtUserName->setText("张超");
//    ui->txtUserPwd->setText("123456");
}
//管理员身份单选按钮的单击事件，暂时被注释掉了
void LoginDialog::on_radioButtonAdmin_clicked()
{
//    ui->txtUserName->setText("admin");
//    ui->txtUserPwd->setText("admin");
}



// 以下是调试用的
void LoginDialog::on_p_clicked()
{
    QSqlQuery query;
    qDebug() <<query.exec("INSERT INTO customer (Id, CustomerName) VALUES (1,2)");
    qDebug() <<"update01!";
    qDebug() <<query.exec("INSERT INTO customer (CustomerName, CustomerSex, CustomerPassword, CustomerPhone) VALUES (1,2,3,4)");
    qDebug() <<"update02!";
    qDebug() <<query.exec("INSERT INTO log (time, do) VALUES (6, 6)");
    qDebug() <<"update03!";
    qDebug() <<query.exec("INSERT INTO customer (CustomerName, CustomerSex) VALUES (1,2)");
    qDebug() <<"update04!";
}
