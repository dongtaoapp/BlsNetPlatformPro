#ifndef PIEWND_H
#define PIEWND_H

#include <QWidget>
#include <QtCharts>
#include <QPieSeries>

using namespace QtCharts;


namespace Ui {
class PieWnd;
}

class PieWnd : public QWidget
{
    Q_OBJECT
public:
    explicit PieWnd(QWidget *parent = 0);
    ~PieWnd();
    void setRightValue(int right);//按压准确性
    void PressBreakTime(int time);//按压中断时间
    void setvcvRightValue(int right);//吹起准确性

    void CreatePie();

    void CreateChartView();

    void testData();
private:
    Ui::PieWnd *ui;

    //按压深度准确性
    QChartView *pressdeepview;
    QPieSeries *pressdeepseries;
    QPieSlice *normalslice;
    QPieSlice *lackslice;
    QPieSlice *overslice;

    //按压位置的准确性
    QChartView *presspostionView;
    QPieSeries *presspostionseries;
    QPieSlice *centelslice;
    QPieSlice *upslice;
    QPieSlice *downslice;
    QPieSlice *leftslice;
    QPieSlice *rightslice;

    //放松位置的准确性
    QChartView *leavepostionView;
    QPieSeries *leavepostionseries;
    QPieSlice *rightpostionslice;
    QPieSlice *erroslice;

    //通气体积的准确性
    QChartView *vcvmmpostionView;
    QPieSeries *vcvmmpostionseries;
    QPieSlice *normalvcvslice;
    QPieSlice *lackvcvslice;
    QPieSlice *overvcvslice;

    //通气时间的准确性
    QChartView *vcvtimeView;
    QPieSeries *vcvtimeseries;
    QPieSlice *normalvcvtimeslice;
    QPieSlice *lackvcvtimeslice;
    QPieSlice *overvcvtimeslice;



};

#endif // PIEWND_H
