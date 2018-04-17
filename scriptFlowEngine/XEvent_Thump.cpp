#include ".\XEvent_Thump.h"

#include "..\elementParse\SEvent_Thump.h"


namespace jysoft { namespace flowEngine 
{
	CXEvent_Thump::CXEvent_Thump(void)
	{
		m_sImplementNum = 0;
	}

	CXEvent_Thump::~CXEvent_Thump(void)
	{
	}

	bool CXEvent_Thump::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXEvent_Thump" )
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
	std::string CXEvent_Thump::getEventCaption()
	{
		return CSEvent_Thump::getAction_Thump_Caption();
	}

	/*******************************************************************************/
	// 函数名称： Parse_EventFromXml
	// 功能：   解析体征参数内容
	// 参数：   IXMLDOMNode *pXMLShapeNode:
	// 返回值: 
	bool CXEvent_Thump::Parse_EventFromXml(pugi::xml_node *pXMLShapeNode, IGetPhysiologyActionObj *pGetActionObj)
	{
		bool bThump = true;
		m_sImplementNum = 0;
		return CSEvent_Thump::explainParamsFromXML(pXMLShapeNode, &bThump);
	}

	/*******************************************************************************/
	// 功能：   是否触发设定的事件
	// 参数：   
	// 返回值: 满足(TRUE)；不满足(FALSE)
	bool CXEvent_Thump::IsSatisfactionEvent()
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
	void CXEvent_Thump::ClearSatisfactionInfo()
	{
		m_sImplementNum = 0;
	}

	/*******************************************************************************/
	// 功能：   事件处理
	// 参数：   
	// 返回值: 
	void CXEvent_Thump::DoHandleEventIrp(irp::CVirEventIrp  *pEventIrp)
	{
		;
	}

}}
