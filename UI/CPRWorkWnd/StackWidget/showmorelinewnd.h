#ifndef SHOWMORELINEWND_H
#define SHOWMORELINEWND_H
#include <QTableView>
#include <QStandardItemModel>
#include <QList>
#include <QLabel>
#include <QResizeEvent>
#include "showlinebasewnd.h"
#include "qmtabwnd.h"

class MoreWnd : public QTableView{
    Q_OBJECT
public :
    MoreWnd(QWidget *parent = 0);
    ~MoreWnd(){};
    void TabInit();

     QList<QMTabwnd *>GetMoreWndlist(){return btnList;}
protected:
    void resizeEvent(QResizeEvent *event);
private:
     QList<QMTabwnd *> btnList;
     QStandardItemModel *m_model;
};



class showMoreLineWnd : public ShowLineBaseWnd
{
   Q_OBJECT
public:
    showMoreLineWnd(QWidget *parent = 0);
    ~showMoreLineWnd(){;}
    void TabWndInit();
public:
    void UpPageEvent(){};
    void DownPageEvent(){};
    void GetManikinData(QVariant data){};
    QList<QMTabwnd *> GetMoreLineWnd(){return m_tabwnd->GetMoreWndlist();}

private:
    MoreWnd *m_tabwnd;
    QLabel *time;//CPR脚本时间
};

#endif // SHOWMORELINEWND_H
