#ifndef CHECKOUTDIALOG_H
#define CHECKOUTDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QTableView>

namespace Ui {
class CheckOutDialog;
}

class CheckOutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CheckOutDialog(QWidget *parent = 0);
    ~CheckOutDialog();

     void InitForm();
     void BindCustomInfo(QString tableName, QTableView *tableView,
                        QString columnNames[], int columnWidths[]);

public slots:
    void showCustomerInfo();


private slots:
    void on_button_find_clicked();

    void on_push_find_clicked();

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::CheckOutDialog *ui;

    QSqlQueryModel *QueryModel;     //查询模型
    QTableView *TableView;          //显示数据的表格对象

    QString ColumnNames[8];         //列名数组声明
    int ColumnWidths[8];            //列宽数组声明
};

#endif // CHECKOUTDIALOG_H
