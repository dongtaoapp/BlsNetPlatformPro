#include ".\ICardiogramLeads.h"


namespace jysoft { namespace simulator { 

	ICardiogramLeads::ICardiogramLeads(void)
	{
		for (int index = 0; index < 9; ++index)
		{
			m_pEcgLeadParam[index] = NULL;
		}
		m_eBasicRhythm  = BR_None;
        //m_pI12LeadsStorage  = NULL;
	}


	ICardiogramLeads::~ICardiogramLeads(void)
	{
		for (int index = 0; index < 9; ++index)
		{
			delete m_pEcgLeadParam[index] ;
		}
        //if( m_pI12LeadsStorage != NULL )
        //{
        //	m_pI12LeadsStorage->Release();
        //}
	}

	/*******************************************************************************/
	// �������ƣ� GetEcgLeadParam
	// ���ܣ� ����ָ�������ĵ�ͼ�Ĳ���������
	// ������ 
	//        RhythmLead  eEcgLeadType:  
	// ����ֵ:  
	CVirCardiogramParam * ICardiogramLeads::GetEcgLeadParam(RhythmLead  eEcgLeadType)
	{
		CVirCardiogramParam * pCardiogramLeadParam = NULL;
		if( eEcgLeadType != Lead_aVR && eEcgLeadType != Lead_aVL && eEcgLeadType != Lead_aVF )
		{
			if( eEcgLeadType <= Lead_III )
			{
				pCardiogramLeadParam = m_pEcgLeadParam[int(eEcgLeadType)];
			}
			else if( eEcgLeadType >= Lead_V1 )
			{
				pCardiogramLeadParam = m_pEcgLeadParam[int(eEcgLeadType)-3];
			}
		}
		return pCardiogramLeadParam;
	}

	//��������ʱ��
	int ICardiogramLeads::GetCycleTime()
	{
		//I ����������Ϊ׼
		return m_pEcgLeadParam[0]->GetCycleTime();
	}

	//���ص�ǰ������
	int ICardiogramLeads::Get_iRhythmHR()
	{
		//I ����������Ϊ׼
		return m_pEcgLeadParam[0]->GetRhythmHR();
	}

	//�����ĵ�ʱ��Ѫ��������ʱ��
	bool ICardiogramLeads::GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime)
	{
		//I ����������Ϊ׼...
		return m_pEcgLeadParam[0]->GetSpO2BeginTimeToCardiogram(/*out*/lBeginTime, /*out*/lCycleTime);
	}

	//�����粩ʱ��Ѫ��������ʱ��
	bool ICardiogramLeads::GetSpO2BeginTimeToExtrasyst(/*out*/long &lBeginTime, /*out*/long &lPreSpO2BeginTime, /*out*/long &lCycleTime)
	{
		//I ����������Ϊ׼...
		return m_pEcgLeadParam[0]->GetSpO2BeginTimeToExtrasyst(/*out*/lBeginTime, /*out*/lPreSpO2BeginTime, /*out*/lCycleTime);
	}

}}
