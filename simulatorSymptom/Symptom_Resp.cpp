#include <algorithm>
#include <boost/foreach.hpp>
#include ".\symptom_resp.h"
#include ".\IModifiedSymptomsOp.h"
#include ".\XAction_Resp.h"

#include "..\Common\DecodeUtil.h"
#include "..\Common\PatientRuleInterfaceGlobal.h"

#include "..\elementParse\SAction_Resp.h"


using namespace jysoft::simulator::base;
namespace jysoft { namespace simulator 
{
	CSymptom_Resp::CSymptom_Resp(void)
	{
		m_pRespBuildInterface = NULL;
		m_pShowRespInterface  = NULL;
	}

	CSymptom_Resp::~CSymptom_Resp(void)
	{
		
	}

	/*******************************************************************************/
	// 函数名称： IsKindOf
	// 功能：   判断体征的类别
	// 参数：   const CString &strClassName
	// 返回值: 
	bool CSymptom_Resp::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_Resp" )
			return true;
		return false;
	}

	//根据标示名称判断体征参数
	bool CSymptom_Resp::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_Resp::isAction_Resp( strCaption );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   IModifiedSymptomsOp *pInterfacePtr
	// 返回值: 
	void CSymptom_Resp::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;
	
		//设置默认呼吸
		m_eRespMode  = RM_Normal;
		m_nRespRate  = 14;

		pInterfacePtr->AddNewModifiedSymptom( this );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   
	//          CXActionVirtual *pVirAction:         对应体征值
	//          short sTransTime:                    转换时间（单位：秒）
	// 返回值: 
	void CSymptom_Resp::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime/*=0*/)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_Resp::getAction_Resp_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 	
		//----------------------------------------------------------------------------------------------------
		int   nSrcRespRate  = m_nRespRate;
		CXAction_Resp *pAction_Breath = (CXAction_Resp *)pVirAction;
		if( pAction_Breath->GetRespMode() != m_eRespMode || pAction_Breath->GetValue_AbsoluteRR( nSrcRespRate ) != m_nRespRate )
		{
			m_eRespMode = pAction_Breath->GetRespMode();
			if( sTransTime == 0 )
			{
				m_nRespRate = pAction_Breath->GetValue_AbsoluteRR( nSrcRespRate );
			}

			m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
		}
	}

	//初始化呼吸模拟曲线构造器
	void CSymptom_Resp::InitialRespBuild(SimulatePatientType ePatientType)
	{
		if( m_pRespBuildInterface != NULL )
		{
			m_pRespBuildInterface->InitializeBuild(m_eRespMode, m_nRespRate);
		}
	}

	//修改呼吸模拟曲线构造器
	void CSymptom_Resp::ModifyRespBuild()
	{
		if( m_pRespBuildInterface != NULL )
		{
			m_pRespBuildInterface->OnModifyRespBuildType(m_eRespMode, m_nRespRate);
		}
	}

	/*******************************************************************************/
	// 函数名称： OnLinkSimulatorBarUpdateInterfaceShow
	// 功能：   断开模拟人面板显示连接
	// 参数：   
	// 返回值:
	void CSymptom_Resp::OnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate )
	{
		//呼吸模式显示接口
		CShowRespRateUpdateInterface *pShowRespInterface = pShowAggregate->Get_ShowRespUpdateInterfacePtr();
		if( m_pShowRespInterface == NULL )
		{
			m_pShowRespInterface  = pShowRespInterface;
		}
		else if( pShowRespInterface != NULL )
		{
			m_pShowRespInterface->SetNextInterfacePtr( pShowRespInterface );
		}
		if( pShowRespInterface != NULL )
		{
			pShowRespInterface->LinkUpdateShow();
			pShowRespInterface->OnShowRespRate( m_eRespMode, m_nRespRate );
		}
	}

	/*******************************************************************************/
	// 函数名称： OnUnLinkSimulatorBarUpdateInterfaceShow
	// 功能：   断开模拟人面板显示连接
	// 参数：   
	// 返回值:
	void CSymptom_Resp::OnUnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate )
	{
		CShowRespRateUpdateInterface *pShowInterface = pShowAggregate->Get_ShowRespUpdateInterfacePtr();
		if( pShowInterface != NULL )
		{
			m_pShowRespInterface = (CShowRespRateUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowRespInterface, pShowInterface);
			//断开显示操作
			pShowInterface->UnLinkUpdateShow();
		}
	}

	// 函数名称： OnUpdateInterfaceShow
	// 功能：   更新界面显示
	// 参数：   
	// 返回值: 
	void CSymptom_Resp::OnUpdateInterfaceShow()
	{
		if( m_pShowRespInterface != NULL )
		{
			m_pShowRespInterface->OnShowRespRate(m_eRespMode, m_nRespRate);
		}
	}
}}
