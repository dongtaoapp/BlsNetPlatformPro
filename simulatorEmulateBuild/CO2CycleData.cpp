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
		//�����ļ��ڵĺ���ʱCO2����
		std::string  strExhaledCO2File = etCO2ResoucePath + "\\ExhaledCO2Data.txt";
		m_cExhaledCO2Segment.LoadOriginSegmentData( strExhaledCO2File );
		//�����ļ��ڵ�����ʱCO2����
		std::string  strInspiratedCO2File = etCO2ResoucePath + "\\InspiratedCO2Data.txt";
		m_cInspiratedCO2Segment.LoadOriginSegmentData( strInspiratedCO2File );
		//����CO2%
		m_cExhaledCO2Segment.Set_CO2Percent( nCO2Per );
		//���ò������ݶ�ȡ�����¼
		m_pReadSegment = &m_cExhaledCO2Segment;
		m_dwReadPos    = 0;
	}

	void CCO2CycleData::ModifyCO2PerValue( int nCO2Per )
	{
		m_cExhaledCO2Segment.Set_CO2Percent( nCO2Per );
	}

	/*******************************************************************************/
	// �������ƣ� CO2SimulateSignOp
	// ���ܣ� ����ʱ��������CO2��ģ���źŴ���
	// ������  BOOL bInspiration: ����(TRUE); ����(FALSE)
	//         int nMilliChangeTime: CO2������������ʱ�䣨0.1���룩
	//         int nMilliOtherTime:  �������������������ʱ�䣨0.1���룩
	// ����ֵ:  
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
	//���ܣ���ȡ���������ڵ���������
	//������int iMilliTime:          ʱ�䣨0.1���룩
	//      float *pcBuffer:         ���ص���������
	//����ֵ:  �������ݵĳ���
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

	//���غ�������
	int  CCO2CycleData::GetRespRate()
	{
		return m_cExhaledCO2Segment.Get_CurrentCO2Percent();
	}
}}}
