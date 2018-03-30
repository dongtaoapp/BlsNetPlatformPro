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
		//断开显示后通知
		cutLinkPatientTimeUpdateShow();
	}

	void CShowPatientTimeUpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkPatientTimeUpdateShow();
	}

	//显示当前病人的时间
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
