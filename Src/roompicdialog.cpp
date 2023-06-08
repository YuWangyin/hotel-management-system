#include "roompicdialog.h"
#include "ui_roompicdialog.h"


RoomPicDialog::RoomPicDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomPicDialog)
{
    ui->setupUi(this);
    ui->label->setScaledContents(true);
    ui->label_2->setScaledContents(true);
    ui->label_3->setScaledContents(true);
    ui->label_4->setScaledContents(true);
    ui->label_5->setScaledContents(true);
    ui->label_6->setScaledContents(true);
   // ui->label_7->setScaledContents(true);
    ui->label_8->setScaledContents(true);
    ui->label_9->setScaledContents(true);
    //ui->label_10->setScaledContents(true);

}

RoomPicDialog::~RoomPicDialog()
{
    delete ui;
}
