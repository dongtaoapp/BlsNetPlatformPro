#include ".\showframetimeupdateinterface.h"

namespace jysoft { namespace simulator { namespace base {

	CShowFrameTimeUpdateInterface::CShowFrameTimeUpdateInterface(void)
	{
	}

	CShowFrameTimeUpdateInterface::~CShowFrameTimeUpdateInterface(void)
	{
	}

	bool CShowFrameTimeUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowFrameTimeUpdateInterface" )
		{
			return true;
		}
		return IUpdateShowVir::isKindOf( className );
	}

	void CShowFrameTimeUpdateInterface::UnLinkUpdateShow()
	{
		//断开显示后通知
		cutLinkFrameTimeUpdateShow();
	}

	void CShowFrameTimeUpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkFrameTimeUpdateShow();
	}

	//显示当前运行场景的时间
	void CShowFrameTimeUpdateInterface::OnShowFrameTimeUpdate(long  lFrameTime)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowFrameTimeUpdateInterface" ) )
			{
				CShowFrameTimeUpdateInterface *pShowFrameTimeInterface = (CShowFrameTimeUpdateInterface *)pInterface;
				pShowFrameTimeInterface->ShowFrameTimeUpdate( lFrameTime );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
