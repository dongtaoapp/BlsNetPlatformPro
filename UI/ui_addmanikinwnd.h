/********************************************************************************
** Form generated from reading UI file 'addmanikinwnd.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDMANIKINWND_H
#define UI_ADDMANIKINWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addManikinWnd
{
public:
    QLineEdit *ManikinEdit;
    QPushButton *okBtn;
    QPushButton *returnBtn;
    QLabel *label;

    void setupUi(QWidget *addManikinWnd)
    {
        if (addManikinWnd->objectName().isEmpty())
            addManikinWnd->setObjectName(QStringLiteral("addManikinWnd"));
        addManikinWnd->resize(518, 542);
        addManikinWnd->setStyleSheet(QLatin1String("QPushButton{\n"
"	border-style:solid;\n"
"	width: 81px;\n"
"	height: 30px;\n"
"	background-color: #21b0f2;\n"
"	border-radius: 2px;\n"
"	width: 33px;\n"
"	height: 16px;\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 16px;\n"
"	font-weight: normal;\n"
"	line-height: 70px;\n"
"	color: #ffffff;\n"
"}"));
        ManikinEdit = new QLineEdit(addManikinWnd);
        ManikinEdit->setObjectName(QStringLiteral("ManikinEdit"));
        ManikinEdit->setGeometry(QRect(80, 150, 365, 31));
        ManikinEdit->setStyleSheet(QLatin1String("width: 71px;\n"
"height: 14px;\n"
"font-family: PingFangSC-Regular;\n"
"font-size: 18px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #b6b8c4;"));
        okBtn = new QPushButton(addManikinWnd);
        okBtn->setObjectName(QStringLiteral("okBtn"));
        okBtn->setGeometry(QRect(310, 370, 91, 23));
        okBtn->setCursor(QCursor(Qt::PointingHandCursor));
        returnBtn = new QPushButton(addManikinWnd);
        returnBtn->setObjectName(QStringLiteral("returnBtn"));
        returnBtn->setGeometry(QRect(90, 370, 91, 23));
        returnBtn->setCursor(QCursor(Qt::PointingHandCursor));
        label = new QLabel(addManikinWnd);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 90, 231, 31));
        label->setStyleSheet(QLatin1String("width: 96px;\n"
"height: 17px;\n"
"font-family: PingFangSC-Regular;\n"
"font-size: 18px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #b6b8c4;"));

        retranslateUi(addManikinWnd);

        QMetaObject::connectSlotsByName(addManikinWnd);
    } // setupUi

    void retranslateUi(QWidget *addManikinWnd)
    {
        addManikinWnd->setWindowTitle(QApplication::translate("addManikinWnd", "Form", Q_NULLPTR));
        okBtn->setText(QApplication::translate("addManikinWnd", "\347\241\256\350\256\244", Q_NULLPTR));
        returnBtn->setText(QApplication::translate("addManikinWnd", "\350\277\224\345\233\236", Q_NULLPTR));
        label->setText(QApplication::translate("addManikinWnd", "\350\276\223\345\205\245\346\240\207\350\257\206\347\240\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class addManikinWnd: public Ui_addManikinWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDMANIKINWND_H