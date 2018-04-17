#include ".\CardiogramTorsade_DP.h"
#include ".\CardiogramTorsade_DPParam_I12.h"

#include "..\common\EncodeConv.h"

namespace jysoft { namespace simulator { namespace ecg {

	//==================================test================================================//
	#define   _LEAD_SUM     9 /*9*/
	//================================End test==============================================//

	CCardiogramTorsade_DP::CCardiogramTorsade_DP( IStorage *pRootStorage )
	{
		USES_CONVERSION;
		if(pRootStorage != NULL)
		{
			pRootStorage->OpenStorage(L"Torsade DP",NULL,STGM_READ|STGM_SHARE_EXCLUSIVE,0,0, &m_pI12LeadsStorage);
		}
		if( m_pI12LeadsStorage != NULL )
		{
			IStorage *pEcgLeadsStorage[9];
            const std::string  strEcgLeadsName[] = {"I", "II", "III", "V1", "V2", "V3", "V4", "V5", "V6"};
			for (int nStep = 0; nStep < 9; ++nStep)
			{
                m_pI12LeadsStorage->OpenStorage(s2w(strEcgLeadsName[nStep]).c_str(),NULL,STGM_READ|STGM_SHARE_EXCLUSIVE,0,0, &pEcgLeadsStorage[nStep]);
				m_pEcgLeadParam[nStep] = new CCardiogramTorsade_DPParam_I12( pEcgLeadsStorage[nStep] );
			}
		}
	}

	CCardiogramTorsade_DP::~CCardiogramTorsade_DP(void)
	{
	}

    bool CCardiogramTorsade_DP::IsCanParamExpress(BasicRhythm eRhythm, int uHR)
	{
		bool bRtn = false;
		switch(eRhythm)
		{
		case BR_Torsade_DP:
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
    bool CCardiogramTorsade_DP::IsCanExpressCardiogramParam(BasicRhythm eRhythm, int uHR)
	{
		return CCardiogramTorsade_DP::IsCanParamExpress( eRhythm, uHR );
	}

	/*******************************************************************************/
	// 函数名称： LoadCardiogramLeadsParam
	// 功能： 加载心电图各导联的参数值
	// 参数： 
	//         
	// 返回值:
    bool CCardiogramTorsade_DP::LoadCardiogramLeadsParam( BasicRhythm eRhythm, int uHR, short sConduct, short sExtendParam )
	{
		m_eBasicRhythm = eRhythm;
		for (int index = 0; index < _LEAD_SUM /*9*/; ++index)
		{
			if( m_pEcgLeadParam[index] == NULL )
				return FALSE;
			m_pEcgLeadParam[index]->LoadCardiogramParam( QRS_A, eRhythm, uHR, sConduct, sExtendParam );
		}
		return TRUE;
	}

	/*******************************************************************************/
	// 函数名称： ReLoadCardiogramParam
	// 功能： 
	// 参数：  
	// 返回值: 
	void CCardiogramTorsade_DP::ReLoadCardiogramParam()
	{
		for (int index = 0; index < _LEAD_SUM /*9*/; ++index)
		{
			m_pEcgLeadParam[index]->ReLoadCardiogramParam();
		}
	}

	/*******************************************************************************/
	// 函数名称： SeteRefurbishDataRange
	// 功能： 设定构建数据的程度
	// 参数：  
	// 返回值: 
	void CCardiogramTorsade_DP::SeteRefurbishDataRange(_eRefurbishDataRange eRange)
	{
		for (int index = 0; index < _LEAD_SUM /*9*/; ++index)
		{
			m_pEcgLeadParam[index]->SeteRefurbishDataRange( eRange );
		}
	}

	// 返回构建数据的程度最深的枚举值（RD_LoadConfigFile最深，RD_NoChange最浅）
	_eRefurbishDataRange CCardiogramTorsade_DP::GeteRefurbishDataRange()
	{
		_eRefurbishDataRange   eRtnRange = RD_NoChange;
		for (int index = 0; index < _LEAD_SUM /*9*/; ++index)
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
}}}
