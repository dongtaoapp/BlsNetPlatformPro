#include ".\showetco2updateinterface.h"


namespace jysoft { namespace simulator { namespace base {

	CShowEtCO2UpdateInterface::CShowEtCO2UpdateInterface(void)
	{
	}

	CShowEtCO2UpdateInterface::~CShowEtCO2UpdateInterface(void)
	{
	}

	bool CShowEtCO2UpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowEtCO2UpdateInterface" )
			return true;
		return IUpdateShowVir::isKindOf(className);
	}

	void CShowEtCO2UpdateInterface::UnLinkUpdateShow()
	{
		//�Ͽ���ʾ��֪ͨ
		cutLinkEtCO2UpdateShow();
	}

	void CShowEtCO2UpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkEtCO2UpdateShow();
	}

	/*******************************************************************************/
	// �������ƣ� OnShowEtCO2Value
	// ���ܣ� ��ʾ����CO2Ũ��
	// ������ int nCO2Value:                CO2Ũ�ȣ���λ���ٷְ٣�
	// ����ֵ:  
	void CShowEtCO2UpdateInterface::OnShowEtCO2Value(int nCO2Value)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowEtCO2UpdateInterface" ) )
			{
				CShowEtCO2UpdateInterface *pShowEtCO2Interface = (CShowEtCO2UpdateInterface *)pInterface;
				pShowEtCO2Interface->ShowEtCO2Value( nCO2Value );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}
	/*******************************************************************************/
	// �������ƣ� OnShowEtCO2Range
	// ���ܣ� ��ʾ����CO2Ũ�������ķ�Χ����
	// ������ int nMinCO2Value:              ������СCO2Ũ�ȣ���λ���ٷְ٣� 
	//        int nMaxCO2Value:              �������CO2Ũ�ȣ���λ���ٷְ٣� 
	// ����ֵ:  
	void CShowEtCO2UpdateInterface::OnShowEtCO2Range(int nMinCO2Value, int nMaxCO2Value)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowEtCO2UpdateInterface" ) )
			{
				CShowEtCO2UpdateInterface *pShowEtCO2Interface = (CShowEtCO2UpdateInterface *)pInterface;
				pShowEtCO2Interface->ShowEtCO2Range(nMinCO2Value, nMaxCO2Value);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
