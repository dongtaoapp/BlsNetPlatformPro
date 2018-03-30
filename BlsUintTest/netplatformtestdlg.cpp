#include "netplatformtestdlg.h"
#include "ui_netplatformtestdlg.h"

NetPlatformTestDlg::NetPlatformTestDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetPlatformTestDlg)
{
    ui->setupUi(this);
}

NetPlatformTestDlg::~NetPlatformTestDlg()
{
    delete ui;
}
