#ifndef SETSYSWND_H
#define SETSYSWND_H

#include <QDialog>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
class countWidget:public QWidget{
    Q_OBJECT
public :
    countWidget(QWidget *parent = 0,int Count = 1000000);
    ~countWidget(){;}
public:
    void clearNum(){numLa->clear();currentCount = 0;}
    void setText(int num);
    QString IntToQString();
    int GetCueentCount(){return currentCount;}
public slots:
    void addBtnClickedEvent();
    void reduceBtnClickedEvent();
private:
    QPushButton *addBtn;
    QPushButton *reduceBtn;
    QLabel *numLa;
    int totalCount,currentCount;


};


namespace Ui {
class SetSysWnd;
}

class SetSysWnd : public QDialog
{
    Q_OBJECT

public:
    explicit SetSysWnd(QWidget *parent = 0);
    ~SetSysWnd();
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
private slots:
    void on_cancelBtn_clicked();
    void on_closeBtn_clicked();
private:
    Ui::SetSysWnd *ui;
    int xOffset,yOffset;
    countWidget *pressSpeachitem1;countWidget *pressSpeachitem2;
    countWidget *pressdeep1;countWidget *pressdeep2;
    countWidget *VLTime1;countWidget *VLTime2;
    countWidget *VLBulk1;countWidget *VLBulk2;
};

#endif // SETSYSWND_H
