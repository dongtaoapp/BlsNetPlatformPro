#ifndef CPRREALTIMEPRESURERATESHOWWND_H
#define CPRREALTIMEPRESURERATESHOWWND_H

#include <QWidget>
#include <QTimer>
#include <QMutex>

#include "..\Common\CommonGlobal.h"


namespace Ui {
class CPRRealTimePresureRateShowWnd;
}

class CPRRealTimePresureRateShowWnd : public QWidget
{
    Q_OBJECT

public:
    explicit CPRRealTimePresureRateShowWnd(QWidget *parent = 0);
    ~CPRRealTimePresureRateShowWnd();
public:
    void    paintEvent(QPaintEvent *event);
public:
    void    ClearRealTimeShow();
    //接受cpr数据并显示其中的按压频率数据
    void    DistributeCPRData(_CPRData *lpDataPtr, int nLength);
public slots:
    void    updateUI();
public:
    QList<QPoint> m_lstPresureRate;         //按压频率实时数据
private slots:
    void on_pushButton_clicked();
signals:
    void    updatePresureRate(int nPresureRate);
private:
    Ui::CPRRealTimePresureRateShowWnd *ui;
private:
    QTimer *m_timer;
    int     m_nMaxDataCount;
    QMutex  m_mutex;
    bool    m_bPauseRealTimeShow;   //暂停实时数据显示
};

#endif // CPRREALTIMEPRESURERATESHOWWND_H
