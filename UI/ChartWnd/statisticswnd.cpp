#include "statisticswnd.h"
#include "ui_statisticswnd.h"
#include "cprworkdefin.h"
#include <QStandardItem>
#include <qDebug>
#include <QStandardItem>
#include <QCheckBox>
#define TableSheet "QHeaderView::section{background-color:#2c2e43;font-family:PingFangSC-Regular;font-size: 18px;font-weight: 900;\
                    line-height: 70px;color: #b6b8c4;border-style:solid}\
                    QHeaderView::checked{background-color:#2c2e43;color: #b6b8c4;}\
                    QTableView{background-color:#2c2e43;font-family:PingFangSC-Regular;font-size: 18px;font-weight: normal;\
                    line-height: 70px;color: #b6b8c4;border:2px solid #2c2e43}\
                    QTableView::item::selected{background-color:#2c2e43;font-family: PingFangSC-Regular;\
                    font-size: 18px;font-weight: normal;line-height: 70px;color: #b6b8c4;}"
#define CHBoxSheet "QCheckBox{font-family:PingFangSC-Regular;font-size: 18px;font-weight: normal;line-height: 70px;color: #b6b8c4;}\
                    QCheckBox::indicator:checked{image:url(:/image/Check.png);}\
                    QCheckBox::indicator:unchecked{image:url(:/image/Uncheck.png);}"
StatisticsWnd::StatisticsWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsWnd)
{
    ui->setupUi(this);
    this->setStyleSheet(BtnClickedSheet);
    ui->searchEdit->setPlaceholderText(tr("搜索"));


    m_model = new QStandardItemModel();
    m_model->setColumnCount(3);
    m_barwnd = new BarWnd();
    m_piewnd = new PieWnd();
    ui->stackedWidget->insertWidget(Barwidget,m_barwnd);
    ui->stackedWidget->insertWidget(Piewidget,m_piewnd);

    btnGroup.addButton(ui->PrintBtn,Print);
    btnGroup.addButton(ui->SaveBtn,Save);
    btnGroup.addButton(ui->PieBtn,Pie);
    btnGroup.addButton(ui->BarBtn,Bar);
    connect(&btnGroup,SIGNAL(buttonClicked(int)),this,SLOT(BtnClickedEvent(int)));
    connect(&CBGroup,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(CBClickedEvent(QAbstractButton *)));
    connect(ui->searchBtn,SIGNAL(clicked(bool)),this,SLOT(SearchEvent()));
    InitTabView();
}

StatisticsWnd::~StatisticsWnd()
{
    delete ui;
}

void StatisticsWnd::InitTabView()
{
    ui->tableView->setStyleSheet(TableSheet);
    ui->tableView->horizontalHeader()->setVisible(false);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setShowGrid(false);
    ui->tableView->setFocusPolicy(Qt::NoFocus);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->verticalHeader()->setDefaultSectionSize(50);
}

void StatisticsWnd::GetConSuccessManikinList(QStringList list)
{
    Manikinlist.clear();
    Manikinlist = list;
    InitManikinList();
    BtnClickedEvent(Pie);
}
void StatisticsWnd::InitManikinList()
{
   for(int i = 0;i<Manikinlist.size();i++){
       QStandardItem *remark =  new QStandardItem();
       m_model->setItem(i,0,remark);
   }
   ui->tableView->setModel(m_model);
   ui->tableView->setColumnWidth(0,130);
   ui->tableView->setColumnWidth(1,65);
   ui->tableView->setColumnWidth(2,65);
   for(int i = 0;i<Manikinlist.size();i++){
       QCheckBox *box = new QCheckBox();
       box->setStyleSheet(CHBoxSheet);
       box->setText(QString(" ")+Manikinlist.at(i));
       ui->tableView->setIndexWidget(m_model->index(i,0),box);
       CBGroup.addButton(box,i);
   }
}

void StatisticsWnd::BtnClickedEvent(int index)
{
    if((index == Pie)||(index == Bar)){
        ui->PieBtn->setStyleSheet(BtnNoclicked);ui->BarBtn->setStyleSheet(BtnNoclicked);
        if(index == Pie){
            ui->PieBtn->setStyleSheet(BtnClicked);
            ui->stackedWidget->setCurrentIndex(Piewidget);
        }
        if(index == Bar){
            ui->BarBtn->setStyleSheet(BtnClicked);
            ui->stackedWidget->setCurrentIndex(Barwidget);
        }
    }
    if(index == Print){
       //TODO
    }
    if(index == Save){
      //TODO
    }

}

void StatisticsWnd::CBClickedEvent(QAbstractButton *cb)
{   //TODO
    QCheckBox *box = static_cast<QCheckBox *>(cb);
    qDebug()<<__FUNCTION__<<box->text();
}

void StatisticsWnd::SearchEvent()
{
    qDebug()<<__FUNCTION__<<ui->searchEdit->text();
}
