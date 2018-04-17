#pragma once
#include <list>
#include <pugixml.hpp>
#include ".\IAclsFlowStrategy.h"
#include ".\XEventVirtual.h"

#include "..\Common\CommonGlobal.h"
#include "..\Common\EventHandleClockIrpOp.h"
#include "..\Common\EventHandleCustomIrpOp.h"

#include "..\simulatorsymptom\xvirtualcomponent.h"


namespace jysoft { namespace flowEngine 
{
	class CXVirtualEventFrame : public simulator::CXVirtualComponent
								,public irp::CEventHandleCustomIrpOp
								,public irp::CEventHandleClockIrpOp
	{
	public:
		CXVirtualEventFrame(IAclsFlowStrategy   *pFlowStrategy);
		virtual ~CXVirtualEventFrame(void);
	protected:
		IAclsFlowStrategy*               m_pAlcsFlowStrategy;
		std::list<CXEventVirtual *>      m_lstEvents;
		eEventSign                       m_eEventSign;
		pugi::xml_node                   m_xmlEventFrameDOMNode;
	public: //函数重载
		/*******************************************************************************/
		//功能：处理场景事件IRP函数
		//参数：
		//      CVirtualIrp *pCurrIrp：
		//返回值:  后续不再处理（FALSE);
		virtual bool doHandleCustomEventIrpOp(irp::CVirtualIrp *pCurrIrp);
		/*******************************************************************************/
		//功能：处理时钟事件IRP函数
		//参数：
		//      CVirtualIrp *pCurrIrp：
		//返回值:  后续不再处理（FALSE);
		virtual bool doHandleClockIrpOp(irp::CVirtualIrp *pCurrIrp);
	public:
		virtual bool isKindOf(const std::string &strClassName);
		virtual eEventSign Get_eEventSign();
		/*******************************************************************************/
		//功能：处理事件IRP函数虚函数
		//参数：
		//      CVirEventIrp *pCurrEventIrp：
		//返回值:  事件框是否条件满足(TURE:满足；FALSE:不满足)
		virtual bool DoHandleEventIrp(irp::CVirEventIrp *pCurrEventIrp) = 0;
	public:
		//解析事件框
		bool ParseEvents(const pugi::xml_node &eventFrameNode);
	};
}}