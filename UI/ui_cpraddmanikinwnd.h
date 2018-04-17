/********************************************************************************
** Form generated from reading UI file 'cpraddmanikinwnd.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPRADDMANIKINWND_H
#define UI_CPRADDMANIKINWND_H

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

class Ui_CPRAddManikinWnd
{
public:
    QLabel *TitleLa;
    QPushButton *closeBtn;
    QLabel *la;
    QLineEdit *addManikinlineEdit;
    QPushButton *cancelBtn;
    QPushButton *okBtn;

    void setupUi(QDialog *CPRAddManikinWnd)
    {
        if (CPRAddManikinWnd->objectName().isEmpty())
            CPRAddManikinWnd->setObjectName(QStringLiteral("CPRAddManikinWnd"));
        CPRAddManikinWnd->resize(843, 513);
        CPRAddManikinWnd->setStyleSheet(QLatin1String("QPushButton#okBtn,#cancelBtn{\n"
"	border-style:solid;\n"
"	background-color:#21b0f2;\n"
"	color:white;\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 18px;\n"
"	\n"
"}"));
        TitleLa = new QLabel(CPRAddManikinWnd);
        TitleLa->setObjectName(QStringLiteral("TitleLa"));
        TitleLa->setGeometry(QRect(0, 0, 843, 60));
        TitleLa->setStyleSheet(QLatin1String("font-family: PingFangSC-Regular;\n"
"font-size: 24px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #21b0f2;\n"
"background-color: #232639;"));
        closeBtn = new QPushButton(CPRAddManikinWnd);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setGeometry(QRect(794, 12, 41, 41));
        closeBtn->setCursor(QCursor(Qt::PointingHandCursor));
        closeBtn->setStyleSheet(QLatin1String("border-style:solid;\n"
"image:url(:/image/X.png);"));
        la = new QLabel(CPRAddManikinWnd);
        la->setObjectName(QStringLiteral("la"));
        la->setGeometry(QRect(90, 150, 461, 31));
        la->setStyleSheet(QLatin1String("font-family: PingFangSC-Regular;\n"
"font-size: 20px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #b6b8c4;"));
        addManikinlineEdit = new QLineEdit(CPRAddManikinWnd);
        addManikinlineEdit->setObjectName(QStringLiteral("addManikinlineEdit"));
        addManikinlineEdit->setGeometry(QRect(90, 210, 467, 37));
        addManikinlineEdit->setStyleSheet(QLatin1String("font-family: PingFangSC-Regular;\n"
"font-size: 20px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #b6b8c4;"));
        cancelBtn = new QPushButton(CPRAddManikinWnd);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setGeometry(QRect(180, 430, 81, 31));
        cancelBtn->setCursor(QCursor(Qt::PointingHandCursor));
        okBtn = new QPushButton(CPRAddManikinWnd);
        okBtn->setObjectName(QStringLiteral("okBtn"));
        okBtn->setGeometry(QRect(390, 430, 91, 31));
        okBtn->setCursor(QCursor(Qt::PointingHandCursor));

        retranslateUi(CPRAddManikinWnd);

        QMetaObject::connectSlotsByName(CPRAddManikinWnd);
    } // setupUi

    void retranslateUi(QDialog *CPRAddManikinWnd)
    {
        CPRAddManikinWnd->setWindowTitle(QApplication::translate("CPRAddManikinWnd", "Dialog", Q_NULLPTR));
        TitleLa->setText(QApplication::translate("CPRAddManikinWnd", "   \346\267\273\345\212\240\346\250\241\346\213\237\344\272\272", Q_NULLPTR));
        closeBtn->setText(QString());
        la->setText(QApplication::translate("CPRAddManikinWnd", "\350\276\223\345\205\245\346\240\207\350\257\206\347\240\201", Q_NULLPTR));
        cancelBtn->setText(QApplication::translate("CPRAddManikinWnd", "\345\217\226\346\266\210", Q_NULLPTR));
        okBtn->setText(QApplication::translate("CPRAddManikinWnd", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CPRAddManikinWnd: public Ui_CPRAddManikinWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPRADDMANIKINWND_H
