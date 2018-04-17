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
	//���ܣ������¼�IRP�����麯��
	//������
	//      CVirEventIrp *pCurrEventIrp��
	//����ֵ:  �¼����Ƿ���������(TURE:���㣻FALSE:������)
	bool CXSingleEventFrame::DoHandleEventIrp(irp::CVirEventIrp *pCurrEventIrp)
	{
		if( m_lstEvents.size() == 0 )
		{
			return false;
		}
		CXEventVirtual  *pVirEvent = *m_lstEvents.begin();
		//�����¼�IRP
		pVirEvent->DoHandleEventIrp( pCurrEventIrp );
		return pVirEvent->IsSatisfactionEvent();
	}
}}
