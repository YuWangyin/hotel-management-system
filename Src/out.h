#ifndef OUT_H
#define OUT_H

#include <QWidget>
#include <QDialog>
#include <QSqlQueryModel>
#include <QTableView>



namespace Ui {
class Out;
}

class Out : public QWidget
{
    Q_OBJECT

public:
    explicit Out(QWidget *parent = 0);
    ~Out();

    void InitForm();
    void BindCustomInfo(QString tableName, QTableView *tableView,
                       QString columnNames[], int columnWidths[]);
    void Table2ExcelByHtml(QTableView *table,QString title);

public slots:
    void showCustomerInfo();



private slots:
    void on_button_find_clicked();

    void on_button_out_clicked();

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::Out *ui;

    QSqlQueryModel *QueryModel;     //查询模型
    QTableView *TableView;          //显示数据的表格对象

    QString ColumnNames[8];         //列名数组声明
    int ColumnWidths[8];            //列宽数组声明
};

#endif // OUT_H
