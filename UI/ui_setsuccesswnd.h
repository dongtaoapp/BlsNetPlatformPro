/********************************************************************************
** Form generated from reading UI file 'setsuccesswnd.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETSUCCESSWND_H
#define UI_SETSUCCESSWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SetSuccessWnd
{
public:
    QLabel *titleLa;
    QPushButton *closeBtn;
    QLabel *operateTimeLabel;
    QLabel *breakTimeLabel;
    QLabel *pressLabel;
    QLabel *pressRightLabel;
    QLabel *blowingLabel;
    QLabel *pressfrequencyLabel;
    QLabel *HandModelLabel;
    QPushButton *cancelBtn;
    QPushButton *saveBtn;
    QPushButton *popularizeBtn;
    QPushButton *acbtn;
    QLabel *la1;
    QLabel *la2;
    QLabel *la3;
    QLabel *la4;
    QLabel *la5;
    QLabel *la6;
    QLabel *la7;

    void setupUi(QDialog *SetSuccessWnd)
    {
        if (SetSuccessWnd->objectName().isEmpty())
            SetSuccessWnd->setObjectName(QStringLiteral("SetSuccessWnd"));
        SetSuccessWnd->resize(1066, 698);
        SetSuccessWnd->setStyleSheet(QLatin1String("QLabel#operateTimeLabel,#breakTimeLabel,#pressLabel,#pressRightLabel,#HandModelLabel,#blowingLabel,#pressfrequencyLabel{\n"
"border-style:solid;\n"
"font-family: PingFangSC-Regular;\n"
"font-size: 20px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #21b0f2;\n"
"\n"
"border-bottom:1px solid  #21b0f2;\n"
"}\n"
"\n"
"QLabel#la1,#la2,#la3,#la4,#la5,#la6,#la7{\n"
"	border-style:solid;\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 20px;\n"
"	font-weight: normal;\n"
"	line-height: 70px;\n"
"	color: #21b0f2;\n"
"}\n"
"QPushButton#saveBtn,#cancelBtn{\n"
"	border-style:solid;\n"
"	background-color:#21b0f2;\n"
"	color:white;\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 18px;\n"
"	\n"
"}\n"
"QPushButton#popularizeBtn,#acbtn{\n"
"	border-style:solid;\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 18px;\n"
"	font-weight: normal;\n"
"	line-height: 70px;\n"
"	color: #21b0f2;\n"
"}\n"
"QSpinBox{\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 24px;\n"
"	font-weight: normal;\n"
"	line-"
                        "height: 70px;\n"
"	color: #21b0f2;\n"
"}\n"
"QSpinBox::up-button {\n"
"   subcontrol-position:right;\n"
"	   \n"
"}\n"
"QSpinBox::down-button {\n"
"	subcontrol-position:left\n"
";\n"
"	image: url(:/image/down.png) \n"
"}"));
        titleLa = new QLabel(SetSuccessWnd);
        titleLa->setObjectName(QStringLiteral("titleLa"));
        titleLa->setGeometry(QRect(0, 0, 1066, 60));
        titleLa->setStyleSheet(QLatin1String("font-family: PingFangSC-Regular;\n"
"font-size: 24px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #21b0f2;\n"
"background-color: #373950;"));
        closeBtn = new QPushButton(SetSuccessWnd);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setGeometry(QRect(1004, 20, 31, 23));
        closeBtn->setCursor(QCursor(Qt::PointingHandCursor));
        closeBtn->setStyleSheet(QLatin1String("border-style:solid;\n"
"image:url(:/image/1.png)"));
        operateTimeLabel = new QLabel(SetSuccessWnd);
        operateTimeLabel->setObjectName(QStringLiteral("operateTimeLabel"));
        operateTimeLabel->setGeometry(QRect(40, 150, 200, 50));
        operateTimeLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        breakTimeLabel = new QLabel(SetSuccessWnd);
        breakTimeLabel->setObjectName(QStringLiteral("breakTimeLabel"));
        breakTimeLabel->setGeometry(QRect(300, 150, 200, 50));
        breakTimeLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        pressLabel = new QLabel(SetSuccessWnd);
        pressLabel->setObjectName(QStringLiteral("pressLabel"));
        pressLabel->setGeometry(QRect(570, 150, 200, 50));
        pressLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        pressRightLabel = new QLabel(SetSuccessWnd);
        pressRightLabel->setObjectName(QStringLiteral("pressRightLabel"));
        pressRightLabel->setGeometry(QRect(860, 150, 200, 50));
        pressRightLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        blowingLabel = new QLabel(SetSuccessWnd);
        blowingLabel->setObjectName(QStringLiteral("blowingLabel"));
        blowingLabel->setGeometry(QRect(40, 410, 200, 50));
        blowingLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        pressfrequencyLabel = new QLabel(SetSuccessWnd);
        pressfrequencyLabel->setObjectName(QStringLiteral("pressfrequencyLabel"));
        pressfrequencyLabel->setGeometry(QRect(360, 410, 200, 50));
        pressfrequencyLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        HandModelLabel = new QLabel(SetSuccessWnd);
        HandModelLabel->setObjectName(QStringLiteral("HandModelLabel"));
        HandModelLabel->setGeometry(QRect(690, 410, 200, 50));
        HandModelLabel->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        cancelBtn = new QPushButton(SetSuccessWnd);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setGeometry(QRect(380, 630, 81, 31));
        saveBtn = new QPushButton(SetSuccessWnd);
        saveBtn->setObjectName(QStringLiteral("saveBtn"));
        saveBtn->setGeometry(QRect(590, 630, 81, 31));
        popularizeBtn = new QPushButton(SetSuccessWnd);
        popularizeBtn->setObjectName(QStringLiteral("popularizeBtn"));
        popularizeBtn->setGeometry(QRect(700, 490, 74, 36));
        acbtn = new QPushButton(SetSuccessWnd);
        acbtn->setObjectName(QStringLiteral("acbtn"));
        acbtn->setGeometry(QRect(810, 490, 74, 36));
        la1 = new QLabel(SetSuccessWnd);
        la1->setObjectName(QStringLiteral("la1"));
        la1->setGeometry(QRect(100, 235, 20, 20));
        la2 = new QLabel(SetSuccessWnd);
        la2->setObjectName(QStringLiteral("la2"));
        la2->setGeometry(QRect(200, 235, 20, 20));
        la3 = new QLabel(SetSuccessWnd);
        la3->setObjectName(QStringLiteral("la3"));
        la3->setGeometry(QRect(420, 235, 20, 20));
        la4 = new QLabel(SetSuccessWnd);
        la4->setObjectName(QStringLiteral("la4"));
        la4->setGeometry(QRect(670, 235, 21, 20));
        la4->setAlignment(Qt::AlignCenter);
        la5 = new QLabel(SetSuccessWnd);
        la5->setObjectName(QStringLiteral("la5"));
        la5->setGeometry(QRect(960, 235, 21, 20));
        la5->setAlignment(Qt::AlignCenter);
        la6 = new QLabel(SetSuccessWnd);
        la6->setObjectName(QStringLiteral("la6"));
        la6->setGeometry(QRect(140, 495, 21, 20));
        la6->setAlignment(Qt::AlignCenter);
        la7 = new QLabel(SetSuccessWnd);
        la7->setObjectName(QStringLiteral("la7"));
        la7->setGeometry(QRect(460, 495, 21, 20));
        la7->setAlignment(Qt::AlignCenter);

        retranslateUi(SetSuccessWnd);

        QMetaObject::connectSlotsByName(SetSuccessWnd);
    } // setupUi

    void retranslateUi(QDialog *SetSuccessWnd)
    {
        SetSuccessWnd->setWindowTitle(QApplication::translate("SetSuccessWnd", "Dialog", Q_NULLPTR));
        titleLa->setText(QApplication::translate("SetSuccessWnd", "      CPR\346\212\242\346\225\221\346\210\220\345\212\237\346\235\241\344\273\266\350\256\276\347\275\256", Q_NULLPTR));
        closeBtn->setText(QString());
        operateTimeLabel->setText(QApplication::translate("SetSuccessWnd", "\346\223\215\344\275\234\346\227\266\351\227\264", Q_NULLPTR));
        breakTimeLabel->setText(QApplication::translate("SetSuccessWnd", "\344\270\255\346\226\255\346\227\266\351\227\264", Q_NULLPTR));
        pressLabel->setText(QApplication::translate("SetSuccessWnd", "\346\214\211\345\216\213\346\227\266\351\227\264\345\215\240\346\257\224", Q_NULLPTR));
        pressRightLabel->setText(QApplication::translate("SetSuccessWnd", "\346\214\211\345\216\213\346\255\243\347\241\256\347\216\207", Q_NULLPTR));
        blowingLabel->setText(QApplication::translate("SetSuccessWnd", "\345\220\271\350\265\267\346\255\243\347\241\256\347\216\207", Q_NULLPTR));
        pressfrequencyLabel->setText(QApplication::translate("SetSuccessWnd", "\346\214\211\345\216\213\351\242\221\347\216\207\346\255\243\347\241\256\347\216\207", Q_NULLPTR));
        HandModelLabel->setText(QApplication::translate("SetSuccessWnd", "\346\223\215\344\275\234\346\250\241\345\274\217", Q_NULLPTR));
        cancelBtn->setText(QApplication::translate("SetSuccessWnd", "\345\217\226\346\266\210", Q_NULLPTR));
        saveBtn->setText(QApplication::translate("SetSuccessWnd", "\344\277\235\345\255\230", Q_NULLPTR));
        popularizeBtn->setText(QApplication::translate("SetSuccessWnd", "\346\231\256\345\217\212", Q_NULLPTR));
        acbtn->setText(QApplication::translate("SetSuccessWnd", "\345\256\236\346\210\230", Q_NULLPTR));
        la1->setText(QApplication::translate("SetSuccessWnd", "\345\210\206", Q_NULLPTR));
        la2->setText(QApplication::translate("SetSuccessWnd", "\347\247\222", Q_NULLPTR));
        la3->setText(QApplication::translate("SetSuccessWnd", "\347\247\222", Q_NULLPTR));
        la4->setText(QApplication::translate("SetSuccessWnd", "%", Q_NULLPTR));
        la5->setText(QApplication::translate("SetSuccessWnd", "%", Q_NULLPTR));
        la6->setText(QApplication::translate("SetSuccessWnd", "%", Q_NULLPTR));
        la7->setText(QApplication::translate("SetSuccessWnd", "%", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SetSuccessWnd: public Ui_SetSuccessWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETSUCCESSWND_H
