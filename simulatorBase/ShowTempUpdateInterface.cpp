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
		//断开显示后通知
		cutLinkTempUpdateShow();
	}

	void CShowTempUpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkTempUpdateShow();
	}

	/*******************************************************************************/
	// 函数名称： OnShowTempValue
	// 功能： 显示的数值
	// 参数： int nSpO2Value:              值
	// 返回值:  
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
	// 函数名称： OnShowTempRange
	// 功能： 显示正常的范围区间
	// 参数： float fMinValue:              区间最小值
	//        float fMaxValue:              区间最大值
	// 返回值:  
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
