#include "setsyswnd.h"
#include "ui_setsyswnd.h"

countWidget::countWidget(QWidget *parent, int Count):
    QWidget(parent),currentCount(0)
{
    totalCount = Count;

    addBtn = new QPushButton(this);addBtn->setGeometry(0,0,30,30);
    addBtn->setStyleSheet(QString("border-style:solid;image:url(:/image/up.png)"));

    numLa = new QLabel(this);numLa->setGeometry(3,30,40,30);
    numLa->setStyleSheet(QString("font-family: PingFangSC-Regular;font-size: 24px;font-weight: normal;line-height: 70px;color: #21b0f2;"));
    numLa->setText(IntToQString());

    reduceBtn = new QPushButton(this);reduceBtn->setGeometry(0,60,30,30);
    reduceBtn->setStyleSheet(QString("border-style:solid;image:url(:/image/down.png)"));

    connect(addBtn,SIGNAL(clicked()),this,SLOT(addBtnClickedEvent()));
    connect(reduceBtn,SIGNAL(clicked()),this,SLOT(reduceBtnClickedEvent()));

}

void countWidget::setText(int num)
{
    currentCount = num;
    numLa->setText(IntToQString());
}

QString countWidget::IntToQString()
{
    QString num;
    if((0<=currentCount)&&(currentCount<=9)){
        num = QString("0")+QString::number(currentCount);
    }
    else{
        num = QString::number(currentCount);
    }
    return num;
}

void countWidget::addBtnClickedEvent()
{
     currentCount++;
     if(currentCount>=totalCount){
         currentCount = 0;
         numLa->setText(IntToQString());
         return;
     }
     else{
        numLa->setText(IntToQString());
     }
}

void countWidget::reduceBtnClickedEvent()
{
    currentCount--;
    if((currentCount<0)||(currentCount == 0)){
        currentCount = 0;
        numLa->setText(IntToQString());
        return;
    }
    else{
        numLa->setText(IntToQString());
    }
}















SetSysWnd::SetSysWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetSysWnd)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉标题栏

    pressSpeachitem1 = new countWidget(this);
    pressSpeachitem1->move(250,210);
    pressSpeachitem2 = new countWidget(this);
    pressSpeachitem2->move(350,210);

    pressdeep1 = new countWidget(this);
    pressdeep1->move(630,210);
    pressdeep2 = new countWidget(this);
    pressdeep2->move(730,210);

    VLTime1 = new countWidget(this);
    VLTime1->move(250,435);
    VLTime2 = new countWidget(this);
    VLTime2->move(350,435);

    VLBulk1 = new countWidget(this);
    VLBulk1->move(630,435);
    VLBulk2 = new countWidget(this);
    VLBulk2->move(730,435);

}

SetSysWnd::~SetSysWnd()
{
    delete ui;
}

void SetSysWnd::on_cancelBtn_clicked()
{
    this->close();
}

void SetSysWnd::on_closeBtn_clicked()
{
    this->close();
}

void SetSysWnd::mousePressEvent (QMouseEvent *event)
{
   this->xOffset = event->globalPos().rx() - this->pos().rx();
   this->yOffset = event->globalPos().ry() - this->pos().ry();
}

void SetSysWnd::mouseMoveEvent(QMouseEvent * event)
{
  if((event->buttons() == Qt::LeftButton)&&((0<event->pos().ry())&&(event->pos().ry()<60))){
     this->move(event->globalX()-this->xOffset,event->globalY()-this->yOffset);
  }
}

