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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SCWnd
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QWidget *widget;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *searchLineEdit;
    QPushButton *searthBtn;
    QLabel *label_2;
    QTableView *tableView;

    void setupUi(QWidget *SCWnd)
    {
        if (SCWnd->objectName().isEmpty())
            SCWnd->setObjectName(QStringLiteral("SCWnd"));
        SCWnd->resize(1014, 672);
        gridLayout = new QGridLayout(SCWnd);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(SCWnd);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 20));
        label->setMaximumSize(QSize(244, 16777215));
        label->setStyleSheet(QLatin1String("font-family: PingFangSC-Regular;\n"
"font-size: 14px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #b6b8c4;"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        widget = new QWidget(SCWnd);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QStringLiteral("background-color:white;"));

        gridLayout->addWidget(widget, 0, 1, 4, 1);

        widget_2 = new QWidget(SCWnd);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMaximumSize(QSize(244, 28));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        searchLineEdit = new QLineEdit(widget_2);
        searchLineEdit->setObjectName(QStringLiteral("searchLineEdit"));
        searchLineEdit->setMinimumSize(QSize(0, 28));
        searchLineEdit->setMaximumSize(QSize(208, 16777215));
        searchLineEdit->setStyleSheet(QLatin1String("\n"
"border-style:solid;\n"
"border:1px solid #7d7d7d;\n"
"border-right:1px solid #11111111;\n"
"\n"
"font-family: PingFangSC-Regular;\n"
"font-size: 14px;\n"
"font-weight: normal;;\n"
"line-height: 70px;\n"
"color: #d7d7d7;"));

        horizontalLayout->addWidget(searchLineEdit);

        searthBtn = new QPushButton(widget_2);
        searthBtn->setObjectName(QStringLiteral("searthBtn"));
        searthBtn->setMinimumSize(QSize(28, 28));
        searthBtn->setMaximumSize(QSize(36, 16777215));
        searthBtn->setCursor(QCursor(Qt::PointingHandCursor));
        searthBtn->setStyleSheet(QLatin1String("\n"
"border-style:solid;\n"
"border:1px solid #7d7d7d;\n"
"border-left:1px solid #11111111;\n"
"image:url(:/image/search_button.png);"));

        horizontalLayout->addWidget(searthBtn);


        gridLayout->addWidget(widget_2, 1, 0, 1, 1);

        label_2 = new QLabel(SCWnd);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(0, 20));
        label_2->setMaximumSize(QSize(244, 16777215));
        label_2->setStyleSheet(QLatin1String("font-family: PingFangSC-Regular;\n"
"font-size: 14px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #21b0f2;"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        tableView = new QTableView(SCWnd);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setMaximumSize(QSize(244, 16777215));

        gridLayout->addWidget(tableView, 3, 0, 1, 1);


        retranslateUi(SCWnd);

        QMetaObject::connectSlotsByName(SCWnd);
    } // setupUi

    void retranslateUi(QWidget *SCWnd)
    {
        SCWnd->setWindowTitle(QApplication::translate("SCWnd", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("SCWnd", "\346\250\241\346\213\237\344\272\272\345\210\227\350\241\250", Q_NULLPTR));
        searthBtn->setText(QString());
        label_2->setText(QApplication::translate("SCWnd", "\346\250\241\346\213\237\344\272\272    \345\247\223\345\220\215    \346\210\220\347\273\251", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SCWnd: public Ui_SCWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCWND_H
