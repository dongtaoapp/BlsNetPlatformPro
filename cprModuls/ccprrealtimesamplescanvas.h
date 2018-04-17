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
    //���ػ����е�cpr���ݣ��������ݵ�˳��Ϊ������->������
    int    GetCprDataInMem(/*out*/_CPRData *ptrCPRDatas, int nMaxLength);
    //��ȡָ��buff�е����ݣ��������ݵ�˳��Ϊ������->������
    int    GetCprDataInBuf(/*out*/_CPRData *ptrCPRDatas,ICPRSampleBufferState* pSampleBufferState, int nLength);
protected:
//    //�Խ���ʾ��֪ͨ
//    virtual void doLinkCPRRealTimeUpdateShow() { };
//    //�Ͽ���ʾ��֪ͨ
//    virtual void cutLinkCPRRealTimeUpdateShow() { };
    //�õ�CPR������
    virtual void LoadCPRSample(const _CPRData *ptrCPRDatas, int nLength);
    //��������־
    virtual void AddCPRErrorSign(_eCPRErrorSign eErrorSign);
protected:
    ICPRSampleBufferState*                          m_pSampleBufferState;
    QMutex                                          m_cMutex;
    std::list<ICPRSampleBufferState* >              m_lstCprBuff;
    IDistributeCPRRealTimeData*                     m_pDistributeCPRRealTimeData;
//    bool                                            m_bCpring;  //�Ƿ����ڽ���cpr

};

#endif // CCPRREALTIMESAMPLESCANVAS_H
