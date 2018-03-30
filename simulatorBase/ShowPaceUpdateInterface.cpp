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
		//�Ͽ���ʾ��֪ͨ
		cutLinkPacesetUpdateShow();
	}

	void CShowPaceUpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkPacesetUpdateShow();
	}

	/*******************************************************************************/
	// �������ƣ� OnShowPaceset
	// ���ܣ�   �����𲫵�����
	// ������   
	//          BOOL bEnablePace:  �Ƿ�����
	//          short sElectric:   ������
	// ����ֵ:
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
