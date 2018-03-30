#ifndef SHOWLINEBASEWND_H
#define SHOWLINEBASEWND_H

#include <QWidget>
class ShowLineBaseWnd : public QWidget
{
    Q_OBJECT
public:
    ShowLineBaseWnd(QWidget *parent =  0);
    ~ShowLineBaseWnd(){;}
public:
    virtual void UpPageEvent() = 0;
    virtual void DownPageEvent() = 0;
    virtual void GetManikinData(QVariant data) = 0;

};

#endif // SHOWLINEBASEWND_H
