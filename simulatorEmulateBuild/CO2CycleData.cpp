#include ".\co2cycledata.h"
#include ".\CO2SimulateStateGlobal.h"

namespace jysoft { namespace simulator { namespace etCO2 {

	CCO2CycleData::CCO2CycleData(void)
	{
		m_pReadSegment = NULL;
		m_dwReadPos    = 0;
	}

	CCO2CycleData::~CCO2CycleData(void)
	{
	}

	void CCO2CycleData::InitialCO2CycleData( const std::string &etCO2ResoucePath, int nCO2Per )
	{
		//加载文件内的呼气时CO2数据
		std::string  strExhaledCO2File = etCO2ResoucePath + "\\ExhaledCO2Data.txt";
		m_cExhaledCO2Segment.LoadOriginSegmentData( strExhaledCO2File );
		//加载文件内的吸气时CO2数据
		std::string  strInspiratedCO2File = etCO2ResoucePath + "\\InspiratedCO2Data.txt";
		m_cInspiratedCO2Segment.LoadOriginSegmentData( strInspiratedCO2File );
		//设置CO2%
		m_cExhaledCO2Segment.Set_CO2Percent( nCO2Per );
		//设置采样数据读取情况记录
		m_pReadSegment = &m_cExhaledCO2Segment;
		m_dwReadPos    = 0;
	}

	void CCO2CycleData::ModifyCO2PerValue( int nCO2Per )
	{
		m_cExhaledCO2Segment.Set_CO2Percent( nCO2Per );
	}

	/*******************************************************************************/
	// 函数名称： CO2SimulateSignOp
	// 功能： 呼吸时，产生对CO2的模拟信号处理
	// 参数：  BOOL bInspiration: 吸气(TRUE); 呼气(FALSE)
	//         int nMilliChangeTime: CO2骤升（降）的时间（0.1毫秒）
	//         int nMilliOtherTime:  骤升（降）后接下来的时间（0.1毫秒）
	// 返回值:  
	void CCO2CycleData::CO2SimulateSignOp(bool bInspiration, int nMilliChangeTime, int nMilliOtherTime)
	{
		if( m_cExhaledCO2Segment.IsEmpty() )
		{
			m_cMutex.Lock();
			if( bInspiration == false )
			{
				m_cExhaledCO2Segment.InitilaCO2Segment(nMilliChangeTime, nMilliOtherTime);
			}
			m_pReadSegment = &m_cExhaledCO2Segment;
			m_dwReadPos    = 0;
			m_cMutex.Unlock();
		}
		else
		{
			if (m_pReadSegment->isKindOf("CExhaledCO2Segment") && bInspiration)
			{
				int nCO2Per = m_cExhaledCO2Segment.Get_CurrentCO2Percent();
				m_cInspiratedCO2Segment.InitilaCO2Segment(nCO2Per, nMilliChangeTime, nMilliOtherTime);
				m_cMutex.Lock();
				m_pReadSegment = &m_cInspiratedCO2Segment;
				m_dwReadPos    = 0;
				m_cMutex.Unlock();
			}
			else if( m_pReadSegment->isKindOf("CInspiratedCO2Segment") && !bInspiration)
			{
				m_cExhaledCO2Segment.InitilaCO2Segment( nMilliChangeTime, nMilliOtherTime);
				m_cMutex.Lock();
				m_pReadSegment = &m_cExhaledCO2Segment;
				m_dwReadPos    = 0;
				m_cMutex.Unlock();
			}
		}
	}

	/*******************************************************************************/
	//功能：获取滑块区域内的曲线数据
	//参数：int iMilliTime:          时间（0.1豪秒）
	//      float *pcBuffer:         返回的曲线数据
	//返回值:  曲线数据的长度
	DWORD CCO2CycleData::GetPhysioloySimulateData(int iMilliTime, ICO2SimulateState *pEtCO2SimulateState, /*out*/float *pcBuffer )
	{
		DWORD  dwNum = (DWORD)m_cExhaledCO2Segment.GetSampleNum( iMilliTime );
		if( pcBuffer != NULL )
		{
			m_cMutex.Lock();
			if( m_pReadSegment->IsEmpty() )
			{
				m_dwReadPos = 0;
				for (DWORD item = 0; item < dwNum; ++item)
				{
					pcBuffer[item] = 0.0f;
				}
			}
			else
			{
				float *fSamplePtr = m_pReadSegment->GetSamplePtr();
				DWORD dwSumNum = m_pReadSegment->GetSampleSumNumber();
				if( dwSumNum >= (m_dwReadPos + dwNum) )
				{
					::memcpy(pcBuffer, fSamplePtr+m_dwReadPos, dwNum*sizeof(float));
					m_dwReadPos += dwNum;
				}
				else if( dwSumNum > m_dwReadPos )
				{
					float *fSamplePtr = m_pReadSegment->GetSamplePtr();
					DWORD dwReadNum = m_pReadSegment->GetSampleSumNumber() - m_dwReadPos;
					::memcpy(pcBuffer, fSamplePtr+m_dwReadPos, dwReadNum*sizeof(float));
					m_dwReadPos += dwReadNum;
					for (DWORD item = 0; item < (dwNum-dwReadNum); ++item)
					{
						pcBuffer[dwReadNum+item] = pcBuffer[dwReadNum-1];
					}
				}
				else
				{
					float *fSamplePtr = m_pReadSegment->GetSamplePtr();
					for (DWORD item = 0; item < dwNum; ++item)
					{
						pcBuffer[item] = fSamplePtr[m_dwReadPos-1];
					}
					if( pEtCO2SimulateState != NULL )
					{
						pEtCO2SimulateState->DoExhaledCO2EndHandle( m_pReadSegment );
					}
				}
			}
			m_cMutex.Unlock();
		}
		return dwNum;
	}

	//返回呼吸次数
	int  CCO2CycleData::GetRespRate()
	{
		return m_cExhaledCO2Segment.Get_CurrentCO2Percent();
	}
}}}
