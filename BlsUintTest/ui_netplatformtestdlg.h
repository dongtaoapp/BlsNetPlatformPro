/********************************************************************************
** Form generated from reading UI file 'netplatformtestdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETPLATFORMTESTDLG_H
#define UI_NETPLATFORMTESTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_NetPlatformTestDlg
{
public:

    void setupUi(QDialog *NetPlatformTestDlg)
    {
        if (NetPlatformTestDlg->objectName().isEmpty())
            NetPlatformTestDlg->setObjectName(QStringLiteral("NetPlatformTestDlg"));
        NetPlatformTestDlg->resize(400, 300);

        retranslateUi(NetPlatformTestDlg);

        QMetaObject::connectSlotsByName(NetPlatformTestDlg);
    } // setupUi

    void retranslateUi(QDialog *NetPlatformTestDlg)
    {
        NetPlatformTestDlg->setWindowTitle(QApplication::translate("NetPlatformTestDlg", "NetPlatformTestDlg", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NetPlatformTestDlg: public Ui_NetPlatformTestDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETPLATFORMTESTDLG_H
