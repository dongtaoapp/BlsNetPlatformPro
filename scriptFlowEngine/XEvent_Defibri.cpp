#include ".\XEvent_Defibri.h"

#include "..\ElementParse\SEvent_Defibr.h"

#include "..\SimulatorBase\EventIrp_SimulateTrigger.h"

namespace jysoft { namespace flowEngine 
{
	CXEvent_Defibri::CXEvent_Defibri(void)
	{
		m_sImplementNum   = 0;
		m_pAction_Defibri = NULL;
	}

	CXEvent_Defibri::~CXEvent_Defibri(void)
	{
	}

	bool CXEvent_Defibri::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXEvent_Defibri" )
		{
			return true;
		}
		return false;
	}

	/*******************************************************************************/
	// 函数名称： GetEventCaption
	// 功能：   返回体征标识名
	// 参数：   
	// 返回值: 
	std::string CXEvent_Defibri::getEventCaption()
	{
		return CSEvent_Defibr::getEvent_Defibr_Caption();
	}

	/*******************************************************************************/
	// 函数名称： Parse_EventFromXml
	// 功能：   解析体征参数内容
	// 参数：   IXMLDOMNode *pXMLShapeNode:
	// 返回值: 
	bool CXEvent_Defibri::Parse_EventFromXml(pugi::xml_node *pXMLShapeNode, IGetPhysiologyActionObj *pGetActionObj)
	{
		bool bSec = CSEvent_Defibr::explainParamsFromXML(pXMLShapeNode, &m_sAccumulateNum, &m_sDefibrEnergy);
		m_sImplementNum  = 0;
		//获取触颤设置Action
		m_pAction_Defibri  = pGetActionObj->getAction_DefibriPtr();
		return bSec ;
	}

	/*******************************************************************************/
	// 功能：   是否触发设定的事件
	// 参数：   
	// 返回值: 满足(TRUE)；不满足(FALSE)
	bool CXEvent_Defibri::IsSatisfactionEvent()
	{
		if( m_sImplementNum >= m_sAccumulateNum )
		{
			return true;
		}
		return false;
	}

	/*******************************************************************************/
	// 功能：   清除事件触发相关的记录信息
	// 参数：   
	// 返回值: 
	void CXEvent_Defibri::ClearSatisfactionInfo()
	{
		m_sImplementNum  = 0;
	}

	/*******************************************************************************/
	// 功能：   事件处理
	// 参数：   
	// 返回值: 
	void CXEvent_Defibri::DoHandleEventIrp(irp::CVirEventIrp  *pEventIrp)
	{
		if( pEventIrp->isKindOf( "CEventIrp_SimulateTrigger" ) )
		{
			irp::CEventIrp_SimulateTrigger *pSimulateTriggerEvent = (irp::CEventIrp_SimulateTrigger *)pEventIrp;
			if( pSimulateTriggerEvent->m_strTriggerEventName == CSEvent_Defibr::getEvent_Defibr_Caption() )
			{
				m_sImplementNum += 1;
			}
		}
	}

}}
