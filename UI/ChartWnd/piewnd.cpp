#include "piewnd.h"
#include "ui_piewnd.h"

PieWnd::PieWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PieWnd)
{
    ui->setupUi(this);

    PressBreakTime(80);

    setRightValue(90);

    setvcvRightValue(70);


    CreatePie();


    testData();
}

PieWnd::~PieWnd()
{
    delete ui;
}
void PieWnd::setRightValue(int right)
{
    ui->pressrightValueLa->resize(right*2,12);
}
void PieWnd::PressBreakTime(int time)
{
    ui->PressBreakTimeLa->setText(QString("按压中断时间: %1 S").arg(QString::number(time)));
}
void PieWnd::setvcvRightValue(int right)
{
    ui->vcvrightvaluela->resize(right*2,12);
}
void PieWnd::CreatePie()
{
    //按压深度的准确性
    normalslice = new QPieSlice();normalslice->setColor(QColor(33,176,242));normalslice->setBorderColor(QColor(0,0,0,0));
    lackslice = new QPieSlice();lackslice->setColor(QColor(245,191,57));lackslice->setBorderColor(QColor(0,0,0,0));
    overslice = new QPieSlice();overslice->setColor(QColor(240,14,55));overslice->setBorderColor(QColor(0,0,0,0));
    pressdeepseries = new QPieSeries();pressdeepseries->setHoleSize(0.35);
    pressdeepseries->append(normalslice);pressdeepseries->append(lackslice);pressdeepseries->append(overslice);

    //按压位置的准确性
    centelslice = new QPieSlice();centelslice->setColor(QColor(33,176,242));centelslice->setBorderColor(QColor(0,0,0,0));
    upslice = new QPieSlice();upslice->setColor(QColor(164,4,181));upslice->setBorderColor(QColor(0,0,0,0));
    downslice = new QPieSlice();downslice->setColor(QColor(115,184,59));downslice->setBorderColor(QColor(0,0,0,0));
    leftslice = new QPieSlice();leftslice->setColor(QColor(245,191,57));leftslice->setBorderColor(QColor(0,0,0,0));
    rightslice = new QPieSlice();rightslice->setColor(QColor(244,87,32));rightslice->setBorderColor(QColor(0,0,0,0));
    presspostionseries = new QPieSeries();presspostionseries->setHoleSize(0.35);
    presspostionseries->append(centelslice);presspostionseries->append(upslice);presspostionseries->append(downslice);
    presspostionseries->append(leftslice);presspostionseries->append(rightslice);

    //放松位置的准确性
    rightpostionslice = new QPieSlice();rightpostionslice->setColor(QColor(33,176,242));rightpostionslice->setBorderColor(QColor(0,0,0,0));
    erroslice = new QPieSlice();erroslice->setColor(QColor(244,87,32));erroslice->setBorderColor(QColor(0,0,0,0));
    leavepostionseries = new QPieSeries();leavepostionseries->setHoleSize(0.35);
    leavepostionseries->append(rightpostionslice);leavepostionseries->append(erroslice);

    //通气体积的准确性
    normalvcvslice = new QPieSlice();normalvcvslice->setColor(QColor(33,176,242));normalvcvslice->setBorderColor(QColor(0,0,0,0));
    lackvcvslice = new QPieSlice();lackvcvslice->setColor(QColor(245,191,57));lackvcvslice->setBorderColor(QColor(0,0,0,0));
    overvcvslice = new QPieSlice();overvcvslice->setColor(QColor(240,14,55));overvcvslice->setBorderColor(QColor(0,0,0,0));
    vcvmmpostionseries = new QPieSeries();vcvmmpostionseries->setHoleSize(0.35);
    vcvmmpostionseries->append(normalvcvslice);vcvmmpostionseries->append(lackvcvslice);vcvmmpostionseries->append(overvcvslice);

    //通气时间的准确性
    normalvcvtimeslice = new QPieSlice();normalvcvtimeslice->setColor(QColor(33,176,242));normalvcvtimeslice->setBorderColor(QColor(0,0,0,0));
    lackvcvtimeslice = new QPieSlice();lackvcvtimeslice->setColor(QColor(245,191,57));lackvcvtimeslice->setBorderColor(QColor(0,0,0,0));
    overvcvtimeslice = new QPieSlice();overvcvtimeslice->setColor(QColor(240,14,55));overvcvtimeslice->setBorderColor(QColor(0,0,0,0));
    vcvtimeseries = new QPieSeries();vcvtimeseries->setHoleSize(0.35);
    vcvtimeseries->append(normalvcvtimeslice);vcvtimeseries->append(lackvcvtimeslice);vcvtimeseries->append(overvcvtimeslice);

    CreateChartView();
}
void PieWnd::CreateChartView()
{
    pressdeepview = new QChartView(ui->pressdeepwnd);
    pressdeepview->setGeometry(-100,-90,400,300);
    pressdeepview->setRenderHint(QPainter::Antialiasing);
    pressdeepview->chart()->addSeries(pressdeepseries);

    presspostionView = new QChartView(ui->presspostionwnd);
    presspostionView->setGeometry(-100,-90,400,300);
    presspostionView->setRenderHint(QPainter::Antialiasing);
    presspostionView->chart()->addSeries(presspostionseries);

    leavepostionView = new QChartView(ui->leavepostionwnd);
    leavepostionView->setGeometry(-100,-90,400,300);
    leavepostionView->setRenderHint(QPainter::Antialiasing);
    leavepostionView->chart()->addSeries(leavepostionseries);

    vcvmmpostionView = new QChartView(ui->vcvmmwnd);
    vcvmmpostionView->setGeometry(-100,-90,400,300);
    vcvmmpostionView->setRenderHint(QPainter::Antialiasing);
    vcvmmpostionView->chart()->addSeries(vcvmmpostionseries);

    vcvtimeView = new QChartView(ui->vcvtimewnd);
    vcvtimeView->setGeometry(-100,-90,400,300);
    vcvtimeView->setRenderHint(QPainter::Antialiasing);
    vcvtimeView->chart()->addSeries(vcvtimeseries);


}
void PieWnd::testData()
{
    normalslice->setValue(1.0);lackslice->setValue(1.0);overslice->setValue(1.0);
    centelslice->setValue(3.0);upslice->setValue(3.0);downslice->setValue(3.0);leftslice->setValue(3.0);rightslice->setValue(3.0);

    rightpostionslice->setValue(50.0);erroslice->setValue(50.0);

    normalvcvslice->setValue(1.0);lackvcvslice->setValue(1.0);overvcvslice->setValue(1.0);

    normalvcvtimeslice->setValue(1.0);lackvcvtimeslice->setValue(1.0);overvcvtimeslice->setValue(1.0);
}
