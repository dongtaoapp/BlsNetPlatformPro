#include ".\XEvent_AED.h"

#include "..\elementParse\SEvent_AED.h"


namespace jysoft { namespace flowEngine 
{
	CXEvent_AED::CXEvent_AED(void)
	{
		m_bStartupAED = false;
		m_sImplementNum = 0;
	}
	
	CXEvent_AED::~CXEvent_AED(void)
	{
	}

	bool CXEvent_AED::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXEvent_AED" )
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
	std::string CXEvent_AED::getEventCaption()
	{
		return CSEvent_AED::getEvent_AED_Caption();
	}

	/*******************************************************************************/
	// 函数名称： Parse_EventFromXml
	// 功能：   解析体征参数内容
	// 参数：   IXMLDOMNode *pXMLShapeNode:
	// 返回值: 
	bool CXEvent_AED::Parse_EventFromXml(pugi::xml_node *pXMLShapeNode, IGetPhysiologyActionObj *pGetActionObj)
	{
		m_sImplementNum = 0;
		boost::tribool   bStartupAED = false;
		return CSEvent_AED::explainParamsFromXML(pXMLShapeNode, /*out*/&bStartupAED);
	}

	/*******************************************************************************/
	// 功能：   是否触发设定的事件
	// 参数：   
	// 返回值: 满足(TRUE)；不满足(FALSE)
	bool CXEvent_AED::IsSatisfactionEvent()
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
	void CXEvent_AED::ClearSatisfactionInfo()
	{
		m_sImplementNum = 0;
	}

	/*******************************************************************************/
	// 功能：   事件处理
	// 参数：   
	// 返回值: 
	void CXEvent_AED::DoHandleEventIrp(irp::CVirEventIrp  *pEventIrp)
	{

	}
}}
