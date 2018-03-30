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
		//断开显示后通知
		cutLinkSpO2UpdateShow();
	}

	void CShowSpO2UpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkSpO2UpdateShow();
	}

	/*******************************************************************************/
	// 函数名称： OnShowSpO2Value
	// 功能： 显示血氧的数值
	// 参数： int nSpO2Value:              血氧值（单位：百分比） 
	// 返回值:  
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
	// 函数名称： OnShowSpO2Range
	// 功能： 显示血氧正常的范围区间
	// 参数： int nMinValue:              区间最小血氧值（单位：百分比） 
	//        int nMaxValue:              区间最大血氧值（单位：百分比） 
	// 返回值:  
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
