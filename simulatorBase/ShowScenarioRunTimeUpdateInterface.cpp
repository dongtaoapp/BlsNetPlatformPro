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
		//�Ͽ���ʾ��֪ͨ
		cutLinkScenarioRunTimeUpdateShow();
	}

	void CShowScenarioRunTimeUpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkScenarioRunTimeUpdateShow();
	}

	//��ʾ��ǰ�ű�����ʱ��
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
