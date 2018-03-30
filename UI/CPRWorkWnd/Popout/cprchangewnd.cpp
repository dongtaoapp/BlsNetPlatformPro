#include "cprchangewnd.h"
#include "ui_cprchangewnd.h"

CPRChangeWnd::CPRChangeWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPRChangeWnd)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉标题栏

}

CPRChangeWnd::~CPRChangeWnd()
{
    delete ui;
}

void CPRChangeWnd::on_closeBtn_clicked()
{
    this->close();
}
