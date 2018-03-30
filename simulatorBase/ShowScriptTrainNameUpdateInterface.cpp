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
		//�Ͽ���ʾ��֪ͨ
		cutLinkScriptNameUpdateShow();
	}

	void CShowScriptTrainNameUpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkScriptNameUpdateShow();
	}

	//��ʾ��ѵ�ű�����
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
