/********************************************************************************
** Form generated from reading UI file 'setmanikinwnd.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETMANIKINWND_H
#define UI_SETMANIKINWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SetManikinWnd
{
public:
    QLabel *titleLa;
    QPushButton *closeBtn;
    QLabel *la1;
    QLabel *pointLa;
    QLabel *Linela;
    QLabel *la2;
    QLabel *Linela_2;
    QLabel *VLa;
    QLabel *la2_2;
    QLabel *Linela_3;
    QLabel *la1_2;
    QLabel *Linela_4;
    QLabel *pointLa_2;
    QLabel *VLa_2;
    QLabel *la1_3;
    QLabel *pointLa_3;
    QLabel *Linela_5;
    QPushButton *cancelBtn;
    QPushButton *saveBtn;
    QPushButton *bpm_Btn1;
    QPushButton *bpm_Btn2;
    QPushButton *bpm_Btn3;
    QPushButton *bpm_Btn4;
    QPushButton *voiceBtn_on;
    QPushButton *voiceBtn_OFF;
    QPushButton *AFCanBtn;
    QPushButton *AFNoBtn;
    QPushButton *AFIgnoreBtn;
    QPushButton *SuccessCPRBtn;
    QPushButton *SuccessAFBtn;
    QLabel *countLa;

    void setupUi(QDialog *SetManikinWnd)
    {
        if (SetManikinWnd->objectName().isEmpty())
            SetManikinWnd->setObjectName(QStringLiteral("SetManikinWnd"));
        SetManikinWnd->resize(942, 688);
        SetManikinWnd->setMinimumSize(QSize(942, 688));
        SetManikinWnd->setStyleSheet(QLatin1String("QLabel#la1,#la2,#la1_2,#la2_2,#la1_3,#countLa{\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 20px;\n"
"	font-weight: normal;\n"
"	line-height: 70px;\n"
"	color: #21b0f2;\n"
"}\n"
"QLabel#Linela,#Linela_2,#VLa,#Linela_3,#Linela_4,#Linela_5,#VLa_2{\n"
"	background-color: rgba(33, 176, 242, 0.5);\n"
"}\n"
"\n"
"QPushButton#saveBtn,#cancelBtn{\n"
"	border-style:solid;\n"
"	background-color:#21b0f2;\n"
"	color:white;\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 18px;	\n"
"}\n"
"QPushButton#bpm_Btn1,#bpm_Btn2,#bpm_Btn3,#bpm_Btn4,#voiceBtn_on,#voiceBtn_OFF,#AFCanBtn,#AFNoBtn,#AFIgnoreBtn,#SuccessCPRBtn,#SuccessAFBtn{\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 20px;\n"
"	font-weight: normal;\n"
"	line-height: 70px;\n"
"	color: #21b0f2;\n"
"}"));
        titleLa = new QLabel(SetManikinWnd);
        titleLa->setObjectName(QStringLiteral("titleLa"));
        titleLa->setGeometry(QRect(0, 0, 940, 60));
        titleLa->setMinimumSize(QSize(940, 60));
        titleLa->setMaximumSize(QSize(940, 60));
        titleLa->setStyleSheet(QLatin1String("font-family: PingFangSC-Regular;\n"
"font-size: 24px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #21b0f2;\n"
"background-color:#232639;;"));
        closeBtn = new QPushButton(SetManikinWnd);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setGeometry(QRect(884, 20, 41, 23));
        closeBtn->setMinimumSize(QSize(41, 23));
        closeBtn->setMaximumSize(QSize(41, 23));
        closeBtn->setStyleSheet(QLatin1String("border-style:solid;\n"
"image:url(:/image/X.png);\n"
""));
        la1 = new QLabel(SetManikinWnd);
        la1->setObjectName(QStringLiteral("la1"));
        la1->setGeometry(QRect(60, 100, 71, 21));
        la1->setMinimumSize(QSize(71, 21));
        pointLa = new QLabel(SetManikinWnd);
        pointLa->setObjectName(QStringLiteral("pointLa"));
        pointLa->setGeometry(QRect(40, 110, 4, 4));
        pointLa->setMinimumSize(QSize(4, 4));
        pointLa->setStyleSheet(QStringLiteral("background-color: #00c594;"));
        Linela = new QLabel(SetManikinWnd);
        Linela->setObjectName(QStringLiteral("Linela"));
        Linela->setGeometry(QRect(60, 140, 456, 1));
        Linela->setMinimumSize(QSize(456, 1));
        la2 = new QLabel(SetManikinWnd);
        la2->setObjectName(QStringLiteral("la2"));
        la2->setGeometry(QRect(710, 100, 82, 21));
        la2->setMinimumSize(QSize(82, 21));
        Linela_2 = new QLabel(SetManikinWnd);
        Linela_2->setObjectName(QStringLiteral("Linela_2"));
        Linela_2->setGeometry(QRect(600, 140, 300, 1));
        Linela_2->setMinimumSize(QSize(300, 1));
        VLa = new QLabel(SetManikinWnd);
        VLa->setObjectName(QStringLiteral("VLa"));
        VLa->setGeometry(QRect(560, 110, 1, 50));
        VLa->setMinimumSize(QSize(1, 50));
        la2_2 = new QLabel(SetManikinWnd);
        la2_2->setObjectName(QStringLiteral("la2_2"));
        la2_2->setGeometry(QRect(710, 270, 91, 21));
        la2_2->setMinimumSize(QSize(91, 21));
        Linela_3 = new QLabel(SetManikinWnd);
        Linela_3->setObjectName(QStringLiteral("Linela_3"));
        Linela_3->setGeometry(QRect(600, 310, 300, 1));
        la1_2 = new QLabel(SetManikinWnd);
        la1_2->setObjectName(QStringLiteral("la1_2"));
        la1_2->setGeometry(QRect(60, 270, 91, 21));
        la1_2->setMinimumSize(QSize(91, 21));
        Linela_4 = new QLabel(SetManikinWnd);
        Linela_4->setObjectName(QStringLiteral("Linela_4"));
        Linela_4->setGeometry(QRect(60, 310, 456, 1));
        pointLa_2 = new QLabel(SetManikinWnd);
        pointLa_2->setObjectName(QStringLiteral("pointLa_2"));
        pointLa_2->setGeometry(QRect(40, 280, 4, 4));
        pointLa_2->setMinimumSize(QSize(4, 4));
        pointLa_2->setStyleSheet(QStringLiteral("background-color: #00c594;"));
        VLa_2 = new QLabel(SetManikinWnd);
        VLa_2->setObjectName(QStringLiteral("VLa_2"));
        VLa_2->setGeometry(QRect(560, 280, 1, 50));
        la1_3 = new QLabel(SetManikinWnd);
        la1_3->setObjectName(QStringLiteral("la1_3"));
        la1_3->setGeometry(QRect(60, 440, 101, 21));
        pointLa_3 = new QLabel(SetManikinWnd);
        pointLa_3->setObjectName(QStringLiteral("pointLa_3"));
        pointLa_3->setGeometry(QRect(40, 450, 4, 4));
        pointLa_3->setStyleSheet(QStringLiteral("background-color: #00c594;"));
        Linela_5 = new QLabel(SetManikinWnd);
        Linela_5->setObjectName(QStringLiteral("Linela_5"));
        Linela_5->setGeometry(QRect(60, 480, 830, 1));
        cancelBtn = new QPushButton(SetManikinWnd);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setGeometry(QRect(250, 620, 81, 30));
        saveBtn = new QPushButton(SetManikinWnd);
        saveBtn->setObjectName(QStringLiteral("saveBtn"));
        saveBtn->setGeometry(QRect(530, 620, 81, 30));
        bpm_Btn1 = new QPushButton(SetManikinWnd);
        bpm_Btn1->setObjectName(QStringLiteral("bpm_Btn1"));
        bpm_Btn1->setGeometry(QRect(60, 170, 98, 40));
        bpm_Btn2 = new QPushButton(SetManikinWnd);
        bpm_Btn2->setObjectName(QStringLiteral("bpm_Btn2"));
        bpm_Btn2->setGeometry(QRect(180, 170, 98, 40));
        bpm_Btn3 = new QPushButton(SetManikinWnd);
        bpm_Btn3->setObjectName(QStringLiteral("bpm_Btn3"));
        bpm_Btn3->setGeometry(QRect(300, 170, 98, 40));
        bpm_Btn4 = new QPushButton(SetManikinWnd);
        bpm_Btn4->setObjectName(QStringLiteral("bpm_Btn4"));
        bpm_Btn4->setGeometry(QRect(420, 170, 98, 40));
        voiceBtn_on = new QPushButton(SetManikinWnd);
        voiceBtn_on->setObjectName(QStringLiteral("voiceBtn_on"));
        voiceBtn_on->setGeometry(QRect(620, 170, 98, 40));
        voiceBtn_OFF = new QPushButton(SetManikinWnd);
        voiceBtn_OFF->setObjectName(QStringLiteral("voiceBtn_OFF"));
        voiceBtn_OFF->setGeometry(QRect(760, 170, 98, 40));
        AFCanBtn = new QPushButton(SetManikinWnd);
        AFCanBtn->setObjectName(QStringLiteral("AFCanBtn"));
        AFCanBtn->setGeometry(QRect(60, 350, 90, 48));
        AFNoBtn = new QPushButton(SetManikinWnd);
        AFNoBtn->setObjectName(QStringLiteral("AFNoBtn"));
        AFNoBtn->setGeometry(QRect(200, 350, 90, 48));
        AFIgnoreBtn = new QPushButton(SetManikinWnd);
        AFIgnoreBtn->setObjectName(QStringLiteral("AFIgnoreBtn"));
        AFIgnoreBtn->setGeometry(QRect(340, 350, 90, 48));
        SuccessCPRBtn = new QPushButton(SetManikinWnd);
        SuccessCPRBtn->setObjectName(QStringLiteral("SuccessCPRBtn"));
        SuccessCPRBtn->setGeometry(QRect(60, 500, 90, 48));
        SuccessAFBtn = new QPushButton(SetManikinWnd);
        SuccessAFBtn->setObjectName(QStringLiteral("SuccessAFBtn"));
        SuccessAFBtn->setGeometry(QRect(190, 500, 90, 48));
        countLa = new QLabel(SetManikinWnd);
        countLa->setObjectName(QStringLiteral("countLa"));
        countLa->setGeometry(QRect(755, 355, 20, 20));
        countLa->setAlignment(Qt::AlignCenter);

        retranslateUi(SetManikinWnd);

        QMetaObject::connectSlotsByName(SetManikinWnd);
    } // setupUi

    void retranslateUi(QDialog *SetManikinWnd)
    {
        SetManikinWnd->setWindowTitle(QApplication::translate("SetManikinWnd", "Dialog", Q_NULLPTR));
        titleLa->setText(QApplication::translate("SetManikinWnd", "     \346\250\241\346\213\237\344\272\272\350\256\276\347\275\256", Q_NULLPTR));
        closeBtn->setText(QString());
        la1->setText(QApplication::translate("SetManikinWnd", "\350\212\202\346\213\215\345\231\250", Q_NULLPTR));
        pointLa->setText(QApplication::translate("SetManikinWnd", "TextLabel", Q_NULLPTR));
        Linela->setText(QString());
        la2->setText(QApplication::translate("SetManikinWnd", "\350\257\255\351\237\263\346\217\220\347\244\272", Q_NULLPTR));
        Linela_2->setText(QString());
        VLa->setText(QString());
        la2_2->setText(QApplication::translate("SetManikinWnd", "\351\231\244\351\242\244\346\254\241\346\225\260", Q_NULLPTR));
        Linela_3->setText(QString());
        la1_2->setText(QApplication::translate("SetManikinWnd", "\350\203\275\345\220\246\351\231\244\351\242\244", Q_NULLPTR));
        Linela_4->setText(QString());
        pointLa_2->setText(QApplication::translate("SetManikinWnd", "TextLabel", Q_NULLPTR));
        VLa_2->setText(QString());
        la1_3->setText(QApplication::translate("SetManikinWnd", "\346\210\220\345\212\237\346\235\241\344\273\266", Q_NULLPTR));
        pointLa_3->setText(QApplication::translate("SetManikinWnd", "TextLabel", Q_NULLPTR));
        Linela_5->setText(QString());
        cancelBtn->setText(QApplication::translate("SetManikinWnd", "\345\217\226\346\266\210", Q_NULLPTR));
        saveBtn->setText(QApplication::translate("SetManikinWnd", "\344\277\235\345\255\230", Q_NULLPTR));
        bpm_Btn1->setText(QApplication::translate("SetManikinWnd", "OFF", Q_NULLPTR));
        bpm_Btn2->setText(QApplication::translate("SetManikinWnd", "100bpm", Q_NULLPTR));
        bpm_Btn3->setText(QApplication::translate("SetManikinWnd", "110bpm", Q_NULLPTR));
        bpm_Btn4->setText(QApplication::translate("SetManikinWnd", "120bpm", Q_NULLPTR));
        voiceBtn_on->setText(QApplication::translate("SetManikinWnd", "\345\274\200", Q_NULLPTR));
        voiceBtn_OFF->setText(QApplication::translate("SetManikinWnd", "\345\205\263", Q_NULLPTR));
        AFCanBtn->setText(QApplication::translate("SetManikinWnd", "\350\203\275", Q_NULLPTR));
        AFNoBtn->setText(QApplication::translate("SetManikinWnd", "\345\220\246", Q_NULLPTR));
        AFIgnoreBtn->setText(QApplication::translate("SetManikinWnd", "\345\277\275\347\225\245", Q_NULLPTR));
        SuccessCPRBtn->setText(QApplication::translate("SetManikinWnd", "CPR", Q_NULLPTR));
        SuccessAFBtn->setText(QApplication::translate("SetManikinWnd", "\351\231\244\351\242\244", Q_NULLPTR));
        countLa->setText(QApplication::translate("SetManikinWnd", "\346\254\241", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SetManikinWnd: public Ui_SetManikinWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETMANIKINWND_H
