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
	// 函数名称： GetEcgLeadParam
	// 功能： 返回指定导联心电图的参数构建类
	// 参数： 
	//        RhythmLead  eEcgLeadType:  
	// 返回值:  
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

	//返回周期时间
	int ICardiogramLeads::GetCycleTime()
	{
		//I 导联的数据为准
		return m_pEcgLeadParam[0]->GetCycleTime();
	}

	//返回当前的心率
	int ICardiogramLeads::Get_iRhythmHR()
	{
		//I 导联的数据为准
		return m_pEcgLeadParam[0]->GetRhythmHR();
	}

	//产生心电时，血氧的启动时间
	bool ICardiogramLeads::GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime)
	{
		//I 导联的数据为准...
		return m_pEcgLeadParam[0]->GetSpO2BeginTimeToCardiogram(/*out*/lBeginTime, /*out*/lCycleTime);
	}

	//产生早博时，血氧的启动时间
	bool ICardiogramLeads::GetSpO2BeginTimeToExtrasyst(/*out*/long &lBeginTime, /*out*/long &lPreSpO2BeginTime, /*out*/long &lCycleTime)
	{
		//I 导联的数据为准...
		return m_pEcgLeadParam[0]->GetSpO2BeginTimeToExtrasyst(/*out*/lBeginTime, /*out*/lPreSpO2BeginTime, /*out*/lCycleTime);
	}

}}
