#include "setmanikinwnd.h"
#include "ui_setmanikinwnd.h"
#include "cprworkdefin.h"
#include <qDebug>
SetManikinWnd::SetManikinWnd(QWidget *parent) :
    QDialog(parent),bmp(-1),voice(-1),AF(-1),successTerm(-1),
    ui(new Ui::SetManikinWnd)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去掉标题栏
    AFTime = new countWidget(this);
    AFTime->move(700,320);
    buttonGroup.addButton(ui->bpm_Btn1,BPM1);buttonGroup.addButton(ui->bpm_Btn2,BPM2);buttonGroup.addButton(ui->bpm_Btn3,BPM3);buttonGroup.addButton(ui->bpm_Btn4,BPM4);
    buttonGroup.addButton(ui->voiceBtn_on,VoiceOn);buttonGroup.addButton(ui->voiceBtn_OFF,VoiceOFF);
    buttonGroup.addButton(ui->AFCanBtn,AFCan);buttonGroup.addButton(ui->AFNoBtn,AFNo);buttonGroup.addButton(ui->AFIgnoreBtn,AFIgnore);
    buttonGroup.addButton(ui->SuccessCPRBtn,SuccessCPR);buttonGroup.addButton(ui->SuccessAFBtn,SuccessAF);
    connect(&buttonGroup,SIGNAL(buttonClicked(int)),this,SLOT(BtnClickedEvent(int)));
}
SetManikinWnd::~SetManikinWnd()
{
    delete ui;
}
void SetManikinWnd::BtnClickedEvent(int ID)
{
    if((BPM1<=ID)&&(ID<=BPM4)){
        ui->bpm_Btn1->setStyleSheet(BtnNoclicked);ui->bpm_Btn2->setStyleSheet(BtnNoclicked);
        ui->bpm_Btn3->setStyleSheet(BtnNoclicked);ui->bpm_Btn4->setStyleSheet(BtnNoclicked);
        if(ID==BPM1){ui->bpm_Btn1->setStyleSheet(BtnClicked);}if(ID==BPM2){ui->bpm_Btn2->setStyleSheet(BtnClicked);}
        if(ID==BPM3){ui->bpm_Btn3->setStyleSheet(BtnClicked);}if(ID==BPM4){ui->bpm_Btn4->setStyleSheet(BtnClicked);}
        bmp = ID;
    }
    if((VoiceOn<=ID)&&(ID<=VoiceOFF)){
        ui->voiceBtn_on->setStyleSheet(BtnNoclicked);ui->voiceBtn_OFF->setStyleSheet(BtnNoclicked);\
        if(ID==VoiceOn){ui->voiceBtn_on->setStyleSheet(BtnClicked);}if(ID==VoiceOFF){ui->voiceBtn_OFF->setStyleSheet(BtnClicked);}
        voice = ID;
    }
    if((AFCan<=ID)&&(ID<=AFIgnore)){
        ui->AFCanBtn->setStyleSheet(BtnNoclicked);ui->AFNoBtn->setStyleSheet(BtnNoclicked);ui->AFIgnoreBtn->setStyleSheet(BtnNoclicked);
        if(ID==AFCan){ui->AFCanBtn->setStyleSheet(BtnClicked);}if(ID==AFNo){ui->AFNoBtn->setStyleSheet(BtnClicked);}
        if(ID==AFIgnore){ui->AFIgnoreBtn->setStyleSheet(BtnClicked);}
        AF = ID;
    }
    if((SuccessCPR<=ID)&&(ID<=SuccessAF)){
        ui->SuccessAFBtn->setStyleSheet(BtnNoclicked);ui->SuccessCPRBtn->setStyleSheet(BtnNoclicked);
        if(ID==SuccessCPR){ui->SuccessCPRBtn->setStyleSheet(BtnClicked);}if(ID==SuccessAF){ui->SuccessAFBtn->setStyleSheet(BtnClicked);}
        successTerm = ID;
    }
}
/**点击事件*/
void SetManikinWnd::on_closeBtn_clicked()
{
     this->close();
}
void SetManikinWnd::on_cancelBtn_clicked()
{
    this->close();
}
void SetManikinWnd::mousePressEvent (QMouseEvent *event)
{
   this->xOffset = event->globalPos().rx() - this->pos().rx();
   this->yOffset = event->globalPos().ry() - this->pos().ry();
}
void SetManikinWnd::mouseMoveEvent(QMouseEvent * event)
{
  if((event->buttons() == Qt::LeftButton)&&((0<event->pos().ry())&&(event->pos().ry()<60))){
     this->move(event->globalX()-this->xOffset,event->globalY()-this->yOffset);
  }
}
