#ifndef NETPLATFORMTESTDLG_H
#define NETPLATFORMTESTDLG_H

#include <QDialog>

namespace Ui {
class NetPlatformTestDlg;
}

class NetPlatformTestDlg : public QDialog
{
    Q_OBJECT

public:
    explicit NetPlatformTestDlg(QWidget *parent = 0);
    ~NetPlatformTestDlg();

private:
    Ui::NetPlatformTestDlg *ui;
};

#endif // NETPLATFORMTESTDLG_H
