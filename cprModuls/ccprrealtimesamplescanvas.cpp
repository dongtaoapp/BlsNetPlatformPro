#include "ccprrealtimesamplescanvas.h"
#include "QMutexLocker"

#include "..\Common\ParseCPRData_Singleton.h"

CCPRRealTimeSamplesCanvas::CCPRRealTimeSamplesCanvas()
{
    m_pSampleBufferState = NULL;
    m_pDistributeCPRRealTimeData = NULL;
//    m_bCpring = false;
}

CCPRRealTimeSamplesCanvas::~CCPRRealTimeSamplesCanvas()
{
    std::list<ICPRSampleBufferState*>::iterator it;
    for(it=m_lstCprBuff.begin();it!=m_lstCprBuff.end();it++)
    {
      ICPRSampleBufferState* item = *it;
      if(item->isKindOf("CCPRSamplingBufferState"))
      {
          delete ((CCPRSamplingBufferState*)item);
      }
      else if(item->isKindOf("CCPRSampleEmptyBufferState"))
      {
          delete ((CCPRSampleEmptyBufferState*)item);
      }
    }
    m_lstCprBuff.clear();
}

void CCPRRealTimeSamplesCanvas::StartLinkCprRealTimeShowInterface(IDistributeCPRRealTimeData *pDistributeCPRRealTimeData)
{
    m_pDistributeCPRRealTimeData = pDistributeCPRRealTimeData;
    const int nNeededLen = m_pDistributeCPRRealTimeData->GetNeededCPRDataLen();
//    _CPRData cprDatas[nNeededLen];
    _CPRData *pCprDatas = new _CPRData[nNeededLen];
    QMutexLocker lock(&m_cMutex);
    int nDataLen = GetCprDataInMem(pCprDatas,nNeededLen);
    m_pDistributeCPRRealTimeData->DistributeCPRDataInMem(pCprDatas,nDataLen);
    delete[] pCprDatas;
}

void CCPRRealTimeSamplesCanvas::CutLinkCprRealTimeShowInterface()
{
    //��ս�������
    m_pDistributeCPRRealTimeData->AllClear();
    m_pDistributeCPRRealTimeData = NULL;
}

int CCPRRealTimeSamplesCanvas::GetCprDataInMem(_CPRData *ptrCPRDatas, int nMaxLength)
{
    if(m_lstCprBuff.empty() || nMaxLength == 0)
        return 0;

    int nGetDataLen = 0;
    std::list<ICPRSampleBufferState*>::reverse_iterator it;
    for(it = m_lstCprBuff.rbegin(); it != m_lstCprBuff.rend(); it++)
    {
        ICPRSampleBufferState* pCPRSampleBuffer = *it;
        if(pCPRSampleBuffer != NULL)
        {
            if(!pCPRSampleBuffer->cprBuff.empty())
            {
                std::list<_CPRData>::reverse_iterator itCpr;
                for(itCpr = pCPRSampleBuffer->cprBuff.rbegin(); itCpr != pCPRSampleBuffer->cprBuff.rend(); itCpr++)
                {
                    _CPRData data = *itCpr;
                    ptrCPRDatas[nGetDataLen] = data;
                    nGetDataLen++;
                    //����Ѵﵽ���������
                    if( nGetDataLen == nMaxLength)
                        break;
                }
            }

        }
        if( nGetDataLen == nMaxLength)
            break;
    }
    return nGetDataLen;
}

int CCPRRealTimeSamplesCanvas::GetCprDataInBuf(_CPRData *ptrCPRDatas,ICPRSampleBufferState *pSampleBufferState, int nLength)
{

    int nIndex = nLength;
    std::list<_CPRData>::reverse_iterator itCpr;
    for(itCpr = pSampleBufferState->cprBuff.rbegin(); (itCpr != pSampleBufferState->cprBuff.rend()) && (nIndex > 0); itCpr++,nIndex--)
    {
        ptrCPRDatas[nLength - nIndex] = *itCpr;
    }


    return nLength - nIndex;
}

void CCPRRealTimeSamplesCanvas::LoadCPRSample(const _CPRData *ptrCPRDatas, int nLength)
{
    const CParseCPRData_Singleton &cParseCPRData = CParseCPRData_Singleton::get_const_instance();
    QMutexLocker lock(&m_cMutex);
    int nSendLen = 0; //�ñ�����¼��cprʵʱ��ʾ�ؼ��������ݵĳ��ȣ�����ͳ��һ������ʵʱ��ʾ�ؼ����ݶ�������
    for(short index = 0; index < nLength; ++index)
    {
        if(m_pSampleBufferState != NULL && m_pSampleBufferState->isKindOf("CCPRSamplingBufferState"))
        {
            //�ж�CPR��������
            if(cParseCPRData.judgeCPRStartOrStopOrder(ptrCPRDatas[index], false))
            {
                //�յ�����ָ��,Ͷ�ݽ���ָ��ǰ������
                if(nSendLen > 0)
                {
                    _CPRData* pSendData = new _CPRData[nSendLen];
                    int nGetDataLen = GetCprDataInBuf(pSendData,m_pSampleBufferState,nSendLen);
                     m_pDistributeCPRRealTimeData->DistributeCPRData(pSendData,nGetDataLen);
                    delete[] pSendData;
                }
                nSendLen = 0;


                m_pSampleBufferState = (ICPRSampleBufferState*)new CCPRSampleEmptyBufferState();
                ((CCPRSampleEmptyBufferState*)m_pSampleBufferState)->startAddEmptyCprData();
                m_lstCprBuff.push_back(m_pSampleBufferState);
            }
            else
            {
                ((CCPRSamplingBufferState*)m_pSampleBufferState)->addCprData(ptrCPRDatas[index]);
                //���������ʵʱ��ʾ�ӿڣ���ͳ�Ʒ������ݵĳ���
                if(m_pDistributeCPRRealTimeData != NULL)
                {

                    nSendLen++;

                    //�������ȫ�����꣬��Ͷ������
                    if(index+1 ==  nLength)
                    {
                        _CPRData* pSendData = new _CPRData[nSendLen];
                        int nGetDataLen = GetCprDataInBuf(pSendData,m_pSampleBufferState,nSendLen);
                         m_pDistributeCPRRealTimeData->DistributeCPRData(pSendData,nGetDataLen);
                        delete[] pSendData;
                    }

//                      _CPRData d = ptrCPRDatas[index];
//                    m_pDistributeCPRRealTimeData->DistributeCPRData(&d,1);
                }
            }
        }
        else
        {
            //�ж�CPR��ʼ����
            if(cParseCPRData.judgeCPRStartOrStopOrder(ptrCPRDatas[index], true))
            {
                if(m_pSampleBufferState == NULL)
                {
                    m_pSampleBufferState = (ICPRSampleBufferState*)new CCPRSamplingBufferState();
                    m_lstCprBuff.push_back(m_pSampleBufferState);

                }
                else if(m_pSampleBufferState->isKindOf("CCPRSampleEmptyBufferState"))
                {
                    ((CCPRSampleEmptyBufferState*)m_pSampleBufferState)->stopAddEmptyCprData();
                    m_pSampleBufferState = (ICPRSampleBufferState*)new CCPRSamplingBufferState();
                    m_lstCprBuff.push_back(m_pSampleBufferState);
                }

            }
        }
    }


}

void CCPRRealTimeSamplesCanvas::AddCPRErrorSign(_eCPRErrorSign eErrorSign)
{
    if(m_pDistributeCPRRealTimeData != NULL)
    {
        m_pDistributeCPRRealTimeData->AddCPRErrorSign(eErrorSign);
    }
}
