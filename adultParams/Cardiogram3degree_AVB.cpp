#include ".\Cardiogram3degree_AVB.h"
#include ".\Cardiogram3degree_AVBParam_I12.h"

#include "..\common\EncodeConv.h"

namespace jysoft { namespace simulator { namespace ecg {

	//==================================test================================================//
	#define   _LEAD_SUM     9 /*9*/
	//================================End test==============================================//

	CCardiogram3degree_AVB::CCardiogram3degree_AVB(IStorage *pRootStorage )
	{
		USES_CONVERSION;
		if(pRootStorage != NULL)
		{
			pRootStorage->OpenStorage(L"3 degree AVB",NULL,STGM_READ|STGM_SHARE_EXCLUSIVE,0,0, &m_pI12LeadsStorage);
		}
		if( m_pI12LeadsStorage != NULL )
		{
			IStorage *pEcgLeadsStorage[9];
            const std::string  strEcgLeadsName[] = {"I", "II", "III", "V1", "V2", "V3", "V4", "V5", "V6"};
			for (int nStep = 0; nStep < 9; ++nStep)
			{
                m_pI12LeadsStorage->OpenStorage(s2w(strEcgLeadsName[nStep]).c_str(),NULL,STGM_READ|STGM_SHARE_EXCLUSIVE,0,0, &pEcgLeadsStorage[nStep]);
				m_pEcgLeadParam[nStep] = new CCardiogram3degree_AVBParam_I12( pEcgLeadsStorage[nStep] );
			}
		}
	}

	CCardiogram3degree_AVB::~CCardiogram3degree_AVB(void)
	{
	}

    bool CCardiogram3degree_AVB::IsCanParamExpress(BasicRhythm eRhythm, int uHR)
	{
		bool bRtn = false;
		switch(eRhythm)
		{
		case BR_3degree_AVB:
			{
				bRtn = true;
				break;
			}
		default:
			{
				bRtn = false;
				break;
			}
		}
		return bRtn;
	}

	/*******************************************************************************/
	// 函数名称： IsCanExpressCardiogramParam
	// 功能： 根据传入的心电图描述，是否能用此对象得到画此心电图所需要的参数。
	// 参数：  
	// 返回值: 
    bool CCardiogram3degree_AVB::IsCanExpressCardiogramParam(BasicRhythm eRhythm, int uHR)
	{
		return CCardiogram3degree_AVB::IsCanParamExpress(eRhythm, uHR);
	}

	/*******************************************************************************/
	// 函数名称： LoadCardiogramLeadsParam
	// 功能： 加载心电图各导联的参数值
	// 参数： 
	//         
	// 返回值:
    bool CCardiogram3degree_AVB::LoadCardiogramLeadsParam( BasicRhythm eRhythm, int uHR, short sConduct, short sExtendParam )
	{
		m_eBasicRhythm  = eRhythm;
		for (int index = 0; index < _LEAD_SUM/*9*/; ++index)
		{
			if( m_pEcgLeadParam[index] == NULL )
				return false;
			m_pEcgLeadParam[index]->LoadCardiogramParam( QRS_A, eRhythm, uHR, sConduct, sExtendParam );
		}
		return true;
	}

	/*******************************************************************************/
	// 函数名称： ReLoadCardiogramParam
	// 功能： 
	// 参数：  
	// 返回值: 
	void CCardiogram3degree_AVB::ReLoadCardiogramParam()
	{
		for (int index = 0; index < _LEAD_SUM/*9*/; ++index)
		{
			m_pEcgLeadParam[index]->ReLoadCardiogramParam();
		}
	}

	/*******************************************************************************/
	// 函数名称： SeteRefurbishDataRange
	// 功能： 设定构建数据的程度
	// 参数：  
	// 返回值: 
	void CCardiogram3degree_AVB::SeteRefurbishDataRange(_eRefurbishDataRange eRange)
	{
		for (int index = 0; index < _LEAD_SUM/*9*/; ++index)
		{
			m_pEcgLeadParam[index]->SeteRefurbishDataRange( eRange );
		}
	}

	// 返回构建数据的程度最深的枚举值（RD_LoadConfigFile最深，RD_NoChange最浅）
	_eRefurbishDataRange CCardiogram3degree_AVB::GeteRefurbishDataRange()
	{
		_eRefurbishDataRange   eRtnRange = RD_NoChange;
		for (int index = 0; index < _LEAD_SUM/*9*/; ++index)
		{
			_eRefurbishDataRange eRange = m_pEcgLeadParam[index]->GeteRefurbishDataRange();
			if( eRange != RD_NoChange )
			{
				if( eRtnRange == RD_NoChange )
				{
					eRtnRange  = eRange;
				}
				else if( eRtnRange > eRange )
				{
					eRtnRange = eRange;
				}
			}
		}
		return eRtnRange;
	}

	/*******************************************************************************/
	// 函数名称： ResetSyncFlag
	// 功能： 重置同步标识符，用于下周期导联构建的协调
	// 参数：  
	// 返回值: 
	void CCardiogram3degree_AVB::ResetSyncFlag()
	{
		CCardiogram3degree_AVBParam_I12 *pIIParam = (CCardiogram3degree_AVBParam_I12 *)m_pEcgLeadParam[0];
		for (int index = 0; index < _LEAD_SUM; ++index)
		{
			CCardiogram3degree_AVBParam_I12 *pEcgParam = (CCardiogram3degree_AVBParam_I12 *)m_pEcgLeadParam[index];
			if( pIIParam->m_dwSumRunTime != pEcgParam->m_dwSumRunTime || pIIParam->m_nSumBasicSegTime != pEcgParam->m_nSumBasicSegTime || pIIParam->m_nBasicSeg_LExtentTime != pEcgParam->m_nBasicSeg_LExtentTime )
			{
				pEcgParam->m_dwSumRunTime          = pIIParam->m_dwSumRunTime;
				pEcgParam->m_nSumBasicSegTime      = pIIParam->m_nSumBasicSegTime;
				pEcgParam->m_nBasicSeg_LExtentTime = pIIParam->m_nBasicSeg_LExtentTime;
			}
		}
	}

}}}
