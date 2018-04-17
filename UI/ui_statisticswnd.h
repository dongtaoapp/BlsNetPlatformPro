/********************************************************************************
** Form generated from reading UI file 'statisticswnd.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTICSWND_H
#define UI_STATISTICSWND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatisticsWnd
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *PrintBtn;
    QPushButton *SaveBtn;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *PieBtn;
    QPushButton *BarBtn;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *InfoLa;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *searchEdit;
    QPushButton *searchBtn;
    QLabel *label_2;
    QTableView *tableView;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;

    void setupUi(QWidget *StatisticsWnd)
    {
        if (StatisticsWnd->objectName().isEmpty())
            StatisticsWnd->setObjectName(QStringLiteral("StatisticsWnd"));
        StatisticsWnd->resize(999, 749);
        StatisticsWnd->setStyleSheet(QStringLiteral(""));
        verticalLayout_2 = new QVBoxLayout(StatisticsWnd);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        PrintBtn = new QPushButton(StatisticsWnd);
        PrintBtn->setObjectName(QStringLiteral("PrintBtn"));
        PrintBtn->setMinimumSize(QSize(48, 75));
        PrintBtn->setMaximumSize(QSize(48, 16777215));
        PrintBtn->setCursor(QCursor(Qt::PointingHandCursor));
        PrintBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(PrintBtn);

        SaveBtn = new QPushButton(StatisticsWnd);
        SaveBtn->setObjectName(QStringLiteral("SaveBtn"));
        SaveBtn->setMinimumSize(QSize(48, 75));
        SaveBtn->setMaximumSize(QSize(48, 75));
        SaveBtn->setCursor(QCursor(Qt::PointingHandCursor));
        SaveBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(SaveBtn);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(StatisticsWnd);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(1, 75));
        label->setMaximumSize(QSize(1, 75));
        label->setStyleSheet(QStringLiteral("background-color:black;"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        PieBtn = new QPushButton(StatisticsWnd);
        PieBtn->setObjectName(QStringLiteral("PieBtn"));
        PieBtn->setMinimumSize(QSize(48, 75));
        PieBtn->setMaximumSize(QSize(48, 75));
        PieBtn->setCursor(QCursor(Qt::PointingHandCursor));
        PieBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(PieBtn);

        BarBtn = new QPushButton(StatisticsWnd);
        BarBtn->setObjectName(QStringLiteral("BarBtn"));
        BarBtn->setMinimumSize(QSize(48, 75));
        BarBtn->setMaximumSize(QSize(48, 75));
        BarBtn->setCursor(QCursor(Qt::PointingHandCursor));
        BarBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(BarBtn);

        horizontalSpacer_3 = new QSpacerItem(1138, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        InfoLa = new QLabel(StatisticsWnd);
        InfoLa->setObjectName(QStringLiteral("InfoLa"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(InfoLa->sizePolicy().hasHeightForWidth());
        InfoLa->setSizePolicy(sizePolicy);
        InfoLa->setMinimumSize(QSize(266, 40));
        InfoLa->setMaximumSize(QSize(266, 40));
        InfoLa->setStyleSheet(QLatin1String("font-family: PingFangSC-Regular;\n"
"font-size: 14px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #b6b8c4;"));

        verticalLayout->addWidget(InfoLa);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        searchEdit = new QLineEdit(StatisticsWnd);
        searchEdit->setObjectName(QStringLiteral("searchEdit"));
        sizePolicy.setHeightForWidth(searchEdit->sizePolicy().hasHeightForWidth());
        searchEdit->setSizePolicy(sizePolicy);
        searchEdit->setMinimumSize(QSize(230, 41));
        searchEdit->setMaximumSize(QSize(230, 41));
        searchEdit->setStyleSheet(QLatin1String("border-style:solid;\n"
"border-left:1px solid #7d7d7d;\n"
"border-top:1px solid #7d7d7d;\n"
"border-bottom:1px solid #7d7d7d;\n"
"\n"
"border-left:1px solid white;\n"
"font-family: PingFangSC-Regular;\n"
"font-size: 14px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #d7d7d7;"));

        horizontalLayout_2->addWidget(searchEdit);

        searchBtn = new QPushButton(StatisticsWnd);
        searchBtn->setObjectName(QStringLiteral("searchBtn"));
        sizePolicy.setHeightForWidth(searchBtn->sizePolicy().hasHeightForWidth());
        searchBtn->setSizePolicy(sizePolicy);
        searchBtn->setMinimumSize(QSize(41, 41));
        searchBtn->setCursor(QCursor(Qt::PointingHandCursor));
        searchBtn->setStyleSheet(QLatin1String("border-style:solid;\n"
"background-color:#2c2e43;\n"
"border-right:1px solid #7d7d7d;\n"
"border-top:1px solid #7d7d7d;\n"
"border-bottom:1px solid #7d7d7d;\n"
"image:url(:/image/search_button.png);\n"
""));

        horizontalLayout_2->addWidget(searchBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        label_2 = new QLabel(StatisticsWnd);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(266, 30));
        label_2->setMaximumSize(QSize(266, 30));
        label_2->setStyleSheet(QLatin1String("font-family: PingFangSC-Regular;\n"
"font-size: 14px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #21b0f2;"));
        label_2->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        verticalLayout->addWidget(label_2);

        tableView = new QTableView(StatisticsWnd);
        tableView->setObjectName(QStringLiteral("tableView"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy1);
        tableView->setMinimumSize(QSize(266, 0));
        tableView->setMaximumSize(QSize(266, 16777215));

        verticalLayout->addWidget(tableView);


        horizontalLayout_3->addLayout(verticalLayout);

        stackedWidget = new QStackedWidget(StatisticsWnd);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy2);
        stackedWidget->setMinimumSize(QSize(0, 0));
        stackedWidget->setStyleSheet(QStringLiteral("background-color:white;"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        stackedWidget->addWidget(page_2);

        horizontalLayout_3->addWidget(stackedWidget);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 4);

        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 10);

        retranslateUi(StatisticsWnd);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(StatisticsWnd);
    } // setupUi

    void retranslateUi(QWidget *StatisticsWnd)
    {
        StatisticsWnd->setWindowTitle(QApplication::translate("StatisticsWnd", "Form", Q_NULLPTR));
        PrintBtn->setText(QString());
        SaveBtn->setText(QString());
        label->setText(QString());
        PieBtn->setText(QString());
        BarBtn->setText(QString());
        InfoLa->setText(QApplication::translate("StatisticsWnd", "  \346\250\241\346\213\237\344\272\272\345\210\227\350\241\250", Q_NULLPTR));
        searchBtn->setText(QString());
        label_2->setText(QApplication::translate("StatisticsWnd", "       \346\250\241\346\213\237\344\272\272       \345\247\223\345\220\215     \346\210\220\347\273\251", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class StatisticsWnd: public Ui_StatisticsWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTICSWND_H
