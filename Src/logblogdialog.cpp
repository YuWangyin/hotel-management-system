#include "logblogdialog.h"
#include "ui_logblogdialog.h"

#include "app/myapp.h"


//导出到excel需要加的头文件
#include <QTableWidget>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QAxObject>
//++++++++++++

LogBlogDialog::LogBlogDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogBlogDialog)
{
    ui->setupUi(this);
    this->InitForm();
}

LogBlogDialog::~LogBlogDialog()
{
    delete ui;
}

void LogBlogDialog::InitForm()
{
    //初始化表格列名和列宽
    ColumnNames[0] = tr("时间");
    ColumnNames[1] = tr("出发的动作");
    ColumnNames[2] = tr("内容");
    ColumnNames[3] = tr("操作员名字");

    ColumnWidths[0] = 220;
    ColumnWidths[1] = 120;
    ColumnWidths[2] = 180;
    ColumnWidths[3] = 120;

    //ui->ckTriggerType->setChecked(false);
    ui->ckUserName->setChecked(false);//设置默认不选中

    //ui->dateStart->setEnabled(false);
    //ui->dateEnd->setEnabled(false);
    ui->cboxUserName->setEnabled(false); //设置用户名下拉框不可用
    //ui->cboxTriggerType->setEditable(false);

    this->MyBindTable("log"," ",ui->tableView,ColumnNames,ColumnWidths); //绑定日志数据到表格中

    //ui->dateStart->setDate(QDate::currentDate());
    //ui->dateEnd->setDate(QDate::currentDate());

    if(Myapp::LastLoginter !="admin")//如果登录的用户名不是admin

    {
        ui->btnDelete->setEnabled(false);//则不能删除日志
    }
}
void LogBlogDialog::MyBindTable(QString tableName, QString where,QTableView *tableView, QString columnNames[], int columnWidths[])
{
    QueryModel = new QSqlQueryModel(this);
    TableView = tableView;
    QString sql = "SELECT * FROM " + tableName+where;//查询功能的SQL语句
    QueryModel->setQuery(sql);
    TableView->setModel(QueryModel);

    //依次设置列标题、列宽等
    for (int i = 0;i<TableView->model()->columnCount();i++)
    {
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);     //设置列标题
        TableView->setColumnWidth(i,columnWidths[i]);                   //设置列宽
    }

    TableView->horizontalHeader()->setHighlightSections(false);         //点击表头时不对表头光亮
    TableView->setSelectionMode(QAbstractItemView::ContiguousSelection);//选中模式为多行选中
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);     //选中整行
    TableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(92,188,227,200)}"
                              "QTableView::item:selected{background-color:#1B89A1}");
}

/*
 *函数功能：按条件查询
*/
void LogBlogDialog::on_btnSelect_clicked()
{
    QString sql = " where 1 = 1";

    if(ui->ckUserName->isChecked())
    {
        if(ui->cboxUserName->currentText() == "监督官")// 如果选择了监督官，管理员
        {
            sql+=" and user='"+ui->cboxUserName->currentText()+"'";
        }

        if(ui->cboxUserName->currentText() == "组员")// 如果选择了组员，普通用户
        {
            sql+=" and can='"+ui->cboxUserName->currentText()+"'";
        }


    }
//    if(ui->ckTriggerType->isChecked())
//    {
//        sql+=" and can ='"+ui->cboxTriggerType->currentText();
//    }
//    if(ui->ckTriggerTime->isChecked())
//    {
//        if (ui->dateStart->date() > ui->dateEnd->date())
//        {
//            myHelper::ShowMessageBoxError(tr("开始时间不能大于结束时间!"));
//            return;
//        }
//        sql+=" and date(TriggerTimer) >='"+ui->dateStart->date().toString("yyyy-MM-dd")+"'";
//        sql+=" and date(TriggerTimer) <='"+ui->dateEnd->date().toString("yyyy-MM-dd")+"'";
//    }

    this->MyBindTable("log",sql,ui->tableView,ColumnNames,ColumnWidths);// 调用函数进行表格数据的绑定
}




//void LogBlogDialog::on_ckTriggerTime_clicked(bool checked)
//{
//    ui->dateEnd->setEnabled(checked);
//    ui->dateStart->setEnabled(checked);
//}


//void LogBlogDialog::on_ckTriggerType_clicked(bool checked)
//{
//    ui->cboxTriggerType->setEditable(checked);
//}


//功能：根据是否选中来使能或禁用cboxUserName组合框
void LogBlogDialog::on_ckUserName_clicked(bool checked)
{
    ui->cboxUserName->setEnabled(checked);
}

//功能：删除数据库log表中的一条记录，并在tableView中更新显示内容
void LogBlogDialog::on_btnDelete_clicked()
{
	//创建一个QSqlQueryModel对象，用于查询数据库中log表的内容
    QSqlQueryModel userMode(ui->tableView);
    QString sql = "SELECT *FROM log;";
    qDebug() <<sql;
    userMode.setQuery(QString(sql));
	//获取当前tableView中选中的行的行号，并获取该行的记录
    int Row = ui->tableView->currentIndex().row();
    QSqlRecord record = userMode.record(Row);
    //从数据库的log表中删除一条记录
    QSqlQuery query;
    QString time = record.value(0).toString();
    sql = "delete from log where time = '"+time+"'";
    qDebug() <<sql;
    qDebug()<<query.exec("delete from log where time = '"+time+"'");
    qDebug() <<"update ok!";


    //将删除后的表的内容显示在tableView中
    MyBindTable("log"," ",ui->tableView,ColumnNames,ColumnWidths);

	//弹出信息提示框，表示删除成功
    myHelper::ShowMessageBoxInfo("删除成功");

//    if(Myapp::CurrentUserName != "admin")
//    {
//        myHelper::ShowMessageBoxError(tr("你没有权限删除记录"));
//        return;
//    }
}

//将记录导出到excel中
void LogBlogDialog::on_btnExcel_clicked()
{
    QString title;
    Table2ExcelByHtml(ui->tableView,title);


}


//Table2ExcelByHtml是将控件tableview的数据导出到excel中的函数
void LogBlogDialog::Table2ExcelByHtml(QTableView *tableview,QString title)
{
    QString fileName = QFileDialog::getSaveFileName(tableview, "保存",QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),"Excel 文件(*.xls *.xlsx)");
    if (fileName!="")
    {
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

void LogBlogDialog::on_tableView_activated(const QModelIndex &index)
{

}
