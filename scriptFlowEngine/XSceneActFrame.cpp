#include <boost/foreach.hpp>
#include ".\XSceneActFrame.h"
#include ".\ParseShapeFactory.h"

#include "..\simulatorSymptom\XActionVirtual.h"


using namespace jysoft::simulator;
namespace jysoft { namespace flowEngine 
{
	CXSceneActFrame::CXSceneActFrame(unsigned short dwFrameID)
	{
		m_dwFrameID      = dwFrameID;
		m_eActHandleType = SA_None;
		m_sDurationTime  = 0;
		m_pActEvent      = NULL;
		m_bExitFlow      = false;
	}

	CXSceneActFrame::~CXSceneActFrame(void)
	{
		if( m_pActEvent != NULL )
		{
			delete m_pActEvent;
		}
	}

	bool CXSceneActFrame::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXSceneActFrame" )
		{
			return true;
		}
		return CXScenario::isKindOf( strClassName );
	}

	//返回当前场景设置的体征列表
	void CXSceneActFrame::GetScenarioActions(std::list<simulator::CXActionVirtual *>* plstActions)
	{
		BOOST_FOREACH(auto pVirAction, m_lstActions)
		{
			plstActions->push_back( pVirAction );
		}
	}

	//解析情景框的所有体征及相关信息
	void CXSceneActFrame::ParseSceneActFrame(pugi::xml_node *pScenarioNode, IGetPhysiologyActionObj *pGetActionObj)
	{
		//解析情景框的所有体征
		ParseScenario( pScenarioNode );
		//解析事件
		for (pugi::xml_node_iterator it = pScenarioNode->begin(); it != pScenarioNode->end(); ++it)
		{
			if( std::string(it->name()) == "actEvent" )
			{
				LoadActEventFromXML( &(*it), pGetActionObj );
				break;
			}
		}
	}

	void CXSceneActFrame::LoadActEventFromXML(pugi::xml_node *pXMLActChild, IGetPhysiologyActionObj *pGetActionObj)
	{
		;
	}

	//解析场景框的所有体征（不生成CXAction_FrameTime项） hjg 2014.2.28 add
	void CXSceneActFrame::ParseActions(pugi::xml_node *pScenarioNode)
	{
		BOOST_FOREACH(auto x, m_lstActions)
		{
			delete x;
		}
		m_lstActions.clear();
		//---------------------------------------------------------------------
		//解析生理体征参数
		for (pugi::xml_node_iterator it = pScenarioNode->begin(); it != pScenarioNode->end(); ++it)
		{
			std::string  nodeName( it->name() );
			if( nodeName == "actions" )
			{
				for (pugi::xml_node_iterator actionNode = it->begin(); actionNode != it->end(); ++actionNode)
				{
					//解析对应的生理体征
					std::list<CXActionVirtual *>  lstActions;
					CParseShapeFactory::get_const_instance().ParseActionObject(&(*actionNode), &lstActions);
					//添加到属性列表中
					BOOST_FOREACH(auto pVirAction, lstActions)
					{
						m_lstActions.push_back( pVirAction );
					}
				}
				break;
			}
		}
	}

	/*******************************************************************************/
	//功能：处理事件IRP函数虚函数
	//参数：
	//      CVirEventIrp *pCurrEventIrp：
	//      /*out*/_ScheduleSceneState &eSceneState:    
	//返回值:  触发事件是否满足(TURE:满足；FALSE:不满足)
	bool CXSceneActFrame::DoHandleEventIrp(irp::CVirEventIrp *pCurrEventIrp, /*out*/_ScheduleSceneState &eSceneState)
	{
		if( m_pActEvent != NULL )
		{
			m_pActEvent->DoHandleEventIrp( pCurrEventIrp );
			if( m_pActEvent->IsSatisfactionEvent() )
			{
				if( m_eActHandleType == SA_Occur )
				{
					eSceneState = m_bExitFlow ? DSS_Logouted : DSS_SceneActSchedule;
					return true;
				}
				else if( m_eActHandleType == SA_UnoccurDurationTime )
				{
					m_sActTime = -1;
				}
				else if( m_sActTime == -1 )
				{
					m_sActTime = 0;
				}
			}
		}
		return false;
	}

	/*******************************************************************************/
	//功能：处理时钟事件IRP函数
	//参数：
	//      CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
	bool CXSceneActFrame::DoHandleClockIrpOp(irp::CEventIrp_ClockTime *pCurrClockTimeIrp, /*out*/_ScheduleSceneState &eSceneState)
	{
		if( m_pActEvent != NULL && m_sActTime > -1 )
		{
			m_sActTime += pCurrClockTimeIrp->GetValue_ClockEvent();
			if( m_sActTime > m_sDurationTime )
			{
				eSceneState = m_bExitFlow ? DSS_Logouted : DSS_SceneActSchedule;
				return true;
			}
		}
		return false;
	}

	/*******************************************************************************/
	//功能：激活情景框的处理状态
	//参数：   
	//      BOOL bReactive:     是否重新激活
	//返回值: 
	void CXSceneActFrame::DoStateActiveSceneFrame(bool bReactive)
	{
		if( m_pActEvent != NULL )
		{
			//清除事件触发相关的记录信息
			m_pActEvent->ClearSatisfactionInfo();
		}
		switch ( m_eActHandleType )
		{
		case SA_Occur:
		case SA_StipulatedTimeRear:
			{
				m_sActTime  = -1;
				break;
			}
		case SA_UnoccurDurationTime:
			{
				m_sActTime = !bReactive ? 0 : -1;
				break;
			}
		}
	}
}}
