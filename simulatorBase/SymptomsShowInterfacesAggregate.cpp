#include ".\SymptomsShowInterfacesAggregate.h"


using namespace jysoft::simulator::base;
namespace jysoft { namespace simulator 
{
	CSymptomsShowInterfacesAggregate::CSymptomsShowInterfacesAggregate(void)
	{
		//�ĵ�ͼ��ʾ�ӿ�
		m_pShowECGInterface       = NULL;
		//EMD��ʾ�ӿ�
		m_pShowEMDInterface       = NULL;
		//Ѫѹ��ʾ�ӿ�
		m_pShowNIBPInterface      = NULL;
		//����ģʽ��ʾ�ӿ�
		m_pShowRespInterface      = NULL;
		//��������ʾ�ӿ�
		m_pShowPaceInterface      = NULL;
	}

	CSymptomsShowInterfacesAggregate::~CSymptomsShowInterfacesAggregate(void)
	{
	}

	void CSymptomsShowInterfacesAggregate::Set_ShowECGUpdateInterfacePtr(CShowECGUpdateInterface *pShowECGInterface)
	{
		if( m_pShowECGInterface == NULL )
		{
			m_pShowECGInterface = pShowECGInterface;
		}
		else
		{
			m_pShowECGInterface->SetNextInterfacePtr( pShowECGInterface );
		}
	}

	void CSymptomsShowInterfacesAggregate::Set_ShowEMDUpdateInterfacePtr(CShowECGUpdateInterface *pShowEMDInterface)
	{
		if( m_pShowEMDInterface == NULL )
		{
			m_pShowEMDInterface = pShowEMDInterface;
		}
		else
		{
			m_pShowEMDInterface->SetNextInterfacePtr( pShowEMDInterface );
		}
	}

	void CSymptomsShowInterfacesAggregate::Set_ShowRespUpdateInterfacePtr(CShowRespRateUpdateInterface *pShowRespInterface)
	{
		if( m_pShowRespInterface == NULL )
		{
			m_pShowRespInterface = pShowRespInterface;
		}
		else
		{
			m_pShowRespInterface->SetNextInterfacePtr( pShowRespInterface );
		}
	}

	void CSymptomsShowInterfacesAggregate::Set_ShowNIBPUpdateInterfacePtr( CShowNIBPUpdateInterface *pShowNIBPUpdateInterface )
	{
		if( m_pShowNIBPInterface == NULL )
		{
			m_pShowNIBPInterface = pShowNIBPUpdateInterface;
		}
		else
		{
			m_pShowNIBPInterface->SetNextInterfacePtr( pShowNIBPUpdateInterface );
		}
	}

	void CSymptomsShowInterfacesAggregate::Set_ShowPaceUpdateInterfacePtr( CShowPaceUpdateInterface *pShowPaceInterface )
	{
		if( m_pShowPaceInterface == NULL )
		{
			m_pShowPaceInterface = pShowPaceInterface;
		}
		else
		{
			m_pShowPaceInterface->SetNextInterfacePtr( pShowPaceInterface );
		}
	}
}}
