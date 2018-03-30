#include "setsuccesswnd.h"
#include "ui_setsuccesswnd.h"
#include "cprworkdefin.h"
#include <qDebug>
SetSuccessWnd::SetSuccessWnd(QWidget *parent) :
    QDialog(parent),workModel(-1),
    ui(new Ui::SetSuccessWnd)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉标题栏
    workTime1 = new countWidget(this,60);workTime1->move(60,200);
    workTime2 = new countWidget(this,60);workTime2->move(160,200);
    breakTime = new countWidget(this,60);breakTime->move(370,200);
    pressTimePrecent = new countWidget(this,100);pressTimePrecent->move(620,200);
    pressRightPrecent = new countWidget(this,100);pressRightPrecent->move(910,200);
    blowRightPrecent = new countWidget(this,100);blowRightPrecent->move(100,460);
    pressfrequencyPrecent = new countWidget(this,100);pressfrequencyPrecent->move(420,460);

    btngroup.addButton(ui->popularizeBtn,Popularize);btngroup.addButton(ui->acbtn,Practice);
    connect(&btngroup,SIGNAL(buttonClicked(int)),this,SLOT(BtnClickedEvent(int)));

}

SetSuccessWnd::~SetSuccessWnd()
{
    delete ui;
}

void SetSuccessWnd::on_cancelBtn_clicked()
{
    this->close();
}
void SetSuccessWnd::on_saveBtn_clicked()
{
    //TODO 保存
    qDebug()<<__FUNCTION__;
}
void SetSuccessWnd::BtnClickedEvent(int ID)
{
    ui->acbtn->setStyleSheet(BtnNoclicked);ui->popularizeBtn->setStyleSheet(BtnNoclicked);
    if(ID == Popularize){ui->popularizeBtn->setStyleSheet(BtnClicked);}if(ID==Practice){ui->acbtn->setStyleSheet(BtnClicked);}
    workModel = ID;
}
void SetSuccessWnd::on_closeBtn_clicked()
{
    this->close();
}
void SetSuccessWnd::mousePressEvent (QMouseEvent *event)
{
   this->xOffset = event->globalPos().rx() - this->pos().rx();
   this->yOffset = event->globalPos().ry() - this->pos().ry();
}
void SetSuccessWnd::mouseMoveEvent(QMouseEvent * event)
{
  if((event->buttons() == Qt::LeftButton)&&((0<event->pos().ry())&&(event->pos().ry()<60))){
     this->move(event->globalX()-this->xOffset,event->globalY()-this->yOffset);
  }
}


