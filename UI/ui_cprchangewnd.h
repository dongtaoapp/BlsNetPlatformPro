/********************************************************************************
** Form generated from reading UI file 'cprchangewnd.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPRCHANGEWND_H
#define UI_CPRCHANGEWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CPRChangeWnd
{
public:
    QLabel *titleLa;
    QPushButton *closeBtn;
    QLabel *la1;
    QLineEdit *lineEdit;
    QLabel *la2;
    QLineEdit *lineEdit_2;
    QPushButton *cancelBtn;
    QPushButton *okBtn;

    void setupUi(QDialog *CPRChangeWnd)
    {
        if (CPRChangeWnd->objectName().isEmpty())
            CPRChangeWnd->setObjectName(QStringLiteral("CPRChangeWnd"));
        CPRChangeWnd->resize(843, 513);
        CPRChangeWnd->setStyleSheet(QLatin1String("QLabel#la1,#la2{\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 20px;\n"
"	font-weight: normal;\n"
"	line-height: 70px;\n"
"	color: #b6b8c4;\n"
"}\n"
"QLineEdit{\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 20px;\n"
"	font-weight: normal;\n"
"	line-height: 70px;\n"
"	color: #b6b8c4;\n"
"}\n"
"QPushButton#okBtn,#cancelBtn{\n"
"	border-style:solid;\n"
"	background-color:#21b0f2;\n"
"	color:white;\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 18px;\n"
"	\n"
"}"));
        titleLa = new QLabel(CPRChangeWnd);
        titleLa->setObjectName(QStringLiteral("titleLa"));
        titleLa->setGeometry(QRect(0, 0, 843, 60));
        titleLa->setStyleSheet(QLatin1String("font-family: PingFangSC-Regular;\n"
"font-size: 24px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #21b0f2;\n"
"background-color:#232639;;"));
        closeBtn = new QPushButton(CPRChangeWnd);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setGeometry(QRect(784, 12, 51, 41));
        closeBtn->setStyleSheet(QLatin1String("border-style:solid;\n"
"image:url(:/image/X.png)"));
        la1 = new QLabel(CPRChangeWnd);
        la1->setObjectName(QStringLiteral("la1"));
        la1->setGeometry(QRect(150, 145, 251, 31));
        lineEdit = new QLineEdit(CPRChangeWnd);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(150, 200, 467, 37));
        la2 = new QLabel(CPRChangeWnd);
        la2->setObjectName(QStringLiteral("la2"));
        la2->setGeometry(QRect(150, 300, 251, 31));
        lineEdit_2 = new QLineEdit(CPRChangeWnd);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(150, 360, 467, 37));
        cancelBtn = new QPushButton(CPRChangeWnd);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setGeometry(QRect(190, 460, 81, 31));
        okBtn = new QPushButton(CPRChangeWnd);
        okBtn->setObjectName(QStringLiteral("okBtn"));
        okBtn->setGeometry(QRect(370, 460, 81, 31));

        retranslateUi(CPRChangeWnd);

        QMetaObject::connectSlotsByName(CPRChangeWnd);
    } // setupUi

    void retranslateUi(QDialog *CPRChangeWnd)
    {
        CPRChangeWnd->setWindowTitle(QApplication::translate("CPRChangeWnd", "Dialog", Q_NULLPTR));
        titleLa->setText(QApplication::translate("CPRChangeWnd", "  \346\233\277\346\215\242\346\250\241\346\213\237\344\272\272", Q_NULLPTR));
        closeBtn->setText(QString());
        la1->setText(QApplication::translate("CPRChangeWnd", "\345\275\223\345\211\215\346\240\207\350\257\206\347\240\201", Q_NULLPTR));
        la2->setText(QApplication::translate("CPRChangeWnd", "\350\276\223\345\205\245\346\226\260\347\232\204\346\240\207\350\257\206\347\240\201", Q_NULLPTR));
        cancelBtn->setText(QApplication::translate("CPRChangeWnd", "\345\217\226\346\266\210", Q_NULLPTR));
        okBtn->setText(QApplication::translate("CPRChangeWnd", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CPRChangeWnd: public Ui_CPRChangeWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPRCHANGEWND_H
