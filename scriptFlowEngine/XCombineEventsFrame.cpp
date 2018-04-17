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
	//���ܣ������¼�IRP�����麯��
	//������
	//      CVirEventIrp *pCurrEventIrp��
	//����ֵ:  �¼����Ƿ���������(TURE:���㣻FALSE:������)
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
