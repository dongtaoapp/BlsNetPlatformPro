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
		//�Ͽ���ʾ��֪ͨ
		cutLinkEventSignUpdateShow();
	}

	void CShowEventSignUpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkEventSignUpdateShow();
	}

	// ����µı�־
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

	// �Ƴ���־
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

	//Ĭ������
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

	// ��������¼�
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

	// CPR����¼�
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

	// ������¼�
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

	// ���ܲ���¼�
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

	// ��������¼�
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
