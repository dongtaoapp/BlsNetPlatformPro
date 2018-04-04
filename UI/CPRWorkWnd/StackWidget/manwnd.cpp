#include "manwnd.h"
#include "ui_manwnd.h"

ManWnd::ManWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManWnd)
{
    ui->setupUi(this);
}

ManWnd::~ManWnd()
{
    delete ui;
}
