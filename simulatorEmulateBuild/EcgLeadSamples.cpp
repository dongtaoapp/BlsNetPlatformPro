#include <boost/assert.hpp>
#include ".\EcgLeadSamples.h"


namespace jysoft { namespace simulator { namespace ecg {

	//==================================test================================================//
	#define   _LEAD_SUM     12 /*12*/
	//================================End test==============================================//

	CEcgLeadSamples::CEcgLeadSamples(void)
	{
		m_pTempBuff            = NULL;
		m_dwTempBuffSize       = 0;
	}

	CEcgLeadSamples::~CEcgLeadSamples(void)
	{
		delete [] m_pTempBuff;;
		m_dwTempBuffSize   = 0;
	}

	/*******************************************************************************/
	// 函数名称： DirectOverlapLinkSampleData
	// 功能： 起始位置叠加操作
	// 参数：  
	//        CEcgLeadSamples &cSrcLeadSamples:
	// 返回值: 
	void CEcgLeadSamples::DirectOverlapLinkSampleData( CEcgLeadSamples &cSrcLeadSamples )
	{
		for( int nLead = 0; nLead < _LEAD_SUM/*12*/; ++nLead )
		{
			CSample *pSrcLeadSample = cSrcLeadSamples.GetEcgLeadSample((RhythmLead)nLead);
			//叠加操作
			GetEcgLeadSample((RhythmLead)nLead)->DirectOverlapLinkSampleData( pSrcLeadSample );
		}
	}

	/*******************************************************************************/
	// 函数名称： CombineLeadSamples
	// 功能： 整合各导联的数据到数据交互缓冲池，用于输出
	// 参数： 
	//        int nMiliCycleTime:          周期时间(0.1ms)        
	// 返回值:  
	I12LeadSample * CEcgLeadSamples::CombineLeadSamples(int nMiliCycleTime)
	{
		DWORD   dwSampleNum = (DWORD)GetSampleNum( nMiliCycleTime );
		//重置临时数据交互缓冲池大小
		ResetTempBuffSize( dwSampleNum );
		for (DWORD dwStep = 0; dwStep < dwSampleNum; ++dwStep)
		{
			// I 导联
			float *fptrSample = m_cLeadSample[0].m_pPtrData + dwStep;
			m_pTempBuff[dwStep].m_fSampleI = *fptrSample;
			// II 导联
			if( m_cLeadSample[1].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[1].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleII = *fptrSample;
			}
			// III 导联
			if( m_cLeadSample[2].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[2].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleIII = *fptrSample;
			}
			// aVR 导联
			if( m_cLeadSample[3].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[3].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleaVR = *fptrSample;
			}
			// aVL 导联
			if( m_cLeadSample[4].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[4].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleaVL = *fptrSample;
			}
			// aVF 导联
			if( m_cLeadSample[5].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[5].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleaVF = *fptrSample;
			}
			// V1 导联
			if( m_cLeadSample[6].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[6].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleV1 = *fptrSample;
			}
			// V2 导联
			if( m_cLeadSample[7].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[7].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleV2 = *fptrSample;
			}
			// V3 导联
			if( m_cLeadSample[8].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[8].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleV3 = *fptrSample;
			}
			// V4 导联
			if( m_cLeadSample[9].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[9].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleV4 = *fptrSample;
			}
			// V5 导联
			if( m_cLeadSample[10].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[10].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleV5 = *fptrSample;
			}
			// V6 导联
			if( m_cLeadSample[11].m_pPtrData != NULL )
			{
				fptrSample = m_cLeadSample[11].m_pPtrData + dwStep;
				m_pTempBuff[dwStep].m_fSampleV6 = *fptrSample;
			}
		}
		return m_pTempBuff;
	}

	/*******************************************************************************/
	// 函数名称： ClearEcgLeadCycleData
	// 功能： 清除各导联周期时间内的心电图数据，并保留剩余数据
	// 参数： 
	//        int nMiliCycleTime:          周期时间(0.1ms)
	// 返回值:  
	void CEcgLeadSamples::ClearEcgLeadCycleData(int nMiliCycleTime)
	{
		for( int nLead = 0; nLead < _LEAD_SUM/*12*/; ++nLead )
		{
			int iSumTime = m_cLeadSample[nLead].GetSampleSumTime();
			if( iSumTime > nMiliCycleTime )
			{
				float *fBegin = m_cLeadSample[nLead].GetSamplePtr(0);
				float *fEnd = m_cLeadSample[nLead].GetSamplePtr(nMiliCycleTime);
				float *fEnd2 = fBegin + m_cLeadSample[nLead].m_dwSize; 
				for(;fEnd < fEnd2;++fEnd,++fBegin)
					*fBegin = *fEnd;
				m_cLeadSample[nLead].m_dwSize = m_cLeadSample[nLead].GetSampleNum(iSumTime-nMiliCycleTime);
			}
			else
			{
				m_cLeadSample[nLead].m_dwSize = 0;
			}
		}
	}

	/*******************************************************************************/
	// 函数名称： CutEcgLeadCycleExtendData
	// 功能： 切除超出周期部分的数据 
	// 参数： 
	//        int nMiliCycleTime:          周期时间(0.1ms)
	// 返回值:  
	bool CEcgLeadSamples::CutEcgLeadCycleExtendData(int nMiliCycleTime)
	{
		bool   bCutExtendData = false;
		for( int nLead = 0; nLead < _LEAD_SUM/*12*/; ++nLead )
		{
			if(m_cLeadSample[nLead].GetSampleSumTime() > nMiliCycleTime)
			{//将超出周期的部分切除掉
				float fBeginValue = 0.0f;
				m_cLeadSample[nLead].CutSampleDataHandle(nMiliCycleTime-20,true);
				fBeginValue = *m_cLeadSample[nLead].GetSamplePtr(nMiliCycleTime-20);
				m_cLeadSample[nLead].AddSampleData(nMiliCycleTime-20,20,fBeginValue,0.0f);
				//--------------------------------------------------------------------------------------------
				if( !bCutExtendData )
				{
					bCutExtendData = true;
				}
			}
		}
		return bCutExtendData;
	}

	/*******************************************************************************/
	// 函数名称： GetBuildEcgLeadSampleNum
	// 功能： 返回构建的心电图数据数量
	// 参数： 
	//        
	// 返回值: 
	UINT CEcgLeadSamples::GetBuildEcgLeadSampleNum()
	{
		UINT    uBuildSize = 0;
		for( int nLead = 0; nLead < _LEAD_SUM/*12*/; ++nLead )
		{
			if( m_cLeadSample[nLead].m_dwSize == 0 )
			{
				uBuildSize = 0;
				break;
			}
	#ifdef  _DEBUG
			if( uBuildSize != 0 && uBuildSize != m_cLeadSample[nLead].m_dwSize )
			{
                BOOST_ASSERT( 0 );
			}
	#endif
			uBuildSize = m_cLeadSample[nLead].m_dwSize;
		}
		return uBuildSize;
	}

	//清空各导联的心电图数据
	void CEcgLeadSamples::EmptyEcgLeadSamples()
	{
		for( int nLead = 0; nLead < _LEAD_SUM/*12*/; ++nLead )
		{
			m_cLeadSample[nLead].m_dwSize = 0;
		}
	}

	/*******************************************************************************/
	// 函数名称： CombineArtifactData
	// 功能： 添加肌颤或50/60HZ时的数据
	// 参数： 
	//        Artifact eArtiface:  
	//        int iCycleTime:  
	//        UINT uArtifactNum:         
	// 返回值:  
	UINT  CEcgLeadSamples::CombineArtifactData(Artifact eArtiface, int iCycleTime, UINT uArtifactNum)
	{
	#define  PI    3.1415926
		switch(eArtiface)
		{
		case AF_None:
			{
				break;
			}
		case AF_Muscular: //肌肉颤动
			{
				UINT uCycleNum = 0;
				unsigned int  nSampleNum = GetSampleNum( iCycleTime );
				float *fValuePtr = GetTriangleCycleData(30,uCycleNum);
				for( unsigned int iIndex = 0; iIndex < nSampleNum; ++iIndex )
				{
					for( int nLead = 0; nLead < _LEAD_SUM/*12*/; ++nLead )
					{
						float *fptrSample = m_cLeadSample[nLead].GetSamplePtr( 0 ) + iIndex;
						float df = 0.0f;
						*fptrSample += 0.07 * fValuePtr[uArtifactNum%uCycleNum] * (1+sin(2.0f*PI*13*uArtifactNum*0.0025));
					}
					++uArtifactNum;
				}
				break;
			}
		case AF_Frequent: //50/60赫兹的干扰
			{
				unsigned int  nSampleNum = GetSampleNum( iCycleTime );
				for( unsigned int iIndex = 0; iIndex < nSampleNum; ++iIndex )
				{
					for( int nLead = 0; nLead < _LEAD_SUM/*12*/; ++nLead )
					{
						float *fptrSample = m_cLeadSample[nLead].GetSamplePtr( 0 ) + iIndex;
						*fptrSample += 0.15 * (1+sin(2.0f*PI*50*uArtifactNum*0.0025));
					}
					++uArtifactNum;
				}
				break;
			}
		}
		return uArtifactNum;
	}

	float* CEcgLeadSamples::GetTriangleCycleData(int nFrequent, UINT &uCycleNum)
	{
	#define  PI    3.1415926
		static float fValue[100];
		uCycleNum = 400/nFrequent;//周期的点数
		bool bBeforeHalf = true;
		for(int i=1; i<= uCycleNum; ++i)
		{
			if(bBeforeHalf == true)
				fValue[i-1] = 2.0f*nFrequent*i*0.0025;
			if(bBeforeHalf && fValue[i-1] > 1.0f)
			{
				bBeforeHalf = false;
			}
			if(bBeforeHalf == false)
			{//用一段的函数计算
				fValue[i-1] = 2.0f*nFrequent*(1.0f/nFrequent - i*0.0025);
			}
		}
		return fValue;
	}

	//重置临时数据交互缓冲池大小
	void CEcgLeadSamples::ResetTempBuffSize(DWORD dwSize)
	{
		if( m_dwTempBuffSize < dwSize )
		{
			if( m_pTempBuff != NULL )
			{
				delete [] m_pTempBuff;
			}
			m_pTempBuff = new I12LeadSample[dwSize];
			m_dwTempBuffSize    = dwSize;
		}
	}
}}}
