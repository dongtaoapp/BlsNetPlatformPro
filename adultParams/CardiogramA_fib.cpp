#include ".\CardiogramA_fib.h"
#include ".\CardiogramA_fibParam_I12.h"

#include "..\common\EncodeConv.h"

namespace jysoft { namespace simulator { namespace ecg {

	//==================================test================================================//
	#define   _LEAD_SUM     9 /*9*/
	//================================End test==============================================//

	CCardiogramA_fib::CCardiogramA_fib(IStorage *pRootStorage )
	{
		USES_CONVERSION;
		if(pRootStorage != NULL)
		{
			pRootStorage->OpenStorage(L"A. fib",NULL,STGM_READ|STGM_SHARE_EXCLUSIVE,0,0, &m_pI12LeadsStorage);
		}
		if( m_pI12LeadsStorage != NULL )
		{
			IStorage *pEcgLeadsStorage[9];
            const std::string  strEcgLeadsName[] = {"I", "II", "III", "V1", "V2", "V3", "V4", "V5", "V6"};
			for (int nStep = 0; nStep < 9; ++nStep)
			{
                m_pI12LeadsStorage->OpenStorage(s2w(strEcgLeadsName[nStep]).c_str(),NULL,STGM_READ|STGM_SHARE_EXCLUSIVE,0,0, &pEcgLeadsStorage[nStep]);
				m_pEcgLeadParam[nStep] = new CCardiogramA_fibParam_I12( this, pEcgLeadsStorage[nStep] );
			}
		}
		//---------------------------------------------------------------------------------------------------------------------
		m_uHR         = 0;
		m_nCycleTime  = 0;
	}

	CCardiogramA_fib::~CCardiogramA_fib(void)
	{
	}

    bool CCardiogramA_fib::IsCanParamExpress(BasicRhythm eRhythm, int uHR)
	{
		bool bRtn = false;
		switch(eRhythm)
		{
		case BR_AFib:
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
    bool CCardiogramA_fib::IsCanExpressCardiogramParam(BasicRhythm eRhythm, int uHR)
	{
		return CCardiogramA_fib::IsCanParamExpress( eRhythm, uHR );
	}

	/*******************************************************************************/
	// 函数名称： LoadCardiogramLeadsParam
	// 功能： 加载心电图各导联的参数值
	// 参数： 
	//         
	// 返回值:
    bool CCardiogramA_fib::LoadCardiogramLeadsParam( BasicRhythm eRhythm, int uHR, short sConduct, short sExtendParam )
	{
		m_uHR  = uHR;
		//随机定义周期时间
		m_nCycleTime  = RadonA_fibCycleTime( uHR );
		m_eBasicRhythm = eRhythm;
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
	void CCardiogramA_fib::ReLoadCardiogramParam()
	{
		//随机定义周期时间
		m_nCycleTime  = RadonA_fibCycleTime( m_uHR );
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
	void CCardiogramA_fib::SeteRefurbishDataRange(_eRefurbishDataRange eRange)
	{
		for (int index = 0; index < _LEAD_SUM/*9*/; ++index)
		{
			m_pEcgLeadParam[index]->SeteRefurbishDataRange( eRange );
		}
	}

	// 返回构建数据的程度最深的枚举值（RD_LoadConfigFile最深，RD_NoChange最浅）
	_eRefurbishDataRange CCardiogramA_fib::GeteRefurbishDataRange()
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
	void CCardiogramA_fib::ResetSyncFlag()
	{
		CCardiogramA_fibParam_I12 *pIIParam = (CCardiogramA_fibParam_I12 *)m_pEcgLeadParam[0];
		for (int index = 0; index < _LEAD_SUM/*9*/; ++index)
		{
			CCardiogramA_fibParam_I12 *pEcgParam = (CCardiogramA_fibParam_I12 *)m_pEcgLeadParam[index];
			if( pIIParam->m_dwSumRunTime != pEcgParam->m_dwSumRunTime || pIIParam->m_nSumBasicSegTime != pEcgParam->m_nSumBasicSegTime || pIIParam->m_nBasicSeg_LExtentTime != pEcgParam->m_nBasicSeg_LExtentTime )
			{
				pEcgParam->m_dwSumRunTime          = pIIParam->m_dwSumRunTime;
				pEcgParam->m_nSumBasicSegTime      = pIIParam->m_nSumBasicSegTime;
				pEcgParam->m_nBasicSeg_LExtentTime = pIIParam->m_nBasicSeg_LExtentTime;
			}
		}
	}

	//随机定义周期时间
    int CCardiogramA_fib::RadonA_fibCycleTime( int uHR )
	{
		static int iCycleTime[][15] = {
			{5000,7000,9000,4800,11000,13000,14000,15000,3800,17000,18000,20000,22000,23000,25000},//50HR
			{5500,7000,7500,9500,10500,4800,12000,12500,13500,3800,16500,18500,20500,10500,20000},//60HR
			{5000,5400,6400,7500,8400,9400,10400,10500,3800,12400,13400,16000,16400,17400,7400},//70HR
			{5000,5300,6300,7300,8300,9300,10300,11300,12200,12300,13300,13300,11300,16300,16300},//80HR
			{4400,5300,5500,6400,7000,7400,3800,9000,10000,16400,9400,10400,11500,18000,25000},//90HR
			{4800,4500,5400,5600,5100,6100,6500,6600,7200,7300,7600,9100,13300,18000,22000},//100HR
			{5600,4500,4800,5100,6100,6500,6600,7600,9100,9400,7300,9500,7200,18000,5400},//105HR
			{4300,4500,4800,5000,6000,6100,7000,8000,8500,8700,5600,6600,6000,11500,8200},//110HR
			{4300,4800,5000,4500,7000,5600,6600,6000,6100,8000,8500,8700,6000,11500,8200},//115HR
			{3700,3800,3900,4000,4600,5100,5500,6200,6400,7000,8300,7600,3900,11500,5500},//120HR
			{3700,3800,3900,4000,4600,5100,5500,6200,6400,7000,8300,7600,3900,7800,5500},//125HR
			{3700,3800,3900,4000,4600,5100,5500,6200,6400,7000,8300,7600,3900,7800,5500},//130HR
			{3800,3900,4100,4500,4600,4000,4300,4400,6000,4100,5300,6500,4400,6100,5600},//135HR
			{3800,3900,4100,4500,4600,4000,4300,4400,6000,4100,5300,6500,4400,6100,5600},//140HR
			{3800,3900,4100,4500,4600,4000,4300,4400,6000,4100,5300,6500,4400,6100,5600},//145HR
			{3800,3900,4100,4500,4600,4000,4300,4400,6000,4100,5300,6500,4400,6100,5600},//150HR
			{3200,3300,3500,3600,3700,3800,3900,4000,4300,4500,5000,5500,5400,5900,6000},//155HR
			{3200,3300,3500,3600,3700,3800,3900,4000,4300,4500,5000,5500,5400,5900,6000},//160HR
			{3200,3300,3500,3600,3700,3800,3900,4000,4300,4500,5000,5500,5400,5900,6000},//165HR
			{3200,3300,3500,3600,3700,3800,3900,4000,4300,4500,5000,5500,5400,5900,6000},//170HR
			{1900,2400,2600,2500,2700,2900,3000,3400,3600,3800,3900,4700,4100,4200,4500},//175HR
			{1900,2400,2600,2500,2700,2900,3000,3400,3600,3800,3900,4700,4100,4200,4500},//180HR
			{1900,2400,2600,2500,2700,2900,3000,3400,3600,3800,3900,4700,4100,4200,4500},//185HR
			{1900,2000,2100,2300,2400,2600,2700,3100,3300,3600,3800,3900,4000,5000,7000},//190HR
			{1900,2000,2100,2300,2400,2600,2700,3100,3300,3600,3800,3900,4000,5000,7000},//195HR
			{1900,2000,2100,2300,2400,2600,2700,3100,3300,3600,3800,3900,4000,5000,7000} //200HR
		};
		//--------------------------------------------------------------------------
		int iHRStep = uHR/10 - 5;
		if( uHR > 100 && uHR <= 200 )
		{
			iHRStep = (uHR-100)/5 + 5;
		}
		//---------------------------------------------------------------------------
		srand( (unsigned)time( NULL ) );

		int iStep = rand();
		iStep = iStep%15;
		return iCycleTime[iHRStep][iStep];
	}

}}}
