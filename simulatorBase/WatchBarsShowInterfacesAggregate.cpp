#include ".\watchbarsshowinterfacesaggregate.h"


namespace jysoft { namespace simulator {

	using namespace base;

	CWatchBarsShowInterfacesAggregate::CWatchBarsShowInterfacesAggregate(void)
	{
		//心电图信息显示接口，包括心律名称、心率次数、心率正常范围等信息
		m_pShowHRInterface       = NULL;
		//血氧信息显示接口
		m_pShowSpO2ValueInterface = NULL;
		//CO2浓度信息显示接口
		m_pShowEtCO2ValueInterface = NULL;
		//有创血压信息显示接口
		m_pShowABPValueInterface = NULL;
		//无创血压信息显示接口
		m_pShowNIBPValueInterface = NULL;
		//呼吸次数信息显示接口
		m_pShowRRInterface       = NULL;
		//模拟监控面板“嘀嘀”音提示启动信号
		m_pHeartStartSignInterface = NULL;
		//外围体温（指：舌下、肛温和液下温度）
		m_pShowPTempValueInterface       = NULL;
	}

	CWatchBarsShowInterfacesAggregate::~CWatchBarsShowInterfacesAggregate(void)
	{
	}

	void CWatchBarsShowInterfacesAggregate::Set_ShowHRUpdateInterfacePtr(CShowECGUpdateInterface *pEcgInterface, bool bRemove/*=FALSE*/)
	{
		if( bRemove == false )
		{
			if( m_pShowHRInterface == NULL )
			{
				m_pShowHRInterface = pEcgInterface;
			}
			else
			{
				m_pShowHRInterface->SetNextInterfacePtr( pEcgInterface );
			}
		}
		else
		{
			if( m_pShowHRInterface != NULL )
			{
				m_pShowHRInterface = (CShowECGUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowHRInterface, pEcgInterface);
			}
		}
	}

	void CWatchBarsShowInterfacesAggregate::Set_ShowSpO2ValueUpdateInterfacePtr(CShowSpO2UpdateInterface *pSpO2Interface, bool bRemove/*=FALSE*/)
	{
		if( bRemove == false )
		{
			if( m_pShowSpO2ValueInterface == NULL )
			{
				m_pShowSpO2ValueInterface = pSpO2Interface;
			}
			else
			{
				m_pShowSpO2ValueInterface->SetNextInterfacePtr( pSpO2Interface );
			}
		}
		else
		{
			if( m_pShowSpO2ValueInterface != NULL )
			{
				m_pShowSpO2ValueInterface = (CShowSpO2UpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowSpO2ValueInterface, pSpO2Interface);
			}
		}
	}

	void CWatchBarsShowInterfacesAggregate::Set_ShowEtCO2ValueUpdateInterfacePtr(CShowEtCO2UpdateInterface *pEtCO2Interface, bool bRemove/*=FALSE*/)
	{
		if( bRemove == false )
		{
			if( m_pShowEtCO2ValueInterface == NULL )
			{
				m_pShowEtCO2ValueInterface = pEtCO2Interface;
			}
			else
			{
				m_pShowEtCO2ValueInterface->SetNextInterfacePtr( pEtCO2Interface );
			}
		}
		else
		{
			if( m_pShowEtCO2ValueInterface != NULL )
			{
				m_pShowEtCO2ValueInterface = (CShowEtCO2UpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowEtCO2ValueInterface, pEtCO2Interface);
			}
		}
	}

	void CWatchBarsShowInterfacesAggregate::Set_ShowABPValueUpdateInterfacePtr(CShowABPUpdateInterface *pABPInterface, bool bRemove/*=FALSE*/)
	{
		if( bRemove == false )
		{
			if( m_pShowABPValueInterface == NULL )
			{
				m_pShowABPValueInterface = pABPInterface;
			}
			else
			{
				m_pShowABPValueInterface->SetNextInterfacePtr( pABPInterface );
			}
		}
		else
		{
			if( m_pShowABPValueInterface != NULL )
			{
				m_pShowABPValueInterface = (CShowABPUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowABPValueInterface, pABPInterface);
			}
		}
	}

	void CWatchBarsShowInterfacesAggregate::Set_ShowNIBPValueUpdateInterfacePtr(CShowNIBPUpdateInterface *pNIBPInterface, bool bRemove/*=FALSE*/)
	{
		if( bRemove == false )
		{
			if( m_pShowNIBPValueInterface == NULL )
			{
				m_pShowNIBPValueInterface = pNIBPInterface;
			}
			else
			{
				m_pShowNIBPValueInterface->SetNextInterfacePtr( pNIBPInterface );
			}
		}
		else
		{
			if( m_pShowNIBPValueInterface != NULL )
			{
				m_pShowNIBPValueInterface = (CShowNIBPUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowNIBPValueInterface, pNIBPInterface);
			}
		}
	}

	void CWatchBarsShowInterfacesAggregate::Set_ShowRespRateUpdateInterfacePtr(CShowRespRateUpdateInterface *pRRInterface, bool bRemove/*=FALSE*/)
	{
		if( bRemove == false )
		{
			if( m_pShowRRInterface == NULL )
			{
				m_pShowRRInterface = pRRInterface;
			}
			else
			{
				m_pShowRRInterface->SetNextInterfacePtr( pRRInterface );
			}
		}
		else
		{
			if( m_pShowRRInterface != NULL )
			{
				m_pShowRRInterface = (CShowRespRateUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowRRInterface, pRRInterface);
			}
		}
	}

	void CWatchBarsShowInterfacesAggregate::Set_HeartStartSignInterface(IHeartStartSign *pHeartSignInterface, bool bRemove/*=FALSE*/)
	{
		if( bRemove == false )
		{
			if( m_pHeartStartSignInterface == NULL )
			{
				m_pHeartStartSignInterface = pHeartSignInterface;
			}
			else
			{
				m_pHeartStartSignInterface->SetNextInterfacePtr( pHeartSignInterface );
			}
		}
		else
		{
			if( m_pHeartStartSignInterface != NULL )
			{
				m_pHeartStartSignInterface = (IHeartStartSign *)IBedirecteLinksVir::RemoveInterfacePtr(m_pHeartStartSignInterface, pHeartSignInterface);
			}
		}
	}

	void CWatchBarsShowInterfacesAggregate::Set_ShowPTempValueInterfacePtr(CShowTempUpdateInterface *pPTempInterface, bool bRemove/*=FALSE*/)
	{
		if( bRemove == false )
		{
			if( m_pShowPTempValueInterface == NULL )
			{
				m_pShowPTempValueInterface = pPTempInterface;
			}
			else
			{
				m_pShowPTempValueInterface->SetNextInterfacePtr( pPTempInterface );
			}
		}
		else
		{
			if( m_pShowPTempValueInterface != NULL )
			{
				m_pShowPTempValueInterface = (CShowTempUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowPTempValueInterface, pPTempInterface);
			}
		}
	}

}}
