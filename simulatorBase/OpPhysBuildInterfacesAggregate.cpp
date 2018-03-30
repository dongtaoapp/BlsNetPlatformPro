#include ".\opphysbuildinterfacesaggregate.h"
#include ".\WatchBarsShowInterfacesAggregate.h"

using namespace jysoft::simulator::base;

namespace jysoft { namespace simulator {

	COpPhysBuildInterfacesAggregate::COpPhysBuildInterfacesAggregate(void)
	{
		m_pOpECGBuildInterface    =  NULL;
		m_pOpSpO2BuildInterface   =  NULL;
		m_pEtCO2BuildInterface    =  NULL;
		m_pRespBuildInterface     =  NULL;
		m_pABPBuildInterface      =  NULL;
	}

	COpPhysBuildInterfacesAggregate::~COpPhysBuildInterfacesAggregate(void)
	{
	
	}

	/*******************************************************************************/
	// 函数名称： StartLinkWatchBarsShowInterfaces
	// 功能： 初始连接模拟监控面板的显示接口
	// 参数： CWatchBarsShowInterfacesAggregate *pShowAggregate:        
	// 返回值:  
	void COpPhysBuildInterfacesAggregate::StartLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		//返回心电图信息显示接口
		m_pOpECGBuildInterface->SetRelateECGShowInterface( pShowAggregate->Get_ShowHRUpdateInterfacePtr() );
		//血氧信息显示接口
		m_pOpSpO2BuildInterface->SetRelateSpO2ShowInterface( pShowAggregate->Get_ShowSpO2ValueUpdateInterfacePtr() );
		//呼吸次数信息显示接口
		CShowRespRateUpdateInterface *pShowRespRateInterface  = pShowAggregate->Get_ShowRespRateUpdateInterfacePtr();
		m_pRespBuildInterface->SetRelateRespRateShowInterface( pShowRespRateInterface );
		//etCO2浓度信息显示接口
		CShowEtCO2UpdateInterface *pShowEtCO2Interface = pShowAggregate->Get_ShowEtCO2ValueUpdateInterfacePtr();
		m_pEtCO2BuildInterface->SetRelateEtCO2ShowInterface( pShowEtCO2Interface );
		//....
		m_pABPBuildInterface->SetRelateABPShowInterface( pShowAggregate->Get_ShowABPValueUpdateInterfacePtr() );

	}

	/*******************************************************************************/
	// 函数名称： UnLinkWatchBarsShowInterfaces
	// 功能： 断开模拟监控面板的显示接口
	// 参数： CWatchBarsShowInterfacesAggregate *pShowAggregate:        
	// 返回值:  
	void COpPhysBuildInterfacesAggregate::UnLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		//返回心电图信息显示接口
		CShowECGUpdateInterface *pShowHRInterface = pShowAggregate->Get_ShowHRUpdateInterfacePtr();
		if( pShowHRInterface != NULL )
		{
			m_pOpECGBuildInterface->RemoveRelateECGShowInterface( pShowHRInterface );
			pShowHRInterface->UnLinkUpdateShow();
		}
		//血氧信息显示接口
		CShowSpO2UpdateInterface *pShowSpO2Interface  = pShowAggregate->Get_ShowSpO2ValueUpdateInterfacePtr();
		if( pShowSpO2Interface != NULL )
		{
			m_pOpSpO2BuildInterface->RemoveRelateSpO2ShowInterface( pShowSpO2Interface );
			pShowSpO2Interface->UnLinkUpdateShow();
		}
		//ABP信息显示接口
		CShowABPUpdateInterface *pShowABPInterface  = pShowAggregate->Get_ShowABPValueUpdateInterfacePtr();
		if( pShowABPInterface != NULL )
		{
			m_pABPBuildInterface->RemoveRelateABPShowInterface( pShowABPInterface );
			pShowABPInterface->UnLinkUpdateShow();
		}
		//呼吸次数信息显示接口
		CShowRespRateUpdateInterface *pShowRespRateInterface  = pShowAggregate->Get_ShowRespRateUpdateInterfacePtr();
		if( pShowRespRateInterface != NULL )
		{
			m_pRespBuildInterface->RemoveRelateRespRateShowInterface( pShowRespRateInterface );
			pShowRespRateInterface->UnLinkUpdateShow();
		}
		//etCO2浓度信息显示接口
		CShowEtCO2UpdateInterface *pShowEtCO2Interface  = pShowAggregate->Get_ShowEtCO2ValueUpdateInterfacePtr();
		if( pShowEtCO2Interface != NULL )
		{
			m_pEtCO2BuildInterface->RemoveRelateEtCO2ShowInterface( pShowEtCO2Interface );
			pShowEtCO2Interface->UnLinkUpdateShow();
		}
	}

}}
