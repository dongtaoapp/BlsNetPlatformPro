/********************************************************************************
** Form generated from reading UI file 'cprrealtimecavue.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPRREALTIMECAVUE_H
#define UI_CPRREALTIMECAVUE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cprRealTimeCavue
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *cprRealTimeCavue)
    {
        if (cprRealTimeCavue->objectName().isEmpty())
            cprRealTimeCavue->setObjectName(QStringLiteral("cprRealTimeCavue"));
        cprRealTimeCavue->resize(400, 300);
        pushButton = new QPushButton(cprRealTimeCavue);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 210, 75, 23));

        retranslateUi(cprRealTimeCavue);

        QMetaObject::connectSlotsByName(cprRealTimeCavue);
    } // setupUi

    void retranslateUi(QWidget *cprRealTimeCavue)
    {
        cprRealTimeCavue->setWindowTitle(QApplication::translate("cprRealTimeCavue", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("cprRealTimeCavue", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class cprRealTimeCavue: public Ui_cprRealTimeCavue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPRREALTIMECAVUE_H
