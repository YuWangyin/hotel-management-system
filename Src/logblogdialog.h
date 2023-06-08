#ifndef LOGBLOGDIALOG_H
#define LOGBLOGDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QTableView>

#include "app/mysqlapi.h"

namespace Ui {
class LogBlogDialog;
}

class LogBlogDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LogBlogDialog(QWidget *parent = 0);
    ~LogBlogDialog();
    void InitForm();

    //将某个表中的数据绑定到指定的TableView上
    void MyBindTable(QString tableName, QString where,QTableView *tableView,
                     QString columnNames[], int columnWidths[]);
    void Table2ExcelByHtml(QTableView *table,QString title);
    
private slots:
    void on_btnSelect_clicked();


    //void on_ckTriggerTime_clicked(bool checked);


   // void on_ckTriggerType_clicked(bool checked);


    void on_ckUserName_clicked(bool checked);

    void on_btnDelete_clicked();

    void on_btnExcel_clicked();

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::LogBlogDialog *ui;

    QSqlQueryModel *QueryModel;     //查询模型
    QTableView *TableView;          //显示数据的表格对象

    QString ColumnNames[5];         //列名数组声明
    int ColumnWidths[5];            //列宽数组声明
};

#endif // LOGBLOGDIALOG_H
