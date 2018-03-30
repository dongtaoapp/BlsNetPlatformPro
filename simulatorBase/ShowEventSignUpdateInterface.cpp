#include ".\showeventsignupdateinterface.h"


namespace jysoft { namespace simulator { namespace base {

	CShowEventSignUpdateInterface::CShowEventSignUpdateInterface(void)
	{
	}

	CShowEventSignUpdateInterface::~CShowEventSignUpdateInterface(void)
	{
	}

	bool CShowEventSignUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowEventSignUpdateInterface" )
		{
			return true;
		}
		return IUpdateShowVir::isKindOf( className );
	}

	void CShowEventSignUpdateInterface::UnLinkUpdateShow()
	{
		//断开显示后通知
		cutLinkEventSignUpdateShow();
	}

	void CShowEventSignUpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkEventSignUpdateShow();
	}

	// 添加新的标志
	void CShowEventSignUpdateInterface::OnAddNewEventSign(eEventSign eSign)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowEventSignUpdateInterface" ) )
			{
				CShowEventSignUpdateInterface *pEventSignInterface = (CShowEventSignUpdateInterface *)pInterface;
				pEventSignInterface->AddNewEventSign( eSign );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	// 移除标志
	void CShowEventSignUpdateInterface::OnRemoveEventSign(eEventSign eSign)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowEventSignUpdateInterface" ) )
			{
				CShowEventSignUpdateInterface *pEventSignInterface = (CShowEventSignUpdateInterface *)pInterface;
				pEventSignInterface->RemoveEventSign( eSign );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	//默认设置
	void CShowEventSignUpdateInterface::OnDefaultHandle(void)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowEventSignUpdateInterface" ) )
			{
				CShowEventSignUpdateInterface *pEventSignInterface = (CShowEventSignUpdateInterface *)pInterface;
				pEventSignInterface->DefaultHandle();
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	// 除颤侦测事件
	void CShowEventSignUpdateInterface::OnSimulateDefibrTriggerEventUpdateShow( short sEnergy /*=-1*/ )
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowEventSignUpdateInterface" ) )
			{
				CShowEventSignUpdateInterface *pEventSignInterface = (CShowEventSignUpdateInterface *)pInterface;
				pEventSignInterface->SimulateDefibrTriggerEventUpdateShow( sEnergy );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	// CPR侦测事件
	void CShowEventSignUpdateInterface::OnSimulateCPRTriggerEventUpdateShow()
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowEventSignUpdateInterface" ) )
			{
				CShowEventSignUpdateInterface *pEventSignInterface = (CShowEventSignUpdateInterface *)pInterface;
				pEventSignInterface->SimulateCPRTriggerEventUpdateShow( );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	// 起搏侦测事件
	void CShowEventSignUpdateInterface::OnSimulatePaceTriggerEventUpdateShow( short sHeartRate )
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowEventSignUpdateInterface" ) )
			{
				CShowEventSignUpdateInterface *pEventSignInterface = (CShowEventSignUpdateInterface *)pInterface;
				pEventSignInterface->SimulatePaceTriggerEventUpdateShow( sHeartRate );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	// 气管插管事件
	void CShowEventSignUpdateInterface::OnSimulateIntubateTriggerEventUpdateShow( short sPosition )
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowEventSignUpdateInterface" ) )
			{
				CShowEventSignUpdateInterface *pEventSignInterface = (CShowEventSignUpdateInterface *)pInterface;
				pEventSignInterface->SimulateIntubateTriggerEventUpdateShow( sPosition );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	// 脉搏检查事件
	void CShowEventSignUpdateInterface::OnSimulatePulseCheckTriggerEventUpdateShow( short sPosition /*=0*/ )
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowEventSignUpdateInterface" ) )
			{
				CShowEventSignUpdateInterface *pEventSignInterface = (CShowEventSignUpdateInterface *)pInterface;
				pEventSignInterface->SimulatePulseCheckTriggerEventUpdateShow( sPosition );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
