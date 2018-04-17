#include <boost/foreach.hpp>
#include ".\xcombineeventsframe.h"


namespace jysoft { namespace flowEngine 
{
	CXCombineEventsFrame::CXCombineEventsFrame(IAclsFlowStrategy   *pFlowStrategy)
								  : CXVirtualEventFrame(pFlowStrategy)
	{
	}

	CXCombineEventsFrame::~CXCombineEventsFrame(void)
	{
	}

	bool CXCombineEventsFrame::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXCombineEventsFrame")
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
	bool CXCombineEventsFrame::DoHandleEventIrp(irp::CVirEventIrp *pCurrEventIrp)
	{
		if( m_lstEvents.size() == 0 )
		{
			return false;
		}
		//--------------------------------------------------------------------------
		BOOST_FOREACH(auto pVirEvent, m_lstEvents)
		{
			pVirEvent->DoHandleEventIrp( pCurrEventIrp );
		}
		BOOST_FOREACH(auto pVirEvent, m_lstEvents)
		{
			if( !pVirEvent->IsSatisfactionEvent() )
			{
				return false;
			}
		}
		return true;
	}
}}
