/********************************************************************************
** Form generated from reading UI file 'barwnd.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BARWND_H
#define UI_BARWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BarWnd
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_3;
    QWidget *widget_2;

    void setupUi(QWidget *BarWnd)
    {
        if (BarWnd->objectName().isEmpty())
            BarWnd->setObjectName(QStringLiteral("BarWnd"));
        BarWnd->resize(1351, 733);
        BarWnd->setStyleSheet(QStringLiteral("QWidget{border:1px solid #c0c0c0;}"));
        verticalLayout = new QVBoxLayout(BarWnd);
        verticalLayout->setSpacing(30);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(20, 16, 20, 40);
        widget = new QWidget(BarWnd);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 2));
        label->setStyleSheet(QStringLiteral("border:1px solid #21b0f2;"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        verticalLayout->addWidget(widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget_3 = new QWidget(BarWnd);
        widget_3->setObjectName(QStringLiteral("widget_3"));

        horizontalLayout->addWidget(widget_3);

        widget_2 = new QWidget(BarWnd);
        widget_2->setObjectName(QStringLiteral("widget_2"));

        horizontalLayout->addWidget(widget_2);

        horizontalLayout->setStretch(0, 10);
        horizontalLayout->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 10);

        retranslateUi(BarWnd);

        QMetaObject::connectSlotsByName(BarWnd);
    } // setupUi

    void retranslateUi(QWidget *BarWnd)
    {
        BarWnd->setWindowTitle(QApplication::translate("BarWnd", "Form", Q_NULLPTR));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BarWnd: public Ui_BarWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BARWND_H
