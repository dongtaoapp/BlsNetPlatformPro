#include "showlistwnd.h"
#include <QPainter>
//#include <QtCore/qmath.h>
//#include <QPainterPath>
#include <QStyleOption>
#include <qDebug>
#define HInterval 30
#define VInterval 20
#define ITemWidth 440
#define ITemHeight 201
#define HeadWidth  60
showListWnd::showListWnd(QWidget *parent):
    ShowLineBaseWnd(parent)
{
    this->setStyleSheet(QString("background-color:white"));
    InitWnd();
}

void showListWnd::InitWnd()
{
    QMlistWnd *item1 = new QMlistWnd(this,QMlistWnd::WhiteBlackground);
   item1->setGeometry(HInterval,VInterval+HeadWidth,ITemWidth,ITemHeight);
    item_list.append(item1);

    QMlistWnd *item2 = new QMlistWnd(this,QMlistWnd::WhiteBlackground);
    item2->setGeometry(HInterval*2+ITemWidth,VInterval+HeadWidth,ITemWidth,ITemHeight);
    item_list.append(item2);

    QMlistWnd *item3 = new QMlistWnd(this,QMlistWnd::WhiteBlackground);
    item3->setGeometry(HInterval*3+ITemWidth*2,VInterval+HeadWidth,ITemWidth,ITemHeight);
    item_list.append(item3);

    QMlistWnd *item4 = new QMlistWnd(this,QMlistWnd::WhiteBlackground);
    item4->setGeometry(HInterval,VInterval*2+ITemHeight+HeadWidth,ITemWidth,ITemHeight);
    item_list.append(item4);

    QMlistWnd *item5 = new QMlistWnd(this,QMlistWnd::WhiteBlackground);
    item5->setGeometry(HInterval*2+ITemWidth,VInterval*2+ITemHeight+HeadWidth,ITemWidth,ITemHeight);
    item_list.append(item5);

    QMlistWnd *item6 = new QMlistWnd(this,QMlistWnd::WhiteBlackground);
    item6->setGeometry(HInterval*3+ITemWidth*2,VInterval*2+ITemHeight+HeadWidth,ITemWidth,ITemHeight);
    item_list.append(item6);

    QMlistWnd *item7 = new QMlistWnd(this,QMlistWnd::WhiteBlackground);
    item7->setGeometry(HInterval,VInterval*3+ITemHeight*2+HeadWidth,ITemWidth,ITemHeight);
    item_list.append(item7);

    QMlistWnd *item8 = new QMlistWnd(this,QMlistWnd::WhiteBlackground);
    item8->setGeometry(HInterval*2+ITemWidth,VInterval*3+ITemHeight*2+HeadWidth,ITemWidth,ITemHeight);
    item_list.append(item8);

    QMlistWnd *item9 = new QMlistWnd(this,QMlistWnd::WhiteBlackground);
    item9->setGeometry(HInterval*3+ITemWidth*2,VInterval*3+ITemHeight*2+HeadWidth,ITemWidth,ITemHeight);
    item_list.append(item9);

    connect(item1,SIGNAL(clicked(bool)),this,SLOT(ItemClicked()));connect(item1,SIGNAL(MDoubleClicked(QString)),this,SLOT(ItemDoubleClicked(QString)));
    connect(item2,SIGNAL(clicked(bool)),this,SLOT(ItemClicked()));connect(item2,SIGNAL(MDoubleClicked(QString)),this,SLOT(ItemDoubleClicked(QString)));
    connect(item3,SIGNAL(clicked(bool)),this,SLOT(ItemClicked()));connect(item3,SIGNAL(MDoubleClicked(QString)),this,SLOT(ItemDoubleClicked(QString)));
    connect(item4,SIGNAL(clicked(bool)),this,SLOT(ItemClicked()));connect(item4,SIGNAL(MDoubleClicked(QString)),this,SLOT(ItemDoubleClicked(QString)));
    connect(item5,SIGNAL(clicked(bool)),this,SLOT(ItemClicked()));connect(item5,SIGNAL(MDoubleClicked(QString)),this,SLOT(ItemDoubleClicked(QString)));
    connect(item6,SIGNAL(clicked(bool)),this,SLOT(ItemClicked()));connect(item6,SIGNAL(MDoubleClicked(QString)),this,SLOT(ItemDoubleClicked(QString)));
    connect(item7,SIGNAL(clicked(bool)),this,SLOT(ItemClicked()));connect(item7,SIGNAL(MDoubleClicked(QString)),this,SLOT(ItemDoubleClicked(QString)));
    connect(item8,SIGNAL(clicked(bool)),this,SLOT(ItemClicked()));connect(item8,SIGNAL(MDoubleClicked(QString)),this,SLOT(ItemDoubleClicked(QString)));
    connect(item9,SIGNAL(clicked(bool)),this,SLOT(ItemClicked()));connect(item9,SIGNAL(MDoubleClicked(QString)),this,SLOT(ItemDoubleClicked(QString)));

    ItemClicked();

}

void showListWnd::GetManikinData(QVariant data)
{

}

void showListWnd::UpPageEvent()
{

}

void showListWnd::DownPageEvent()
{

}

void showListWnd::ItemClicked()
{
    foreach(QMlistWnd *wnd, item_list){
        wnd->sheet();
    }
    if(QObject::sender() != 0){
        static_cast<QMlistWnd *>(QObject::sender())->clickedSheet();
    }
}

void showListWnd::ItemDoubleClicked(QString remark)
{
    if(remark.isEmpty()){
        return;
    }
    emit ManikinDoubleClicked(remark);
}


void showListWnd::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
