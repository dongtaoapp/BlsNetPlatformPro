#include <boost/bind.hpp>
#include <boost/assert.hpp>
#include ".\symptom_abp.h"
#include ".\IModifiedSymptomsOp.h"
#include ".\XAction_ABP.h"

#include "..\Common\DecodeUtil.h"

#include "..\elementParse\SAction_ABP.h"

#include "..\SimulatorBase\WatchBarsShowInterfacesAggregate.h"


using namespace jysoft::simulator::base;
namespace jysoft { namespace simulator 
{
	CSymptom_ABP::CSymptom_ABP(void) : m_cNIBPTimer(60*1000, boost::bind(&CSymptom_ABP::Set_NIBPCurrentValue, this))
	{
		m_pABPBuildInterface = NULL;
		m_pShowNIBPInterface = NULL;

		m_bModifyNIBPValue  = false;
		//设置默认血压值
		m_nShrinkValue_ABP  = 120;
		m_nStretchValue_ABP = 80;
	}

	CSymptom_ABP::~CSymptom_ABP(void)
	{
		m_cNIBPTimer.killTimer();
	}

	/*******************************************************************************/
	// 函数名称： IsKindOf
	// 功能：   判断体征的类别
	// 参数：   const CString &strClassName
	// 返回值: 
	bool CSymptom_ABP::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_ABP" )
		{
			return true;
		}
		return false;
	}

	//根据标示名称判断体征参数
	bool CSymptom_ABP::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_ABP::isAction_BP( strCaption );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   IModifiedSymptomsOp *pInterfacePtr
	// 返回值: 
	void CSymptom_ABP::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;

		m_nShrinkValue_NIBP  = 120;
		m_nStretchValue_NIBP = 80;

		m_bModifyNIBPValue  = true;

		pInterfacePtr->AddNewModifiedSymptom( this );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   
	//          CXActionVirtual *pVirAction:         对应体征值
	//          short sTransTime:                    转换时间（单位：秒）
	// 返回值: 
	void CSymptom_ABP::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime/*=0*/)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_ABP::getAction_BP_Caption()) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 
		CXAction_ABP  *pAction_ABP = (CXAction_ABP *)pVirAction;
		if( pAction_ABP->m_dwField == 0x01 )
		{
			//设置血压
			if( m_nShrinkValue_ABP != pAction_ABP->GetValue_AbsoluteShrink( m_nShrinkValue_ABP ) || m_nStretchValue_ABP != pAction_ABP->GetValue_AbsoluteStretch( m_nStretchValue_ABP ) )
			{
				if( sTransTime == 0 )
				{
					m_nShrinkValue_ABP  = pAction_ABP->GetValue_AbsoluteShrink( m_nShrinkValue_ABP );
					m_nStretchValue_ABP = pAction_ABP->GetValue_AbsoluteStretch( m_nStretchValue_ABP );
					//计算无创血压
					m_nShrinkValue_NIBP = m_nShrinkValue_ABP;
					m_nStretchValue_NIBP = m_nStretchValue_ABP;

					m_bModifyNIBPValue  = true;
					m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
				}
			}
		}
	}

	//初始化血压模拟曲线构造器
	void CSymptom_ABP::InitialABPBuild(SimulatePatientType ePatientType)
	{
		if( m_pABPBuildInterface != NULL )
		{
			m_pABPBuildInterface->OnModifyABPValue( m_nShrinkValue_ABP, m_nStretchValue_ABP );
		}
		//=======创建线程==============
		m_cNIBPTimer.startTimer();
	}

	//修改血压模拟曲线构造器
	void CSymptom_ABP::ModifyABPBuild()
	{
		if( m_pABPBuildInterface != NULL )
		{
			m_pABPBuildInterface->OnModifyABPValue( m_nShrinkValue_ABP, m_nStretchValue_ABP );
		}
	}

	//根据ABP的数值，获取NIBP(1分钟)
	void CSymptom_ABP::Set_NIBPCurrentValue()
	{
		if( m_nShrinkValue_NIBP != m_nShrinkValue_ABP || m_nStretchValue_NIBP != m_nStretchValue_ABP )
		{
			m_nShrinkValue_NIBP  =  m_nShrinkValue_ABP;
			m_nStretchValue_NIBP =  m_nStretchValue_ABP;

			m_bModifyNIBPValue  = true;

			//设置修改标志
			m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
		}
	}

	// 函数名称： OnUpdateInterfaceShow
	// 功能：   更新界面显示
	// 参数：   
	// 返回值: 
	void CSymptom_ABP::OnUpdateInterfaceShow()
	{
		if( m_pShowNIBPInterface != NULL )
		{
			m_pShowNIBPInterface->OnShowNIBPValue(m_nShrinkValue_ABP, m_nStretchValue_ABP); 
		}
		//--------------------------------------------------------------------------------------
		m_bModifyNIBPValue  = false;
	}

	void CSymptom_ABP::SetShowNIBPInterface(CShowNIBPUpdateInterface *pShowInterface)
	{
		if( m_pShowNIBPInterface == NULL )
		{
			m_pShowNIBPInterface  = pShowInterface;
		}
		else if( pShowInterface != NULL )
		{
			m_pShowNIBPInterface->SetNextInterfacePtr( pShowInterface );
		}
		if( m_pShowNIBPInterface != NULL )
		{
			m_pShowNIBPInterface->LinkUpdateShow();
			m_pShowNIBPInterface->OnShowNIBPValue(m_nShrinkValue_NIBP, m_nStretchValue_NIBP);
		}
	}

	/*******************************************************************************/
	// 函数名称： OnLinkWatchBarUpdateInterfaceShow
	// 功能：   连接模拟监控显示连接
	// 参数：   
	// 返回值:
	void CSymptom_ABP::OnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		CShowNIBPUpdateInterface *pShowInterface = pShowAggregate->Get_ShowNIBPValueUpdateInterfacePtr();
		//关联NIBP显示接口
		SetShowNIBPInterface( pShowInterface );
	}

	/*******************************************************************************/
	// 函数名称： OnUnLinkWatchBarUpdateInterfaceShow
	// 功能：   断开模拟监控显示连接
	// 参数：   
	// 返回值:
	void CSymptom_ABP::OnUnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate)
	{
		CShowNIBPUpdateInterface *pShowInterface = pShowAggregate->Get_ShowNIBPValueUpdateInterfacePtr();
		if( pShowInterface != NULL )
		{
			m_pShowNIBPInterface = (CShowNIBPUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowNIBPInterface, pShowInterface);
			//断开显示操作
			pShowInterface->UnLinkUpdateShow();
		}
	}

	/*******************************************************************************/
	// 函数名称： OnLinkSimulatorBarUpdateInterfaceShow
	// 功能：   连接模拟人面板显示连接
	// 参数：   
	// 返回值:
	void CSymptom_ABP::OnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate )
	{
		CShowNIBPUpdateInterface *pShowInterface = pShowAggregate->Get_ShowNIBPUpdateInterfacePtr();

		SetShowNIBPInterface( pShowInterface );
	}	

	/*******************************************************************************/
	// 函数名称： OnUnLinkSimulatorBarUpdateInterfaceShow
	// 功能：   断开模拟人面板显示连接
	// 参数：   
	// 返回值:
	void CSymptom_ABP::OnUnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate )
	{
		CShowNIBPUpdateInterface *pShowInterface = pShowAggregate->Get_ShowNIBPUpdateInterfacePtr();
		if( pShowInterface != NULL )
		{
			m_pShowNIBPInterface = (CShowNIBPUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowNIBPInterface, pShowInterface);
			//断开显示操作
			pShowInterface->UnLinkUpdateShow();
		}
	}

	//设置传送NIBP指令
	void  CSymptom_ABP::SetEnableTranslateNIBPOrder()
	{
		m_bModifyNIBPValue = true;
		m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
	}
}}
