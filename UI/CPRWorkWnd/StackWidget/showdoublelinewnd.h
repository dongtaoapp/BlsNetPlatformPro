#ifndef SHOWDOUBLELINEWND_H
#define SHOWDOUBLELINEWND_H
#include "qmtabdoublewnd.h"
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QResizeEvent>
#include "showlinebasewnd.h"
class DoubleWnd : public QListWidget{
    Q_OBJECT
public :
    DoubleWnd(QWidget *parent = 0);
    ~DoubleWnd(){};
    QList<QMTabDoubleWnd *> GetDoubleWnd(){return doubleLineWnd_List;}
protected:
    void resizeEvent(QResizeEvent *event);
private:
     QListWidgetItem *item1;QListWidgetItem *item2;
     QMTabDoubleWnd *wnd1;QMTabDoubleWnd *wnd2;
     QList<QMTabDoubleWnd *> doubleLineWnd_List;

};




class ShowDoubleLineWnd : public ShowLineBaseWnd
{
    Q_OBJECT
public:
    ShowDoubleLineWnd(QWidget *parent = 0);
    ~ShowDoubleLineWnd(){;}

     QList<QMTabDoubleWnd *> GetDounleLineWnd(){return m_listWnd->GetDoubleWnd();}

public:
     void UpPageEvent(){};
     void DownPageEvent(){};
     void GetManikinData(QVariant data){};
private:
    DoubleWnd *m_listWnd;
    QLabel *time;//CPR脚本时间
};

#endif // SHOWDOUBLELINEWND_H
