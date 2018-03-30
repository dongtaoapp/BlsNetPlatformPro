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
		//断开显示后通知
		cutLinkCPRDetailActUpdateShow();
	}

	void CShowCPRActUpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkCPRDetailActUpdateShow();
	}

	//仰头、平躺
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

	//人工呼吸开始\结束(TRUE:开始；FALSE:结束)
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

	//按压开始\结束(TRUE:开始；FALSE:结束)
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

	//完成五个循环的CPR
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

	//结束CPR操作
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
