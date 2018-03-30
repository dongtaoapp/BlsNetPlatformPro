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
		//断开显示后通知
		cutLinkEtCO2UpdateShow();
	}

	void CShowEtCO2UpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkEtCO2UpdateShow();
	}

	/*******************************************************************************/
	// 函数名称： OnShowEtCO2Value
	// 功能： 显示呼出CO2浓度
	// 参数： int nCO2Value:                CO2浓度（单位：百分百）
	// 返回值:  
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
	// 函数名称： OnShowEtCO2Range
	// 功能： 显示呼出CO2浓度正常的范围区间
	// 参数： int nMinCO2Value:              区间最小CO2浓度（单位：百分百） 
	//        int nMaxCO2Value:              区间最大CO2浓度（单位：百分百） 
	// 返回值:  
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
