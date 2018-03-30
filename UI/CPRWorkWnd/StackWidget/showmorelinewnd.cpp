#include "showmorelinewnd.h"
#include "cprworkdefin.h"
#include <QDebug>
#include <QHeaderView>
#include <QGridLayout>
#include <QLabel>
showMoreLineWnd::showMoreLineWnd(QWidget *parent):
    ShowLineBaseWnd(parent)
{
    time = new QLabel(this);time->setAlignment(Qt::AlignCenter);time->setGeometry(30,5,1130,41);
    time->setStyleSheet(QString("border-style:solid;border:1px solid rgba(0, 0, 0, 0.5);font-family: PingFangSC-Regular;font-size: 18px;font-weight: 900;color: #88857e;"));
    time->setText("00:00:25");


    m_tabwnd = new QTableView(this);
    m_tabwnd->setShowGrid(false);
    m_tabwnd->setFocusPolicy(Qt::NoFocus);
    m_tabwnd->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tabwnd->verticalHeader()->hide();
    m_tabwnd->horizontalHeader()->hide();
    m_tabwnd->setStyleSheet(QString("border-style:solid"));
    m_tabwnd->setGeometry(30,60,1440,751);


    m_model = new QStandardItemModel();
    m_model->setColumnCount(2);
    TabWndInit();
}

void showMoreLineWnd::TabWndInit()
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
    m_tabwnd->setModel(m_model);

    for(int i = 0;i<3;i++){
         QMTabwnd *btn = new QMTabwnd();
         btn->setIndexNum(i+1);
         m_tabwnd->setIndexWidget(m_model->index(i,0),btn);
         btnList.append(btn);
         QMTabwnd *btn1 = new QMTabwnd();
         btn->setIndexNum(i+2);
         btnList.append(btn1);
         m_tabwnd->setIndexWidget(m_model->index(i,1),btn1);
    }


    m_tabwnd->verticalHeader()->setDefaultSectionSize(220);
    m_tabwnd->setColumnWidth(0,565);
    m_tabwnd->setColumnWidth(1,565);
}

void showMoreLineWnd::UpPageEvent()
{

}

void showMoreLineWnd::DownPageEvent()
{

}

void showMoreLineWnd::GetManikinData(QVariant data)
{

}

void showMoreLineWnd::listWndState(bool show)
{
    if(!show){
        time->setGeometry(30,5,1350,41);
        m_tabwnd->move(30,60);
        m_tabwnd->verticalHeader()->setDefaultSectionSize(220);
        m_tabwnd->setColumnWidth(0,700);
        m_tabwnd->setColumnWidth(1,650);
    }
    else if(show){
        time->setGeometry(30,5,1130,41);
        m_tabwnd->move(30,60);
        m_tabwnd->verticalHeader()->setDefaultSectionSize(220);
        m_tabwnd->setColumnWidth(0,565);
        m_tabwnd->setColumnWidth(1,565);

    }
}
