#include "romminfo.h"
#include "ui_romminfo.h"


RommInfo::RommInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RommInfo)
{
    ui->setupUi(this);
    ui->label_4->setScaledContents(true);
    ui->label_5->setScaledContents(true);
    ui->label_6->setScaledContents(true);
}

RommInfo::~RommInfo()
{
    delete ui;
}
