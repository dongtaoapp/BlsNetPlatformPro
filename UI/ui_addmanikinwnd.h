/********************************************************************************
** Form generated from reading UI file 'addmanikinwnd.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDMANIKINWND_H
#define UI_ADDMANIKINWND_H

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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addManikinWnd
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *ManikinEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *returnBtn;
    QPushButton *okBtn;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *addManikinWnd)
    {
        if (addManikinWnd->objectName().isEmpty())
            addManikinWnd->setObjectName(QStringLiteral("addManikinWnd"));
        addManikinWnd->resize(430, 516);
        addManikinWnd->setStyleSheet(QLatin1String("QPushButton{\n"
"	border-style:solid;\n"
"	width: 81px;\n"
"	height: 30px;\n"
"	background-color: #21b0f2;\n"
"	border-radius: 2px;\n"
"	width: 33px;\n"
"	height: 16px;\n"
"	font-family: PingFangSC-Regular;\n"
"	font-size: 16px;\n"
"	font-weight: normal;\n"
"	line-height: 70px;\n"
"	color: #ffffff;\n"
"}"));
        gridLayout = new QGridLayout(addManikinWnd);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(60, 60, 60, 60);
        verticalSpacer_2 = new QSpacerItem(20, 62, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(addManikinWnd);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setStyleSheet(QLatin1String("width: 96px;\n"
"height: 17px;\n"
"font-family: PingFangSC-Regular;\n"
"font-size: 18px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #b6b8c4;"));

        verticalLayout->addWidget(label);

        ManikinEdit = new QLineEdit(addManikinWnd);
        ManikinEdit->setObjectName(QStringLiteral("ManikinEdit"));
        sizePolicy.setHeightForWidth(ManikinEdit->sizePolicy().hasHeightForWidth());
        ManikinEdit->setSizePolicy(sizePolicy);
        ManikinEdit->setStyleSheet(QLatin1String("width: 71px;\n"
"height: 14px;\n"
"font-family: PingFangSC-Regular;\n"
"font-size: 18px;\n"
"font-weight: normal;\n"
"line-height: 70px;\n"
"color: #b6b8c4;"));

        verticalLayout->addWidget(ManikinEdit);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 143, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(60);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        returnBtn = new QPushButton(addManikinWnd);
        returnBtn->setObjectName(QStringLiteral("returnBtn"));
        returnBtn->setMinimumSize(QSize(40, 40));
        returnBtn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(returnBtn);

        okBtn = new QPushButton(addManikinWnd);
        okBtn->setObjectName(QStringLiteral("okBtn"));
        okBtn->setMinimumSize(QSize(40, 40));
        okBtn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(okBtn);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 72, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 4, 0, 1, 1);


        retranslateUi(addManikinWnd);

        QMetaObject::connectSlotsByName(addManikinWnd);
    } // setupUi

    void retranslateUi(QWidget *addManikinWnd)
    {
        addManikinWnd->setWindowTitle(QApplication::translate("addManikinWnd", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("addManikinWnd", "\350\276\223\345\205\245\346\240\207\350\257\206\347\240\201", Q_NULLPTR));
        returnBtn->setText(QApplication::translate("addManikinWnd", "\350\277\224\345\233\236", Q_NULLPTR));
        okBtn->setText(QApplication::translate("addManikinWnd", "\347\241\256\350\256\244", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class addManikinWnd: public Ui_addManikinWnd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDMANIKINWND_H
