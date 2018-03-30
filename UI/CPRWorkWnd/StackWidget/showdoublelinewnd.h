#ifndef SHOWDOUBLELINEWND_H
#define SHOWDOUBLELINEWND_H
#include "qmtabdoublewnd.h"
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include "showlinebasewnd.h"
class ShowDoubleLineWnd : public ShowLineBaseWnd
{
    Q_OBJECT
public:
    ShowDoubleLineWnd(QWidget *parent = 0);
    ~ShowDoubleLineWnd(){;}

     QList<QMTabDoubleWnd *> GetDounleLineWnd(){return doubleLineWnd_List;}

     void TabItemInit();
public:
     void UpPageEvent();
     void DownPageEvent();
     void GetManikinData(QVariant data);
public slots:
     void listWndState(bool show);
private:
    QList<QMTabDoubleWnd *> doubleLineWnd_List;
    QListWidget *m_listWnd;

    QLabel *time;//CPR脚本时间

    QListWidgetItem *item1;QListWidgetItem *item2;

};

#endif // SHOWDOUBLELINEWND_H
