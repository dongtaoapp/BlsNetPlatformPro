#include "showdoublelinewnd.h"
#include "cprworkdefin.h"
#include <QLabel>
#include <QVBoxLayout>
#include <qDebug>
DoubleWnd::DoubleWnd(QWidget *parent) :
    QListWidget(parent)
{
    this->setStyleSheet(QString("border-style:solid"));
    item1 = new QListWidgetItem(this);
    wnd1 = new QMTabDoubleWnd();
    doubleLineWnd_List.append(wnd1);

    item2 = new QListWidgetItem(this);
    wnd2 = new QMTabDoubleWnd();
    doubleLineWnd_List.append(wnd2);

}

void DoubleWnd::resizeEvent(QResizeEvent *event)
{
    item1->setSizeHint(QSize(event->size().width(),event->size().height()/2.0));
    this->setItemWidget(item1,wnd1);
    item2->setSizeHint(QSize(event->size().width(),event->size().height()/2.0));
    this->setItemWidget(item2,wnd2);
}






ShowDoubleLineWnd::ShowDoubleLineWnd(QWidget *parent) :
    ShowLineBaseWnd(parent)
{
   time = new QLabel(this);time->setAlignment(Qt::AlignCenter);
   time->setStyleSheet(QString("border-style:solid;border:1px solid rgba(0, 0, 0, 0.5);font-family: PingFangSC-Regular;font-size: 18px;font-weight: 900;color: #88857e;"));
   time->setText("00:00:25");
   m_listWnd = new DoubleWnd(this);
   QVBoxLayout *hlayout = new QVBoxLayout();
   hlayout->addWidget(time,2);
   hlayout->addWidget(m_listWnd,40);
   hlayout->setMargin(10);
   hlayout->setSpacing(30);
   this->setLayout(hlayout);



}
