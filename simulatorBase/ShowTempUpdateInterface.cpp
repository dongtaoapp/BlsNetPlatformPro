#include ".\showtempupdateinterface.h"

namespace jysoft { namespace simulator { namespace base {

	CShowTempUpdateInterface::CShowTempUpdateInterface(void)
	{
	}

	CShowTempUpdateInterface::~CShowTempUpdateInterface(void)
	{
	}


	bool CShowTempUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowTempUpdateInterface" )
		{
			return true;
		}
		return IUpdateShowVir::isKindOf( className );
	}

	void CShowTempUpdateInterface::UnLinkUpdateShow()
	{
		//�Ͽ���ʾ��֪ͨ
		cutLinkTempUpdateShow();
	}

	void CShowTempUpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkTempUpdateShow();
	}

	/*******************************************************************************/
	// �������ƣ� OnShowTempValue
	// ���ܣ� ��ʾ����ֵ
	// ������ int nSpO2Value:              ֵ
	// ����ֵ:  
	void CShowTempUpdateInterface::OnShowTempValue(float fValue)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowTempUpdateInterface" ) )
			{
				CShowTempUpdateInterface *pShowInterface = (CShowTempUpdateInterface *)pInterface;
				pShowInterface->ShowTempValue( fValue );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnShowTempRange
	// ���ܣ� ��ʾ�����ķ�Χ����
	// ������ float fMinValue:              ������Сֵ
	//        float fMaxValue:              �������ֵ
	// ����ֵ:  
	void CShowTempUpdateInterface::OnShowTempRange(float fMinValue, float fMaxValue)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowTempUpdateInterface" ) )
			{
				CShowTempUpdateInterface *pShowInterface = (CShowTempUpdateInterface *)pInterface;
				pShowInterface->ShowTempRange( fMinValue, fMaxValue );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
