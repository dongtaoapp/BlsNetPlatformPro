#include <math.h>
#include ".\symptom_temperature.h"
#include ".\IModifiedSymptomsOp.h"
#include ".\XActionVirtual.h"
#include ".\XAction_Temperature.h"

#include "..\ElementParse\SAction_Temperature.h"

#include "..\SimulatorBase\WatchBarsShowInterfacesAggregate.h"


using namespace jysoft::simulator::base;
namespace jysoft { namespace simulator 
{
	CSymptom_Temperature::CSymptom_Temperature(void)
	{
		m_pShowPTempValueInterface = NULL;
	}

	CSymptom_Temperature::~CSymptom_Temperature(void)
	{
	}

	/*******************************************************************************/
	// 函数名称： IsKindOf
	// 功能：   判断体征的类别
	// 参数：   const CString &strClassName
	// 返回值: 
	bool CSymptom_Temperature::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_Temperature" )
		{
			return true;
		}
		return false;
	}

	//根据标示名称判断体征参数
	bool CSymptom_Temperature::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_Temperature::isAction_Temperature( strCaption );
	}
	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   IModifiedSymptomsOp *pInterfacePtr
	// 返回值: 
	void CSymptom_Temperature::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;

		m_fP_TempValue   = 35.2f;

		pInterfacePtr->AddNewModifiedSymptom( this );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   
	//          CXActionVirtual *pVirAction:         对应体征值
	//          short sTransTime:                    转换时间（单位：秒）
	// 返回值: 
	void CSymptom_Temperature::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime/*=0*/)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_Temperature::getAction_Temperature_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 		
		CXAction_Temperature *pAction_Temp = (CXAction_Temperature *)pVirAction;

		if( sTransTime == 0 )
		{
			m_fP_TempValue  = pAction_Temp->GetValue_P_Temp();
		}
		m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );

	}

	void CSymptom_Temperature::SetShowTemperatureValueInterface(CShowTempUpdateInterface *ptemp)
	{
		m_pShowPTempValueInterface = ptemp;
		if(m_pShowPTempValueInterface)
		{
			m_pShowPTempValueInterface->LinkUpdateShow();
			m_pShowPTempValueInterface->OnShowTempValue(m_fP_TempValue);
		}
	}

	// 函数名称： OnUpdateInterfaceShow
	// 功能：   更新界面显示
	// 参数：   
	// 返回值: 
	void CSymptom_Temperature::OnUpdateInterfaceShow()
	{
		if( m_pShowPTempValueInterface ) 
		{
			m_pShowPTempValueInterface->OnShowTempValue(m_fP_TempValue);
		}
	}

	/*******************************************************************************/
	// 函数名称： OnLinkWatchBarUpdateInterfaceShow
	// 功能：   连接模拟监控显示连接
	// 参数：   
	// 返回值:
	void CSymptom_Temperature::OnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		CShowTempUpdateInterface *pShowPTempInterface = pShowAggregate->Get_ShowPTempValueInterfacePtr();
		//设置关联的显示接口
		SetShowTemperatureValueInterface( pShowPTempInterface);
	}

	/*******************************************************************************/
	// 函数名称： OnUnLinkWatchBarUpdateInterfaceShow
	// 功能：   断开显示连接
	// 参数：   
	// 返回值:
	void CSymptom_Temperature::OnUnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		CShowTempUpdateInterface *pShowPTempInterface = pShowAggregate->Get_ShowPTempValueInterfacePtr();
		if( pShowPTempInterface != NULL )
		{
			m_pShowPTempValueInterface = (CShowTempUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowPTempValueInterface, pShowPTempInterface);
			//断开显示操作
			pShowPTempInterface->UnLinkUpdateShow();
		}
	}
}}
