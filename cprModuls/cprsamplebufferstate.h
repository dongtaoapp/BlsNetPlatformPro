#ifndef CPRSAMPLEBUFFERSTATE_H
#define CPRSAMPLEBUFFERSTATE_H

#include ".\cprmoduls_global.h"
#include <string>
#include <list>
#include <QObject>

#include "..\Common\CommonGlobal.h"


/*-----------------------------------------------------------------------------------------------------------------
类说明：     CPR采样数据显示时，数据提供方式定义接口类
创建人：	 hjg
创建时间：   2008/12/25
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
    // 函数名称： OnWriteCPRRealTimeData
    // 功能： 写入CPR采样数据
    // 参数： lpDataPtrs: CPR数据
    //        int nLength: 数据个数
    // 返回值:
    virtual void OnWriteCPRRealTimeData(const _CPRData *lpDataPtrs, short sLength){}
public:
    std::list<_CPRData>         cprBuff;
};


/*-----------------------------------------------------------------------------------------------------------------
类说明：     CPR采样数据显示时，无采样数据提供方式类
创建人：	 hjg
创建时间：   2008/12/25
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
类说明：     CPR采样数据显示时，采样数据提供方式类
创建人：	 hjg
创建时间：   2008/12/25
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
//    // 函数名称： OnGetCPRRealTimeData
//    // 功能： 获取CPR采样数据
//    // 参数： /*out*/BYTE *lpDataPtr: CPR数据
//    //        int nLength: 获取的采样数据个数
//    // 返回值:
//    virtual int OnGetCPRRealTimeData(/*out*/_CPRData *lpDataPtr, int nLength, bool *bExchangeState);
//private:
//    short      m_sEmptySampleNum;    //空采样数据缺失计数【注：连续无数据表示不再提供显示数据】
};

#endif // CPRSAMPLEBUFFERSTATE_H
