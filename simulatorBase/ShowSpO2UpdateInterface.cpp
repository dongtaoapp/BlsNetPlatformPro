#include ".\showspo2updateinterface.h"


namespace jysoft { namespace simulator { namespace base {

	CShowSpO2UpdateInterface::CShowSpO2UpdateInterface(void)
	{
	}

	CShowSpO2UpdateInterface::~CShowSpO2UpdateInterface(void)
	{
	}

	bool CShowSpO2UpdateInterface::isKindOf(const std::string &className)
	{
		if(className == "CShowSpO2UpdateInterface" )
		{
			return true;
		}
		return IUpdateShowVir::isKindOf(className);
	}

	void CShowSpO2UpdateInterface::UnLinkUpdateShow()
	{
		//�Ͽ���ʾ��֪ͨ
		cutLinkSpO2UpdateShow();
	}

	void CShowSpO2UpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkSpO2UpdateShow();
	}

	/*******************************************************************************/
	// �������ƣ� OnShowSpO2Value
	// ���ܣ� ��ʾѪ������ֵ
	// ������ int nSpO2Value:              Ѫ��ֵ����λ���ٷֱȣ� 
	// ����ֵ:  
	void CShowSpO2UpdateInterface::OnShowSpO2Value(int nSpO2Value)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowSpO2UpdateInterface" ) )
			{
				CShowSpO2UpdateInterface *pShowSpO2Interface = (CShowSpO2UpdateInterface *)pInterface;
				pShowSpO2Interface->ShowSpO2Value( nSpO2Value );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnShowSpO2Range
	// ���ܣ� ��ʾѪ�������ķ�Χ����
	// ������ int nMinValue:              ������СѪ��ֵ����λ���ٷֱȣ� 
	//        int nMaxValue:              �������Ѫ��ֵ����λ���ٷֱȣ� 
	// ����ֵ:  
	void CShowSpO2UpdateInterface::OnShowSpO2Range(int nMinValue, int nMaxValue)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowSpO2UpdateInterface" ) )
			{
				CShowSpO2UpdateInterface *pShowSpO2Interface = (CShowSpO2UpdateInterface *)pInterface;
				pShowSpO2Interface->ShowSpO2Range(nMinValue, nMaxValue);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
