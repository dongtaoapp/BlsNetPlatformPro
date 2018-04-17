#include ".\respnormaltypestate.h"
#include ".\RespParamImpl.h"

#include "..\AdultParams\AdultRespParam.h"

namespace jysoft { namespace simulator { namespace resp {

	CRespNormalTypeState::CRespNormalTypeState(SimulatePatientType ePatientType)
								: IRespBuildTypeState()
	{
		switch( ePatientType )
		{
		case SPT_Adult:
			{
				m_pRespParams = new CRespParamImpl<CAdultRespParam>();
				break;
			}
		}
	}

	CRespNormalTypeState::CRespNormalTypeState()
	{
		m_pRespParams  = NULL;
	}

	CRespNormalTypeState::~CRespNormalTypeState(void)
	{
		if( m_pRespParams != NULL )
		{
			delete m_pRespParams;
			m_pRespParams = NULL;
		}
	}

	bool CRespNormalTypeState::isKindOf(const std::string &className)
	{
		if( className == "CRespNormalTypeState" )
			return true;
		return false;
	}

	/*******************************************************************************/
	// 函数名称： InitialLoadOriginSimulateData
	// 功能： 加载原始呼吸数据
	// 参数： 
	// 返回值:  
	void CRespNormalTypeState::InitialLoadOriginSimulateData(const std::string &respResoucePath, int nRespRate) 
	{
		//加载吸气数据
		if( m_pOriginInspirationSegment == NULL )
		{
			m_pOriginInspirationSegment = new CInspirationSegment();
		}
		std::string strInspirateFilePath = respResoucePath + "\\InspirationData.txt";
		m_pOriginInspirationSegment->LoadSegmentData(strInspirateFilePath);
		//加载呼气数据
		if( m_pOriginExhaleSegment == NULL )
		{
			m_pOriginExhaleSegment = new CExhaleSegment();
		}
		std::string strExhaleFilePath = respResoucePath + "\\ExhaleData.txt";
		m_pOriginExhaleSegment->LoadSegmentData( strExhaleFilePath );
		//设定缺省的呼吸次数
		m_nRespRate = nRespRate;
		//加载参数
		m_pRespParams->LoadRespParams( nRespRate );
	}
	/*******************************************************************************/
	// 函数名称： OnModifyRespRate
	// 功能： 修改呼吸次数
	// 参数： int nRespRate: 新的呼吸次数
	// 返回值:  
	void CRespNormalTypeState::OnModifyRespRate(int nRespRate) 
	{
		m_cMutex.Lock();
		m_nRespRate = nRespRate;
		//加载参数
		m_pRespParams->LoadRespParams( m_nRespRate );
		m_cMutex.Unlock();
	}
	/*******************************************************************************/
	// 函数名称： OnCombineNextRespCycleData
	// 功能： 返回下周期的呼吸数据
	// 参数： float fCurrentRemainVolume:           当前的气量
	//        CRespCycleDataCollects *pRespCollect: 
	// 返回值:  
	CRespCycleData * CRespNormalTypeState::OnCombineNextRespCycleData(float fCurrentRemainVolume, CRespCycleDataCollects *pRespCollect)
	{
		m_cMutex.Lock();
		_eRefurbishDataRange  eRefurbishRange = m_pRespParams->Get_eRefurbishDataRange();
		int nRespRate       = m_nRespRate;
		//吸气时间(单位:0.1ms)
		int nMillitInspirationTime = m_pRespParams->GetInspriationTime();
		//本周期的总气量(单位:ml)
		float fSumVolume    =  m_pRespParams->GetRespVolume();
		//本周期结束后的残留的量(单位:ml)
		float fRemainVolume = m_pRespParams->GetRespRemainVolume();
		//返回周期时间(单位：0.1ms)
		int   nSumTime      = m_pRespParams->GetRespCycleTime();
		m_cMutex.Unlock();
		CRespCycleData *pRespCycleData = pRespCollect->RemoveRespCycleData();
		if( pRespCycleData != NULL && !pRespCycleData->JudgeIsRepeatCycleData(nRespRate, nMillitInspirationTime, fCurrentRemainVolume,fSumVolume, fRemainVolume))
		{
			delete pRespCycleData;
			pRespCycleData = NULL;
		}
		//生成新的周期数据
		if( pRespCycleData == NULL )
		{
			CInspirationSegment  *pInspirationSegment = NULL;
			CExhaleSegment       *pExhaleSegment      = NULL;
			if(nRespRate != 0)
			{
				//生成吸气段采样数据
				pInspirationSegment = new CInspirationSegment();
				pInspirationSegment->Clone( m_pOriginInspirationSegment );
				pInspirationSegment->ZoomSegmentDataHandle( nMillitInspirationTime );
				pInspirationSegment->ZoomRespVolumeHandle(fCurrentRemainVolume, fSumVolume);
				//生成呼气段采样数据
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
				//设置当前残留的量
				pRespApneaCycleData->Set_CurrentRemainVolume(fCurrentRemainVolume);
				//设置本周期结束后的残留的量
				pRespApneaCycleData->Set_RemainVolume(fApneaRemainVolume);
			}
		}
		pRespCycleData->Set_RespCycleTime( nSumTime );
		pRespCycleData->ResetPrepareReadSampleData();
		//设定数据更新范围
		pRespCycleData->m_eRefurbishDataRange = eRefurbishRange;
		//设定CO2的时间
		pRespCycleData->Set_InspirationToCO2Time( m_pRespParams->GetCO2Time_Inspiration() );
		pRespCycleData->Set_ExhaleToCO2Time( m_pRespParams->GetCO2Time_Exhale() );
		//设置修改标志
		m_pRespParams->SetRefurbishDataRangeToNoChange();
		return pRespCycleData;
	}
}}}
