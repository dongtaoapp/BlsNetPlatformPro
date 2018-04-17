#include ".\CardiogramAgonale.h"
#include ".\CardiogramAgonaleParam_I12.h"

#include "..\common\EncodeConv.h"

namespace jysoft { namespace simulator { namespace ecg {

	//==================================test================================================//
	#define   _LEAD_SUM     9 /*9*/
	//================================End test==============================================//

	CCardiogramAgonale::CCardiogramAgonale( IStorage *pRootStorage )
	{
		USES_CONVERSION;
		if(pRootStorage != NULL)
		{
			pRootStorage->OpenStorage(L"Agonale",NULL,STGM_READ|STGM_SHARE_EXCLUSIVE,0,0, &m_pI12LeadsStorage);
		}
		if( m_pI12LeadsStorage != NULL )
		{
			IStorage *pEcgLeadsStorage[9];
            const std::string  strEcgLeadsName[] = {"I", "II", "III", "V1", "V2", "V3", "V4", "V5", "V6"};
			for (int nStep = 0; nStep < 9; ++nStep)
			{
                m_pI12LeadsStorage->OpenStorage(s2w(strEcgLeadsName[nStep]).c_str(),NULL,STGM_READ|STGM_SHARE_EXCLUSIVE,0,0, &pEcgLeadsStorage[nStep]);
				m_pEcgLeadParam[nStep] = new CCardiogramAgonaleParam_I12( pEcgLeadsStorage[nStep] );
			}
		}
	}

	CCardiogramAgonale::~CCardiogramAgonale(void)
	{
	}

    bool CCardiogramAgonale::IsCanParamExpress(BasicRhythm eRhythm, int uHR)
	{
		bool bRtn = false;
		switch(eRhythm)
		{
		case BR_AgonalRhythm:
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
	// �������ƣ� IsCanExpressCardiogramParam
	// ���ܣ� ���ݴ�����ĵ�ͼ�������Ƿ����ô˶���õ������ĵ�ͼ����Ҫ�Ĳ�����
	// ������  
	// ����ֵ: 
    bool CCardiogramAgonale::IsCanExpressCardiogramParam(BasicRhythm eRhythm, int uHR)
	{
		return CCardiogramAgonale::IsCanParamExpress( eRhythm, uHR);
	}

	/*******************************************************************************/
	// �������ƣ� LoadCardiogramLeadsParam
	// ���ܣ� �����ĵ�ͼ�������Ĳ���ֵ
	// ������ 
	//         
	// ����ֵ:
    bool CCardiogramAgonale::LoadCardiogramLeadsParam( BasicRhythm eRhythm, int uHR, short sConduct, short sExtendParam )
	{
		m_eBasicRhythm  = eRhythm;
		for (int index = 0; index < _LEAD_SUM /*9*/; ++index)
		{
			if( m_pEcgLeadParam[index] == NULL )
				return false;
			m_pEcgLeadParam[index]->LoadCardiogramParam( QRS_A, eRhythm, uHR, sConduct, sExtendParam );
		}
		return true;
	}

	/*******************************************************************************/
	// �������ƣ� ReLoadCardiogramParam
	// ���ܣ� 
	// ������  
	// ����ֵ: 
	void CCardiogramAgonale::ReLoadCardiogramParam()
	{
		for (int index = 0; index < _LEAD_SUM /*9*/; ++index)
		{
			m_pEcgLeadParam[index]->ReLoadCardiogramParam();
		}
	}

	/*******************************************************************************/
	// �������ƣ� ResetSyncFlag
	// ���ܣ� ����ͬ����ʶ�������������ڵ���������Э��
	// ������  
	// ����ֵ: 
	void CCardiogramAgonale::ResetSyncFlag()
	{
		CCardiogramAgonaleParam_I12 *pIIParam = (CCardiogramAgonaleParam_I12 *)m_pEcgLeadParam[0];
		for (int index = 0; index < _LEAD_SUM/*9*/; ++index)
		{
			CCardiogramAgonaleParam_I12 *pEcgParam = (CCardiogramAgonaleParam_I12 *)m_pEcgLeadParam[index];
			if( pIIParam->m_dwSumRunTime != pEcgParam->m_dwSumRunTime || pIIParam->m_nSumBasicSegTime != pEcgParam->m_nSumBasicSegTime || pIIParam->m_nBasicSeg_LExtentTime != pEcgParam->m_nBasicSeg_LExtentTime )
			{
				pEcgParam->m_dwSumRunTime          = pIIParam->m_dwSumRunTime;
				pEcgParam->m_nSumBasicSegTime      = pIIParam->m_nSumBasicSegTime;
				pEcgParam->m_nBasicSeg_LExtentTime = pIIParam->m_nBasicSeg_LExtentTime;
			}
		}
	}

	/*******************************************************************************/
	// �������ƣ� SeteRefurbishDataRange
	// ���ܣ� �趨�������ݵĳ̶�
	// ������  
	// ����ֵ: 
	void CCardiogramAgonale::SeteRefurbishDataRange(_eRefurbishDataRange eRange)
	{
		for (int index = 0; index < _LEAD_SUM /*9*/; ++index)
		{
			m_pEcgLeadParam[index]->SeteRefurbishDataRange( eRange );
		}
	}

	// ���ع������ݵĳ̶������ö��ֵ��RD_LoadConfigFile���RD_NoChange��ǳ��
	_eRefurbishDataRange CCardiogramAgonale::GeteRefurbishDataRange()
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
