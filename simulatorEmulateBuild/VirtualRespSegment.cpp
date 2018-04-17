#include <math.h>
#include <fstream>
#include "Windows.h"
#include "gdiplus.h"
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include ".\virtualrespsegment.h"


using namespace Gdiplus;
namespace jysoft { namespace simulator { namespace resp {

    CVirtualRespSegment::CVirtualRespSegment(void)
    {
        m_iSampleSec = 25;   //ÿ��Ĳ�����
        m_fRemainVolume = 0.0f;
        m_fSumVolume  = 0.0f;
        //============================================
        m_hHandle    = NULL;
        m_pPtrData   = NULL;
        m_dwGlobalSize = 0;
        m_dwSize     = 0;
        m_bEmpty     = true;
    }

    CVirtualRespSegment::~CVirtualRespSegment(void)
    {
        ResetEmptySegment();
        if( m_hHandle != NULL )
        {
            ::HeapDestroy(m_hHandle);
        }
        m_hHandle = NULL;
    }

    //���ز����ε�ʱ��(0.1΢��)
    int  CVirtualRespSegment::GetSampleSumTime()
    {
        return 1000*10*m_dwSize/m_iSampleSec;
    }

    //����ʱ��(0.1΢��)���ز������ָ��
    //ע��iTime����0
    float * CVirtualRespSegment::GetSamplePtr(int  iTime)
    {
        int iStep = m_iSampleSec * iTime/10000;
        return m_pPtrData+iStep;
    }

    /*******************************************************************************/
    //���ܣ� �����ļ��ڵĺ�������
    //������ const CString &strFilePath: �����ļ�·��
    //����ֵ:
    bool CVirtualRespSegment::LoadSegmentData(const std::string &strFilePath)
    {
        //����Ϊ��
        ResetEmptySegment();
        //����Txt�ļ��еĲ�������
        std::ifstream  ifs( strFilePath.c_str() );
        if( !ifs.bad() )
        {
            long  dwSumSize  = 0;
            std::string strData;
            do
            {
                char cData[21];
                strData.clear();
                ifs.getline(cData, 20);
                strData = std::string( cData );
                if( !strData.empty() )
                {
                    float fData = boost::lexical_cast<float>(strData);
                    //�������ݿռ�
                    if( m_dwGlobalSize <= dwSumSize )
                    {
                        AllocSample( dwSumSize + 512 );
                    }
                    m_pPtrData[dwSumSize] = fData;
                    dwSumSize += 1;
                }
            } while (!strData.empty());
            ifs.close();
            m_dwSize  = dwSumSize;
        }
        else
        {
            return false;
        }
        m_bEmpty = false;
        //�趨�����������������
        GetVolumeMessageFromSegmentData(/*out*/m_fRemainVolume, /*out*/m_fSumVolume);
        return true;
    }

    //����Ϊ��
    void CVirtualRespSegment::ResetEmptySegment()
    {
        m_fRemainVolume = 0.0f;
        m_fSumVolume  = 0.0f;
        if(m_hHandle != NULL && m_pPtrData != NULL )
        {
            ::HeapFree(m_hHandle,HEAP_NO_SERIALIZE,m_pPtrData);
        }
        m_pPtrData     = NULL;
        m_dwGlobalSize = 0;
        m_dwSize       = 0;
        m_bEmpty       = true;
    }

    //�������ݿռ�
    void CVirtualRespSegment::AllocSample(unsigned long  dwGlobalSize)
    {
        if( m_hHandle == NULL )
        {
            m_hHandle = ::HeapCreate(HEAP_NO_SERIALIZE,0,0);
        }
        if( m_dwGlobalSize < dwGlobalSize )
        {
            m_dwGlobalSize = (dwGlobalSize/512+1)*512;
            if( m_pPtrData == NULL )
            {
                m_pPtrData  = (float *)::HeapAlloc( m_hHandle,HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY,m_dwGlobalSize*sizeof(float) );
            }
            else
            {
                m_pPtrData = (float *)::HeapReAlloc(m_hHandle,HEAP_ZERO_MEMORY,(void *)m_pPtrData,m_dwGlobalSize*sizeof(float));
            }
        }
    }

    //����
    void CVirtualRespSegment::Clone(CVirtualRespSegment *pOrgRespSegment)
    {
        m_iSampleSec = pOrgRespSegment->m_iSampleSec;
        if( m_hHandle == NULL )
        {
            m_hHandle = ::HeapCreate(HEAP_NO_SERIALIZE,0,0);
        }
        else if( m_pPtrData != NULL )
        {
            short  dwGlobalSize = ((pOrgRespSegment->m_dwSize + 1)/512 + 1) * 512;
            if( m_dwGlobalSize < dwGlobalSize )
            {
                ::HeapFree(m_hHandle,HEAP_NO_SERIALIZE, m_pPtrData);
                m_pPtrData  = NULL;
            }
        }
        if( m_pPtrData == NULL )
        {
            m_dwGlobalSize = pOrgRespSegment->m_dwSize + 1;
            m_dwGlobalSize = (m_dwGlobalSize/512 + 1) * 512;
            m_pPtrData = (float *)::HeapAlloc(m_hHandle,HEAP_ZERO_MEMORY,m_dwGlobalSize*sizeof(float));
        }

        m_dwSize = pOrgRespSegment->m_dwSize;
        if(pOrgRespSegment->m_pPtrData != NULL)
            ::memcpy((void *)m_pPtrData,(void *)pOrgRespSegment->m_pPtrData,m_dwSize*sizeof(float));
        m_bEmpty = false;
        m_fRemainVolume  = pOrgRespSegment->m_fRemainVolume;
        m_fSumVolume   = pOrgRespSegment->m_fSumVolume;
    }

    /*******************************************************************************/
    // �������ƣ� ZoomSegmentDataHandle
    // ���ܣ� ���Ų������ݴ���
    // ������ int iMilliChgedTime: ѹ������ʱ��(��λ:0.1ms)
    // ����ֵ:
    //         ע�����º����Ŀ�ʼλ�ö�Ϊ��㣬��Чʱ��Ϊ���в�����
    void CVirtualRespSegment::ZoomSegmentDataHandle(int iMilliChgedTime)
    {
    #define  DEFINITE   0.0001
        int iValidTime = 10000 * m_dwSize / m_iSampleSec;
        if(iValidTime == iMilliChgedTime)
            return;
        float fZoom = 1.0f * iMilliChgedTime/iValidTime;
        if(::fabs(fZoom-1.0) > DEFINITE)
        {
            int iSize = GetSampleNum(iMilliChgedTime)+100;
            short  dwAllocSize = ( iSize*sizeof(float)/512 + 1) * 512;
            float *pPtr = (float *)::HeapAlloc(m_hHandle,HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY,dwAllocSize );
            short iNum =0;//ʵ�ʱ���ĸ���
            if(fZoom > 1.0)
            {//��չ����
                float fSample = 1.0f/fZoom;
                pPtr[iNum++] = *m_pPtrData;
                for(short iStep = 1; iStep < m_dwSize;)
                {
                    float fValue = (*(m_pPtrData+iStep) - *(m_pPtrData+(iStep-1)))/2 + *(m_pPtrData+iStep-1);
                    if((fSample - 1.0) > DEFINITE)
                    {
                        fSample -= 1.0f;
                        ++iStep;
                    }
                    fSample += 1.0f/fZoom;
                    pPtr[iNum] =fValue;
                    ++iNum;
                }
            }else
            {//��������ȡ����
                float fRate = 1.0f/fZoom;
                float fSample = fRate;
                pPtr[iNum++] = *m_pPtrData;
                for(short iStep = 1; iStep < m_dwSize; ++iStep)
                {
                    if( (fSample - (iStep-1)) > DEFINITE &&  fSample < (iStep + DEFINITE))
                    {
                        float fValue = (*(m_pPtrData + (iStep-1)) + *(m_pPtrData +iStep))/2;
                        pPtr[iNum] =fValue;
                        ++iNum;
                        fSample += fRate;
                    }
                }
            }
            if(m_dwGlobalSize < iNum)
            {
                m_dwGlobalSize = (iNum*sizeof(float)/512 + 1)*512/sizeof(float);
                ::HeapFree(m_hHandle,HEAP_NO_SERIALIZE,m_pPtrData);
                m_pPtrData = (float *)::HeapAlloc(m_hHandle,HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY,m_dwGlobalSize*sizeof(float));
            }
            ::memcpy((void *)m_pPtrData,(void *)pPtr,iNum*sizeof(float));
            float *pEndPtr = GetSamplePtr(iMilliChgedTime);
            float fValue = m_pPtrData[iNum-1];
            for(;m_pPtrData + iNum < pEndPtr;++iNum)
            {
                m_pPtrData[iNum] = fValue;
            }
            m_dwSize = iNum;
            ::HeapFree(m_hHandle,HEAP_NO_SERIALIZE, pPtr);
        }
        //�ɲ������ݻ�ȡ��ǰ�Ĳ��������ͳ�����
        GetVolumeMessageFromSegmentData(/*out*/m_fRemainVolume, /*out*/m_fSumVolume);
    }

    /*******************************************************************************/
    // �������ƣ� ZoomRespVolumeHandle
    // ���ܣ� ͬ��ӳ�䷽ʽ�޸Ĳ�������
    // ������ float fRemainVolume��������������λ��ml��
    //        float fSumVolume ��  �������  ����λ��ml��
    // ����ֵ:
    void CVirtualRespSegment::ZoomRespVolumeHandle(float fRemainVolume, float fSumVolume)
    {
        //�޸Ĳ�������
        for (short nIndex = 0; nIndex < m_dwSize; ++nIndex)
        {
            m_pPtrData[nIndex] -= m_fRemainVolume;
        }
        float fOriginTideVolume = m_fSumVolume - m_fRemainVolume;
        //���㳱����
        float  fTideVoluem = fSumVolume - fRemainVolume;
        Matrix   cMatrix;
        float fSy = fTideVoluem/fOriginTideVolume;
        //---------------------------------------------------------------------------------
        cMatrix.SetElements(1.0f,0.0f,0.0f,fSy,0.0f,0);
        PointF   cTmpPoint[100];
        short   dwSize = m_dwSize;
        while ( dwSize > 0 )
        {
            short  dwCalculateNum = dwSize > 100 ? 100 : dwSize;
            for (short nIndex = 0; nIndex < dwCalculateNum; ++nIndex)
            {
                cTmpPoint[nIndex].X = nIndex*1.0f;
                cTmpPoint[nIndex].Y = m_pPtrData[m_dwSize-dwSize+nIndex];
            }
            //ͨ�������������
            cMatrix.TransformPoints(cTmpPoint, dwCalculateNum);
            //�޸Ļ������ڵ�����
            for (short nIndex = 0; nIndex < dwCalculateNum; ++nIndex)
            {
                m_pPtrData[m_dwSize-dwSize+nIndex] = cTmpPoint[nIndex].Y + fRemainVolume;
            }
            dwSize -= dwCalculateNum;
        }
        m_fRemainVolume = fRemainVolume;
        m_fSumVolume  = fSumVolume;
    }
}}}
