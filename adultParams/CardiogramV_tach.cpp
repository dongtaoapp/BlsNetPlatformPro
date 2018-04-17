#include ".\CardiogramV_tach.h"
#include ".\CardiogramV_tachParam_I12.h"

#include "..\common\EncodeConv.h"


namespace jysoft { namespace simulator { namespace ecg {

	//==================================test================================================//
	#define   _LEAD_SUM     9 /*9*/
	//================================End test==============================================//

	CCardiogramV_tach::CCardiogramV_tach(IStorage *pRootStorage )
	{
		USES_CONVERSION;
		if(pRootStorage != NULL)
		{
			pRootStorage->OpenStorage(L"V. tach",NULL,STGM_READ|STGM_SHARE_EXCLUSIVE,0,0, &m_pI12LeadsStorage);
		}
		if( m_pI12LeadsStorage != NULL )
		{
			IStorage *pEcgLeadsStorage[9];
            const std::string  strEcgLeadsName[] = {"I", "II", "III", "V1", "V2", "V3", "V4", "V5", "V6"};
			for (int nStep = 0; nStep < 9; ++nStep)
			{
                m_pI12LeadsStorage->OpenStorage(s2w(strEcgLeadsName[nStep]).c_str(),NULL,STGM_READ|STGM_SHARE_EXCLUSIVE,0,0, &pEcgLeadsStorage[nStep]);
				m_pEcgLeadParam[nStep] = new CCardiogramV_tachParam_I12( pEcgLeadsStorage[nStep] );
			}
		}
	}

	CCardiogramV_tach::~CCardiogramV_tach(void)
	{
	}

    bool CCardiogramV_tach::IsCanParamExpress(BasicRhythm eRhythm, int uHR)
	{
		bool bRtn = false;
		switch(eRhythm)
		{
		case BR_VTach:
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
    bool CCardiogramV_tach::IsCanExpressCardiogramParam(BasicRhythm eRhythm, int uHR)
	{
		return CCardiogramV_tach::IsCanParamExpress( eRhythm, uHR );
	}

	/*******************************************************************************/
	// �������ƣ� LoadCardiogramLeadsParam
	// ���ܣ� �����ĵ�ͼ�������Ĳ���ֵ
	// ������ 
	//         
	// ����ֵ:
    bool CCardiogramV_tach::LoadCardiogramLeadsParam( BasicRhythm eRhythm, int uHR, short sConduct, short sExtendParam )
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
	void CCardiogramV_tach::ReLoadCardiogramParam()
	{
		for (int index = 0; index < _LEAD_SUM /*9*/; ++index)
		{
			m_pEcgLeadParam[index]->ReLoadCardiogramParam();
		}
	}

	/*******************************************************************************/
	// �������ƣ� SeteRefurbishDataRange
	// ���ܣ� �趨�������ݵĳ̶�
	// ������  
	// ����ֵ: 
	void CCardiogramV_tach::SeteRefurbishDataRange(_eRefurbishDataRange eRange)
	{
		for (int index = 0; index < _LEAD_SUM /*9*/; ++index)
		{
			m_pEcgLeadParam[index]->SeteRefurbishDataRange( eRange );
		}
	}

	// ���ع������ݵĳ̶������ö��ֵ��RD_LoadConfigFile���RD_NoChange��ǳ��
	_eRefurbishDataRange CCardiogramV_tach::GeteRefurbishDataRange()
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
