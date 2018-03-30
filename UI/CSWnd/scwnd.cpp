#include "scwnd.h"
#include "ui_scwnd.h"
#include <QLabel>
#include <QString>
SCWnd::SCWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SCWnd)
{
    ui->setupUi(this);
    QLabel *la = new QLabel(this);la->setStyleSheet(QString("font-size:20px;font-family:SimHei;color:white"));
    la->setText(QString("                               体征检查\0"));
}

SCWnd::~SCWnd()
{
    delete ui;
}
