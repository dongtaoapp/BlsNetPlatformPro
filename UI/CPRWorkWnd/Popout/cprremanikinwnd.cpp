#include "cprremanikinwnd.h"
#include "ui_cprremanikinwnd.h"

CPRReManikinWnd::CPRReManikinWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPRReManikinWnd)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉标题栏

}

CPRReManikinWnd::~CPRReManikinWnd()
{
    delete ui;
}

void CPRReManikinWnd::on_closeBtn_clicked()
{
    this->close();
}
