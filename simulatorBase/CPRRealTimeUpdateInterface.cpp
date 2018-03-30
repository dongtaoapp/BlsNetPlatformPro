#include "CPRRealTimeUpdateInterface.h"

namespace jysoft{  namespace cpr {

	CCPRRealTimeUpdateInterface::CCPRRealTimeUpdateInterface(void)
	{
	}

	CCPRRealTimeUpdateInterface::~CCPRRealTimeUpdateInterface(void)
	{
	}

	bool CCPRRealTimeUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CCPRRealTimeUpdateInterface" )
		{
			return true;
		}
		return IUpdateShowVir::isKindOf( className );
	}

	void CCPRRealTimeUpdateInterface::UnLinkUpdateShow()
	{
		//断开显示后通知
		cutLinkCPRRealTimeUpdateShow();
	}

	void CCPRRealTimeUpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkCPRRealTimeUpdateShow();
	}

	//得到CPR的数据
	void CCPRRealTimeUpdateInterface::OnLoadCPRSample(const _CPRData *ptrCPRDatas, int nLength)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf("CCPRRealTimeUpdateInterface") )
			{
				CCPRRealTimeUpdateInterface *pShowCPRInterface = (CCPRRealTimeUpdateInterface *)pInterface;
				pShowCPRInterface->LoadCPRSample( ptrCPRDatas, nLength );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	// 加入错误标志
	void CCPRRealTimeUpdateInterface::OnAddCPRErrorSign(_eCPRErrorSign eErrorSign)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CCPRRealTimeUpdateInterface" ) )
			{
				CCPRRealTimeUpdateInterface *pShowCPRInterface = (CCPRRealTimeUpdateInterface *)pInterface;
				pShowCPRInterface->AddCPRErrorSign( eErrorSign );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}
}}
