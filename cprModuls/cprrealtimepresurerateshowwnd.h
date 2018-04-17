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
    //����cpr���ݲ���ʾ���еİ�ѹƵ������
    void    DistributeCPRData(_CPRData *lpDataPtr, int nLength);
public slots:
    void    updateUI();
public:
    QList<QPoint> m_lstPresureRate;         //��ѹƵ��ʵʱ����
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
    bool    m_bPauseRealTimeShow;   //��ͣʵʱ������ʾ
};

#endif // CPRREALTIMEPRESURERATESHOWWND_H
