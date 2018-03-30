#include "registermanikinwnd.h"
#include "ui_registermanikinwnd.h"
#include <qDebug>
#include <QString>
#include <QFile>
#include <QScrollBar>
#include <QCoreApplication>
#include <QIcon>


#define QCheckBoxSheet "QCheckBox{font-family:PingFangSC-Regular;font-size: 18px;font-weight: normal;line-height: 70px;color: #b6b8c4;}\
                        QCheckBox::indicator:checked{image:url(:/image/Check.png);}\
                        QCheckBox::indicator:unchecked{image:url(:/image/Uncheck.png);}"
#define TabViewSheet "QHeaderView::section{background-color:#2c2e43;font-family:PingFangSC-Regular;font-size: 18px;font-weight: 900;line-height: 70px;color: #b6b8c4;border-style:solid}\
                      QHeaderView::checked{background-color:#2c2e43;color: #b6b8c4;}\
                      QTableView{background-color:#2c2e43;font-family:PingFangSC-Regular;font-size: 18px;font-weight: normal;line-height: 70px;color: #b6b8c4;border:2px solid #2c2e43}\
                      QTableView::item::selected{background-color:#2c2e43;font-family: PingFangSC-Regular;font-size: 18px;font-weight: normal;line-height: 70px;color: #b6b8c4;} \
                      }"
RegisterManikinWnd::RegisterManikinWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterManikinWnd)
{
    ui->setupUi(this);
    m_view = new QTableView(this);
    m_view->setGeometry(80,60,450,400);
    m_view->verticalScrollBar()->setStyleSheet(QString("QScrollBar:vertical{ \
                                                                             background-color:#2c2e43;\
                                                                             padding-top:20px;\
                                                                             padding-bottom:20px; \
                                                                             padding-left:3px;\
                                                                             padding-right:3px; \
                                                                             border-left:1px solid #d7d7d7;}\
                                                                             QScrollBar::handle:vertical{\
                                                                             background:##2c2e43; \
                                                                             border-radius:6px;\
                                                                             min-height:80px;}  \
                                                                             background:#2c2e43;}\
"));
    m_model = new QStandardItemModel();
    m_model->setColumnCount(4);
    CheckGroup.setExclusive(false);
    connect(ui->addManikinBtn,SIGNAL(clicked(bool)),this,SLOT(AddManikinBtnClickedEvent()));
    connect(ui->ConManikinBtn,SIGNAL(clicked(bool)),this,SLOT(ConManikinBntClickedEvent()));
    connect(&CheckGroup,SIGNAL(buttonClicked(int)),this,SLOT(CheckGroupClicked(int)));
    connect(&BtnGroup,SIGNAL(buttonClicked(int)),this,SLOT(BtnGroupClicked(int)));
    GetManikinRemarkByIniFile();
}

RegisterManikinWnd::~RegisterManikinWnd()
{
    delete ui;

}

void RegisterManikinWnd::InitTableView()
{
    int num  = RemarkList.size();
    if(num == 0)return;
    m_model->setRowCount(RemarkList.size());
    QStringList headerList;
    headerList.append(QStringLiteral("  序号"));
    headerList.append(QStringLiteral("标识码"));
    headerList.append(QStringLiteral("IP地址"));
    headerList.append(QStringLiteral("操作"));
    m_model->setHorizontalHeaderLabels(headerList);
    for(int i = 0;i<num;i++){
        M_Data _data;
        QStandardItem *IDitem = new QStandardItem();
        m_model->setItem(i,0,IDitem);

        QStandardItem *Remarkitem = new QStandardItem();
        Remarkitem->setText(QString("  ")+RemarkList.at(i));
        _data.Remark = RemarkList.at(i);
        m_model->setItem(i,1,Remarkitem);

        QStandardItem *ipitem = new QStandardItem();
        if(info_map.contains(RemarkList.at(i))){
            ipitem->setText(info_map[RemarkList.at(i)]);
            _data.IP = info_map[RemarkList.at(i)];
        }
        else{
            ipitem->setText(QString("  0.0.0.0"));
        }
        m_model->setItem(i,2,ipitem);
        QStandardItem *deleteItem = new QStandardItem();
        m_model->setItem(i,3,deleteItem);
        Num_info.insert(i,_data);
    }
    m_view->setModel(m_model);

    for(int i = 0;i<num;i++){
        QCheckBox *box = new QCheckBox();
        box->setText(QString("  ")+QString::number(i+1));
        box->setStyleSheet(QCheckBoxSheet);
        CheckGroup.addButton(box,i);
        m_view->setIndexWidget(m_model->index(i,0),box);

        QPushButton *btn = new QPushButton();
        btn->setStyleSheet(QString("image:url(:/image/1.png)"));
        BtnGroup.addButton(btn,i);
        m_view->setIndexWidget(m_model->index(i,3),btn);
    }


    m_view->setShowGrid(false);
    m_view->setStyleSheet(TabViewSheet);
    m_view->verticalHeader()->hide();
    m_view->setFocusPolicy(Qt::NoFocus);
    m_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_view->verticalHeader()->setDefaultSectionSize(80);

    //SET ColumWidth
    m_view->setColumnWidth(0,m_view->width()*0.21);
    m_view->setColumnWidth(1,m_view->width()*0.26);
    m_view->setColumnWidth(2,m_view->width()*0.26);
    m_view->setColumnWidth(3,m_view->width()*0.26);
}

void RegisterManikinWnd::ConManikinBntClickedEvent()
{
        // wite Remark
    QFile file(QCoreApplication::applicationDirPath()+QString("/Resource/ManikinRemark.txt"));
    file.open(QFile::WriteOnly|QFile::Truncate);
    file.close();
    if(file.open(QIODevice::WriteOnly|QIODevice::Append)){
        foreach(QString remark,RemarkList){
            file.write((remark + QString(";")).toLatin1());
        }
    file.close();
    }
    emit ConManikin();
}

void RegisterManikinWnd::AddManikinBtnClickedEvent()
{
    emit addManikin();
}

void RegisterManikinWnd::CheckGroupClicked(int id)
{
    if(Num_info.contains(id)){
    }
}

void RegisterManikinWnd::BtnGroupClicked(int id)
{
    if(Num_info.contains(id)){
        if(RemarkList.contains(Num_info[id].Remark)){
            RemarkList.removeAll(Num_info[id].Remark);
        }
        m_view->hideRow(id);
    }
}

void RegisterManikinWnd::addManikinList(QString Remark)
{
   RemarkList.append(Remark);
   InitTableView();
}

void RegisterManikinWnd::GetManikinRemarkByIniFile()
{
    QFile file(QCoreApplication::applicationDirPath()+QString("/Resource/ManikinRemark.txt"));
    if(file.open(QIODevice::ReadOnly)){
        QString info;
        info.prepend(file.readAll().data());
        file.close();
        RemarkList.clear();
        Num_info.clear();
        for(int i = 0;i<info.count(";");i++){
            RemarkList.append(info.section(";",i,i));
        }
    }

    InitTableView();
}


