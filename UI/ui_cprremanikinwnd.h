/********************************************************************************
** Form generated from reading UI file 'cprremanikinwnd.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPRREMANIKINWND_H
#define UI_CPRREMANIKINWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CPRReManikinWnd
{
public:
    QLabel *la;
    QLabel *TitleLa;
    QPushButton *closeBtn;
    QLabel *label;
    QPushButton *pushButton;
    QLabel *label_2;

    void setupUi(QDialog *CPRReManikinWnd)
    {
        if (CPRReManikinWnd->objectName().isEmpty())
            CPRReManikinWnd->setObjectName(QStringLiteral("CPRReManikinWnd"));
        CPRReManikinWnd->resize(843, 388);
        la = new QLabel(CPRReManikinWnd);
        la->setObjectName(QStringLiteral("la"));
        la->setGeometry(QRect(250, 170, 61, 31));
        la->setStyleSheet(QLatin1String("font-family: PingFangSC-Regular;\n"
"font-size: 20px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #b6b8c4;"));
        TitleLa = new QLabel(CPRReManikinWnd);
        TitleLa->setObjectName(QStringLiteral("TitleLa"));
        TitleLa->setGeometry(QRect(0, 0, 843, 60));
        TitleLa->setStyleSheet(QLatin1String("font-family: PingFangSC-Regular;\n"
"font-size: 24px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #21b0f2;\n"
"background-color:#232639;;\n"
""));
        closeBtn = new QPushButton(CPRReManikinWnd);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setGeometry(QRect(794, 10, 41, 41));
        closeBtn->setStyleSheet(QLatin1String("border-style:solid;\n"
"image:url(:/image/X.png);"));
        label = new QLabel(CPRReManikinWnd);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(307, 170, 111, 31));
        label->setStyleSheet(QLatin1String("font-family: PingFangSC-Regular;\n"
"font-size: 24px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #21b0f2;"));
        pushButton = new QPushButton(CPRReManikinWnd);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(320, 330, 81, 31));
        pushButton->setStyleSheet(QLatin1String("border-style:solid;\n"
"background-color:#21b0f2;\n"
"color:white;\n"
"font-family: PingFangSC-Regular;\n"
"font-size: 18px;"));
        label_2 = new QLabel(CPRReManikinWnd);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(420, 170, 54, 31));
        label_2->setStyleSheet(QLatin1String("font-family: PingFangSC-Regular;\n"
"font-size: 30px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #b6b8c4;"));
        label_2->setAlignment(Qt::AlignCenter);

        retranslateUi(CPRReManikinWnd);

        QMetaObject::connectSlotsByName(CPRReManikinWnd);
    } // setupUi

    void retranslateUi(QDialog *CPRReManikinWnd)
    {
        CPRReManikinWnd->setWindowTitle(QApplication::translate("CPRReManikinWnd", "Dialog", Q_NULLPTR));
        la->setText(QApplication::translate("CPRReManikinWnd", "\345\210\240\351\231\244", Q_NULLPTR));
        TitleLa->setText(QApplication::translate("CPRReManikinWnd", "  \346\217\220\347\244\272", Q_NULLPTR));
        closeBtn->setText(QString());
        label->setText(QApplication::translate("CPRReManikinWnd", "#FF00000", Q_NULLPTR));
        pushButton->setText(QApplication::translate("CPRReManikinWnd", "\347\241\256\345\256\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("CPRReManikinWnd", "?", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CPRReManikinWnd: public Ui_CPRReManikinWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPRREMANIKINWND_H
