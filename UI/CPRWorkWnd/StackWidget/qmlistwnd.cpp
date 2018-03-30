#include "qmlistwnd.h"
#include "CPRWorkWnd/cprworkdefin.h"
#include <QString>
#define BlackgroundBlackSheet "font-family: Montserrat-Bold;\
                               font-size: 200px;\
                               font-weight: 900;\
                               background-color:rgba(0, 0, 0, 0);\
                               color: rgba(255, 255, 255, 0.05);"
#define BlackgroundWhiteSheet "font-family: Montserrat-Bold;\
                          font-size: 200px;\
                          font-weight: 900;\
                          background-color:rgba(0, 0, 0, 0);\
                          color: rgba(0, 0, 0, 0.1);"
QMlistWnd::QMlistWnd(QWidget *parent,blackgroundColor color):
   QPushButton(parent),indexNum(-1),blackgroundLa(Q_NULLPTR)
{
    Bcolor = color;
    setSheet();
}

void QMlistWnd::clickedSheet()
{
    if(Bcolor == blackBlackground){
        this->setStyleSheet(QString("QPushButton{border:1px solid #45c0f9}"));
    }
    if(Bcolor == WhiteBlackground){
        this->setStyleSheet(QString("QPushButton{image:url(:/image/ButtonNoClicked.png)}"));
    }
}

void QMlistWnd::sheet()
{
    if(Bcolor == blackBlackground){
        this->setStyleSheet(QString("QPushButton{border:1px solid #2c2e43}"));
    }
    if(Bcolor == WhiteBlackground){
        this->setStyleSheet(QString("QPushButton{image:url(:/image/ButtonClicked.png)}"));
    }
}

void QMlistWnd::setSheet()
{
    if(Bcolor == None){
        return;
    }
    createControl();
    if(Bcolor == blackBlackground){
        logo8->hide();logo9->hide();
        Data7->hide();Data8->hide();Data9->hide();
        blackgroundLa->setGeometry(5,5,ListWndWidth-10,ListWndHeight-10);
        blackgroundLa->setStyleSheet(BlackgroundBlackSheet);
        logo1->setGeometry(35,25,20,30);
        logo2->setGeometry(35,100,20,30);
        logo3->setGeometry(120,30,20,20);
        logo4->setGeometry(120,70,20,20);
        logo5->setGeometry(120,110,20,20);
        logo6->setGeometry(35,150,20,20);
        logo7->setGeometry(120,150,20,20);

        Data1->setGeometry(30,65,40,25);//总分
        Data2->setGeometry(150,25,40,25);//按压正确百分比
        Data3->setGeometry(150,70,40,25);//吹气正确百分比
        Data4->setGeometry(150,110,40,25);//按压时间占比
        Data5->setGeometry(150,150,40,25);//按压中断时间
        Data6->setGeometry(60,146,40,25);//CPR操作时间

        precentla1->setStyleSheet(QString("font-family: PingFangSC-Regular;font-size: 16px;color: #ffffff;background-color:rgba(0, 0, 0, 0);"));
        precentla1->setText(QString("%"));

        Data1->setStyleSheet(QString("font-family: PingFangSC-Semibold;font-size: 28px;color: #ffffff;background-color:rgba(0, 0, 0, 0);"));
        Data2->setStyleSheet("font-family: PingFangSC-Regular;font-size: 14px;color: #ffffff;background-color:rgba(0, 0, 0, 0);");
        Data3->setStyleSheet("font-family: PingFangSC-Regular;font-size: 14px;color: #ffffff;background-color:rgba(0, 0, 0, 0);");
        Data4->setStyleSheet("font-family: PingFangSC-Regular;font-size: 14px;color: #ffffff;background-color:rgba(0, 0, 0, 0);");
        Data5->setStyleSheet("font-family: PingFangSC-Regular;font-size: 14px;color: #ffffff;background-color:rgba(0, 0, 0, 0);");
        Data6->setStyleSheet("font-family: PingFangSC-Regular;font-size: 14px;color: #ffffff;background-color:rgba(0, 0, 0, 0);");
        precentla1->setGeometry(65,70,15,15);

    }
    if(Bcolor == WhiteBlackground){
        logo3->hide();logo4->hide();logo5->hide();logo6->hide();logo7->hide();precentla1->hide();
        blackgroundLa->setGeometry(20,20,420,181);
        blackgroundLa->setStyleSheet(BlackgroundWhiteSheet);
        logo1->setGeometry(20,20,20,20);
        logo2->setGeometry(405,15,20,30);
        logo8->setGeometry(46,125,20,20);
        logo9->setGeometry(46,157,20,20);

        Data1->setGeometry(30,40,110,71);//总分
        Data1->setStyleSheet(QString("font-family: SourceHanSansCN-Heavy;font-size: 56px;color: #37394f;border-bottom:1px solid #d1cfd1"));
//        Data1->setText("70%");

        Data2->setGeometry(200,70,60,30);//按压深度
        Data2->setStyleSheet(QString("font-family: Montserrat-Bold;font-size: 36px;color: #73b83b;background-color:rgba(0,0,0,0);"));
//        Data2->setText("60");

        Data3->setGeometry(255,70,80,30);//按压频率
        Data3->setStyleSheet(QString("font-family: Montserrat-Bold;font-size: 36px;color: #ec407a;background-color:rgba(0,0,0,0);"));
//        Data3->setText("100");

        Data4->setGeometry(356,70,30,30);
        Data4->setStyleSheet(QString("font-family: PingFangSC-Semibold;font-size: 28px;color: #37394f;background-color:rgba(0,0,0,0);"));
//        Data4->setText(QString("是\0"));

        Data7->setGeometry(350,110,60,20);
        Data7->setStyleSheet(QString("font-family: PingFangSC-Regular;font-size: 14px;color: #666666;background-color:rgba(0,0,0,0);"));
        Data7->setText(QString("释放正确\0"));

        Data5->setGeometry(210,110,30,10);
        Data5->setStyleSheet(QString("font-family: PingFangSC-Regular;font-size: 16px;color: #666666;background-color:rgba(0,0,0,0);"));
        Data5->setText("mm");

        Data6->setGeometry(275,105,30,20);
        Data6->setStyleSheet(QString("font-family: PingFangSC-Regular;font-size: 16px;color: #666666;background-color:rgba(0,0,0,0);"));
        Data6->setText("cpm");

        Data8->setGeometry(96,127,40,12);//CPR操作时间
        Data8->setStyleSheet(QString("font-family: PingFangSC-Regular;font-size: 14px;color: #666666;background-color:rgba(0,0,0,0);"));
//        Data8->setText("00:22");

        Data9->setGeometry(96,160,40,12);//按压中断时间
        Data9->setStyleSheet(QString("font-family: PingFangSC-Regular;font-size: 14px;color: #666666;background-color:rgba(0,0,0,0);"));
//        Data9->setText("00:24");
    }
}

void QMlistWnd::createControl()
{
    blackgroundLa = new QLabel(this);
    blackgroundLa->setAlignment(Qt::AlignHCenter);

    logo1 = new QLabel(this);logo1->setStyleSheet(QString("image:url(:/image/logo1.png);background-color:rgba(0, 0, 0, 0);"));
    logo2 = new QLabel(this);logo2->setStyleSheet(QString("image:url(:/image/logo2.png);background-color:rgba(0, 0, 0, 0);"));
    logo3 = new QLabel(this);logo3->setStyleSheet(QString("image:url(:/image/logo3.png);background-color:rgba(0, 0, 0, 0);"));
    logo4 = new QLabel(this);logo4->setStyleSheet(QString("image:url(:/image/logo4.png);background-color:rgba(0, 0, 0, 0);"));
    logo5 = new QLabel(this);logo5->setStyleSheet(QString("image:url(:/image/logo5.png);background-color:rgba(0, 0, 0, 0);"));
    logo6 = new QLabel(this);logo6->setStyleSheet(QString("image:url(:/image/logo6.png);background-color:rgba(0, 0, 0, 0);"));
    logo7 = new QLabel(this);logo7->setStyleSheet(QString("image:url(:/image/logo7.png);background-color:rgba(0, 0, 0, 0);"));
    logo8 = new QLabel(this);logo8->setStyleSheet(QString("image:url(:/image/logo8.png);background-color:rgba(0, 0, 0, 0);"));
    logo9 = new QLabel(this);logo9->setStyleSheet(QString("image:url(:/image/logo9.png);background-color:rgba(0, 0, 0, 0);"));

    precentla1 = new QLabel(this);

    Data1 = new QLabel(this);

    Data2 = new QLabel(this);
    Data3 = new QLabel(this);
    Data4 = new QLabel(this);
    Data5 = new QLabel(this);
    Data6 = new QLabel(this);
    Data7 = new QLabel(this);
    Data8 = new QLabel(this);
    Data9 = new QLabel(this);
}


void QMlistWnd::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        emit MDoubleClicked(remark);
    }
}

void QMlistWnd::LoadCPRSample(const _CPRData *ptrCPRDatas, int nLength)
{

}

void QMlistWnd::AddCPRErrorSign(_eCPRErrorSign eErrorSign)
{

}

void QMlistWnd::doLinkCPRStatisticUpdateShow()
{   //连接显示通知

}

void QMlistWnd::cutLinkCPRStatisticUpdateShow()
{//断开显示通知
    indexNum = -1;
    remark.clear();
}

void QMlistWnd::UpdateCPRStatistic(boost::optional<int> calcGradePec, int nPressureSumNum, int nPressureRightNum, int nBreathSumNum, int nBreathRightNum)
{
    //    calcGradePec.is
}
//操作时间、按压中断时间通知、按压时间占比

void QMlistWnd::UpdateCPRTimeStatic(int cprPeriodTime, boost::optional<int> interruptTime, boost::optional<int> pressureTimePercent)
{
    if(Bcolor == blackBlackground){
        Data6->setText(QString::number(cprPeriodTime));
        if(pressureTimePercent.is_initialized()){
             Data4->setText(QString::number(*pressureTimePercent)+QString("%"));
        }
    }
    else if(Bcolor == WhiteBlackground){

    }
}
//按压统计：正确百分比、中断时间、平均深度、平均频率、位置正确百分比、释放正确百分比、按压过大、按压过小
void QMlistWnd::UpdatePressureStatic(int calcGradePec, int interruptTime, int nAvergeDepth,
                                     int nAvergeRate, int sumNum, int posRightPec, int releasRightPec, int depthOverNum, int depthLowerNum)
{
    if(Bcolor == blackBlackground){
         Data2->setText(QString::number(calcGradePec)+QString("%"));
         Data5->setText(QString::number(interruptTime)+QString("s"));
    }
    else if(Bcolor == WhiteBlackground){

    }
}
//吹气统计：正确百分比、平均吹气量、平均吹气频率、总吹气数、过大、过小、通气多长、通气多短
void QMlistWnd::UpdateBreathStatic(int calGradePec, int nAvergeVolume, int nAvergeRate,
                                   int sumNum, int volumeOverNum, int volumeLowerNum, int ventiOverTimeNum, int ventiLowerTimeNum)
{
    if(Bcolor == blackBlackground){
        Data3->setText(QString::number(calGradePec)+QString("%"));
    }
    else if(Bcolor == WhiteBlackground){

    }
}
