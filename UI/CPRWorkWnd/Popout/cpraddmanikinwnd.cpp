#include "cpraddmanikinwnd.h"
#include "ui_cpraddmanikinwnd.h"

CPRAddManikinWnd::CPRAddManikinWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPRAddManikinWnd)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉标题栏

}

CPRAddManikinWnd::~CPRAddManikinWnd()
{
    delete ui;
}

void CPRAddManikinWnd::on_closeBtn_clicked()
{
    this->close();
}
