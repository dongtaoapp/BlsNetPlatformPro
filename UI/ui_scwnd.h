/********************************************************************************
** Form generated from reading UI file 'scwnd.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCWND_H
#define UI_SCWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SCWnd
{
public:

    void setupUi(QWidget *SCWnd)
    {
        if (SCWnd->objectName().isEmpty())
            SCWnd->setObjectName(QStringLiteral("SCWnd"));
        SCWnd->resize(400, 300);

        retranslateUi(SCWnd);

        QMetaObject::connectSlotsByName(SCWnd);
    } // setupUi

    void retranslateUi(QWidget *SCWnd)
    {
        SCWnd->setWindowTitle(QApplication::translate("SCWnd", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SCWnd: public Ui_SCWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCWND_H
