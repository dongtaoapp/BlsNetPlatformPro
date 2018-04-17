#include ".\respapneatypestate.h"
#include ".\RespApneaCycleData.h"
#include ".\RespParamImpl.h"

#include "..\AdultParams\AdultApneaRespParam.h"

namespace jysoft { namespace simulator { namespace resp {

	CRespApneaTypeState::CRespApneaTypeState( SimulatePatientType ePatientType)
								: IRespBuildTypeState(  )
	{
		switch( ePatientType )
		{
		case SPT_Adult:
			{
				m_pRespParams = new CRespParamImpl<CAdultApneaRespParam>();
				break;
			}
		}
	}

	CRespApneaTypeState::~CRespApneaTypeState(void)
	{
		if( m_pRespParams != NULL )
		{
			delete m_pRespParams;
			m_pRespParams = NULL;
		}
	}

	bool CRespApneaTypeState::isKindOf(const std::string &className)
	{
		if( className == "CRespApneaTypeState" )
			return true;
		return false;
	}

	/*******************************************************************************/
	// �������ƣ� InitialLoadOriginSimulateData
	// ���ܣ� ����ԭʼ��������
	// ������ 
	// ����ֵ:  
	void CRespApneaTypeState::InitialLoadOriginSimulateData(const std::string &respResoucePath, int nRespRate)
	{
		//������������
		if( m_pOriginInspirationSegment == NULL )
		{
			m_pOriginInspirationSegment = new CInspirationSegment();
		}
		std::string strInspirateFilePath = respResoucePath + "\\InspirationData.txt";
		m_pOriginInspirationSegment->LoadSegmentData(strInspirateFilePath);
		//���غ�������
		if( m_pOriginExhaleSegment == NULL )
		{
			m_pOriginExhaleSegment = new CExhaleSegment();
		}
		std::string strExhaleFilePath = respResoucePath + "\\ExhaleData.txt";
		m_pOriginExhaleSegment->LoadSegmentData( strExhaleFilePath );

		//�趨ȱʡ�ĺ�������
		m_nRespRate = 0;
		//���ز���
		m_pRespParams->LoadRespParams( m_nRespRate );
	}

	/*******************************************************************************/
	// �������ƣ� OnCombineNextRespCycleData
	// ���ܣ� ���������ڵĺ�������
	// ������ float fCurrentRemainVolume:           ��ǰ������
	//        CRespCycleDataCollects *pRespCollect: 
	// ����ֵ:  
	CRespCycleData * CRespApneaTypeState::OnCombineNextRespCycleData(float fCurrentRemainVolume, CRespCycleDataCollects *pRespCollect)
	{
		m_cMutex.Lock();
		_eRefurbishDataRange  eRefurbishRange = m_pRespParams->Get_eRefurbishDataRange();
		int nRespRate       = m_nRespRate;
		//����ʱ��(��λ:0.1ms)
		int nMillitInspirationTime = m_pRespParams->GetInspriationTime();
		//�����ڵ�������(��λ:ml)
		float fSumVolume    =  m_pRespParams->GetRespVolume();
		//�����ڽ�����Ĳ�������(��λ:ml)
		float fRemainVolume = m_pRespParams->GetRespRemainVolume();
		//��������ʱ��(��λ��0.1ms)
		int   nSumTime      = m_pRespParams->GetRespCycleTime();
		m_cMutex.Unlock();
		CRespCycleData *pRespCycleData = pRespCollect->RemoveRespCycleData();
		if( pRespCycleData != NULL && !pRespCycleData->JudgeIsRepeatCycleData(nRespRate, nMillitInspirationTime, fCurrentRemainVolume,fSumVolume, fRemainVolume))
		{
			delete pRespCycleData;
			pRespCycleData = NULL;
		}
		//�����µ���������
		if( pRespCycleData == NULL )
		{
			CInspirationSegment  *pInspirationSegment = NULL;
			CExhaleSegment       *pExhaleSegment      = NULL;
			if(nRespRate != 0)
			{
				//���������β�������
				pInspirationSegment = new CInspirationSegment();
				pInspirationSegment->Clone( m_pOriginInspirationSegment );
				pInspirationSegment->ZoomSegmentDataHandle( nMillitInspirationTime );
				pInspirationSegment->ZoomRespVolumeHandle(fCurrentRemainVolume, fSumVolume);
				//���ɺ����β�������
				pExhaleSegment = new CExhaleSegment();
				pExhaleSegment->Clone( m_pOriginExhaleSegment );
				pExhaleSegment->ZoomSegmentDataHandle( nSumTime - nMillitInspirationTime );
				pExhaleSegment->ZoomRespVolumeHandle(fRemainVolume, fSumVolume);
				//-----------------------------------------------------------------------
				pRespCycleData = new CRespCycleData(pInspirationSegment, pExhaleSegment,nRespRate, nMillitInspirationTime);
			}
			else
			{
				float fApneaRemainVolume = m_pRespParams->GetApneaRemainVolume();
				if( int(fCurrentRemainVolume+0.0001) > int(fApneaRemainVolume+0.0001) )
				{
					pExhaleSegment = new CExhaleSegment();
					pExhaleSegment->Clone( m_pOriginExhaleSegment );
				}
				pRespCycleData = new CRespApneaCycleData(pInspirationSegment, pExhaleSegment, 0, nMillitInspirationTime);
				CRespApneaCycleData *pRespApneaCycleData = (CRespApneaCycleData *)pRespCycleData;
				//���õ�ǰ��������
				pRespApneaCycleData->Set_CurrentRemainVolume(fCurrentRemainVolume);
				//���ñ����ڽ�����Ĳ�������
				pRespApneaCycleData->Set_RemainVolume(fApneaRemainVolume);
			}
		}
		pRespCycleData->Set_RespCycleTime( nSumTime );
		pRespCycleData->ResetPrepareReadSampleData();
		//�趨���ݸ��·�Χ
		pRespCycleData->m_eRefurbishDataRange = eRefurbishRange;
		//�����޸ı�־
		m_pRespParams->SetRefurbishDataRangeToNoChange();

		//�趨CO2��ʱ��
		pRespCycleData->Set_InspirationToCO2Time( m_pRespParams->GetCO2Time_Inspiration() );
		pRespCycleData->Set_ExhaleToCO2Time( m_pRespParams->GetCO2Time_Exhale() );
		return pRespCycleData;
	}
}}}