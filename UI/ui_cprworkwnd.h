/********************************************************************************
** Form generated from reading UI file 'cprworkwnd.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPRWORKWND_H
#define UI_CPRWORKWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CPRWorkWnd
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *startBtn;
    QPushButton *retBtn;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *OneLineBtn;
    QPushButton *doubleLinBtn;
    QPushButton *moreLineBtn;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *UpPageBtn;
    QPushButton *downPageBtn;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *hideListBtn;
    QPushButton *showListBtn;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *setBtn;
    QPushButton *successSetBtn;
    QPushButton *ManikinSetBtn;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *listWidget_2;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;

    void setupUi(QWidget *CPRWorkWnd)
    {
        if (CPRWorkWnd->objectName().isEmpty())
            CPRWorkWnd->setObjectName(QStringLiteral("CPRWorkWnd"));
        CPRWorkWnd->resize(1171, 746);
        CPRWorkWnd->setMinimumSize(QSize(0, 0));
        CPRWorkWnd->setStyleSheet(QLatin1String("QPushButton{\n"
"	border-style:solid;	\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(CPRWorkWnd);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        startBtn = new QPushButton(CPRWorkWnd);
        startBtn->setObjectName(QStringLiteral("startBtn"));
        startBtn->setMinimumSize(QSize(40, 60));
        startBtn->setCursor(QCursor(Qt::PointingHandCursor));
        startBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(startBtn);

        retBtn = new QPushButton(CPRWorkWnd);
        retBtn->setObjectName(QStringLiteral("retBtn"));
        retBtn->setMinimumSize(QSize(40, 60));
        retBtn->setCursor(QCursor(Qt::PointingHandCursor));
        retBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(retBtn);

        horizontalSpacer_2 = new QSpacerItem(17, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(CPRWorkWnd);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(1, 75));
        label->setMaximumSize(QSize(1, 75));
        label->setStyleSheet(QStringLiteral("background-color:black;"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(13, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        OneLineBtn = new QPushButton(CPRWorkWnd);
        OneLineBtn->setObjectName(QStringLiteral("OneLineBtn"));
        OneLineBtn->setMinimumSize(QSize(40, 60));
        OneLineBtn->setCursor(QCursor(Qt::PointingHandCursor));
        OneLineBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(OneLineBtn);

        doubleLinBtn = new QPushButton(CPRWorkWnd);
        doubleLinBtn->setObjectName(QStringLiteral("doubleLinBtn"));
        doubleLinBtn->setMinimumSize(QSize(40, 60));
        doubleLinBtn->setCursor(QCursor(Qt::PointingHandCursor));
        doubleLinBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(doubleLinBtn);

        moreLineBtn = new QPushButton(CPRWorkWnd);
        moreLineBtn->setObjectName(QStringLiteral("moreLineBtn"));
        moreLineBtn->setMinimumSize(QSize(40, 60));
        moreLineBtn->setCursor(QCursor(Qt::PointingHandCursor));
        moreLineBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(moreLineBtn);

        horizontalSpacer_4 = new QSpacerItem(13, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        label_2 = new QLabel(CPRWorkWnd);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(1, 75));
        label_2->setMaximumSize(QSize(1, 75));
        label_2->setStyleSheet(QStringLiteral("background-color:black;"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer_5 = new QSpacerItem(13, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        UpPageBtn = new QPushButton(CPRWorkWnd);
        UpPageBtn->setObjectName(QStringLiteral("UpPageBtn"));
        UpPageBtn->setMinimumSize(QSize(40, 60));
        UpPageBtn->setCursor(QCursor(Qt::PointingHandCursor));
        UpPageBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(UpPageBtn);

        downPageBtn = new QPushButton(CPRWorkWnd);
        downPageBtn->setObjectName(QStringLiteral("downPageBtn"));
        downPageBtn->setMinimumSize(QSize(40, 60));
        downPageBtn->setCursor(QCursor(Qt::PointingHandCursor));
        downPageBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(downPageBtn);

        horizontalSpacer_6 = new QSpacerItem(17, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        label_3 = new QLabel(CPRWorkWnd);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(1, 75));
        label_3->setMaximumSize(QSize(1, 75));
        label_3->setStyleSheet(QStringLiteral("background-color:black;"));

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_7 = new QSpacerItem(17, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        hideListBtn = new QPushButton(CPRWorkWnd);
        hideListBtn->setObjectName(QStringLiteral("hideListBtn"));
        hideListBtn->setMinimumSize(QSize(40, 60));
        hideListBtn->setCursor(QCursor(Qt::PointingHandCursor));
        hideListBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(hideListBtn);

        showListBtn = new QPushButton(CPRWorkWnd);
        showListBtn->setObjectName(QStringLiteral("showListBtn"));
        showListBtn->setMinimumSize(QSize(40, 60));
        showListBtn->setCursor(QCursor(Qt::PointingHandCursor));
        showListBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(showListBtn);

        horizontalSpacer_8 = new QSpacerItem(18, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);

        label_4 = new QLabel(CPRWorkWnd);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(1, 75));
        label_4->setMaximumSize(QSize(1, 75));
        label_4->setStyleSheet(QStringLiteral("background-color:black;"));

        horizontalLayout->addWidget(label_4);

        horizontalSpacer_9 = new QSpacerItem(18, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);

        setBtn = new QPushButton(CPRWorkWnd);
        setBtn->setObjectName(QStringLiteral("setBtn"));
        setBtn->setMinimumSize(QSize(40, 60));
        setBtn->setCursor(QCursor(Qt::PointingHandCursor));
        setBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(setBtn);

        successSetBtn = new QPushButton(CPRWorkWnd);
        successSetBtn->setObjectName(QStringLiteral("successSetBtn"));
        successSetBtn->setMinimumSize(QSize(40, 60));
        successSetBtn->setCursor(QCursor(Qt::PointingHandCursor));
        successSetBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(successSetBtn);

        ManikinSetBtn = new QPushButton(CPRWorkWnd);
        ManikinSetBtn->setObjectName(QStringLiteral("ManikinSetBtn"));
        ManikinSetBtn->setMinimumSize(QSize(40, 60));
        ManikinSetBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(ManikinSetBtn);

        horizontalSpacer = new QSpacerItem(578, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        listWidget_2 = new QListWidget(CPRWorkWnd);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidget_2->sizePolicy().hasHeightForWidth());
        listWidget_2->setSizePolicy(sizePolicy);
        listWidget_2->setMinimumSize(QSize(34, 0));
        listWidget_2->setMaximumSize(QSize(34, 16777215));
        listWidget_2->setStyleSheet(QStringLiteral("border-style:solid;"));

        horizontalLayout_2->addWidget(listWidget_2);

        listWidget = new QListWidget(CPRWorkWnd);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setMinimumSize(QSize(229, 0));
        listWidget->setMaximumSize(QSize(229, 16777215));
        listWidget->setStyleSheet(QLatin1String("border-style:solid;\n"
""));

        horizontalLayout_2->addWidget(listWidget);

        stackedWidget = new QStackedWidget(CPRWorkWnd);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        stackedWidget->setMinimumSize(QSize(0, 0));
        stackedWidget->setMaximumSize(QSize(16777215, 16777215));
        stackedWidget->setStyleSheet(QStringLiteral("background-color:white;"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        stackedWidget->addWidget(page_2);

        horizontalLayout_2->addWidget(stackedWidget);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 7);
        horizontalLayout_2->setStretch(2, 33);

        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 10);

        retranslateUi(CPRWorkWnd);

        QMetaObject::connectSlotsByName(CPRWorkWnd);
    } // setupUi

    void retranslateUi(QWidget *CPRWorkWnd)
    {
        CPRWorkWnd->setWindowTitle(QApplication::translate("CPRWorkWnd", "Form", Q_NULLPTR));
        startBtn->setText(QString());
        retBtn->setText(QString());
        label->setText(QString());
        OneLineBtn->setText(QString());
        doubleLinBtn->setText(QString());
        moreLineBtn->setText(QString());
        label_2->setText(QString());
        UpPageBtn->setText(QString());
        downPageBtn->setText(QString());
        label_3->setText(QString());
        hideListBtn->setText(QString());
        showListBtn->setText(QString());
        label_4->setText(QString());
        setBtn->setText(QString());
        successSetBtn->setText(QString());
        ManikinSetBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CPRWorkWnd: public Ui_CPRWorkWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPRWORKWND_H
