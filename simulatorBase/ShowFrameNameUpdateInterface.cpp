#include ".\showframenameupdateinterface.h"

namespace jysoft { namespace simulator { namespace base {

	CShowFrameNameUpdateInterface::CShowFrameNameUpdateInterface(void)
	{
	}

	CShowFrameNameUpdateInterface::~CShowFrameNameUpdateInterface(void)
	{
	}

	bool CShowFrameNameUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowFrameNameUpdateInterface" )
		{
			return true;
		}
		return IUpdateShowVir::isKindOf( className );
	}

	void CShowFrameNameUpdateInterface::UnLinkUpdateShow()
	{
		//断开显示后通知
		cutLinkFrameNameUpdateShow();
	}

	void CShowFrameNameUpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkFrameNameUpdateShow();
	}

	//显示当前运行场景的名称
	void CShowFrameNameUpdateInterface::OnShowFrameNameUpdate(unsigned long dwFrameId)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowFrameNameUpdateInterface" ) )
			{
				CShowFrameNameUpdateInterface *pShowFrameNameInterface = (CShowFrameNameUpdateInterface *)pInterface;
				pShowFrameNameInterface->ShowFrameNameUpdate( dwFrameId );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
