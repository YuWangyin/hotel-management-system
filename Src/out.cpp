#include "out.h"
#include "ui_out.h"

#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>
#include "app/myhelper.h"

#include "app/iconhelper.h"
#include "app/myapp.h"
#include <QDate>


//导出到excel需要加的头文件
#include <QTableWidget>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QAxObject>
//++++++++++++

Out::Out(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Out)
{
    ui->setupUi(this);
    this->InitForm();
}

Out::~Out()
{
    delete ui;
}

void Out::InitForm()
{
    ColumnNames[0] = tr("订单编号");
    ColumnNames[1] = tr("坑位编号");
    ColumnNames[2] = tr("组员姓名");
    ColumnNames[3] = tr("坑位类型");
    ColumnNames[4] = tr("蹲坑时间");
    ColumnNames[5] = tr("价格");
    ColumnNames[6] = tr("电话");
    ColumnNames[7] = tr("备注");

    ColumnWidths[0] = 70;
    ColumnWidths[1] = 100;
    ColumnWidths[2] = 80;
    ColumnWidths[3] = 100;
    ColumnWidths[4] = 100;
    ColumnWidths[5] = 200;
    ColumnWidths[6] = 160;
    ColumnWidths[7] = 200;

    //将数据库中的一张表中的内容显示到tableView控件上
    BindCustomInfo("outbook",ui->tableView,ColumnNames,ColumnWidths);

    //showCustomerInfo()将点击的tableView列表内容放到各个格子中
    this->connect(ui->tableView,SIGNAL(clicked(QModelIndex)),SLOT(showCustomerInfo()));

}

void Out::BindCustomInfo(QString tableName, QTableView *tableView, QString columnNames[], int columnWidths[])
{
    QueryModel = new QSqlQueryModel(this);
    QString sql = "SELECT *FROM " + tableName+";";
    qDebug() <<sql;
    QueryModel->setQuery(sql);
    tableView->setModel(QueryModel);

    //依次设置列标题、列宽等
    for (int i = 0;i<tableView->model()->columnCount();i++)
    {
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);     //设置列标题
        tableView->setColumnWidth(i,columnWidths[i]);                   //设置列宽
    }

    tableView->horizontalHeader()->setHighlightSections(false);         //点击表头时不对表头光亮
    tableView->setSelectionMode(QAbstractItemView::ContiguousSelection);//选中模式为多行选中
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);     //选中整行
    tableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");
}

/*
 *函数功能:当点击tableView显示当前表格中客户的信息到控件上
*/
void Out::showCustomerInfo()
{
//    QSqlQueryModel userMode(ui->tableView);
//    QString sql = "SELECT *FROM book;";
//    qDebug() <<sql;
//    userMode.setQuery(QString(sql));
//    int Row = ui->tableView->currentIndex().row();
//    QSqlRecord record = userMode.record(Row);
////    ui->CustomerNo->setText(record.value(0).toString());
//    ui->lineEdit_no->setText(record.value(1).toString());
//    ui->lineEdit_name->setText(record.value(2).toString());
////    ui->CustomerRePwd->setText(record.value(3).toString());
////    ui->CustomerPhone->setText(record.value(4).toString());
////    ui->CustomerAddress->setText(record.value(5).toString());
////    ui->ledCustomDate->setText(record.value(6).toString());
////    ui->CustomerRemark->setText(record.value(7).toString());
}


void Out::on_button_find_clicked()
{
        //将更新的表outbook的内容显示在tableView中
        BindCustomInfo("outbook",ui->tableView,ColumnNames,ColumnWidths);

}

void Out::on_button_out_clicked()
{
    QString title;
    Table2ExcelByHtml(ui->tableView,title);// 将 tableView 的内容导出为 Excel 文件

}

//第一个参数是页面上的表格，第二个是导出文件的表头数据
void Out::Table2ExcelByHtml(QTableView *tableview,QString title)
{
	// 获取文件保存路径
    QString fileName = QFileDialog::getSaveFileName(tableview, "保存",QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),"Excel 文件(*.xls *.xlsx)");
    if (fileName!="")
    {
		// 使用 ActiveX 控件连接 Excel
        QAxObject *excel = new QAxObject;
        if (excel->setControl("Excel.Application")) //连接Excel控件
        {
           excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
           excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
           QAxObject *workbooks = excel->querySubObject("WorkBooks");//获取工作簿集合
           workbooks->dynamicCall("Add");//新建一个工作簿
           QAxObject *workbook = excel->querySubObject("ActiveWorkBook");//获取当前工作簿
           QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);

           int i,j;
           //QTablewidget 获取数据的列数
          //int colcount=table->columnCount();
            //QTablewidget 获取数据的行数
           //int rowscount=table->rowCount()

           //QTableView 获取列数
            int colcount = tableview->model()->columnCount();
           //QTableView 获取行数
            int row = tableview->model()->rowCount();

           QAxObject *cell,*col;
           //标题行
           cell=worksheet->querySubObject("Cells(int,int)", 1, 1);
           cell->dynamicCall("SetValue(const QString&)", title);
           cell->querySubObject("Font")->setProperty("Size", 18);
           //调整行高
           worksheet->querySubObject("Range(const QString&)", "1:1")->setProperty("RowHeight", 30);
           //合并标题行
           QString cellTitle;
           cellTitle.append("A1:");
           cellTitle.append(QChar(colcount - 1 + 'A'));
           cellTitle.append(QString::number(1));
           QAxObject *range = worksheet->querySubObject("Range(const QString&)", cellTitle);
           range->setProperty("WrapText", true);
           range->setProperty("MergeCells", true);
           range->setProperty("HorizontalAlignment", -4108);//xlCenter
           range->setProperty("VerticalAlignment", -4108);//xlCenter
           //列标题
           for(i=0;i<colcount;i++)
           {
               QString columnName;
               columnName.append(QChar(i  + 'A'));
               columnName.append(":");
               columnName.append(QChar(i + 'A'));
               col = worksheet->querySubObject("Columns(const QString&)", columnName);
               col->setProperty("ColumnWidth", tableview->columnWidth(i)/6);
               cell=worksheet->querySubObject("Cells(int,int)", 2, i+1);
               //QTableWidget 获取表格头部文字信息
               //columnName=table->horizontalHeaderItem(i)->text();
               //QTableView 获取表格头部文字信息
                columnName=ui->tableView->model()->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString();
               cell->dynamicCall("SetValue(const QString&)", columnName);
               cell->querySubObject("Font")->setProperty("Bold", true);
               cell->querySubObject("Interior")->setProperty("Color",QColor(191, 191, 191));
               cell->setProperty("HorizontalAlignment", -4108);//xlCenter
               cell->setProperty("VerticalAlignment", -4108);//xlCenter
           }

          //数据区

          //QTableWidget 获取表格数据部分
//           for(i=0;i<rowcount;i++){
//               for (j=0;j<colcount;j++)
//               {
//                   worksheet->querySubObject("Cells(int,int)", i+3, j+1)->dynamicCall("SetValue(const QString&)", table->item(i,j)?table->item(i,j)->text():"");
//               }
//           }


          //QTableView 获取表格数据部分
            for(i=0;i<row;i++) //行数
               {
                   for (j=0;j<colcount;j++)   //列数
                   {
                       QModelIndex index = ui->tableView->model()->index(i, j);
                       QString strdata=ui->tableView->model()->data(index).toString();
                       worksheet->querySubObject("Cells(int,int)", i+3, j+1)->dynamicCall("SetValue(const QString&)", strdata);
                   }
               }


           //画框线
           QString lrange;
           lrange.append("A2:");
           lrange.append(colcount - 1 + 'A');
           //lrange.append(QString::number(tableview->rowCount() + 2));
           lrange.append(QString::number(row + 2));
           range = worksheet->querySubObject("Range(const QString&)", lrange);
           range->querySubObject("Borders")->setProperty("LineStyle", QString::number(1));
           range->querySubObject("Borders")->setProperty("Color", QColor(0, 0, 0));
           //调整数据区行高
           QString rowsName;
           rowsName.append("2:");
          //rowsName.append(QString::number(tableview->rowCount() + 2));
          rowsName.append(QString::number(row + 2));
          range = worksheet->querySubObject("Range(const QString&)", rowsName);
          range->setProperty("RowHeight", 20);
          workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(fileName));//保存至fileName
          workbook->dynamicCall("Close()");//关闭工作簿
          excel->dynamicCall("Quit()");//关闭excel
          delete excel;
          excel=NULL;
          if (QMessageBox::question(NULL,"完成","文件已经导出，是否现在打开？",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
          {
              QDesktopServices::openUrl(QUrl("file:///" + QDir::toNativeSeparators(fileName)));
          }
      }
      else
      {
          QMessageBox::warning(NULL,"错误","未能创建 Excel 对象，请安装 Microsoft Excel。",QMessageBox::Apply);
      }
  }
}



void Out::on_tableView_activated(const QModelIndex &index)
{

}
