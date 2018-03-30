#include "showdoublelinewnd.h"
#include "cprworkdefin.h"
#include <QLabel>
#include <QHBoxLayout>
#include <qDebug>
ShowDoubleLineWnd::ShowDoubleLineWnd(QWidget *parent) :
    ShowLineBaseWnd(parent)
{
   time = new QLabel(this);time->setGeometry(10,5,1150,41);time->setAlignment(Qt::AlignCenter);
   time->setStyleSheet(QString("border-style:solid;border:1px solid rgba(0, 0, 0, 0.5);font-family: PingFangSC-Regular;font-size: 18px;font-weight: 900;color: #88857e;"));
   time->setText("00:00:25");
   m_listWnd = new QListWidget(this);
   m_listWnd->setStyleSheet(QString("border-style:solid"));
   m_listWnd->setGeometry(10,60,1150,660);

   TabItemInit();


}

void ShowDoubleLineWnd::TabItemInit()
{
    item1 = new QListWidgetItem(m_listWnd);
    item1->setSizeHint(QSize(1150,330));
    QMTabDoubleWnd *wnd1 = new QMTabDoubleWnd();
    doubleLineWnd_List.append(wnd1);
    m_listWnd->setItemWidget(item1,wnd1);

    item2 = new QListWidgetItem(m_listWnd);
    item2->setSizeHint(QSize(1150,330));
    QMTabDoubleWnd *wnd2 = new QMTabDoubleWnd();
    doubleLineWnd_List.append(wnd2);
    m_listWnd->setItemWidget(item2,wnd2);
}

void ShowDoubleLineWnd::UpPageEvent()
{

}

void ShowDoubleLineWnd::DownPageEvent()
{

}

void ShowDoubleLineWnd::GetManikinData(QVariant data)
{

}

void ShowDoubleLineWnd::listWndState(bool show)
{
    if(!show){
       m_listWnd->setGeometry(30,60,1350,660);
       item1->setSizeHint(QSize(1350,291));item2->setSizeHint(QSize(1350,330));
       time->setGeometry(30,5,1350,41);
    }
    else if(show){
        m_listWnd->setGeometry(10,60,1150,660);
        item1->setSizeHint(QSize(1150,291));item2->setSizeHint(QSize(1150,330));;
        time->setGeometry(10,5,1150,41);
    }
}
