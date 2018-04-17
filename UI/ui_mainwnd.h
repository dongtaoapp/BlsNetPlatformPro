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
#include <QtWidgets/QGridLayout>
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
    QGridLayout *gridLayout;
    QWidget *titleWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
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
        MainWnd->setMaximumSize(QSize(16777215, 16777215));
        MainWnd->setStyleSheet(QLatin1String("QWidget{\n"
"	background-color: #373950;	\n"
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
        gridLayout = new QGridLayout(MainWnd);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(MainWnd);
        titleWidget->setObjectName(QStringLiteral("titleWidget"));
        titleWidget->setMinimumSize(QSize(0, 40));
        titleWidget->setMaximumSize(QSize(16777215, 16777215));
        titleWidget->setStyleSheet(QStringLiteral("background-color:#2c2e43;"));
        verticalLayout = new QVBoxLayout(titleWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(510, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        TitleLabel = new QLabel(titleWidget);
        TitleLabel->setObjectName(QStringLiteral("TitleLabel"));
        TitleLabel->setMinimumSize(QSize(151, 40));
        TitleLabel->setMaximumSize(QSize(250, 40));
        TitleLabel->setStyleSheet(QLatin1String("width: 222px;\n"
"height: 17px;\n"
"font-family: PingFangSC-Regular;\n"
"font-size: 18px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #b6b8c4;"));

        horizontalLayout_3->addWidget(TitleLabel);

        horizontalSpacer_3 = new QSpacerItem(440, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        MinWndBtn = new QPushButton(titleWidget);
        MinWndBtn->setObjectName(QStringLiteral("MinWndBtn"));
        MinWndBtn->setMinimumSize(QSize(40, 40));
        MinWndBtn->setMaximumSize(QSize(40, 40));
        MinWndBtn->setCursor(QCursor(Qt::PointingHandCursor));
        MinWndBtn->setStyleSheet(QLatin1String("QPushButton{\n"
"	image:url(:/image/2.png);\n"
"}\n"
"QPushButton::hover{\n"
"	background-color:#e5e5e5;\n"
"	color:black;\n"
"}"));

        horizontalLayout_3->addWidget(MinWndBtn);

        MaxWndBtn = new QPushButton(titleWidget);
        MaxWndBtn->setObjectName(QStringLiteral("MaxWndBtn"));
        MaxWndBtn->setMinimumSize(QSize(40, 40));
        MaxWndBtn->setMaximumSize(QSize(40, 40));
        MaxWndBtn->setCursor(QCursor(Qt::PointingHandCursor));
        MaxWndBtn->setStyleSheet(QLatin1String("QPushButton::hover{\n"
"	background-color:#e5e5e5;\n"
"	color:black;\n"
"}"));

        horizontalLayout_3->addWidget(MaxWndBtn);

        CloseWndBtn = new QPushButton(titleWidget);
        CloseWndBtn->setObjectName(QStringLiteral("CloseWndBtn"));
        CloseWndBtn->setMinimumSize(QSize(40, 40));
        CloseWndBtn->setMaximumSize(QSize(40, 40));
        CloseWndBtn->setCursor(QCursor(Qt::PointingHandCursor));
        CloseWndBtn->setStyleSheet(QLatin1String("QPushButton{\n"
"	image:url(:/image/1.png);\n"
"}\n"
"QPushButton::hover{\n"
"	background-color:red;\n"
"}"));

        horizontalLayout_3->addWidget(CloseWndBtn);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(20);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        CPRWorkBtn = new QPushButton(titleWidget);
        CPRWorkBtn->setObjectName(QStringLiteral("CPRWorkBtn"));
        CPRWorkBtn->setMinimumSize(QSize(80, 30));
        CPRWorkBtn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(CPRWorkBtn);

        SCBtn = new QPushButton(titleWidget);
        SCBtn->setObjectName(QStringLiteral("SCBtn"));
        SCBtn->setMinimumSize(QSize(80, 30));
        SCBtn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(SCBtn);

        StatisticsBtn = new QPushButton(titleWidget);
        StatisticsBtn->setObjectName(QStringLiteral("StatisticsBtn"));
        StatisticsBtn->setMinimumSize(QSize(60, 30));
        StatisticsBtn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(StatisticsBtn);

        horizontalSpacer = new QSpacerItem(1158, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addWidget(titleWidget, 0, 0, 1, 1);

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

        gridLayout->addWidget(stackedWidget, 1, 0, 1, 1);


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
