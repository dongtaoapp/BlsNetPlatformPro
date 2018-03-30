#include "addmanikinwnd.h"
#include "ui_addmanikinwnd.h"
#include <QString>
addManikinWnd::addManikinWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addManikinWnd)
{
    ui->setupUi(this);
    connect(ui->returnBtn,SIGNAL(clicked(bool)),this,SLOT(backBtnClickedEvent()));
    connect(ui->okBtn,SIGNAL(clicked(bool)),this,SLOT(okBtnClickedEvent()));
}

addManikinWnd::~addManikinWnd()
{
    delete ui;
}

void addManikinWnd::addManikinInfo()
{
      emit addManikin(ui->ManikinEdit->text());
}

void addManikinWnd::okBtnClickedEvent()
{
    addManikinInfo();
}

void addManikinWnd::backBtnClickedEvent()
{
    ui->ManikinEdit->clear();
    emit backSignal();
}
