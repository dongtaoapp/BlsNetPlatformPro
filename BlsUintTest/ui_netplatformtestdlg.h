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
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NetPlatformTestDlg
{
public:
    QPushButton *pushLoadBtn;
    QPushButton *closeButton;

    void setupUi(QDialog *NetPlatformTestDlg)
    {
        if (NetPlatformTestDlg->objectName().isEmpty())
            NetPlatformTestDlg->setObjectName(QStringLiteral("NetPlatformTestDlg"));
        NetPlatformTestDlg->resize(710, 522);
        pushLoadBtn = new QPushButton(NetPlatformTestDlg);
        pushLoadBtn->setObjectName(QStringLiteral("pushLoadBtn"));
        pushLoadBtn->setGeometry(QRect(50, 60, 141, 41));
        closeButton = new QPushButton(NetPlatformTestDlg);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setGeometry(QRect(230, 60, 141, 41));

        retranslateUi(NetPlatformTestDlg);

        QMetaObject::connectSlotsByName(NetPlatformTestDlg);
    } // setupUi

    void retranslateUi(QDialog *NetPlatformTestDlg)
    {
        NetPlatformTestDlg->setWindowTitle(QApplication::translate("NetPlatformTestDlg", "NetPlatformTestDlg", Q_NULLPTR));
        pushLoadBtn->setText(QApplication::translate("NetPlatformTestDlg", "\350\204\232\346\234\254\345\212\240\350\275\275\344\270\200", Q_NULLPTR));
        closeButton->setText(QApplication::translate("NetPlatformTestDlg", "\351\200\200\345\207\272\350\204\232\346\234\254", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NetPlatformTestDlg: public Ui_NetPlatformTestDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETPLATFORMTESTDLG_H
