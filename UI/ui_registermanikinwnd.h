/********************************************************************************
** Form generated from reading UI file 'registermanikinwnd.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERMANIKINWND_H
#define UI_REGISTERMANIKINWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterManikinWnd
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *ConManikinBtn;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *addManikinBtn;

    void setupUi(QWidget *RegisterManikinWnd)
    {
        if (RegisterManikinWnd->objectName().isEmpty())
            RegisterManikinWnd->setObjectName(QStringLiteral("RegisterManikinWnd"));
        RegisterManikinWnd->resize(426, 500);
        RegisterManikinWnd->setStyleSheet(QStringLiteral("image:url(:/image/ss.png);"));
        gridLayout = new QGridLayout(RegisterManikinWnd);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(60);
        gridLayout->setVerticalSpacing(40);
        gridLayout->setContentsMargins(60, 60, 60, 60);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        tableView = new QTableView(RegisterManikinWnd);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setMinimumSize(QSize(0, 0));
        tableView->setMaximumSize(QSize(16777215, 16777215));
        tableView->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(tableView);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(378, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        ConManikinBtn = new QPushButton(RegisterManikinWnd);
        ConManikinBtn->setObjectName(QStringLiteral("ConManikinBtn"));
        ConManikinBtn->setMinimumSize(QSize(81, 30));
        ConManikinBtn->setMaximumSize(QSize(81, 30));
        ConManikinBtn->setCursor(QCursor(Qt::PointingHandCursor));
        ConManikinBtn->setStyleSheet(QLatin1String("border-style:solid;\n"
"width: 33px;\n"
"height: 16px;\n"
"font-family: PingFangSC-Regular;\n"
"font-size: 16px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #ffffff;\n"
"background-color: #21b0f2;\n"
"border-radius: 2px;"));

        horizontalLayout_2->addWidget(ConManikinBtn);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(331, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        addManikinBtn = new QPushButton(RegisterManikinWnd);
        addManikinBtn->setObjectName(QStringLiteral("addManikinBtn"));
        addManikinBtn->setMinimumSize(QSize(80, 30));
        addManikinBtn->setMaximumSize(QSize(80, 30));
        addManikinBtn->setCursor(QCursor(Qt::PointingHandCursor));
        addManikinBtn->setStyleSheet(QLatin1String("border-style:solid;\n"
"\n"
"\n"
"font-family: PingFangSC-Regular;\n"
"font-size: 16px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #ffffff;\n"
"background-color:#2c2e43;\n"
"border-radius: 2px;"));

        horizontalLayout_3->addWidget(addManikinBtn);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);


        retranslateUi(RegisterManikinWnd);

        QMetaObject::connectSlotsByName(RegisterManikinWnd);
    } // setupUi

    void retranslateUi(QWidget *RegisterManikinWnd)
    {
        RegisterManikinWnd->setWindowTitle(QApplication::translate("RegisterManikinWnd", "RegisterManikinWnd", Q_NULLPTR));
        ConManikinBtn->setText(QApplication::translate("RegisterManikinWnd", "\350\277\236\346\216\245", Q_NULLPTR));
        addManikinBtn->setText(QApplication::translate("RegisterManikinWnd", "\345\242\236\345\212\240\346\250\241\346\213\237\344\272\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RegisterManikinWnd: public Ui_RegisterManikinWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERMANIKINWND_H
