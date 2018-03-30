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
		//断开显示后通知
		cutLinkGeneralUpdateShow();
	}

	void CShowGeneralUpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkGeneralUpdateShow();
	}

	/*******************************************************************************/
	// 函数名称： OnShowPhystValue
	// 功能： 显示的数值
	// 参数： float nPhystValue:              值
	// 返回值:  
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
	// 函数名称： OnShowPhystRange
	// 功能： 显示正常的范围区间
	// 参数： float fMinValue:              区间最小值
	//        float fMaxValue:              区间最大值
	// 返回值:  
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
