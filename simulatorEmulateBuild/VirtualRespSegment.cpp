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
        m_iSampleSec = 25;   //每秒的采样率
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

    //返回采样段的时间(0.1微秒)
    int  CVirtualRespSegment::GetSampleSumTime()
    {
        return 1000*10*m_dwSize/m_iSampleSec;
    }

    //根据时间(0.1微秒)返回采样点的指针
    //注：iTime大于0
    float * CVirtualRespSegment::GetSamplePtr(int  iTime)
    {
        int iStep = m_iSampleSec * iTime/10000;
        return m_pPtrData+iStep;
    }

    /*******************************************************************************/
    //功能： 加载文件内的呼吸数据
    //参数： const CString &strFilePath: 数据文件路径
    //返回值:
    bool CVirtualRespSegment::LoadSegmentData(const std::string &strFilePath)
    {
        //设置为空
        ResetEmptySegment();
        //加载Txt文件中的采样数据
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
                    //分配数据空间
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
        //设定残留气量和最大气量
        GetVolumeMessageFromSegmentData(/*out*/m_fRemainVolume, /*out*/m_fSumVolume);
        return true;
    }

    //设置为空
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

    //分配数据空间
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

    //拷贝
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
    // 函数名称： ZoomSegmentDataHandle
    // 功能： 缩放采样数据处理
    // 参数： int iMilliChgedTime: 压缩到的时间(单位:0.1ms)
    // 返回值:
    //         注：以下函数的开始位置都为起点，有效时间为所有采样点
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
            short iNum =0;//实际保存的个数
            if(fZoom > 1.0)
            {//扩展数据
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
            {//从数据区取数据
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
        //由采样数据获取当前的残留气量和潮气量
        GetVolumeMessageFromSegmentData(/*out*/m_fRemainVolume, /*out*/m_fSumVolume);
    }

    /*******************************************************************************/
    // 函数名称： ZoomRespVolumeHandle
    // 功能： 同过映射方式修改采样数据
    // 参数： float fRemainVolume：残留气量（单位：ml）
    //        float fSumVolume ：  最大气量  （单位：ml）
    // 返回值:
    void CVirtualRespSegment::ZoomRespVolumeHandle(float fRemainVolume, float fSumVolume)
    {
        //修改残留气量
        for (short nIndex = 0; nIndex < m_dwSize; ++nIndex)
        {
            m_pPtrData[nIndex] -= m_fRemainVolume;
        }
        float fOriginTideVolume = m_fSumVolume - m_fRemainVolume;
        //计算潮气量
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
            //通过矩阵计算数据
            cMatrix.TransformPoints(cTmpPoint, dwCalculateNum);
            //修改缓冲区内的数据
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
