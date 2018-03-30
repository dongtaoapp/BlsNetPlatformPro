#ifndef SETSUCCESSWND_H
#define SETSUCCESSWND_H

#include <QDialog>
#include <QMouseEvent>
#include "setsyswnd.h"
#include <QButtonGroup>
namespace Ui {
class SetSuccessWnd;
}

class SetSuccessWnd : public QDialog
{
    Q_OBJECT

public:
    enum WorkType{
        Popularize = 1,//普及
        Practice = 2,//实战
    };
    explicit SetSuccessWnd(QWidget *parent = 0);
    ~SetSuccessWnd();
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
private slots:
    void on_closeBtn_clicked();
    void on_cancelBtn_clicked();
    void on_saveBtn_clicked();
    void BtnClickedEvent(int ID);

private:
    Ui::SetSuccessWnd *ui;
    int xOffset,yOffset;
    countWidget *workTime1;
    countWidget *workTime2;
    countWidget *breakTime;
    countWidget *pressTimePrecent;
    countWidget *pressRightPrecent;
    countWidget *blowRightPrecent;
    countWidget *pressfrequencyPrecent;
    QButtonGroup btngroup;
    int workModel;
};

#endif // SETSUCCESSWND_H
