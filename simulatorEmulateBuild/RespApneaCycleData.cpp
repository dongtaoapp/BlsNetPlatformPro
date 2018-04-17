#include ".\respapneacycledata.h"

#include "..\SimulatorBase\ICO2SimulateSign.h"

namespace jysoft { namespace simulator { namespace resp {

	CRespApneaCycleData::CRespApneaCycleData(CInspirationSegment *pInspirationSegment, CExhaleSegment *pExhaleSegment, int nRespRate, int nInspirationTime)
										: CRespCycleData(pInspirationSegment, pExhaleSegment, nRespRate, nInspirationTime)
	{
		m_nRespRate   = 0;
		m_iSampleSec  = 25;//ÿ��Ĳ�����
	}

	CRespApneaCycleData::~CRespApneaCycleData(void)
	{
	}

	/*******************************************************************************/
	// �������ƣ� JudgeIsRepeatCycleData
	// ���ܣ� �ж��Ƿ�ͬһ���ڵ�����
	// ������ int nRespRate:  ��������
	//        int nMillitInspirationTime: ����ʱ��(��λ:0.1ms)
	//        float fCurrentRemainVolume: ��ǰ��������(��λ:ml)    
	//        float fSumVolume:           �����ڵ�������
	//        float fRemainVolume:        �����ڽ�����Ĳ�������(��λ:ml)
	// ����ֵ:  
	bool CRespApneaCycleData::JudgeIsRepeatCycleData(int nRespRate, int nMillitInspirationTime, float fCurrentRemainVolume, float fSumVolume, float fRemainVolume)
	{
		if( nRespRate != 0 )
		{
			return false;
		}
	#define  _INFINITE           0.0001
		if( int(m_fCurrentRemainVolume+_INFINITE) != int(m_fRemainVolume+_INFINITE) )
		{
			return false;
		}
		return true;
	}

	/*******************************************************************************/
	// �������ƣ� ResetPrepareReadSampleData
	// ���ܣ�  �������ݵĶ�ȡ׼��
	// ������ 
	// ����ֵ:  
	void CRespApneaCycleData::ResetPrepareReadSampleData()
	{
	#define  _INFINITE      0.0001
		m_cInspirationLungVolumes.ResetReadBeginPosPtr();
		m_cInspirationLungVolumes.Empty();
		m_cExhaleLungVolumes.ResetReadBeginPosPtr();
		m_cExhaleLungVolumes.Empty();
		//�����½�����
		if( int(m_fCurrentRemainVolume + _INFINITE) != int(m_fRemainVolume + _INFINITE) && m_pExhaleSegment != NULL )
		{
			m_pExhaleSegment->ZoomSegmentDataHandle( m_nInspirationTime );
			m_pExhaleSegment->ZoomRespVolumeHandle(m_fRemainVolume, m_fCurrentRemainVolume );
			float *fSamplePtr = m_pExhaleSegment->GetSamplePtr();
            for (short dwItem = 0; dwItem < m_pExhaleSegment->GetSampleSumNumber(); ++dwItem)
			{
				RespDataStruct  stcRespData;
				stcRespData.m_fLungVolumeValue_L = fSamplePtr[dwItem]/2;
				stcRespData.m_fLungVolumeValue_R = fSamplePtr[dwItem]/2;
				m_cExhaleLungVolumes.WriteData(&stcRespData, 1);
			}
		}
	}

	/*******************************************************************************
	//���ܣ���ȡʱ�������ڵĺ�������
	//������int iMilliTime:          ʱ�䣨0.1���룩
	//      float *pcBuffer:         ���صĺ�������
	//����ֵ: ���ݵĳ���
	*********************************************************************************/
    short CRespApneaCycleData::GetRespSimulateData(int iMilliTime, unsigned char byteAddress, /*out*/float *pcLeftBuffer /*= NULL*/, /*out*/float *pcRightBuffer /*= NULL*/)
	{
        short dwNum = short(iMilliTime * m_iSampleSec * 1e-4);
		if( pcLeftBuffer != NULL  && pcRightBuffer != NULL )
		{
			if( m_cExhaleLungVolumes.GetNoneReadedNum() == 0 )
			{
                for (short dwItem = 0; dwItem < dwNum; ++dwItem)
				{
					pcLeftBuffer[dwItem] = m_fRemainVolume/2;
					pcRightBuffer[dwItem] = m_fRemainVolume/2;
				}
			}
			else
			{
				//����CO2���½��ź�
				if( (m_cExhaleLungVolumes.GetCurrBufferNum() == m_cExhaleLungVolumes.GetNoneReadedNum()) && m_pCO2SimulateSignInteface)
				{
					if( m_pCO2SimulateSignInteface != NULL )
					{
						int nMilliOtherTime = m_nInspirationTime - m_nInspirationToCO2Time;
						m_pCO2SimulateSignInteface->OnCO2SimulateSignOp(TRUE, m_nInspirationToCO2Time, nMilliOtherTime);
					}
					//����ָ��,����ģ���˵ĺ���
					TransportOrderToSimulator( );
				}
				//end hjg 2008/7/29 ���; 8/18���޸�i
				if( m_cExhaleLungVolumes.GetNoneReadedNum() >= dwNum )
				{
					RespDataStruct  stcRespData;
                    for (short dwItem = 0; dwItem < dwNum; ++dwItem)
					{
						m_cExhaleLungVolumes.ReadDataMovePtr(&stcRespData,1);
						pcLeftBuffer[dwItem] = stcRespData.m_fLungVolumeValue_L;
						pcRightBuffer[dwItem] = stcRespData.m_fLungVolumeValue_R;
					}
				}
				else
				{
                    for (short dwItem = 0; dwItem < dwNum; ++dwItem)
					{
						pcLeftBuffer[dwItem] = m_fRemainVolume/2;
						pcRightBuffer[dwItem] = m_fRemainVolume/2;
					}
				}
			}
		}
		return dwNum;
	}
}}}
