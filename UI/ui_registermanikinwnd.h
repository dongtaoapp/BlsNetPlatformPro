/********************************************************************************
** Form generated from reading UI file 'registermanikinwnd.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERMANIKINWND_H
#define UI_REGISTERMANIKINWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterManikinWnd
{
public:
    QPushButton *ConManikinBtn;
    QPushButton *addManikinBtn;

    void setupUi(QWidget *RegisterManikinWnd)
    {
        if (RegisterManikinWnd->objectName().isEmpty())
            RegisterManikinWnd->setObjectName(QStringLiteral("RegisterManikinWnd"));
        RegisterManikinWnd->resize(518, 590);
        RegisterManikinWnd->setStyleSheet(QStringLiteral("image:url(:/image/ss.png);"));
        ConManikinBtn = new QPushButton(RegisterManikinWnd);
        ConManikinBtn->setObjectName(QStringLiteral("ConManikinBtn"));
        ConManikinBtn->setGeometry(QRect(380, 500, 101, 23));
        ConManikinBtn->setCursor(QCursor(Qt::PointingHandCursor));
        ConManikinBtn->setStyleSheet(QLatin1String("border-style:solid;\n"
"width: 33px;\n"
"height: 16px;\n"
"font-family: PingFangSC-Regular;\n"
"font-size: 16px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #ffffff;\n"
"background-color: #21b0f2;\n"
"border-radius: 2px;"));
        addManikinBtn = new QPushButton(RegisterManikinWnd);
        addManikinBtn->setObjectName(QStringLiteral("addManikinBtn"));
        addManikinBtn->setGeometry(QRect(380, 560, 101, 23));
        addManikinBtn->setCursor(QCursor(Qt::PointingHandCursor));
        addManikinBtn->setStyleSheet(QLatin1String("border-style:solid;\n"
"width: 86px;\n"
"height: 16px;\n"
"font-family: PingFangSC-Regular;\n"
"font-size: 16px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #ffffff;"));

        retranslateUi(RegisterManikinWnd);

        QMetaObject::connectSlotsByName(RegisterManikinWnd);
    } // setupUi

    void retranslateUi(QWidget *RegisterManikinWnd)
    {
        RegisterManikinWnd->setWindowTitle(QApplication::translate("RegisterManikinWnd", "RegisterManikinWnd", Q_NULLPTR));
        ConManikinBtn->setText(QApplication::translate("RegisterManikinWnd", "\350\277\236\346\216\245", Q_NULLPTR));
        addManikinBtn->setText(QApplication::translate("RegisterManikinWnd", "\345\242\236\345\212\240\346\250\241\346\213\237\344\272\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RegisterManikinWnd: public Ui_RegisterManikinWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERMANIKINWND_H
