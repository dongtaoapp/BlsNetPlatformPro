#include ".\showpatienttimeupdateinterface.h"

namespace jysoft { namespace simulator { namespace base {

	CShowPatientTimeUpdateInterface::CShowPatientTimeUpdateInterface(void)
	{
	}

	CShowPatientTimeUpdateInterface::~CShowPatientTimeUpdateInterface(void)
	{
	}

	bool CShowPatientTimeUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowPatientTimeUpdateInterface" )
		{
			return true;
		}
		return IUpdateShowVir::isKindOf( className );
	}

	void CShowPatientTimeUpdateInterface::UnLinkUpdateShow()
	{
		//�Ͽ���ʾ��֪ͨ
		cutLinkPatientTimeUpdateShow();
	}

	void CShowPatientTimeUpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkPatientTimeUpdateShow();
	}

	//��ʾ��ǰ���˵�ʱ��
	void CShowPatientTimeUpdateInterface::OnShowPatientTimeUpdate(long  lPatientTime)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowPatientTimeUpdateInterface" ) )
			{
				CShowPatientTimeUpdateInterface *pShowPatientTimeInterface = (CShowPatientTimeUpdateInterface *)pInterface;
				pShowPatientTimeInterface->ShowPatientTimeUpdate( lPatientTime );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
