#ifndef QRUNNINGTIMEWND_H
#define QRUNNINGTIMEWND_H

#include <QWidget>

class QRunningTimeWnd : public QWidget
{
    Q_OBJECT
public:
    explicit QRunningTimeWnd(QWidget *parent = nullptr);
public:
    void paintEvent(QPaintEvent *event);
signals:

public slots:
};

#endif // QRUNNINGTIMEWND_H
