#ifndef SETMANIKINWND_H
#define SETMANIKINWND_H

#include <QDialog>
#include <QMouseEvent>
#include <QButtonGroup>


#include "setsyswnd.h"
namespace Ui {
class SetManikinWnd;
}

class SetManikinWnd : public QDialog
{
    Q_OBJECT
public:
    enum BtnID{
        BPM1 = 0,
        BPM2 = 1,
        BPM3 = 2,
        BPM4 = 3,
        VoiceOn = 4,
        VoiceOFF = 5,
        AFCan = 6,
        AFNo = 7,
        AFIgnore = 8,
        SuccessCPR = 9,
        SuccessAF = 10
    };
    explicit SetManikinWnd(QWidget *parent = 0);
    ~SetManikinWnd();
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
private slots:

    void BtnClickedEvent(int ID);
    void on_closeBtn_clicked();
    void on_cancelBtn_clicked();
private:
    Ui::SetManikinWnd *ui;
    int xOffset,yOffset;
    countWidget *AFTime;
    QButtonGroup buttonGroup;
    int bmp,voice,AF,successTerm;
};

#endif // SETMANIKINWND_H
