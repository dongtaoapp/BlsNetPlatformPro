#include ".\symptom_pace.h"
#include ".\IModifiedSymptomsOp.h"
#include ".\XAction_Pace.h"

#include "..\Common\DecodeUtil.h"

#include "..\ElementParse\SAction_Pace.h"


using namespace jysoft::simulator::base;
namespace jysoft { namespace simulator 
{
	CSymptom_Pace::CSymptom_Pace(void)
	{
		m_pShowPaceInterface  = NULL;
	}

	CSymptom_Pace::~CSymptom_Pace(void)
	{
	}

	/*******************************************************************************/
	// 函数名称： IsKindOf
	// 功能：   判断体征的类别
	// 参数：   const CString &strClassName
	// 返回值: 
	bool CSymptom_Pace::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_Pace" )
		{
			return true;
		}
		return false;
	}

	//根据标示名称判断体征参数
	bool CSymptom_Pace::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_Pace::isAction_Pace( strCaption );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   IModifiedSymptomsOp *pInterfacePtr
	//          tag_TrendValue *pDefaultTrendValue:  相应体征修改的值返回
	// 返回值: 
	void CSymptom_Pace::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;
		//设置默认值
		m_bEnablePace     = TRUE;
		m_sData           = 20;

		m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
	}
	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   
	//          tag_TrendValue *pDefaultTrendValue:  相应体征修改的值返回
	//          CXActionVirtual *pVirAction:         对应体征值
	//          short sTransTime:                    转换时间（单位：秒）
	// 返回值: 
	void CSymptom_Pace::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime/*=0*/)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_Pace::getAction_Pace_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 
		CXAction_Pace  *pAction_Pace = (CXAction_Pace *)pVirAction;
		m_sData       = pAction_Pace->GetValue_PaceElectricData();
		m_bEnablePace = pAction_Pace->GetValue_EnablePace();

		m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
	}

	// 函数名称： OnUpdateInterfaceShow
	// 功能：   更新界面显示
	// 参数：   
	// 返回值: 
	void CSymptom_Pace::OnUpdateInterfaceShow()
	{
		if( m_pShowPaceInterface != NULL )
		{
			m_pShowPaceInterface->OnShowPaceset( m_bEnablePace, m_sData );
		}
	}

	/*******************************************************************************/
	// 函数名称： OnLinkSimulatorBarUpdateInterfaceShow
	// 功能：   断开模拟人面板显示连接
	// 参数：   
	// 返回值:
	void CSymptom_Pace::OnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate )
	{
		//起搏设置显示接口
		CShowPaceUpdateInterface  *pShowInterface = pShowAggregate->Get_ShowPaceUpdateInterfacePtr();
		if( m_pShowPaceInterface == NULL )
		{
			m_pShowPaceInterface = pShowInterface;
		}
		else if( pShowInterface != NULL )
		{
			m_pShowPaceInterface->SetNextInterfacePtr( pShowInterface );
		}
		if( pShowInterface != NULL )
		{
			pShowInterface->LinkUpdateShow();
			pShowInterface->OnShowPaceset( m_bEnablePace, m_sData );
		}
	}

	/*******************************************************************************/
	// 函数名称： OnUnLinkSimulatorBarUpdateInterfaceShow
	// 功能：   断开模拟人面板显示连接
	// 参数：   
	// 返回值:
	void CSymptom_Pace::OnUnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate )
	{
		//起搏设置显示接口
		CShowPaceUpdateInterface  *pShowInterface = pShowAggregate->Get_ShowPaceUpdateInterfacePtr();
		if( pShowInterface != NULL )
		{
			m_pShowPaceInterface = (CShowPaceUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowPaceInterface, pShowInterface);
			//断开显示操作
			pShowInterface->UnLinkUpdateShow();
		}
	}
}}
