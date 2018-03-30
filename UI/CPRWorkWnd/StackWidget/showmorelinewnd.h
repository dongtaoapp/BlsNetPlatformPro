#ifndef SHOWMORELINEWND_H
#define SHOWMORELINEWND_H
#include <QTableView>
#include <QStandardItemModel>
#include <QList>
#include <QLabel>
#include "showlinebasewnd.h"
#include "qmtabwnd.h"
class showMoreLineWnd : public ShowLineBaseWnd
{
   Q_OBJECT
public:
    showMoreLineWnd(QWidget *parent = 0);
    ~showMoreLineWnd(){;}
    void TabWndInit();
public:
    void UpPageEvent();
    void DownPageEvent();
    void GetManikinData(QVariant data);
    QList<QMTabwnd *> GetMoreLineWnd(){return btnList;}

public slots:

    void listWndState(bool show);
private:
    QTableView *m_tabwnd;
    QStandardItemModel *m_model;
    QList<QMTabwnd *> btnList;
    QLabel *time;//CPR脚本时间
};

#endif // SHOWMORELINEWND_H
