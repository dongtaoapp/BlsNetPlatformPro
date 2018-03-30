#include "mainwnd.h"
#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>
#include <QObjectList>
#include <QApplication>
#include <QMetaProperty>
#include <qDebug>
#define QScrollBarSheet "QScrollBar:vertical{width:4px;background-color:#2c2e43}QScrollBar:horizontal{width:4px;background-color:#2c2e43}\
         QScrollBar::handle:vertical{height:10px;background-color:#373a4d;border-radius:4px;}"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWnd w;
    qApp->setFont(QFont("SimHei",10));
    qApp->setStyleSheet(QScrollBarSheet);
    w.m_show();


    return a.exec();
}
