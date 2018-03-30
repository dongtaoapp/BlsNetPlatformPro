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
		//�Ͽ���ʾ��֪ͨ
		cutLinkFrameTimeUpdateShow();
	}

	void CShowFrameTimeUpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkFrameTimeUpdateShow();
	}

	//��ʾ��ǰ���г�����ʱ��
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
