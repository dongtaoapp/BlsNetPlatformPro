#include "mainwnd.h"
#include "ui_mainwnd.h"
#include <qDebug>
#include <QHBoxLayout>
#define BtnInitSheet "font-family: PingFangSC-Regular;font-size: 18px;font-weight: normal;line-height: 70px;color: #b6b8c4;"
#define MainBtnClickedSheet "width: 37px;\
height: 17px;\
font-family: PingFangSC-Regular;\
font-size: 18px;\
font-weight: normal;\
line-height: 70px;\
border-bottom:2px solid #45c0f9;\
color: #21b0f2;"


MainWnd::MainWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWnd)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    this->setLayout(ui->verticalLayout);
    m_cprworkwnd = new CPRWorkWnd();
    m_scwnd = new SCWnd();
    m_swnd = new StatisticsWnd();
    connect(ui->CPRWorkBtn,SIGNAL(clicked(bool)),this,SLOT(CPRWorkBtnClickedEvent()));
    connect(ui->SCBtn,SIGNAL(clicked(bool)),this,SLOT(SCBtnClickedEvent()));
    connect(ui->StatisticsBtn,SIGNAL(clicked(bool)),this,SLOT(SBtnClickedEvent()));
    connect(ui->MinWndBtn,SIGNAL(clicked(bool)),this,SLOT(MinWndBtnClickedEvent()));
    connect(ui->CloseWndBtn,SIGNAL(clicked(bool)),this,SLOT(CloseWndBtnClickedEvent()));
    WndInit();
    CPRWorkBtnClickedEvent();
}

MainWnd::~MainWnd()
{
    delete ui;
}

void MainWnd::BtnSheetInit()
{
    ui->CPRWorkBtn->setStyleSheet(BtnInitSheet);
    ui->SCBtn->setStyleSheet(BtnInitSheet);
    ui->StatisticsBtn->setStyleSheet(BtnInitSheet);
}

void MainWnd::WndInit()
{
    ui->stackedWidget->insertWidget(CPRWORKWND,m_cprworkwnd);
    ui->stackedWidget->insertWidget(SCWND,m_scwnd);
    ui->stackedWidget->insertWidget(SWND,m_swnd);
}

void MainWnd::ChoseManikinEvent()
{
    ui->MaxWndBtn->setEnabled(false);
    background_label = new QLabel(this);
    background_label->setGeometry(0,30,this->width(),this->height());
    m_choseWnd = new ChoseManikinWnd(this);


    m_choseWnd->move((this->width()-m_choseWnd->width())/2,(this->height()-m_choseWnd->height())/2);
    connect(m_choseWnd,SIGNAL(ConManikins()),this,SLOT(ConManikiSuccess()));

}

void MainWnd::m_show()
{
    ChoseManikinEvent();
    this->show();
}

void MainWnd::ConManikiSuccess()
{
   ConnSuccessManikinRemarkList.clear();
   ConnSuccessManikinRemarkList = m_choseWnd->GetRemarkList();
   m_cprworkwnd->GetManikinList(ConnSuccessManikinRemarkList);
   m_swnd->GetConSuccessManikinList(ConnSuccessManikinRemarkList);

   delete background_label;
   m_choseWnd->hide();
}


/**************
*
*按钮点击响应事件
**************/

void MainWnd::CPRWorkBtnClickedEvent()
{
    BtnSheetInit();
    ui->CPRWorkBtn->setStyleSheet(MainBtnClickedSheet);
    ui->stackedWidget->setCurrentIndex(CPRWORKWND);
}

void MainWnd::SCBtnClickedEvent()
{
    BtnSheetInit();
    ui->SCBtn->setStyleSheet(MainBtnClickedSheet);
    ui->stackedWidget->setCurrentIndex(SCWND);
}

void MainWnd::SBtnClickedEvent()
{
    BtnSheetInit();
    ui->StatisticsBtn->setStyleSheet(MainBtnClickedSheet);
    ui->stackedWidget->setCurrentIndex(SWND);
}

void MainWnd::MinWndBtnClickedEvent()
{
    this->showMinimized();
}


void MainWnd::CloseWndBtnClickedEvent()
{
    qApp->quit();
}

void MainWnd::mousePressEvent (QMouseEvent *event)
{
   this->xOffset = event->globalPos().rx() - this->pos().rx();
   this->yOffset = event->globalPos().ry() - this->pos().ry();
}

void MainWnd::mouseMoveEvent(QMouseEvent * event)
{
  if((event->buttons() == Qt::LeftButton)&&((0<event->pos().ry())&&(event->pos().ry()<60))){
     this->move(event->globalX()-this->xOffset,event->globalY()-this->yOffset);
  }
}
