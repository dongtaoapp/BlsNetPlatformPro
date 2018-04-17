#include ".\Cardiogram2degree_AVBII.h"
#include ".\Cardiogram2degree_AVBIIParam_I12.h"

#include "..\common\EncodeConv.h"

namespace jysoft { namespace simulator { namespace ecg {

	//==================================test================================================//
	#define   _LEAD_SUM     9 /*9*/
	//================================End test==============================================//

	CCardiogram2degree_AVBII::CCardiogram2degree_AVBII( IStorage *pRootStorage )
	{
		USES_CONVERSION;
		if(pRootStorage != NULL)
		{
			pRootStorage->OpenStorage(L"2 degree AVB",NULL,STGM_READ|STGM_SHARE_EXCLUSIVE,0,0, &m_pI12LeadsStorage);
		}
		if( m_pI12LeadsStorage != NULL )
		{
			IStorage *pEcgLeadsStorage[9];
            const std::string  strEcgLeadsName[] = {"I", "II", "III", "V1", "V2", "V3", "V4", "V5", "V6"};
			for (int nStep = 0; nStep < 9; ++nStep)
			{
                m_pI12LeadsStorage->OpenStorage(s2w(strEcgLeadsName[nStep]).c_str(),NULL,STGM_READ|STGM_SHARE_EXCLUSIVE,0,0, &pEcgLeadsStorage[nStep]);
				m_pEcgLeadParam[nStep] = new CCardiogram2degree_AVBIIParam_I12( pEcgLeadsStorage[nStep] );
			}
		}
	}

	CCardiogram2degree_AVBII::~CCardiogram2degree_AVBII(void)
	{
	}

    bool CCardiogram2degree_AVBII::IsCanParamExpress(BasicRhythm eRhythm, int uHR)
	{
		bool bRtn = false;
		switch(eRhythm)
		{
		case BR_2degree_AVB_II:
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
    bool CCardiogram2degree_AVBII::IsCanExpressCardiogramParam(BasicRhythm eRhythm, int uHR)
	{
		return CCardiogram2degree_AVBII::IsCanParamExpress(eRhythm, uHR);
	}

	/*******************************************************************************/
	// �������ƣ� LoadCardiogramLeadsParam
	// ���ܣ� �����ĵ�ͼ�������Ĳ���ֵ
	// ������ 
	//         
	// ����ֵ:
    bool CCardiogram2degree_AVBII::LoadCardiogramLeadsParam( BasicRhythm eRhythm, int uHR, short sConduct, short sExtendParam )
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
	// �������ƣ� ReLoadCardiogramParam
	// ���ܣ� 
	// ������  
	// ����ֵ: 
	void CCardiogram2degree_AVBII::ReLoadCardiogramParam()
	{
		for (int index = 0; index < _LEAD_SUM/*9*/; ++index)
		{
			m_pEcgLeadParam[index]->ReLoadCardiogramParam();
		}
	}

	/*******************************************************************************/
	// �������ƣ� SeteRefurbishDataRange
	// ���ܣ� �趨�������ݵĳ̶�
	// ������  
	// ����ֵ: 
	void CCardiogram2degree_AVBII::SeteRefurbishDataRange(_eRefurbishDataRange eRange)
	{
		for (int index = 0; index < _LEAD_SUM/*9*/; ++index)
		{
			m_pEcgLeadParam[index]->SeteRefurbishDataRange( eRange );
		}
	}

	// ���ع������ݵĳ̶������ö��ֵ��RD_LoadConfigFile���RD_NoChange��ǳ��
	_eRefurbishDataRange CCardiogram2degree_AVBII::GeteRefurbishDataRange()
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
	// �������ƣ� ResetSyncFlag
	// ���ܣ� ����ͬ����ʶ�������������ڵ���������Э��
	// ������  
	// ����ֵ: 
	void CCardiogram2degree_AVBII::ResetSyncFlag()
	{
		CCardiogram2degree_AVBIIParam_I12 *pIIParam = (CCardiogram2degree_AVBIIParam_I12 *)m_pEcgLeadParam[0];
		for (int index = 0; index < _LEAD_SUM/*9*/; ++index)
		{
			CCardiogram2degree_AVBIIParam_I12 *pEcgParam = (CCardiogram2degree_AVBIIParam_I12 *)m_pEcgLeadParam[index];
			if( pIIParam->m_bEmptQRS != pEcgParam->m_bEmptQRS || pIIParam->m_nStepNum != pEcgParam->m_nStepNum || pIIParam->m_nSumStepNum != pEcgParam->m_nSumStepNum )
			{
				pEcgParam->m_bEmptQRS    = pIIParam->m_bEmptQRS;
				pEcgParam->m_nStepNum    = pIIParam->m_nStepNum;
				pEcgParam->m_nSumStepNum = pIIParam->m_nSumStepNum;
			}
		}
	}

	void CCardiogram2degree_AVBII::LoadExtrasystParamPre(Extrasys eExtrasyst)
	{
		for (int index = 0; index < _LEAD_SUM /*9*/; ++index)
		{
			m_pEcgLeadParam[index]->LoadExtrasystParamPre( eExtrasyst );
		}
	}

	void CCardiogram2degree_AVBII::LoadExtrasystParam(Extrasys eExtrasyst)
	{
		for (int index = 0; index < _LEAD_SUM /*9*/; ++index)
		{
			m_pEcgLeadParam[index]->LoadExtrasystParam( eExtrasyst );
		}
	}

}}}
