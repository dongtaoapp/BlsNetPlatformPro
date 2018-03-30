#ifndef QMTABWND_H
#define QMTABWND_H
#include <QMouseEvent>
#include <QPushButton>
class QMTabwnd : public QPushButton
{
    Q_OBJECT
public:
    QMTabwnd(QWidget *parent = 0);
    ~QMTabwnd(){;}
    void setIndexNum(int index){indexNum = index;}
    int GetIndexNum(){return indexNum;}

    void setRemark(QString Manikinremark){Remark = Manikinremark;}
    QString GetRemark(){return Remark;}
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
Q_SIGNALS:
    void MDoubleClicked(QString);
private:
    int indexNum;
    QString Remark;//模拟人标识码
};

#endif // QMTABWND_H
