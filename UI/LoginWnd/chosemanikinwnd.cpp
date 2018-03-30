#include "chosemanikinwnd.h"

ChoseManikinWnd::ChoseManikinWnd(QWidget *parent):
    QStackedWidget(parent)
{
    this->resize(600,650);
    this->setObjectName("ChoseManikinWnd");
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);


    RMwnd = new RegisterManikinWnd();
    addMwnd = new addManikinWnd();
    this->insertWidget(RMWND,RMwnd);
    this->insertWidget(ADDMWND,addMwnd);


    this->setStyleSheet(QString("background-color:#2c2e43"));
    connect(addMwnd,SIGNAL(backSignal()),this,SLOT(backEvent()));
    connect(RMwnd,SIGNAL(addManikin()),this,SLOT(addManikinEvent()));
    connect(RMwnd,SIGNAL(ConManikin()),this,SLOT(ConManikinEvent()));
    connect(addMwnd,SIGNAL(addManikin(QString)),RMwnd,SLOT(addManikinList(QString)));

    this->setStyleSheet(QString("QStackedWidget#ChoseManikinWnd{image:url(:/image/ChoseManikinBackground.png)}"));
}

void ChoseManikinWnd::addManikinEvent()
{
    this->setCurrentIndex(ADDMWND);
}

void ChoseManikinWnd::backEvent()
{
    this->setCurrentIndex(RMWND);
    RMwnd->InitTableView();
}

void ChoseManikinWnd::ConManikinEvent()
{
    RemarkList = RMwnd->GetRemarkList();
    emit ConManikins();
}


