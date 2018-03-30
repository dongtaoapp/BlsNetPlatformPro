/********************************************************************************
** Form generated from reading UI file 'barwnd.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BARWND_H
#define UI_BARWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BarWnd
{
public:
    QCommandLinkButton *commandLinkButton;

    void setupUi(QWidget *BarWnd)
    {
        if (BarWnd->objectName().isEmpty())
            BarWnd->setObjectName(QStringLiteral("BarWnd"));
        BarWnd->resize(1151, 761);
        BarWnd->setStyleSheet(QStringLiteral(""));
        commandLinkButton = new QCommandLinkButton(BarWnd);
        commandLinkButton->setObjectName(QStringLiteral("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(120, 200, 371, 271));

        retranslateUi(BarWnd);

        QMetaObject::connectSlotsByName(BarWnd);
    } // setupUi

    void retranslateUi(QWidget *BarWnd)
    {
        BarWnd->setWindowTitle(QApplication::translate("BarWnd", "Form", Q_NULLPTR));
        commandLinkButton->setText(QApplication::translate("BarWnd", "CommandLinkButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BarWnd: public Ui_BarWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BARWND_H
