#include "qmtabwnd.h"

QMTabwnd::QMTabwnd(QWidget *parent):
    QPushButton(parent),indexNum(0)
{
    this->setStyleSheet(QString("font-family: Montserrat-Bold;\
                                font-size: 30px;\
                                font-weight: normal;\
                                line-height: 70px;\
                                border:1px solid #d8d9d9;"));
    this->setText("MoreLine");
}
void QMTabwnd::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        emit MDoubleClicked(Remark);
    }
}
