#include ".\showscripttrainnameupdateinterface.h"

namespace jysoft { namespace simulator { namespace base {

	CShowScriptTrainNameUpdateInterface::CShowScriptTrainNameUpdateInterface(void)
	{
	}

	CShowScriptTrainNameUpdateInterface::~CShowScriptTrainNameUpdateInterface(void)
	{
	}

	bool CShowScriptTrainNameUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowScriptTrainNameUpdateInterface" )
		{
			return true;
		}
		return IUpdateShowVir::isKindOf( className );
	}

	void CShowScriptTrainNameUpdateInterface::UnLinkUpdateShow()
	{
		//断开显示后通知
		cutLinkScriptNameUpdateShow();
	}

	void CShowScriptTrainNameUpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkScriptNameUpdateShow();
	}

	//显示培训脚本名称
	void CShowScriptTrainNameUpdateInterface::OnShowScriptTrainNameUpdate(const std::string &strScriptName)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowScriptTrainNameUpdateInterface" ) )
			{
				CShowScriptTrainNameUpdateInterface *pShowScriptNameInterface = (CShowScriptTrainNameUpdateInterface *)pInterface;
				pShowScriptNameInterface->ShowScriptTrainNameUpdate( strScriptName );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
