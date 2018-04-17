#include "qrunningtimewnd.h"
#include <QPainter>

QRunningTimeWnd::QRunningTimeWnd(QWidget *parent) : QWidget(parent)
{

}

void QRunningTimeWnd::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.fillRect(0,0,this->width(),this->height(),QBrush(QColor(172,176,181)));

    int nTick = (this->width()-58)/6;
    for(int i = 0; i < 6 ; i++)
    {
        int nX = this->width()-58-nTick*i;
        p.drawLine(nX,0,nX,this->height());
    }
}
