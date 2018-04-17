#ifndef CPRSAMPLEBUFFERSTATE_H
#define CPRSAMPLEBUFFERSTATE_H

#include ".\cprmoduls_global.h"
#include <string>
#include <list>
#include <QObject>

#include "..\Common\CommonGlobal.h"


/*-----------------------------------------------------------------------------------------------------------------
��˵����     CPR����������ʾʱ�������ṩ��ʽ����ӿ���
�����ˣ�	 hjg
����ʱ�䣺   2008/12/25
//-----------------------------------------------------------------------------------------------------------------*/

class ICPRSampleBufferState
{
public:
    ICPRSampleBufferState(void);
    virtual ~ICPRSampleBufferState(void);
public:
public:
    virtual bool isKindOf(const std::string &className) = 0;
    /*******************************************************************************/
    // �������ƣ� OnWriteCPRRealTimeData
    // ���ܣ� д��CPR��������
    // ������ lpDataPtrs: CPR����
    //        int nLength: ���ݸ���
    // ����ֵ:
    virtual void OnWriteCPRRealTimeData(const _CPRData *lpDataPtrs, short sLength){}
public:
    std::list<_CPRData>         cprBuff;
};


/*-----------------------------------------------------------------------------------------------------------------
��˵����     CPR����������ʾʱ���޲��������ṩ��ʽ��
�����ˣ�	 hjg
����ʱ�䣺   2008/12/25
//-----------------------------------------------------------------------------------------------------------------*/
class CCPRSampleEmptyBufferState : public QObject
                                ,public ICPRSampleBufferState
{
     Q_OBJECT
public:
    CCPRSampleEmptyBufferState(QObject * parent =0);
    virtual ~CCPRSampleEmptyBufferState(void);
public:
    virtual bool isKindOf(const std::string &className);
public:
    void    timerEvent(QTimerEvent* event);
public:
    void    startAddEmptyCprData() {  m_nTimerId = startTimer(50); }
    void    stopAddEmptyCprData()   { killTimer(m_nTimerId); }
protected:
    int     m_nTimerId;
};


/*-----------------------------------------------------------------------------------------------------------------
��˵����     CPR����������ʾʱ�����������ṩ��ʽ��
�����ˣ�	 hjg
����ʱ�䣺   2008/12/25
//-----------------------------------------------------------------------------------------------------------------*/
class CCPRSamplingBufferState : public ICPRSampleBufferState
{
public:
    CCPRSamplingBufferState(void);
    virtual ~CCPRSamplingBufferState(void);
public:
    virtual bool isKindOf(const std::string &className);
public:
    void    addCprData(_CPRData data) { cprBuff.push_back(data); }
//    /*******************************************************************************/
//    // �������ƣ� OnGetCPRRealTimeData
//    // ���ܣ� ��ȡCPR��������
//    // ������ /*out*/BYTE *lpDataPtr: CPR����
//    //        int nLength: ��ȡ�Ĳ������ݸ���
//    // ����ֵ:
//    virtual int OnGetCPRRealTimeData(/*out*/_CPRData *lpDataPtr, int nLength, bool *bExchangeState);
//private:
//    short      m_sEmptySampleNum;    //�ղ�������ȱʧ������ע�����������ݱ�ʾ�����ṩ��ʾ���ݡ�
};

#endif // CPRSAMPLEBUFFERSTATE_H
