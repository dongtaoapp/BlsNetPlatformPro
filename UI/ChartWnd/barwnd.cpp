#include "barwnd.h"
#include "ui_barwnd.h"

BarWnd::BarWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BarWnd)
{
    ui->setupUi(this);
}

BarWnd::~BarWnd()
{
    delete ui;
}
