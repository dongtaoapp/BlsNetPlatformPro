#ifndef QMLISTWND_H
#define QMLISTWND_H
#include <QPushButton>
#include <QMouseEvent>
#include <QLabel>

#include "CPRRealTimeUpdateInterface.h"
#include "ShowCPRStatisticUpdateInterface.h"
class QMlistWnd : public QPushButton,public  jysoft::cpr::CCPRRealTimeUpdateInterface,public jysoft::cpr::CShowCPRStatisticUpdateInterface
{
    Q_OBJECT
public:
    enum blackgroundColor{
        blackBlackground = 0,
        WhiteBlackground = 1,
        None = 2,
    };

    QMlistWnd(QWidget *parent = 0,blackgroundColor color = blackBlackground);
    ~QMlistWnd(){;}
    void setIndexNum(int index){
        indexNum = index;
        if(blackgroundLa != Q_NULLPTR){blackgroundLa->setText(QString::number(indexNum));}
    }
private:
    int indexNum,Bcolor;
    QString remark;
    QLabel *blackgroundLa;QLabel *logo1;QLabel *logo2;QLabel *logo3;QLabel *logo4;QLabel *logo5;QLabel *logo6;QLabel *logo7;QLabel *logo8;QLabel *logo9;
    QLabel *precentla1;

    QLabel *Data1;QLabel *Data2;QLabel *Data3;QLabel *Data4;QLabel *Data5;QLabel *Data6;QLabel *Data7;QLabel *Data8;QLabel *Data9;


    QString pressTime;
public:
    void clickedSheet();
    void sheet();
    int GetIndexNum(){return indexNum;}
    void setRemark(QString ManikinRemark){remark = ManikinRemark;}
    QString  GetRemark(){return remark;}
    void setSheet();
    void createControl();
Q_SIGNALS:
    void MDoubleClicked(QString);
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

/***********************************
            数据接口
*************************************/
protected:

    void LoadCPRSample(const _CPRData *ptrCPRDatas, int nLength);

    void AddCPRErrorSign(_eCPRErrorSign eErrorSign);

    //对接显示后通知
    virtual void doLinkCPRStatisticUpdateShow();
    //断开显示后通知
    virtual void cutLinkCPRStatisticUpdateShow();
    //重置统计
    virtual void ResetCPRStatistic(_CPRManageState  eState) {};
    //更新统计次
    virtual void UpdateCPRStatistic(boost::optional<int> calcGradePec, int nPressureSumNum, int nPressureRightNum, int nBreathSumNum, int nBreathRightNum);
    //操作时间、按压中断时间通知、按压时间占比
    virtual void UpdateCPRTimeStatic(int cprPeriodTime, boost::optional<int> interruptTime,  boost::optional<int> pressureTimePercent);
    //循环统计：按压:吹气、循环次数
    virtual void UpdateCPRCycle(int pressureNum, int breathNum, boost::optional<int> cycleNum){}
    //按压位置统计(包括进胃)：
    virtual void UpdatePositionStatic(short pos_low, short pos_high, short pos_left, short pos_Right){}
    //进胃统计
    virtual void UpdateInStomachNumber( short sInStomachNum){}
    //按压统计：正确百分比、中断时间、平均深度、平均频率、位置正确百分比、释放正确百分比、按压过大、按压过小
    virtual void UpdatePressureStatic(int calcGradePec, int interruptTime, int nAvergeDepth, int nAvergeRate,
                                      int sumNum, int posRightPec, int releasRightPec, int depthOverNum, int depthLowerNum);
    //吹气统计：正确百分比、平均吹气量、平均吹气频率、总吹气数、过大、过小、通气多长、通气多短
    virtual void UpdateBreathStatic(int calGradePec, int nAvergeVolume, int nAvergeRate, int sumNum, int volumeOverNum,
                                    int volumeLowerNum, int ventiOverTimeNum, int ventiLowerTimeNum);


};

#endif // QMLISTWND_H
