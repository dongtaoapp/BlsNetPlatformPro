#include "showonelinewnd.h"
#include <QLabel>
#include <qDebug>
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>
#include <QHBoxLayout>
#define HeadLaSheet "image:url(:/image/Head.png);background-color:rgba(0, 0, 0, 0);"
#define HeadLaNoSheet "image:url(:/image/HeadNo.png);background-color:rgba(0, 0, 0, 0);"
#define FingerSheet "image:url(:/image/Finger.png);background-color:rgba(0, 0, 0, 0);"
#define FingerNoSheet "image:url(:/image/FingerNo.png);background-color:rgba(0, 0, 0, 0);"
#define bodySheet "image:url(:/image/body.png);background-color:rgba(0, 0, 0, 0);"
#define LaSheet "image:url(:/image/la.png);background-color:rgba(0, 0, 0, 0);font-family: PingFangSC-Medium;font-weight: 900;color: #ffffff;"
#define LaNoSheet "image:url(:/image/laNo.png);background-color:rgba(0, 0, 0, 0);font-family: PingFangSC-Medium;font-weight: 900;color: #ffffff;"
#define PressLaSheet "image:url(:/image/press.png);background-color:rgba(0, 0, 0, 0);"
#define PressLaNoSheet "image:url(:/image/pressNo.png);background-color:rgba(0, 0, 0, 0);"
#define pushLaNoSheet "image:url(:/image/pushNo.png);background-color:rgba(0, 0, 0, 0);"
#define pushLaSheet "image:url(:/image/push.png);background-color:rgba(0, 0, 0, 0);"
#define callLaNoSheet "image:url(:/image/callNo.png);background-color:rgba(0, 0, 0, 0);"
#define callLaSheet "image:url(:/image/call.png);background-color:rgba(0, 0, 0, 0);"
#define fiLaNoSheet "image:url(:/image/fiNo.png);background-color:rgba(0, 0, 0, 0);"
#define fileSheet "image:url(:/image/fi.png);background-color:rgba(0, 0, 0, 0);"
#define handNoSheet "image:url(:/image/handNo.png);background-color:rgba(0, 0, 0, 0);"
#define handSheet "image:url(:/image/hand.png);background-color:rgba(0, 0, 0, 0);"
#define DBNoSheet "image:url(:/image/dbNo.png);background-color:rgba(0, 0, 0, 0);"
#define DBSheet "image:url(:/image/db.png);background-color:rgba(0, 0, 0, 0);"
#define btn1NoSheet "image:url(:/image/btn1No.png);background-color:rgba(0, 0, 0, 0);"
#define btn1Sheet "image:url(:/image/btn1.png);background-color:rgba(0, 0, 0, 0);"
#define btn2NoSheet "image:url(:/image/btn2No.png);background-color:rgba(0, 0, 0, 0);"
#define btn2Sheet "image:url(:/image/btn2.png);background-color:rgba(0, 0, 0, 0);"


/**单列显示 左侧界面**/
LeftWidget::LeftWidget(QWidget *parent):
    QWidget(parent),times(0)
{
    this->resize(290,690);
    CreateControl();
    connect(&btnGroup,SIGNAL(buttonClicked(int)),this,SLOT(BtnClicked(int)));


}

void LeftWidget::CreateControl()
{

    bodyLa = new QPushButton(this);bodyLa->setGeometry(45,50,200,350);bodyLa->setStyleSheet(bodySheet);
    HeadLa = new QPushButton(this);HeadLa->setGeometry(23,74,70,80);HeadLa->setStyleSheet(HeadLaNoSheet);
    FingerLa = new QPushButton(this);FingerLa->setGeometry(195,74,70,80);FingerLa->setStyleSheet(FingerNoSheet);
    la1 = new QPushButton(this);la1->setGeometry(128,180,40,40);la1->setStyleSheet(LaNoSheet);la1->setText(QString("10"));
    la2 = new QPushButton(this);la2->setGeometry(78,230,40,40);la2->setStyleSheet(LaNoSheet);la2->setText(QString("10"));
    la3 = new QPushButton(this);la3->setGeometry(128,230,40,40);la3->setStyleSheet(LaNoSheet);la3->setText(QString("120"));
    la4 = new QPushButton(this);la4->setGeometry(178,230,40,40);la4->setStyleSheet(LaNoSheet);la4->setText(QString("10"));
    la5 = new QPushButton(this);la5->setGeometry(128,280,40,40);la5->setStyleSheet(LaNoSheet);la5->setText(QString("10"));
    la6 = new QPushButton(this);la6->setGeometry(128,330,40,40);la6->setStyleSheet(LaNoSheet);la6->setText(QString("10"));

    pressLa = new QPushButton(this);pressLa->setGeometry(23,460,50,50);pressLa->setStyleSheet(PressLaNoSheet);
    btnGroup.addButton(pressLa,press);
    pushLa = new QPushButton(this);pushLa->setGeometry(88,460,50,50);pushLa->setStyleSheet(pushLaNoSheet);
    btnGroup.addButton(pushLa,push);
    callLa = new QPushButton(this);callLa->setGeometry(153,460,50,50);callLa->setStyleSheet(callLaNoSheet);
    btnGroup.addButton(callLa,call);
    fiLa = new QPushButton(this);fiLa->setGeometry(218,460,50,50);fiLa->setStyleSheet(fiLaNoSheet);
    btnGroup.addButton(fiLa,fi);

    HandLa = new QPushButton(this);HandLa->setGeometry(23,545,50,50);HandLa->setStyleSheet(handNoSheet);
    btnGroup.addButton(HandLa,Hand);
    DBLa = new QPushButton(this);DBLa->setGeometry(88,545,50,50);DBLa->setStyleSheet(DBNoSheet);
    btnGroup.addButton(DBLa,DB);
    btn1 = new QPushButton(this);btn1->setGeometry(153,545,50,50);btn1->setStyleSheet(btn1NoSheet);
    btnGroup.addButton(btn1,btn_1);
    btn2 = new QPushButton(this);btn2->setGeometry(218,545,50,50);btn2->setStyleSheet(btn2NoSheet);
    btnGroup.addButton(btn2,btn_2);

    timesla = new QLabel(this);timesla->setGeometry(125,530,20,20);
    timesla->setStyleSheet(QString("image:url(:/image/redbackground.jpg);color: #ffffff;font-family: PingFangSC-Regular;font-size: 10px;font-weight: 900;background-color:rgba(0, 0, 0, 0);"));
    timesla->setAlignment(Qt::AlignCenter);

    logo1 = new QLabel(this);logo1->setGeometry(20,630,30,30);logo1->setStyleSheet(QString("image:url(:/image/ECG.png);background-color:rgba(0, 0, 0, 0);"));
    Data1 = new QLabel(this);Data1->setGeometry(55,635,100,20);Data1->setStyleSheet("font-family: PingFangSC-Regular;font-size: 11px;color: #333333;font-weight: 600;");
    Data1->setText("on");

    logo2 = new QLabel(this);logo2->setGeometry(120,630,30,30);logo2->setStyleSheet(QString("image:url(:/image/voice.png);background-color:rgba(0, 0, 0, 0);"));
    Data2 = new QLabel(this);Data2->setGeometry(160,635,100,20);Data2->setStyleSheet("font-family: PingFangSC-Regular;font-size: 11px;color: #333333;font-weight: 600;");
    Data2->setText("100bmp");

}

void LeftWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void LeftWidget::BtnClicked(int ID)
{
    qDebug()<<__FUNCTION__<<ID;
    if(ID == DB){
        if(times == 0){DBLa->setStyleSheet(DBSheet);}
        timesla->setText(QString::number(++times));
    }
}




showOneLineWnd::showOneLineWnd(QWidget *parent):
    ShowLineBaseWnd(parent)
{
    time = new QLabel(this);time->setGeometry(5,5,1152,41);time->setAlignment(Qt::AlignCenter);
    time->setStyleSheet(QString("border-style:solid;border:1px solid rgba(0, 0, 0, 0.5);font-family: PingFangSC-Regular;"
                               "font-size: 18px;font-weight: 900;color: #88857e;"));
    time->setText("00:00:50");
    lw = new LeftWidget(this);
    infoWnd = new QWidget(this);
    infoWnd->setStyleSheet(QString("background-color:red"));

    QVBoxLayout *mainlayout = new QVBoxLayout(this);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(lw,2);
    layout->addWidget(infoWnd,6);
    mainlayout->addWidget(time,2);
    mainlayout->addLayout(layout,40);


}



