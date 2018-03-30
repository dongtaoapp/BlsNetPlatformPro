#include ".\showscenarioruntimeupdateinterface.h"

namespace jysoft { namespace simulator { namespace base {

	CShowScenarioRunTimeUpdateInterface::CShowScenarioRunTimeUpdateInterface(void)
	{
	}

	CShowScenarioRunTimeUpdateInterface::~CShowScenarioRunTimeUpdateInterface(void)
	{
	}

	bool CShowScenarioRunTimeUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowScenarioRunTimeUpdateInterface" )
		{
			return true;
		}
		return IUpdateShowVir::isKindOf( className );
	}

	void CShowScenarioRunTimeUpdateInterface::UnLinkUpdateShow()
	{
		//断开显示后通知
		cutLinkScenarioRunTimeUpdateShow();
	}

	void CShowScenarioRunTimeUpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkScenarioRunTimeUpdateShow();
	}

	//显示当前脚本运行时间
    void CShowScenarioRunTimeUpdateInterface::OnShowScenarioRunTimeUpdate(unsigned long  uScenarioTime)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowScenarioRunTimeUpdateInterface" ) )
			{
				CShowScenarioRunTimeUpdateInterface *pShowScenarioRunTimeInterface = (CShowScenarioRunTimeUpdateInterface *)pInterface;
				pShowScenarioRunTimeInterface->ShowScenarioRunTimeUpdate( uScenarioTime );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
