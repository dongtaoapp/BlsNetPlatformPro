#include "showmorelinewnd.h"
#include "cprworkdefin.h"
#include <QDebug>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QLabel>


MoreWnd::MoreWnd(QWidget *parent):
    QTableView(parent)
{
    this->setShowGrid(false);
    this->setFocusPolicy(Qt::NoFocus);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->verticalHeader()->hide();
    this->horizontalHeader()->hide();
    this->setStyleSheet(QString("border-style:solid;"));

    m_model = new QStandardItemModel();
    m_model->setColumnCount(2);
    TabInit();
}

void MoreWnd::TabInit()
{
    QStandardItem *item1 = new QStandardItem();
    m_model->setItem(0,0,item1);
    QStandardItem *item2 = new QStandardItem();
    m_model->setItem(0,1,item2);
    QStandardItem *item3 = new QStandardItem();
    m_model->setItem(1,0,item3);
    QStandardItem *item4 = new QStandardItem();
    m_model->setItem(1,1,item4);
    QStandardItem *item5 = new QStandardItem();
    m_model->setItem(2,0,item5);
    QStandardItem *item6 = new QStandardItem();
    m_model->setItem(2,1,item6);
    this->setModel(m_model);

    for(int i = 0;i<3;i++){
         QMTabwnd *btn = new QMTabwnd();
         btn->setIndexNum(i+1);
         this->setIndexWidget(m_model->index(i,0),btn);
         btnList.append(btn);
         QMTabwnd *btn1 = new QMTabwnd();
         btn->setIndexNum(i+2);
         btnList.append(btn1);
         this->setIndexWidget(m_model->index(i,1),btn1);
    }

}

void MoreWnd::resizeEvent(QResizeEvent *event)
{
    qDebug()<<__FUNCTION__<<event->size().width()<<event->size().height();
    this->verticalHeader()->setDefaultSectionSize(event->size().height()/3.0);
    this->setColumnWidth(0,event->size().width()/2.0);
    this->setColumnWidth(1,event->size().width()/2.0);

}



showMoreLineWnd::showMoreLineWnd(QWidget *parent):
    ShowLineBaseWnd(parent)
{
    time = new QLabel(this);time->setAlignment(Qt::AlignCenter);time->setGeometry(30,5,1130,41);
    time->setStyleSheet(QString("border-style:solid;border:1px solid rgba(0, 0, 0, 0.5);font-family: PingFangSC-Regular;font-size: 18px;font-weight: 900;color: #88857e;"));
    time->setText("00:00:25");

    m_tabwnd = new MoreWnd(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(time,2);
    layout->addWidget(m_tabwnd,40);
    layout->setMargin(10);
    layout->setSpacing(30);
    this->setLayout(layout);
}




