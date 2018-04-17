#include <math.h>
#include <fstream>
#include ".\sample.h"
#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>

#include "..\Common\CommonGlobal.h"

namespace jysoft { namespace simulator {

	CSample::CSample(void)
	{
		m_iSampleSec = 400;
		m_iSampleVolt = 4096;
		//============================================
		m_eAllocType  = Customized;
		m_hHandle     = NULL;
		m_pPtrData    = NULL;
		m_dwGlobalSize = 0;
		m_dwSize      = 0;
		m_dwID        = 0;
	}

	CSample::CSample( HANDLE hAllocHeap, int nAllocSize ) 
	{
		CSample();
		//-------------------------------------------------------------------------
		m_hHandle = hAllocHeap;
		m_eAllocType = ExternalDeliver;
		//初始分配内存
		if( nAllocSize > 0 )
		{
			AllocSample( (unsigned long)nAllocSize );
		}
	}

	CSample::CSample(unsigned long dwID)
	{
		m_dwID = dwID;
		m_iSampleSec = 400;
		m_iSampleVolt = 4096;
		//--------------------------------------------------------------------------
		m_eAllocType   = Customized;
		m_hHandle      = NULL;
		m_pPtrData     = NULL;
		m_dwGlobalSize = 0;
		m_dwSize  = 0;
	}

	CSample::CSample( HANDLE hAllocHeap, unsigned long dwID, int nAllocSize)
	{
		m_dwID = dwID;
		m_iSampleSec = 400;
		m_iSampleVolt = 4096;
		//--------------------------------------------------------------------------
		m_eAllocType   = Customized;
		m_hHandle      = NULL;
		m_pPtrData     = NULL;
		m_dwGlobalSize = 0;
		m_dwSize  = 0;
		//--------------------------------------------------------------------------
		m_hHandle = hAllocHeap;
		m_eAllocType = ExternalDeliver;
		//初始分配内存
		if( nAllocSize > 0 )
		{
			AllocSample( (unsigned long)nAllocSize );
		}
	}

	CSample::~CSample(void)
	{
		try
		{
			if(m_hHandle != NULL && m_pPtrData )
			{
				::HeapFree(m_hHandle,HEAP_NO_SERIALIZE,m_pPtrData);
			}
		}
        catch (...)
		{
		}
		if( m_hHandle != NULL && m_eAllocType != ExternalDeliver )
		{
			::HeapDestroy(m_hHandle);
		}
	}

	void CSample::ResetSample(void)
	{
		try
		{
			if(m_hHandle != NULL && m_pPtrData )
			{
				::HeapFree(m_hHandle,HEAP_NO_SERIALIZE,m_pPtrData);
			}
		}
        catch (...)
		{
		}
		m_pPtrData = NULL;
		m_dwGlobalSize = 0;
		m_dwSize  = 0;
	}

    bool CSample::LoadSampleDataFromTxt(const std::string &strPathFile)
    {
        m_dwSize   = 0;
        //----------------------------------------------------------------------------------
        std::ifstream  ifs( strPathFile.c_str() );
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
                    if( m_dwGlobalSize < (dwSumSize+1) )
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
        return true;
    }

	//加载文件中的采样数据
	bool CSample::LoadSampleDataFromStream(LPSTREAM lpFileSteam)
	{
		if(lpFileSteam == NULL)
			return false;
		m_dwSize   = 0;
		//----------------------------------------------------------------------------------
		static float fDatalst[50];
		ULONG uReadSize = 0;
		lpFileSteam->Read(fDatalst, 50*sizeof(float), &uReadSize);
		uReadSize /= sizeof(float);
	
		unsigned long  dwSumSize  = 0;
		while(uReadSize > 0)
		{
			//分配数据空间
			if( m_dwGlobalSize < (dwSumSize+50) )
			{
				AllocSample( dwSumSize + 512 );
			}
			::memcpy(m_pPtrData+dwSumSize, fDatalst, uReadSize*sizeof(float));
			dwSumSize += (unsigned long)uReadSize;
			lpFileSteam->Read(fDatalst, 50*sizeof(float), &uReadSize);
			uReadSize /= sizeof(float);
		}
		m_dwSize  = dwSumSize;
		return true;
	}


	// 函数名称： ChangeSampleData
	// 功能说明： 
	// 返回值： 
	// 参数： float *fSrcBegin：
	// 参数： const int nCount：
	// 参数： int nBeginTime：确定开始位置
	void CSample::ChangeSampleData(float *fSrcBegin,const int nCount,int nBeginTime)
	{
		float *fBeginPtr = GetSamplePtr(nBeginTime);
		unsigned long nNeedCount = (fBeginPtr-m_pPtrData)+nCount;
		if(nNeedCount > m_dwGlobalSize)
		{
			//分配数据空间
			AllocSample( nNeedCount );
		}
		m_dwSize = nNeedCount;
		fBeginPtr = GetSamplePtr(nBeginTime);
		::memcpy((void *)fBeginPtr,(void *)fSrcBegin,nCount*sizeof(float));
	}

	//拷贝
	void CSample::Clone(CSample *pOrgSample)
	{
		m_iSampleSec = pOrgSample->m_iSampleSec;
		m_iSampleVolt = pOrgSample->m_iSampleVolt;
		//分配数据空间
		AllocSample( pOrgSample->m_dwSize ); 

		m_dwSize = pOrgSample->m_dwSize;
		if(pOrgSample->m_pPtrData != NULL)
			::memcpy((void *)m_pPtrData,(void *)pOrgSample->m_pPtrData,m_dwSize*sizeof(float));
	}

	void CSample::Clone(CSample *pSrcSample,float *fpBegin,float *fpEnd)
	{
		m_iSampleSec = pSrcSample->m_iSampleSec;
		m_iSampleVolt = pSrcSample->m_iSampleVolt;
		unsigned long dwGlobalSize = (fpEnd-fpBegin)+1;
	
		//分配数据空间
		AllocSample( dwGlobalSize ); 
	
		m_dwSize = fpEnd-fpBegin;
		::memcpy((void *)m_pPtrData,(void *)fpBegin,m_dwSize*sizeof(float));
	}

	//返回采样段的时间(0.1微秒)
	int  CSample::GetSampleSumTime()
	{
		return 1000*10*m_dwSize/m_iSampleSec;
	}

	//根据时间(0.1微秒)返回采样点的指针
	//注：iTime大于0
	float * CSample::GetSamplePtr(int  iTime)
	{
		int iStep = m_iSampleSec * iTime/10000;
		return m_pPtrData+iStep;
	}

	//根据X轴的长度(毫米)，返回此长度所代表的时间(0.1微秒)
	int CSample::GetSampleTime(float fX)
	{
		return int(fX/25*10000 + DEFINITE);
	}

	//int nTime：单位0.1微秒
	//返回值：单位(毫米)
	float CSample::GetLength(int nTime)
	{
		return nTime*1.0f*25/10000;
	}

	//根据Y轴的数值，返回表示的电压(单位：毫伏)
	float CSample::GetMilliVolt(float fH)
	{
		return fH/10;
	}

	//根据电压(单位：毫伏)，返回Y轴的数值
	float CSample::GetYFromMilliVolt(float fMillVolt)
	{
		return fMillVolt * 10;
	}


	// 函数名称： AddSampleData
	// 功能说明： 用水平值fValue填充
	// 返回值： 
	// 参数： int nTime：持续时间(单位：0.1毫秒)
	// 参数： float fValue：设定的值(单位：毫伏)
	void  CSample::AddSampleData(int nDstBeginTime, int nTime, float fValue)
	{
		int iNum = int(1.0f*nTime/10000*m_iSampleSec+DEFINITE);
		if( (m_dwSize + iNum ) > m_dwGlobalSize)
		{
			//分配数据空间
			AllocSample( m_dwGlobalSize + iNum ); 
		}
		float *pPtr = GetSamplePtr(nDstBeginTime);
		for(int i=0;i<iNum;i++)
			pPtr[i] = fValue;
		m_dwSize += iNum;
	}


	// 函数名称： AddSampleData
	// 功能说明： 用线段fBeginValue和fEndValue填充
	// 返回值： 
	// 参数： int nDstBeginTime：
	// 参数： int nTime：
	// 参数： float fBeginValue：
	// 参数： float fEndValue：

	void  CSample::AddSampleData(int nDstBeginTime, int nTime, float fBeginValue, float fEndValue)
	{
		int iNum = int(1.0f*nTime/10000*m_iSampleSec+DEFINITE);
		//分配数据空间
		AllocSample( m_dwSize + iNum ); 
	
		float *pPtr = GetSamplePtr(nDstBeginTime);
		float k = (fEndValue-fBeginValue)/iNum;
		for(int i=0;i<iNum;i++)
		{
			pPtr[i] = fBeginValue + i*k;
		}
		m_dwSize += iNum;
	}

	void CSample::AddSampleData(int nDstBeginTime, CSample *pSrcSample,float *fpBegin,float *fpEnd)
	{
		int iAddNum = (fpEnd-fpBegin) + 1;
		//分配数据空间
		AllocSample( m_dwSize + iAddNum ); 
	
		float *pPtr = GetSamplePtr(nDstBeginTime);
		::memcpy((void *)pPtr,(void *)fpBegin,(fpEnd-fpBegin)*sizeof(float));
		m_dwSize += (fpEnd-fpBegin);
	}

	void  CSample::OverlapSampleData(int nDstBeginTime,int nLogicTime,CSample *pSrcSample,float *fpBegin,float *fpEnd)
	{
		int iAddNum = (fpEnd-fpBegin) + 1;
		//分配数据空间
		AllocSample( m_dwSize + iAddNum ); 

		float *pPtr = GetSamplePtr(nDstBeginTime);
		float *pDstEndPtr = GetSamplePtr(nDstBeginTime + nLogicTime);
        BOOST_ASSERT((pDstEndPtr-pPtr) <= (fpEnd-fpBegin));
        int dIntervalSize = int(pDstEndPtr - pPtr);
		for(;pPtr<pDstEndPtr;++fpBegin,++pPtr)
		{
			*pPtr += *fpBegin;
		}
		::memcpy((void *)pPtr,(void *)fpBegin,(fpEnd-fpBegin)*sizeof(float));
		m_dwSize += (fpEnd-fpBegin);
		//对重叠区域做5点除燥
		//RidSampleYawp(nDstBeginTime,nLogicTime);
	}

	//调整采样曲线
	void CSample::AdjustSampleData(float fData)
	{
		for(unsigned long i=0;i<m_dwSize;++i)
			m_pPtrData[i] -= fData;
	}

	//根据指针，返回此位置所代表的时间
	int CSample::GetValidTime(float *pfPos,int nBeginTime)
	{
		float *pfBegin = GetSamplePtr(nBeginTime);
		return 10000*(pfPos-pfBegin)/m_iSampleSec;
	}

	//将采样数据转换为8bit采样的数据
	void CSample::ChangeSampleDataTo8Big()
	{
		for(unsigned long i=0;i<m_dwSize;++i)
		{	
			int n = int(256*(m_pPtrData[i]+2)/4);//X/256=(V-Vmin)/(Vmax-Vmin)
			m_pPtrData[i] =  -2.0f + n * 4/256.0f;
		}
	}

	//除噪
	void  CSample::RidSampleYawp(int nBeginTime, int nValidTime)
	{
		float *fBeginPtr = GetSamplePtr(nBeginTime);
		float *fEndPtr = GetSamplePtr(nBeginTime+nValidTime);
		float *pPtr = (float *)::HeapAlloc(m_hHandle,HEAP_ZERO_MEMORY,(fEndPtr-fBeginPtr+8)*sizeof(float));
		::memcpy((void *)(pPtr+4),(void *)fBeginPtr,(fEndPtr-fBeginPtr)*sizeof(float));
		for(int i=0;i<(fEndPtr-fBeginPtr);++i)
		{
			float fValue = 0.0f;
			for(int iStep = 0;iStep<5;++iStep)
				fValue += pPtr[i+iStep];
			pPtr[i] = fValue/5;
		}
		float fValue = pPtr[4] - fBeginPtr[0];
		for(int i=0;i<(fEndPtr-fBeginPtr);++i)
		{
			fBeginPtr[i] = pPtr[4+i]-fValue;
		}
		::HeapFree(m_hHandle,HEAP_NO_SERIALIZE,pPtr);
	}


	// 函数名称： ZoomSampleDataHandle
	// 功能说明： 缩放采样数据处理
	// 返回值： 
	// 参数： int iChgedTime：修改后的时间
	void  CSample::ZoomSampleDataHandle(int iChgedTime)
	{
		int iValidTime = 10000 * m_dwSize / m_iSampleSec;
		if(iValidTime == iChgedTime)
			return;
		float fZoom = 1.0f * iChgedTime/iValidTime;
		if(::fabs(fZoom-1.0) > DEFINITE)
		{
			int iSize = GetSampleNum(iChgedTime)+100;
			float *pPtr = (float *)::HeapAlloc(m_hHandle,HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY,iSize*sizeof(float));
			unsigned long iNum =0;//实际保存的个数
			if(fZoom > 1.0)
			{//扩展数据
				float fSample = 1.0f/fZoom;
				pPtr[iNum++] = *m_pPtrData;
				for(unsigned long iStep = 1; iStep < m_dwSize;)
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
				for(unsigned long iStep = 1; iStep < m_dwSize; ++iStep)
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
			//分配数据空间
			AllocSample( iNum ); 
		
			::memcpy((void *)m_pPtrData,(void *)pPtr,iNum*sizeof(float));
			float *pEndPtr = GetSamplePtr(iChgedTime);
			float fValue = m_pPtrData[iNum-1];
			for(;m_pPtrData + iNum < pEndPtr;++iNum)
			{
				m_pPtrData[iNum] = fValue;
			}
			m_dwSize = iNum;
			::HeapFree(m_hHandle,HEAP_NO_SERIALIZE,pPtr);
		}
	}

	// 函数名称： CutSampleDataHandle
	// 功能说明： 切割采样数据处理
	// 返回值： 
	// 参数： int iPosTime：  切割的时间点
	// 参数： bool bRmvPostion：移除的部位(true:右边；false:左边)
	void  CSample::CutSampleDataHandle(int iPosTime, bool bRmvPostion)
	{
		float *fPtr = GetSamplePtr(iPosTime);
		if(bRmvPostion == true)
		{//移除右边
			m_dwSize = fPtr - m_pPtrData;
		}
		else
		{
			//移动采样数据
			int iNum = (m_pPtrData + m_dwSize) - fPtr;
			for(int iStep = 0; iStep < iNum; ++iStep)
			{
				m_pPtrData[iStep] = m_pPtrData[iStep+iNum];
			}
			m_dwSize = iNum;
		}
	}

	void  CSample::DirectLinkSampleData(CSample *pSrcSample)
	{
		if(pSrcSample->IsEmpty() || pSrcSample->m_dwSize == 0)
			return;
		//分配数据空间
		AllocSample( m_dwSize + pSrcSample->m_dwSize );

		::memcpy((void *)(m_pPtrData+m_dwSize),(void *)pSrcSample->m_pPtrData,pSrcSample->m_dwSize*sizeof(float));
		m_dwSize += pSrcSample->m_dwSize;
	}

	//水平间隔连接操作
	void  CSample::HoriIntervalLinkSampleData(CSample *pSrcSample,int nIntervalTime, float fValue)
	{
		AddSampleData(GetSampleSumTime(),nIntervalTime,fValue);
		DirectLinkSampleData(pSrcSample);
	}

	//水平延伸操作
	//bool bHorDirect：TURE:向右延伸；FALSE:向左延伸
	void CSample::HoriIntervalLinkSampleData(int nExtendTime, float fValue, bool bHorDirect/*=true*/)
	{
		if(bHorDirect == true)
			AddSampleData(GetSampleSumTime(),nExtendTime,fValue);
		else
		{
			int nAddSum = GetSampleNum(nExtendTime);//增加的点数
			//分配数据空间
			AllocSample( m_dwSize + nAddSum );
		
			for(int i=m_dwSize-1;i>=0;--i)
			{
				m_pPtrData[i+nAddSum] = m_pPtrData[i];
				m_pPtrData[i] = 0.0f;
			}
			for(int i = 0; i< nAddSum;++i)
				m_pPtrData[i] = fValue;
			m_dwSize += nAddSum;
		}
	}

	//水平延长到指定时间长度
	//int nTime：单位0.1微秒
	void  CSample::HoriExtendSampleData(int nTime)
	{
		int  nSumTime = GetSampleSumTime();
		if( nSumTime < nTime )
		{
			AddSampleData(nSumTime, nTime-nSumTime, m_pPtrData[m_dwSize-1]);
		}
	}

	//直线间隔连接操作
	void  CSample::LineIntervalLinkSampleData(CSample *pSrcSample,int nIntervalTime)
	{
		float fBeginValue,fEndValue;
		fBeginValue = m_pPtrData[m_dwSize-1];
		fEndValue = pSrcSample->m_pPtrData[0];
		AddSampleData(GetSampleSumTime(),nIntervalTime,fBeginValue,fEndValue);
		DirectLinkSampleData(pSrcSample);
	}

	//区域重叠操作(注：与pSrcSample有相交，但不是包含)
	void  CSample::OverlapLinkSampleData(CSample *pSrcSample,int nOverlapTime)
	{
		int iGlobalTime = GetSampleSumTime();
		OverlapSampleData(iGlobalTime-nOverlapTime,nOverlapTime,pSrcSample,pSrcSample->m_pPtrData,pSrcSample->m_pPtrData+pSrcSample->m_dwSize);
	}

	//起始位置重叠操作
	void  CSample::DirectOverlapLinkSampleData(const CSample *pSrcSample)
	{
		if(pSrcSample->IsEmpty() || pSrcSample->m_dwSize == 0)
			return;//空的返回
		AllocSample( pSrcSample->m_dwSize );
	
		//重叠区域
		unsigned long dwOverlapSize = m_dwSize < pSrcSample->m_dwSize ? m_dwSize : pSrcSample->m_dwSize;
		float *fpBegin = pSrcSample->m_pPtrData;
		float *pPtr = m_pPtrData;
		for(unsigned long i=0;i<dwOverlapSize;++fpBegin,++pPtr,++i)
		{
			*pPtr += *fpBegin;
		}
		//覆盖其它部分
		if(m_dwSize < pSrcSample->m_dwSize)
		{
			::memcpy(pPtr,fpBegin,(pSrcSample->m_dwSize-m_dwSize)*sizeof(float));
			m_dwSize = pSrcSample->m_dwSize;
		}
	}

	//分配数据空间
	void CSample::AllocSample(unsigned long  dwGlobalSize)
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

	//起始位置开始被pSrcSample覆盖操作
	void  CSample::DirectCoverLinkeSampleData(const CSample *pSrcSample)
	{
		if(pSrcSample->IsEmpty() || pSrcSample->m_dwSize == 0)
			return;//空的返回
		//分配数据空间
		AllocSample( pSrcSample->m_dwGlobalSize );
	
		if(m_dwSize < pSrcSample->m_dwSize)
			m_dwSize = pSrcSample->m_dwSize;
		float *fpBegin = pSrcSample->m_pPtrData;
		float *pPtr = m_pPtrData;
		float *pDstEndPtr = pPtr + pSrcSample->m_dwSize;
		for(;pPtr<pDstEndPtr;++fpBegin,++pPtr)
		{
			*pPtr = *fpBegin;
		}
	}

	//将电压值转换成对应的BYTE值
    int  CSample::ModifyVoltToLogicValue(const float *pBeginPtr, long uSrcSize,/*out*/unsigned char *pDstPtr, int iRate/*=1*/)
	{
		int iRtn = 0;
		for(int iStep = 0; iStep < uSrcSize; iStep += iRate)
		{
            pDstPtr[iRtn] = (unsigned char)::abs(int(256*(pBeginPtr[iStep]+2)/4));
			++iRtn;
		}
		return iRtn;
	}

}}
