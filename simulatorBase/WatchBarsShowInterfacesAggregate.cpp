#include ".\watchbarsshowinterfacesaggregate.h"


namespace jysoft { namespace simulator {

	using namespace base;

	CWatchBarsShowInterfacesAggregate::CWatchBarsShowInterfacesAggregate(void)
	{
		//�ĵ�ͼ��Ϣ��ʾ�ӿڣ������������ơ����ʴ���������������Χ����Ϣ
		m_pShowHRInterface       = NULL;
		//Ѫ����Ϣ��ʾ�ӿ�
		m_pShowSpO2ValueInterface = NULL;
		//CO2Ũ����Ϣ��ʾ�ӿ�
		m_pShowEtCO2ValueInterface = NULL;
		//�д�Ѫѹ��Ϣ��ʾ�ӿ�
		m_pShowABPValueInterface = NULL;
		//�޴�Ѫѹ��Ϣ��ʾ�ӿ�
		m_pShowNIBPValueInterface = NULL;
		//����������Ϣ��ʾ�ӿ�
		m_pShowRRInterface       = NULL;
		//ģ������塰���֡�����ʾ�����ź�
		m_pHeartStartSignInterface = NULL;
		//��Χ���£�ָ�����¡����º�Һ���¶ȣ�
		m_pShowPTempValueInterface       = NULL;
	}

	CWatchBarsShowInterfacesAggregate::~CWatchBarsShowInterfacesAggregate(void)
	{
	}

	void CWatchBarsShowInterfacesAggregate::Set_ShowHRUpdateInterfacePtr(CShowECGUpdateInterface *pEcgInterface, bool bRemove/*=FALSE*/)
	{
		if( bRemove == false )
		{
			if( m_pShowHRInterface == NULL )
			{
				m_pShowHRInterface = pEcgInterface;
			}
			else
			{
				m_pShowHRInterface->SetNextInterfacePtr( pEcgInterface );
			}
		}
		else
		{
			if( m_pShowHRInterface != NULL )
			{
				m_pShowHRInterface = (CShowECGUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowHRInterface, pEcgInterface);
			}
		}
	}

	void CWatchBarsShowInterfacesAggregate::Set_ShowSpO2ValueUpdateInterfacePtr(CShowSpO2UpdateInterface *pSpO2Interface, bool bRemove/*=FALSE*/)
	{
		if( bRemove == false )
		{
			if( m_pShowSpO2ValueInterface == NULL )
			{
				m_pShowSpO2ValueInterface = pSpO2Interface;
			}
			else
			{
				m_pShowSpO2ValueInterface->SetNextInterfacePtr( pSpO2Interface );
			}
		}
		else
		{
			if( m_pShowSpO2ValueInterface != NULL )
			{
				m_pShowSpO2ValueInterface = (CShowSpO2UpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowSpO2ValueInterface, pSpO2Interface);
			}
		}
	}

	void CWatchBarsShowInterfacesAggregate::Set_ShowEtCO2ValueUpdateInterfacePtr(CShowEtCO2UpdateInterface *pEtCO2Interface, bool bRemove/*=FALSE*/)
	{
		if( bRemove == false )
		{
			if( m_pShowEtCO2ValueInterface == NULL )
			{
				m_pShowEtCO2ValueInterface = pEtCO2Interface;
			}
			else
			{
				m_pShowEtCO2ValueInterface->SetNextInterfacePtr( pEtCO2Interface );
			}
		}
		else
		{
			if( m_pShowEtCO2ValueInterface != NULL )
			{
				m_pShowEtCO2ValueInterface = (CShowEtCO2UpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowEtCO2ValueInterface, pEtCO2Interface);
			}
		}
	}

	void CWatchBarsShowInterfacesAggregate::Set_ShowABPValueUpdateInterfacePtr(CShowABPUpdateInterface *pABPInterface, bool bRemove/*=FALSE*/)
	{
		if( bRemove == false )
		{
			if( m_pShowABPValueInterface == NULL )
			{
				m_pShowABPValueInterface = pABPInterface;
			}
			else
			{
				m_pShowABPValueInterface->SetNextInterfacePtr( pABPInterface );
			}
		}
		else
		{
			if( m_pShowABPValueInterface != NULL )
			{
				m_pShowABPValueInterface = (CShowABPUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowABPValueInterface, pABPInterface);
			}
		}
	}

	void CWatchBarsShowInterfacesAggregate::Set_ShowNIBPValueUpdateInterfacePtr(CShowNIBPUpdateInterface *pNIBPInterface, bool bRemove/*=FALSE*/)
	{
		if( bRemove == false )
		{
			if( m_pShowNIBPValueInterface == NULL )
			{
				m_pShowNIBPValueInterface = pNIBPInterface;
			}
			else
			{
				m_pShowNIBPValueInterface->SetNextInterfacePtr( pNIBPInterface );
			}
		}
		else
		{
			if( m_pShowNIBPValueInterface != NULL )
			{
				m_pShowNIBPValueInterface = (CShowNIBPUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowNIBPValueInterface, pNIBPInterface);
			}
		}
	}

	void CWatchBarsShowInterfacesAggregate::Set_ShowRespRateUpdateInterfacePtr(CShowRespRateUpdateInterface *pRRInterface, bool bRemove/*=FALSE*/)
	{
		if( bRemove == false )
		{
			if( m_pShowRRInterface == NULL )
			{
				m_pShowRRInterface = pRRInterface;
			}
			else
			{
				m_pShowRRInterface->SetNextInterfacePtr( pRRInterface );
			}
		}
		else
		{
			if( m_pShowRRInterface != NULL )
			{
				m_pShowRRInterface = (CShowRespRateUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowRRInterface, pRRInterface);
			}
		}
	}

	void CWatchBarsShowInterfacesAggregate::Set_HeartStartSignInterface(IHeartStartSign *pHeartSignInterface, bool bRemove/*=FALSE*/)
	{
		if( bRemove == false )
		{
			if( m_pHeartStartSignInterface == NULL )
			{
				m_pHeartStartSignInterface = pHeartSignInterface;
			}
			else
			{
				m_pHeartStartSignInterface->SetNextInterfacePtr( pHeartSignInterface );
			}
		}
		else
		{
			if( m_pHeartStartSignInterface != NULL )
			{
				m_pHeartStartSignInterface = (IHeartStartSign *)IBedirecteLinksVir::RemoveInterfacePtr(m_pHeartStartSignInterface, pHeartSignInterface);
			}
		}
	}

	void CWatchBarsShowInterfacesAggregate::Set_ShowPTempValueInterfacePtr(CShowTempUpdateInterface *pPTempInterface, bool bRemove/*=FALSE*/)
	{
		if( bRemove == false )
		{
			if( m_pShowPTempValueInterface == NULL )
			{
				m_pShowPTempValueInterface = pPTempInterface;
			}
			else
			{
				m_pShowPTempValueInterface->SetNextInterfacePtr( pPTempInterface );
			}
		}
		else
		{
			if( m_pShowPTempValueInterface != NULL )
			{
				m_pShowPTempValueInterface = (CShowTempUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowPTempValueInterface, pPTempInterface);
			}
		}
	}

}}
