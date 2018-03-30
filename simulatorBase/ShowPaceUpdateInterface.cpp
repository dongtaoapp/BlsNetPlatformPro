#include ".\showpaceupdateinterface.h"


namespace jysoft { namespace simulator { namespace base {

	CShowPaceUpdateInterface::CShowPaceUpdateInterface(void)
	{
	}

	CShowPaceUpdateInterface::~CShowPaceUpdateInterface(void)
	{
	}

	bool CShowPaceUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowPaceUpdateInterface" )
		{
			return true;
		}
		return IUpdateShowVir::isKindOf( className );
	}

	void CShowPaceUpdateInterface::UnLinkUpdateShow()
	{
		//断开显示后通知
		cutLinkPacesetUpdateShow();
	}

	void CShowPaceUpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkPacesetUpdateShow();
	}

	/*******************************************************************************/
	// 函数名称： OnShowPaceset
	// 功能：   更新起搏的设置
	// 参数：   
	//          BOOL bEnablePace:  是否能起搏
	//          short sElectric:   电流量
	// 返回值:
    void CShowPaceUpdateInterface::OnShowPaceset(bool bEnablePace, short sElectric)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowPaceUpdateInterface" ) )
			{
				CShowPaceUpdateInterface *pShowPacesetInterface = (CShowPaceUpdateInterface *)pInterface;
				pShowPacesetInterface->ShowPaceset( bEnablePace, sElectric );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
