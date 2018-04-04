#ifndef SHOWONELINEWND_H
#define SHOWONELINEWND_H
#include <qDebug>
#include "showlinebasewnd.h"

#include <QWidget>
#include <QPaintEvent>
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>
class LeftWidget : public QWidget{
    Q_OBJECT
public :
    enum BtnType{
        press = 1,
        push = 2,
        call = 3,
        fi = 4,
        Hand = 5,
        DB = 6,
        btn_1 = 7,
        btn_2 = 8,
    };
    LeftWidget(QWidget *parent = 0);
    ~LeftWidget(){;}
    void CreateControl();


    QList<QWidget *> widget(){};
protected:
    void paintEvent(QPaintEvent *event);

public slots:
    void BtnClicked(int ID);
private:
    QLabel *timesla;QLabel *logo1;QLabel *logo2;QLabel *Data1;QLabel *Data2;
    QPushButton *la1;QPushButton *la2;QPushButton *la3;QPushButton *la4;QPushButton *la5;QPushButton *la6;/*从上到下 左到右\0*/
    QPushButton *HeadLa;QPushButton *FingerLa;QPushButton *bodyLa;
    QPushButton *pressLa;QPushButton *pushLa;QPushButton *callLa;QPushButton *fiLa;QPushButton *HandLa;QPushButton *DBLa;/*除颤\0*/ QPushButton *btn1; QPushButton *btn2;

    QButtonGroup btnGroup;
    int times;

    QList<QWidget *> wndlist;
};

class showOneLineWnd : public ShowLineBaseWnd
{
    Q_OBJECT
public:
    showOneLineWnd(QWidget *parent = 0);
    ~showOneLineWnd(){;}
public:
    void UpPageEvent(){};
    void DownPageEvent(){};
    void GetManikinData(QVariant data){};
private:
    LeftWidget *lw;
    QLabel *time;//CPR脚本时间
    QWidget *infoWnd;
};

#endif // SHOWONELINEWND_H
