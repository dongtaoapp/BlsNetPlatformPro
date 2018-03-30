#include ".\cprshowinterfacesaggregate.h"

namespace jysoft{  namespace cpr {

	CCPRShowInterfacesAggregate::CCPRShowInterfacesAggregate(void)
	{
		m_pShowCPRDetailActInterface  = NULL;
		m_pShowCPRStatisticInterface  = NULL;
		m_pShowCPRRealTimeInteface    = NULL;
	}

	CCPRShowInterfacesAggregate::~CCPRShowInterfacesAggregate(void)
	{
	}

	//����CPR������⶯����ʾ�ӿ�
	void CCPRShowInterfacesAggregate::Set_ShowCPRDetailActUpdateInterface(CShowCPRActUpdateInterface *pInterface) 
	{ 
		if( m_pShowCPRDetailActInterface == NULL )
		{
			m_pShowCPRDetailActInterface = pInterface; 
		}
		else
		{
			m_pShowCPRDetailActInterface->SetNextInterfacePtr( pInterface );
		}
	}

	//����CPRͳ����ʾ�ӿ�
	void CCPRShowInterfacesAggregate::Set_ShowCPRStatisticUpdateInterface(CShowCPRStatisticUpdateInterface *pInterface) 
	{ 
		if( m_pShowCPRStatisticInterface == NULL )
		{
			m_pShowCPRStatisticInterface = pInterface;
		}
		else
		{
			m_pShowCPRStatisticInterface->SetNextInterfacePtr( pInterface );
		}
	}

	//����CPRʵʩ������ʾ�ӿ�
	void CCPRShowInterfacesAggregate::Set_ShowCPRRealTimeUpdateInterface(CCPRRealTimeUpdateInterface *pInterface) 
	{
		if( m_pShowCPRRealTimeInteface == NULL )
		{
			m_pShowCPRRealTimeInteface = pInterface; 
		}
		else
		{
			m_pShowCPRRealTimeInteface->SetNextInterfacePtr( pInterface );
		}
	}
	//�Ƴ�CPR������⶯����ʾ�ӿ�
	void CCPRShowInterfacesAggregate::Remove_ShowCPRDetailActUpdateInterface(CShowCPRActUpdateInterface *pRmvInterface)
	{
		if( m_pShowCPRDetailActInterface != NULL )
		{
			m_pShowCPRDetailActInterface = (CShowCPRActUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowCPRDetailActInterface, pRmvInterface);
		}
	}
}}
