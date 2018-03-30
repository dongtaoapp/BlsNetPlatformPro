#include ".\ShowCPRActUpdateInterface.h"


namespace jysoft{  namespace cpr {

	CShowCPRActUpdateInterface::CShowCPRActUpdateInterface(void)
	{
	}
	
	CShowCPRActUpdateInterface::~CShowCPRActUpdateInterface(void)
	{
	}

	bool CShowCPRActUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowCPRActUpdateInterface" )
		{
			return true;
		}
		return IUpdateShowVir::isKindOf( className );
	}

	void CShowCPRActUpdateInterface::UnLinkUpdateShow()
	{
		//�Ͽ���ʾ��֪ͨ
		cutLinkCPRDetailActUpdateShow();
	}

	void CShowCPRActUpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkCPRDetailActUpdateShow();
	}

	//��ͷ��ƽ��
	void CShowCPRActUpdateInterface::OnRaiseJowAct(bool bLookUp)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf("CShowCPRActUpdateInterface") )
			{
				CShowCPRActUpdateInterface *pShowCPRDetailActInterface = (CShowCPRActUpdateInterface *)pInterface;
				pShowCPRDetailActInterface->RaiseJowAct( bLookUp );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	//�˹�������ʼ\����(TRUE:��ʼ��FALSE:����)
	void CShowCPRActUpdateInterface::OnBreathStateAct(bool bState)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf("CShowCPRActUpdateInterface") )
			{
				CShowCPRActUpdateInterface *pShowCPRDetailActInterface = (CShowCPRActUpdateInterface *)pInterface;
				pShowCPRDetailActInterface->BreathStateAct( bState );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	//��ѹ��ʼ\����(TRUE:��ʼ��FALSE:����)
	void CShowCPRActUpdateInterface::OnPressureStateAct(bool bState)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf("CShowCPRActUpdateInterface") )
			{
				CShowCPRActUpdateInterface *pShowCPRDetailActInterface = (CShowCPRActUpdateInterface *)pInterface;
				pShowCPRDetailActInterface->PressureStateAct( bState );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	//������ѭ����CPR
	void CShowCPRActUpdateInterface::OnFiveCycleCompleteAct()
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf("CShowCPRActUpdateInterface") )
			{
				CShowCPRActUpdateInterface *pShowCPRDetailActInterface = (CShowCPRActUpdateInterface *)pInterface;
				pShowCPRDetailActInterface->FiveCycleCompleteAct( );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	//����CPR����
	void CShowCPRActUpdateInterface::OnFinishCPROperator(bool bSecceed)
	{	
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf("CShowCPRActUpdateInterface") )
			{
				CShowCPRActUpdateInterface *pShowCPRDetailActInterface = (CShowCPRActUpdateInterface *)pInterface;
				pShowCPRDetailActInterface->FinishCPROperator( bSecceed );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}
