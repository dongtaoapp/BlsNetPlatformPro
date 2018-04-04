/********************************************************************************
** Form generated from reading UI file 'mainwnd.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWND_H
#define UI_MAINWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWnd
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *TitleLabel;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *MinWndBtn;
    QPushButton *MaxWndBtn;
    QPushButton *CloseWndBtn;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *CPRWorkBtn;
    QPushButton *SCBtn;
    QPushButton *StatisticsBtn;
    QSpacerItem *horizontalSpacer;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;

    void setupUi(QWidget *MainWnd)
    {
        if (MainWnd->objectName().isEmpty())
            MainWnd->setObjectName(QStringLiteral("MainWnd"));
        MainWnd->resize(1440, 900);
        MainWnd->setStyleSheet(QLatin1String("QWidget{\n"
"	background-color:#2c2e43\n"
"}\n"
"QWidget#stackedWidget{\n"
"	border-style:solid;\n"
"	border-top:1px solid #000000\n"
"}\n"
"QPushButton{\n"
"	border-style:solid;\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 18px;\n"
"	font-weight: normal;\n"
"	line-height: 70px;\n"
"	color: #b6b8c4;\n"
"}"));
        verticalLayout = new QVBoxLayout(MainWnd);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(558, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        TitleLabel = new QLabel(MainWnd);
        TitleLabel->setObjectName(QStringLiteral("TitleLabel"));
        TitleLabel->setMinimumSize(QSize(151, 20));
        TitleLabel->setMaximumSize(QSize(250, 20));
        TitleLabel->setStyleSheet(QLatin1String("width: 222px;\n"
"height: 17px;\n"
"font-family: PingFangSC-Regular;\n"
"font-size: 18px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #b6b8c4;"));

        horizontalLayout->addWidget(TitleLabel);

        horizontalSpacer_3 = new QSpacerItem(488, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        MinWndBtn = new QPushButton(MainWnd);
        MinWndBtn->setObjectName(QStringLiteral("MinWndBtn"));
        MinWndBtn->setMinimumSize(QSize(40, 20));
        MinWndBtn->setMaximumSize(QSize(20, 10));
        MinWndBtn->setStyleSheet(QLatin1String("QPushButton{\n"
"	image:url(:/image/2.png);\n"
"}\n"
"QPushButton::hover{\n"
"	background-color:#e5e5e5;\n"
"	color:black;\n"
"}"));

        horizontalLayout->addWidget(MinWndBtn);

        MaxWndBtn = new QPushButton(MainWnd);
        MaxWndBtn->setObjectName(QStringLiteral("MaxWndBtn"));
        MaxWndBtn->setMinimumSize(QSize(40, 20));
        MaxWndBtn->setMaximumSize(QSize(20, 10));
        MaxWndBtn->setStyleSheet(QLatin1String("QPushButton::hover{\n"
"	background-color:#e5e5e5;\n"
"	color:black;\n"
"}"));

        horizontalLayout->addWidget(MaxWndBtn);

        CloseWndBtn = new QPushButton(MainWnd);
        CloseWndBtn->setObjectName(QStringLiteral("CloseWndBtn"));
        CloseWndBtn->setMinimumSize(QSize(40, 20));
        CloseWndBtn->setMaximumSize(QSize(20, 10));
        CloseWndBtn->setStyleSheet(QLatin1String("QPushButton{\n"
"	image:url(:/image/1.png);\n"
"}\n"
"QPushButton::hover{\n"
"	background-color:red;\n"
"}"));

        horizontalLayout->addWidget(CloseWndBtn);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        CPRWorkBtn = new QPushButton(MainWnd);
        CPRWorkBtn->setObjectName(QStringLiteral("CPRWorkBtn"));
        CPRWorkBtn->setMinimumSize(QSize(0, 0));
        CPRWorkBtn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(CPRWorkBtn);

        SCBtn = new QPushButton(MainWnd);
        SCBtn->setObjectName(QStringLiteral("SCBtn"));
        SCBtn->setMinimumSize(QSize(0, 0));
        SCBtn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(SCBtn);

        StatisticsBtn = new QPushButton(MainWnd);
        StatisticsBtn->setObjectName(QStringLiteral("StatisticsBtn"));
        StatisticsBtn->setMinimumSize(QSize(0, 0));
        StatisticsBtn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(StatisticsBtn);

        horizontalSpacer = new QSpacerItem(1158, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 1);
        horizontalLayout_2->setStretch(2, 1);
        horizontalLayout_2->setStretch(3, 10);

        verticalLayout->addLayout(horizontalLayout_2);

        stackedWidget = new QStackedWidget(MainWnd);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        stackedWidget->setMinimumSize(QSize(0, 0));
        stackedWidget->setStyleSheet(QStringLiteral(""));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 2);
        verticalLayout->setStretch(2, 40);

        retranslateUi(MainWnd);

        QMetaObject::connectSlotsByName(MainWnd);
    } // setupUi

    void retranslateUi(QWidget *MainWnd)
    {
        MainWnd->setWindowTitle(QApplication::translate("MainWnd", "MainWnd", Q_NULLPTR));
        TitleLabel->setText(QApplication::translate("MainWnd", "CPR\347\275\221\347\273\234\347\211\210Version1.0.0", Q_NULLPTR));
        MinWndBtn->setText(QString());
        MaxWndBtn->setText(QString());
        CloseWndBtn->setText(QString());
        CPRWorkBtn->setText(QApplication::translate("MainWnd", "CPR\346\223\215\344\275\234", Q_NULLPTR));
        SCBtn->setText(QApplication::translate("MainWnd", "\344\275\223\345\276\201\347\233\221\346\212\244", Q_NULLPTR));
        StatisticsBtn->setText(QApplication::translate("MainWnd", "\347\273\237\350\256\241", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWnd: public Ui_MainWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWND_H
