#include ".\showresprateupdateinterface.h"

namespace jysoft { namespace simulator { namespace base {

	CShowRespRateUpdateInterface::CShowRespRateUpdateInterface(void)
	{
	}

	CShowRespRateUpdateInterface::~CShowRespRateUpdateInterface(void)
	{
	}

	bool CShowRespRateUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowRespRateUpdateInterface" )
			return true;
		return IUpdateShowVir::isKindOf(className);
	}

	void CShowRespRateUpdateInterface::UnLinkUpdateShow()
	{
		//断开显示后通知
		cutLinkRespRateUpdateShow();
	}

	void CShowRespRateUpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkRespRateUpdateShow();
	}

	/*******************************************************************************/
	// 函数名称： OnShowRespRate
	// 功能： 显示呼吸次数
	// 参数： int nRate:              呼吸次数（单位：次/分钟）
	// 返回值:  
	void CShowRespRateUpdateInterface::OnShowRespRate(eRespMode  enumMode, int nRate)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowRespRateUpdateInterface" ) )
			{
				CShowRespRateUpdateInterface *pShowRespInterface = (CShowRespRateUpdateInterface *)pInterface;
				pShowRespInterface->ShowRespRate( enumMode, nRate );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// 函数名称： OnShowRespRateRange
	// 功能： 显示血氧正常的范围区间
	// 参数： int nMinRate:              区间最小呼吸次数（单位：次/分钟） 
	//        int nMaxRate:              区间最大呼吸次数（单位：次/分钟） 
	// 返回值:  
	void CShowRespRateUpdateInterface::OnShowRespRateRange(int nMinRate, int nMaxRate)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowRespRateUpdateInterface" ) )
			{
				CShowRespRateUpdateInterface *pShowRespInterface = (CShowRespRateUpdateInterface *)pInterface;
				pShowRespInterface->ShowRespRateRange(nMinRate, nMaxRate);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
