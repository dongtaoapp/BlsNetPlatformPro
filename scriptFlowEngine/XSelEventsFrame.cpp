#include <boost/foreach.hpp>
#include ".\xseleventsframe.h"


namespace jysoft { namespace flowEngine 
{
	CXSelEventsFrame::CXSelEventsFrame(IAclsFlowStrategy   *pFlowStrategy)
							: CXVirtualEventFrame(pFlowStrategy)
	{
	}

	CXSelEventsFrame::~CXSelEventsFrame(void)
	{
	}

	bool CXSelEventsFrame::isKindOf(const std::string &strClassName)
	{
		if(strClassName == "CXSelEventsFrame")
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
	bool CXSelEventsFrame::DoHandleEventIrp(irp::CVirEventIrp *pCurrEventIrp)
	{
		if( m_lstEvents.size() == 0 )
		{
			return false;
		}
		BOOST_FOREACH(auto pVirEvent, m_lstEvents)
		{
			pVirEvent->DoHandleEventIrp( pCurrEventIrp );
			if( pVirEvent->IsSatisfactionEvent() )
			{
				return true;
			}
		}
		return false;
	}
}}
