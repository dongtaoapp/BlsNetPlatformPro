#include "netplatformtestdlg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetPlatformTestDlg w;
    w.show();

    return a.exec();
}
