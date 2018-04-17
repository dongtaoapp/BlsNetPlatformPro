#pragma once
#include ".\xeventvirtual.h"

#include "..\simulatorBase\VirEventIrp.h"


namespace jysoft { namespace flowEngine 
{
	class CXEvent_AED : public CXEventVirtual
	{
	public:
		CXEvent_AED(void);
		virtual ~CXEvent_AED(void);
	public:
		virtual bool isKindOf(const std::string &strClassName);
	public:
		/*******************************************************************************/
		// 函数名称： GetEventCaption
		// 功能：   返回体征标识名
		// 参数：   
		// 返回值: 
		virtual std::string getEventCaption();
		/*******************************************************************************/
		// 函数名称： Parse_EventFromXml
		// 功能：   解析体征参数内容
		// 参数：   IXMLDOMNode *pXMLShapeNode:
		// 返回值: 
		virtual bool Parse_EventFromXml(pugi::xml_node *pXMLShapeNode, IGetPhysiologyActionObj *pGetActionObj);
		/*******************************************************************************/
		// 功能：   是否触发设定的事件
		// 参数：   
		// 返回值: 满足(TRUE)；不满足(FALSE)
		virtual bool IsSatisfactionEvent();
		/*******************************************************************************/
		// 功能：   清除事件触发相关的记录信息
		// 参数：   
		// 返回值: 
		virtual void ClearSatisfactionInfo();
		/*******************************************************************************/
		// 功能：   事件处理
		// 参数：   
		// 返回值: 
		virtual void DoHandleEventIrp(irp::CVirEventIrp  *pEventIrp);
	private:
		short     m_sImplementNum;    //实施事件累积次数
		bool      m_bStartupAED; 
	};
}}
