#ifndef CCPRREALTIMESAMPLESCANVAS_H
#define CCPRREALTIMESAMPLESCANVAS_H

#include ".\cprmoduls_global.h"
#include "cprsamplebufferstate.h"
#include <QMutex>
#include "idistributecprrealtimedata.h"

#include "../simulatorBase/CPRRealTimeUpdateInterface.h"

using namespace jysoft::cpr;

class  CPRMODULSSHARED_EXPORT CCPRRealTimeSamplesCanvas : public CCPRRealTimeUpdateInterface
{
public:
    CCPRRealTimeSamplesCanvas();
    virtual ~CCPRRealTimeSamplesCanvas(void);
public:
    void    StartLinkCprRealTimeShowInterface(IDistributeCPRRealTimeData* pDistributeCPRRealTimeData);
    void    CutLinkCprRealTimeShowInterface(); //{ m_pDistributeCPRRealTimeData = NULL; }
protected:
    //返回缓存中的cpr数据，返回数据的顺序为新数据->旧数据
    int    GetCprDataInMem(/*out*/_CPRData *ptrCPRDatas, int nMaxLength);
    //获取指定buff中的数据，返回数据的顺序为新数据->旧数据
    int    GetCprDataInBuf(/*out*/_CPRData *ptrCPRDatas,ICPRSampleBufferState* pSampleBufferState, int nLength);
protected:
//    //对接显示后通知
//    virtual void doLinkCPRRealTimeUpdateShow() { };
//    //断开显示后通知
//    virtual void cutLinkCPRRealTimeUpdateShow() { };
    //得到CPR的数据
    virtual void LoadCPRSample(const _CPRData *ptrCPRDatas, int nLength);
    //加入错误标志
    virtual void AddCPRErrorSign(_eCPRErrorSign eErrorSign);
protected:
    ICPRSampleBufferState*                          m_pSampleBufferState;
    QMutex                                          m_cMutex;
    std::list<ICPRSampleBufferState* >              m_lstCprBuff;
    IDistributeCPRRealTimeData*                     m_pDistributeCPRRealTimeData;
//    bool                                            m_bCpring;  //是否正在进行cpr

};

#endif // CCPRREALTIMESAMPLESCANVAS_H
