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
	//���ܣ������¼�IRP�����麯��
	//������
	//      CVirEventIrp *pCurrEventIrp��
	//����ֵ:  �¼����Ƿ���������(TURE:���㣻FALSE:������)
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
