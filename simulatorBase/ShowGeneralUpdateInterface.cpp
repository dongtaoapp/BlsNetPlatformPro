#include ".\showgeneralupdateinterface.h"

namespace jysoft { namespace simulator { namespace base {

	CShowGeneralUpdateInterface::CShowGeneralUpdateInterface(void)
	{
	}

	CShowGeneralUpdateInterface::~CShowGeneralUpdateInterface(void)
	{
	}

	bool CShowGeneralUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowGeneralUpdateInterface" )
		{
			return true;
		}
		return IUpdateShowVir::isKindOf( className );
	}

	void CShowGeneralUpdateInterface::UnLinkUpdateShow()
	{
		//�Ͽ���ʾ��֪ͨ
		cutLinkGeneralUpdateShow();
	}

	void CShowGeneralUpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkGeneralUpdateShow();
	}

	/*******************************************************************************/
	// �������ƣ� OnShowPhystValue
	// ���ܣ� ��ʾ����ֵ
	// ������ float nPhystValue:              ֵ
	// ����ֵ:  
	void CShowGeneralUpdateInterface::OnShowPhystValue(float nPhystValue)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowGeneralUpdateInterface" ) )
			{
				CShowGeneralUpdateInterface *pShowInterface = (CShowGeneralUpdateInterface *)pInterface;
				pShowInterface->ShowPhystValue( nPhystValue );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}
	/*******************************************************************************/
	// �������ƣ� OnShowPhystRange
	// ���ܣ� ��ʾ�����ķ�Χ����
	// ������ float fMinValue:              ������Сֵ
	//        float fMaxValue:              �������ֵ
	// ����ֵ:  
	void CShowGeneralUpdateInterface::OnShowPhystRange(float fMinValue, float fMaxValue)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowGeneralUpdateInterface" ) )
			{
				CShowGeneralUpdateInterface *pShowInterface = (CShowGeneralUpdateInterface *)pInterface;
				pShowInterface->ShowPhystRange(fMinValue, fMaxValue);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
