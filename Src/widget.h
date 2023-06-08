#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <Qtimer>
#include "app/frmmessagebox.h"
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QDateTime>

#include "promanage.h"                       //前台管理中心界面
#include "costomerregisterinfodialog.h"      //注册组员信息
#include "romminfo.h"                       //坑位信息界面
#include "modiftroomprice.h"                //修改坑位价格界面
#include "checkcutomdialog.h"               //组员登记坑位界面
#include "logblogdialog.h"                  //操作日志界面
#include "modifypwddialog.h"                //修改密码界面
#include "roompicdialog.h"                  //坑位照片展示界面
#include "backupdatanasedialog.h"           //数据库备份界面
#include "checkoutdialog.h"                 //退坑界面

#include "out.h"                       //顾客取衣服界面


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
private slots:
    void on_btnMenu_Close_clicked();

    void on_btnMenu_Max_clicked();

    void on_btnMenu_Min_clicked();

    void on_pbnAsk_clicked();

    void on_pbnError_clicked();

    void on_pbnHint_clicked();
    void on_pbnRegisterInfo_clicked();

    void on_pbnRoomInfo_clicked();

    void on_pbnModify_clicked();

    void on_pbnModiftPwd_clicked();

    void on_pbnCheck_clicked();

    void on_pbnLonBlog_clicked();

    void on_pbnRoomLock_clicked();

    void on_pbnbackhome_clicked();

    void on_pbnBackDatabase_clicked();

    void on_pbnCheckOut_clicked();

    void on_pbnHelp_clicked();

    void on_toolBox_destroyed();

    void on_label_linkActivated(const QString &link);

public slots:
    void showCurrentTime();
private:
    Ui::Widget *ui;
    QPoint mousePoint;
    bool mousePressed;
    bool max;
    QRect location;
    void InitStyle();

    QTimer *timer;

    //定义其他界面的指针变量
    ProManage *promanage;                       //联系小0
    CostomerRegisterInfoDialog *constumerInfo;  //注册组员信息界面
    RommInfo *romminfo;                         //坑位信息界面
    ModiftRoomPrice *modifyRoom;                //修改坑位信息
    CheckCutomDialog *checkcustom;              //组员登记入住界面
    LogBlogDialog *logblog;                     //操作日志
    ModifyPwdDialog *modifypwd;                 //修改密码
    RoomPicDialog *roompicture;                 //坑位照片展
    BackupDatanaseDialog *backdatabase;         //数据库备份界面
    CheckOutDialog *checkoutRoom;               //退房界面

    Out *outinfo; //组员退出坑位界面
};

#endif // WIDGET_H
