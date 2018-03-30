#ifndef SHOWLISTWND_H
#define SHOWLISTWND_H

#include "showlinebasewnd.h"
#include "qmlistwnd.h"
#include <QPaintEvent>
#include <QList>
class showListWnd : public ShowLineBaseWnd
{
    Q_OBJECT
public:
    showListWnd(QWidget *parent =  0);
    ~showListWnd(){;}

    void InitWnd();

    QList<QMlistWnd *> GetItem(){return item_list;}

    void GetManikinData(QVariant data);
    void UpPageEvent();
    void DownPageEvent();
Q_SIGNALS:
    void ManikinDoubleClicked(QString Remark);
public slots:
    void ItemClicked();
    void ItemDoubleClicked(QString remark);
protected:
    void paintEvent(QPaintEvent *event);
private:
    QList<QMlistWnd *> item_list;/*CPR显示窗口指针*/
};

#endif // SHOWLISTWND_H
