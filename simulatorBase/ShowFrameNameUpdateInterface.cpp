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
		//�Ͽ���ʾ��֪ͨ
		cutLinkFrameNameUpdateShow();
	}

	void CShowFrameNameUpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkFrameNameUpdateShow();
	}

	//��ʾ��ǰ���г���������
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
