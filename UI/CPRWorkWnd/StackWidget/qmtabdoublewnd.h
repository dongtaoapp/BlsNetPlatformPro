#ifndef QMTABDOUBLEWND_H
#define QMTABDOUBLEWND_H
#include <QPushButton>
#include <QMouseEvent>

class QMTabDoubleWnd : public QPushButton
{
    Q_OBJECT
public:
    QMTabDoubleWnd(QWidget *parent = 0);
    ~QMTabDoubleWnd(){;}
    void setIndexNum(int index){indexNum = index;}
    int GetIndexNum(){return indexNum;}

    void setRemrk(QString ManikinRemark){Remark = ManikinRemark;}
    QString GetRemark(){return Remark;}

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
Q_SIGNALS:
    void MDoubleClicked(QString);
private:
    int indexNum;
    QString Remark;//模拟人标识码
};

#endif // QMTABDOUBLEWND_H
