#include "cprworkwnd.h"
#include "ui_cprworkwnd.h"
#include "showdoublelinewnd.h"
#include "showonelinewnd.h"
#include "showmorelinewnd.h"
#include "cprworkdefin.h"
#include <qDebug>

CPRWorkWnd::CPRWorkWnd(QWidget *parent) :
    QWidget(parent),fullscreenlist(false),CurrentBtnID(-1),
    ui(new Ui::CPRWorkWnd)
{
    ui->setupUi(this);

    this->setStyleSheet(BtnClickedSheet);
    CurrentManikin = Q_NULLPTR;
    btngroupInit();
    InitStackWidget();
    InitList2Wnd();
    SMWnd = new SetManikinWnd(this);
    SSysWnd = new SetSysWnd(this);
    SSWnd = new SetSuccessWnd(this);
    addManWnd = new CPRAddManikinWnd(this);
    changeManWnd = new CPRChangeWnd(this);
    ReManWnd = new CPRReManikinWnd(this);
    connect(&btnGroup,SIGNAL(buttonClicked(int)),this,SLOT(BtnClickedEvent(int)));
}



CPRWorkWnd::~CPRWorkWnd()
{
    delete ui;
}

void CPRWorkWnd::btngroupInit()
{
    btnGroup.addButton(ui->startBtn,StartBtn);
    btnGroup.addButton(ui->retBtn,RetBtn);

    btnGroup.addButton(ui->OneLineBtn,OneLineBtn);
    btnGroup.addButton(ui->doubleLinBtn,DoubleLineBtn);
    btnGroup.addButton(ui->moreLineBtn,MoreLineBtn);

    btnGroup.addButton(ui->UpPageBtn,UpPageBtn);
    btnGroup.addButton(ui->downPageBtn,DownPageBtn);

    btnGroup.addButton(ui->hideListBtn,HideListBtn);
    btnGroup.addButton(ui->showListBtn,showListBtn);

    btnGroup.addButton(ui->setBtn,setBtn);
    btnGroup.addButton(ui->successSetBtn,SuccessSetBtn);
    btnGroup.addButton(ui->ManikinSetBtn,ManikinSetBtn);
}



//获取模拟人信息

void CPRWorkWnd::GetManikinList(QStringList list)
{
    ManikinList.clear();
    ManikinList = list;
    InitListWnd();
    InitHiRightWnd();

    BtnClickedEvent(OneLineBtn);
}

void CPRWorkWnd::InitList2Wnd()
{
    for(int i = 0;i<5;i++){
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget_2);item->setSizeHint(QSize(30,40));
        QMlistWnd *wnd = new QMlistWnd(0,QMlistWnd::None);
        if(i==0){
            wnd->setIndexNum(1);wnd->setStyleSheet(QString("image:url(:/image/addManikin.png)"));
        }
        if(i==1){
            wnd->setIndexNum(2);wnd->setStyleSheet(QString("image:url(:/image/changeManikin.png)"));
        }
        if(i==2){
            wnd->setIndexNum(3);wnd->setStyleSheet(QString("image:url(:/image/remove.png)"));
        }
        if(i==3){
            wnd->setIndexNum(4);wnd->setStyleSheet(QString("image:url(:/image/ReCon.png)"));
        }
        if(i==4){
            wnd->setIndexNum(5);wnd->setStyleSheet(QString("image:url(:/image/ConSys.png)"));
        }
        ui->listWidget_2->setItemWidget(item,wnd);
        connect(wnd,SIGNAL(clicked(bool)),this,SLOT(List2WndItemClicked()));
    }
}

//初始化左侧模拟人

void CPRWorkWnd::InitListWnd()
{
    for(int i = 0;i<ManikinList.size();i++){
        QListWidgetItem *item  =  new QListWidgetItem(ui->listWidget); item->setSizeHint(QSize(ListWndWidth,ListWndHeight));  //每次改变Item的高度
        QMlistWnd *wnd = new QMlistWnd();
        wnd->setRemark(ManikinList.at(i));
        wnd->setIndexNum(i+1);
        mlistWnd_list.append(wnd);
        ui->listWidget->setItemWidget(item,wnd);

        connect(wnd,SIGNAL(clicked(bool)),this,SLOT(ListWndItemClicked()));
        connect(wnd,SIGNAL(MDoubleClicked(QString)),this,SLOT(ListWndItemDoubleClicked(QString)));
    }
}
/*
 *初始化隐藏左侧界面
 */
void CPRWorkWnd::InitHiRightWnd()
{
    foreach(QMlistWnd *wnd,listWnd->GetItem()){wnd->setHidden(true);}
    for(int i = 0 ;i<ManikinList.size();i++){
        if(i<9){
          QMlistWnd *wnd =  listWnd->GetItem().at(i);
          wnd->show();
          wnd->setIndexNum(i+1);
          wnd->setRemark(ManikinList.at(i));
        }
        if(i>=9){
             return;
        }
    }
}

void CPRWorkWnd::InitStackWidget()
{
    showOneLineWnd *oneLindWnd = new showOneLineWnd();
    ui->stackedWidget->insertWidget(OneLine,oneLindWnd);

    ShowDoubleLineWnd *doubleLineWnd = new ShowDoubleLineWnd();
    ui->stackedWidget->insertWidget(DoubleLine,doubleLineWnd);

    showMoreLineWnd *moreLineWnd = new showMoreLineWnd();
    ui->stackedWidget->insertWidget(MoreLine,moreLineWnd);
    ui->stackedWidget->setCurrentIndex(OneLine);

    listWnd =  new showListWnd(this);
    listWnd->setGeometry(2,90,1441,760);listWnd->hide();

    connect(listWnd,SIGNAL(ManikinDoubleClicked(QString)),this,SLOT(ManikinDouleClickedEvent(QString)));

}

void CPRWorkWnd::ListWndItemClicked()
{
    for(int i = 0;i<ui->listWidget->count();i++){
       static_cast<QMlistWnd *>(ui->listWidget->itemWidget(ui->listWidget->item(i)))->sheet();
    }
    static_cast<QMlistWnd *>(QObject::sender())->clickedSheet();
}

void CPRWorkWnd::ListWndItemDoubleClicked(QString ManikinRemark)
{
   qDebug()<<__FUNCTION__<<ManikinRemark;
   BtnClickedEvent(HideListBtn);
   BtnClickedEvent(OneLineBtn);
}

void CPRWorkWnd::ManikinDouleClickedEvent(QString ManikinRemark)
{
    qDebug()<<__FUNCTION__<<ManikinRemark;
    ui->listWidget->show();
    BtnClickedEvent(HideListBtn);
    BtnClickedEvent(OneLineBtn);
    for(int i = 0;i<ui->listWidget->count();i++){
      QMlistWnd *wnd = static_cast<QMlistWnd *>(ui->listWidget->itemWidget(ui->listWidget->item(i)));wnd->sheet();
      if(wnd->GetRemark() == ManikinRemark){
       wnd->clickedSheet();
      }
    }
}

void CPRWorkWnd::List2WndItemClicked()
{
    if(CurrentManikin != Q_NULLPTR){
        qDebug()<<__FUNCTION__<<CurrentManikin->GetRemark();
    }
    QMlistWnd *item = static_cast<QMlistWnd *>(QObject::sender());
    switch(item->GetIndexNum()){
        case 1://增加模拟人
            addManWnd->exec();
            break;
        case 2://替换模拟人
            changeManWnd->exec();
            break;
        case 3://移除模拟人
            ReManWnd->exec();
            break;
        case 4://重新连接
            break;
        case 5://连接系统
            break;
    }
}

void CPRWorkWnd::BtnClickedEvent(int index)
{

    CurrentBtnID = index;
    if((StartBtn<=index)&&(index<=RetBtn)){
         if(index==StartBtn){
            //TODO
         }
         else{
            //TODO
         }
        return;
    }
    else if((OneLineBtn<=index)&&(index<=MoreLineBtn)){
        ui->OneLineBtn->setStyleSheet(BtnNoclicked);ui->doubleLinBtn->setStyleSheet(BtnNoclicked);ui->moreLineBtn->setStyleSheet(BtnNoclicked);
       if(index == OneLineBtn){
           ui->OneLineBtn->setStyleSheet(BtnClicked);
           ui->stackedWidget->setCurrentIndex(OneLine);
       }
       if(index== DoubleLineBtn){
           ui->doubleLinBtn->setStyleSheet(BtnClicked);
           ui->stackedWidget->setCurrentIndex(DoubleLine);
       }
       if(index == MoreLineBtn){
           ui->moreLineBtn->setStyleSheet(BtnClicked);
           ui->stackedWidget->setCurrentIndex(MoreLine);
       }
       return;
    }
    else if((UpPageBtn<=index)&&(index<=DownPageBtn)){
        if(index == UpPageBtn){
              if(!listWnd->isHidden()){upPageEvent();}
//            ((ShowLineBaseWnd*)(ui->stackedWidget->currentWidget()))->UpPageEvent();
        }
        else{
//            ((ShowLineBaseWnd *)(ui->stackedWidget->currentWidget()))->DownPageEvent();
            if(!listWnd->isHidden()){downPageEvent();}
        }
        return;
    }
    else if((HideListBtn<=index)&&(index<=showListBtn)){
        ui->hideListBtn->setStyleSheet(BtnNoclicked);ui->showListBtn->setStyleSheet(BtnNoclicked);
        if(index == HideListBtn){
            ui->stackedWidget->show();listWnd->hide();fullscreenlist = false;
            if(!ui->listWidget->isHidden()){
                ui->listWidget_2->hide();ui->listWidget->hide();ui->hideListBtn->setStyleSheet(BtnClicked);
            }
            else{
                ui->listWidget_2->show();ui->listWidget->show(); ui->hideListBtn->setStyleSheet(BtnNoclicked);
            }
            return;
        }
        else{
             ui->stackedWidget->hide();
            if(!fullscreenlist){
              listWnd->show();ui->listWidget_2->hide();ui->listWidget->hide();ui->showListBtn->setStyleSheet(BtnClicked);fullscreenlist = true;
            }
            else{
                listWnd->hide();ui->stackedWidget->show();ui->listWidget_2->show();ui->listWidget->show();ui->showListBtn->setStyleSheet(BtnNoclicked);fullscreenlist = false;
            }
        }
        return;
    }
    else if((setBtn<=index)&&(index<=ManikinSetBtn)){
        if(index == setBtn){SSysWnd->exec();}
        if(index == SuccessSetBtn){SSWnd->exec();}
        if(index == ManikinSetBtn){SMWnd->exec();}
        return;
    }
}

void CPRWorkWnd::downPageEvent()
{
      QMlistWnd *endwnd;
      foreach(QMlistWnd *wnd,listWnd->GetItem()){
          wnd->sheet();
          if(!wnd->isHidden()){
              endwnd = wnd;
          }
      }
      int index = endwnd->GetIndexNum();
      if(index+1>ManikinList.size()){return;}
      for(int i = 0;i<9;i++){
          QMlistWnd *wnd =  listWnd->GetItem().at(i);
          if(i+index+1<=ManikinList.size()){
              wnd->show();
              wnd->setIndexNum(index+1+i);
              wnd->setRemark(ManikinList.at(i+index));
          }
          else{
              wnd->setHidden(true);
          }
      }
}

void CPRWorkWnd::upPageEvent()
{
    QMlistWnd *firstwnd =  listWnd->GetItem().at(0);

    if((firstwnd->GetIndexNum() == 1)){return;}
    foreach(QMlistWnd *wnd,listWnd->GetItem()){wnd->setHidden(false);wnd->sheet();}
    int index = firstwnd->GetIndexNum();
    for(int i = 0;i<listWnd->GetItem().size();i++){
        listWnd->GetItem().at(i)->setRemark(ManikinList.at((index-10)+i));
        listWnd->GetItem().at(i)->setIndexNum(index-9+i);
    }
}
