#include ".\xsingleeventframe.h"

namespace jysoft { namespace flowEngine 
{
	CXSingleEventFrame::CXSingleEventFrame(IAclsFlowStrategy   *pFlowStrategy)
							   : CXVirtualEventFrame(pFlowStrategy)
	{
	}

	CXSingleEventFrame::~CXSingleEventFrame(void)
	{
	}

	bool CXSingleEventFrame::isKindOf(const std::string &strClassName)
	{
		if(strClassName == "CXSingleEventFrame")
		{
			return true;
		}
		return CXVirtualEventFrame::isKindOf(strClassName);
	}

	/*******************************************************************************/
	//功能：处理事件IRP函数虚函数
	//参数：
	//      CVirEventIrp *pCurrEventIrp：
	//返回值:  事件框是否条件满足(TURE:满足；FALSE:不满足)
	bool CXSingleEventFrame::DoHandleEventIrp(irp::CVirEventIrp *pCurrEventIrp)
	{
		if( m_lstEvents.size() == 0 )
		{
			return false;
		}
		CXEventVirtual  *pVirEvent = *m_lstEvents.begin();
		//处理事件IRP
		pVirEvent->DoHandleEventIrp( pCurrEventIrp );
		return pVirEvent->IsSatisfactionEvent();
	}
}}
