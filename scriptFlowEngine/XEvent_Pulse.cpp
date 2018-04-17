#include ".\XEvent_Pulse.h"

#include "..\elementParse\SEvent_Pulse.h"


namespace jysoft { namespace flowEngine 
{
	CXEvent_Pulse::CXEvent_Pulse(void)
	{
		m_sImplementNum = 0;
	}

	CXEvent_Pulse::~CXEvent_Pulse(void)
	{
	}

	bool CXEvent_Pulse::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXEvent_Pulse" )
		{
			return true;
		}
		return CXEventVirtual::isKindOf( strClassName );
	}

	/*******************************************************************************/
	// 函数名称： GetEventCaption
	// 功能：   返回体征标识名
	// 参数：   
	// 返回值: 
	std::string CXEvent_Pulse::getEventCaption()
	{
		return CSEvent_Pulse::getEvent_Pulse_Caption();
	}

	/*******************************************************************************/
	// 函数名称： Parse_EventFromXml
	// 功能：   解析体征参数内容
	// 参数：   IXMLDOMNode *pXMLShapeNode:
	// 返回值: 
	bool CXEvent_Pulse::Parse_EventFromXml(pugi::xml_node *pXMLShapeNode, IGetPhysiologyActionObj *pGetActionObj)
	{
		short sPulseCount, sPulseAct;
		m_sImplementNum = 0;
		return CSEvent_Pulse::explainParamsFromXML(pXMLShapeNode, &sPulseCount, &sPulseAct);
	}

	/*******************************************************************************/
	// 功能：   是否触发设定的事件
	// 参数：   
	// 返回值: 满足(TRUE)；不满足(FALSE)
	bool CXEvent_Pulse::IsSatisfactionEvent()
	{
		if( m_sImplementNum > 0 )
		{
			return true;
		}
		return false;
	}

	/*******************************************************************************/
	// 功能：   清除事件触发相关的记录信息
	// 参数：   
	// 返回值: 
	void CXEvent_Pulse::ClearSatisfactionInfo()
	{
		m_sImplementNum = 0;
	}

	/*******************************************************************************/
	// 功能：   事件处理
	// 参数：   
	// 返回值: 
	void CXEvent_Pulse::DoHandleEventIrp(irp::CVirEventIrp  *pEventIrp)
	{

	}
}}
