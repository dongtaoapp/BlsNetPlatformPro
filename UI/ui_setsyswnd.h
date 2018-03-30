/********************************************************************************
** Form generated from reading UI file 'setsyswnd.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETSYSWND_H
#define UI_SETSYSWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SetSysWnd
{
public:
    QLabel *label;
    QPushButton *closeBtn;
    QLabel *heartLa;
    QLabel *hungLa;
    QLabel *la1;
    QLabel *la2;
    QLabel *la3;
    QLabel *la4;
    QPushButton *cancelBtn;
    QPushButton *saveBtn;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QDialog *SetSysWnd)
    {
        if (SetSysWnd->objectName().isEmpty())
            SetSysWnd->setObjectName(QStringLiteral("SetSysWnd"));
        SetSysWnd->resize(942, 670);
        SetSysWnd->setStyleSheet(QLatin1String("QLabel#la1,#la2,#la3,#la4{\n"
"	border-style:solid;\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 20px;\n"
"	font-weight: normal;\n"
"	line-height: 70px;\n"
"	color: #21b0f2;\n"
"	border-bottom:1px solid  #21b0f2;\n"
"\n"
"}\n"
"QPushButton#saveBtn,#cancelBtn{\n"
"	border-style:solid;\n"
"	background-color:#21b0f2;\n"
"	color:white;\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 18px;\n"
"	\n"
"}"));
        label = new QLabel(SetSysWnd);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 942, 60));
        label->setStyleSheet(QLatin1String("font-family: PingFangSC-Regular;\n"
"font-size: 24px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #21b0f2;\n"
"background-color: #373950;"));
        closeBtn = new QPushButton(SetSysWnd);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setGeometry(QRect(894, 10, 41, 41));
        closeBtn->setStyleSheet(QLatin1String("border-style:solid;\n"
"image:url(:/image/X.png);"));
        heartLa = new QLabel(SetSysWnd);
        heartLa->setObjectName(QStringLiteral("heartLa"));
        heartLa->setGeometry(QRect(70, 140, 54, 81));
        heartLa->setStyleSheet(QString::fromUtf8("image:url(:/image/\345\277\203\347\224\265\345\233\276.png);"));
        hungLa = new QLabel(SetSysWnd);
        hungLa->setObjectName(QStringLiteral("hungLa"));
        hungLa->setGeometry(QRect(70, 400, 54, 61));
        hungLa->setStyleSheet(QString::fromUtf8("image:url(:/image/\350\202\272\351\203\250.png);"));
        la1 = new QLabel(SetSysWnd);
        la1->setObjectName(QStringLiteral("la1"));
        la1->setGeometry(QRect(210, 150, 251, 51));
        la1->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        la2 = new QLabel(SetSysWnd);
        la2->setObjectName(QStringLiteral("la2"));
        la2->setGeometry(QRect(590, 150, 251, 51));
        la2->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        la3 = new QLabel(SetSysWnd);
        la3->setObjectName(QStringLiteral("la3"));
        la3->setGeometry(QRect(210, 380, 251, 51));
        la3->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        la4 = new QLabel(SetSysWnd);
        la4->setObjectName(QStringLiteral("la4"));
        la4->setGeometry(QRect(590, 380, 251, 51));
        la4->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        cancelBtn = new QPushButton(SetSysWnd);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setGeometry(QRect(310, 610, 75, 31));
        saveBtn = new QPushButton(SetSysWnd);
        saveBtn->setObjectName(QStringLiteral("saveBtn"));
        saveBtn->setGeometry(QRect(500, 610, 75, 31));
        label_2 = new QLabel(SetSysWnd);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(305, 245, 16, 31));
        label_2->setStyleSheet(QLatin1String("border-style:solid;\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 20px;\n"
"	font-weight: normal;\n"
"	line-height: 70px;\n"
"	color: #21b0f2;"));
        label_2->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        label_3 = new QLabel(SetSysWnd);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(690, 245, 16, 31));
        label_3->setStyleSheet(QLatin1String("border-style:solid;\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 20px;\n"
"	font-weight: normal;\n"
"	line-height: 70px;\n"
"	color: #21b0f2;"));
        label_3->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        label_4 = new QLabel(SetSysWnd);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(305, 470, 16, 31));
        label_4->setStyleSheet(QLatin1String("border-style:solid;\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 20px;\n"
"	font-weight: normal;\n"
"	line-height: 70px;\n"
"	color: #21b0f2;"));
        label_4->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        label_5 = new QLabel(SetSysWnd);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(690, 470, 16, 31));
        label_5->setStyleSheet(QLatin1String("border-style:solid;\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 20px;\n"
"	font-weight: normal;\n"
"	line-height: 70px;\n"
"	color: #21b0f2;"));
        label_5->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        retranslateUi(SetSysWnd);

        QMetaObject::connectSlotsByName(SetSysWnd);
    } // setupUi

    void retranslateUi(QDialog *SetSysWnd)
    {
        SetSysWnd->setWindowTitle(QApplication::translate("SetSysWnd", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("SetSysWnd", "    \345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        closeBtn->setText(QString());
        heartLa->setText(QString());
        hungLa->setText(QString());
        la1->setText(QApplication::translate("SetSysWnd", "\346\214\211\345\216\213\351\200\237\345\272\246 (bmp)", Q_NULLPTR));
        la2->setText(QApplication::translate("SetSysWnd", "\346\214\211\345\216\213\346\267\261\345\272\246(mm)", Q_NULLPTR));
        la3->setText(QApplication::translate("SetSysWnd", "\351\200\232\346\260\224\346\227\266\351\227\264(msec)", Q_NULLPTR));
        la4->setText(QApplication::translate("SetSysWnd", "\351\200\232\346\260\224\344\275\223\347\247\257(ml)", Q_NULLPTR));
        cancelBtn->setText(QApplication::translate("SetSysWnd", "\345\217\226\346\266\210", Q_NULLPTR));
        saveBtn->setText(QApplication::translate("SetSysWnd", "\344\277\235\345\255\230", Q_NULLPTR));
        label_2->setText(QApplication::translate("SetSysWnd", "~", Q_NULLPTR));
        label_3->setText(QApplication::translate("SetSysWnd", "~", Q_NULLPTR));
        label_4->setText(QApplication::translate("SetSysWnd", "~", Q_NULLPTR));
        label_5->setText(QApplication::translate("SetSysWnd", "~", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SetSysWnd: public Ui_SetSysWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETSYSWND_H
