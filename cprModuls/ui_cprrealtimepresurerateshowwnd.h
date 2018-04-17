/********************************************************************************
** Form generated from reading UI file 'cprrealtimepresurerateshowwnd.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPRREALTIMEPRESURERATESHOWWND_H
#define UI_CPRREALTIMEPRESURERATESHOWWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CPRRealTimePresureRateShowWnd
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *CPRRealTimePresureRateShowWnd)
    {
        if (CPRRealTimePresureRateShowWnd->objectName().isEmpty())
            CPRRealTimePresureRateShowWnd->setObjectName(QStringLiteral("CPRRealTimePresureRateShowWnd"));
        CPRRealTimePresureRateShowWnd->resize(400, 300);
        pushButton = new QPushButton(CPRRealTimePresureRateShowWnd);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(230, 270, 75, 23));

        retranslateUi(CPRRealTimePresureRateShowWnd);

        QMetaObject::connectSlotsByName(CPRRealTimePresureRateShowWnd);
    } // setupUi

    void retranslateUi(QWidget *CPRRealTimePresureRateShowWnd)
    {
        CPRRealTimePresureRateShowWnd->setWindowTitle(QApplication::translate("CPRRealTimePresureRateShowWnd", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("CPRRealTimePresureRateShowWnd", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CPRRealTimePresureRateShowWnd: public Ui_CPRRealTimePresureRateShowWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPRREALTIMEPRESURERATESHOWWND_H
