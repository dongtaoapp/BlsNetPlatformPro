#ifndef MAINWND_H
#define MAINWND_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

#include "cprworkwnd.h"
#include "scwnd.h"
#include "statisticswnd.h"
#include "chosemanikinwnd.h"
namespace Ui {
class MainWnd;
}

class MainWnd : public QWidget
{
    Q_OBJECT

public:
    enum WndType{
        CPRWORKWND = 0,
        SCWND = 1,
        SWND = 2
    };
    explicit MainWnd(QWidget *parent = 0);
    ~MainWnd();
protected:
    void BtnSheetInit();
    void WndInit();
    void ChoseManikinEvent();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
public:
    void m_show();
public slots:
    void CPRWorkBtnClickedEvent();
    void SCBtnClickedEvent();
    void SBtnClickedEvent();
    void MinWndBtnClickedEvent();
    void MaxWndBtnClicledEvent();
    void CloseWndBtnClickedEvent();
    void ConManikiSuccess();
private:
    Ui::MainWnd *ui;
    QLabel *background_label;
    ChoseManikinWnd *m_choseWnd;
    CPRWorkWnd *m_cprworkwnd;
    SCWnd *m_scwnd;
    StatisticsWnd *m_swnd;
    int xOffset,yOffset;
    QStringList ConnSuccessManikinRemarkList;

     QDesktopWidget* desktopWidget;
};

#endif // MAINWND_H
