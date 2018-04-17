#pragma once
#include "xvirtualeventframe.h"


namespace jysoft { namespace flowEngine 
{
	class CXCombineEventsFrame : public CXVirtualEventFrame
	{
	public:
		CXCombineEventsFrame(IAclsFlowStrategy   *pFlowStrategy);
		virtual ~CXCombineEventsFrame(void);
	public:
		virtual bool isKindOf(const std::string &strClassName);
		/*******************************************************************************/
		//功能：处理事件IRP函数虚函数
		//参数：
		//      CVirEventIrp *pCurrEventIrp：
		//返回值:  事件框是否条件满足(TURE:满足；FALSE:不满足)
		virtual bool DoHandleEventIrp(irp::CVirEventIrp *pCurrEventIrp);
	};
}}