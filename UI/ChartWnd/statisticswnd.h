#ifndef STATISTICSWND_H
#define STATISTICSWND_H
#include "barwnd.h"
#include "piewnd.h"
#include <QWidget>
#include <QStandardItemModel>
#include <QButtonGroup>
namespace Ui {
class StatisticsWnd;
}

class StatisticsWnd : public QWidget
{
    Q_OBJECT

public:
    enum BtnType{
        Print = 0,//打印
        Save  = 1,//保存
        Pie = 2,//饼状图
        Bar = 3,//柱状图
    };
    enum WndType{
        Barwidget = 0,
        Piewidget = 1,
    };
    explicit StatisticsWnd(QWidget *parent = 0);
    ~StatisticsWnd();
    void InitTabView();
    void GetConSuccessManikinList(QStringList list);
    void InitManikinList();

public slots:
    void BtnClickedEvent(int index);
    void CBClickedEvent(QAbstractButton *cb);
    void SearchEvent();
private:
    Ui::StatisticsWnd *ui;
    QStandardItemModel *m_model;
    QStringList Manikinlist;
    QButtonGroup btnGroup,CBGroup;
    BarWnd *m_barwnd;
    PieWnd *m_piewnd;
};

#endif // STATISTICSWND_H
