#include ".\XEvent_Defibri.h"

#include "..\ElementParse\SEvent_Defibr.h"

#include "..\SimulatorBase\EventIrp_SimulateTrigger.h"

namespace jysoft { namespace flowEngine 
{
	CXEvent_Defibri::CXEvent_Defibri(void)
	{
		m_sImplementNum   = 0;
		m_pAction_Defibri = NULL;
	}

	CXEvent_Defibri::~CXEvent_Defibri(void)
	{
	}

	bool CXEvent_Defibri::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXEvent_Defibri" )
		{
			return true;
		}
		return false;
	}

	/*******************************************************************************/
	// �������ƣ� GetEventCaption
	// ���ܣ�   ����������ʶ��
	// ������   
	// ����ֵ: 
	std::string CXEvent_Defibri::getEventCaption()
	{
		return CSEvent_Defibr::getEvent_Defibr_Caption();
	}

	/*******************************************************************************/
	// �������ƣ� Parse_EventFromXml
	// ���ܣ�   ����������������
	// ������   IXMLDOMNode *pXMLShapeNode:
	// ����ֵ: 
	bool CXEvent_Defibri::Parse_EventFromXml(pugi::xml_node *pXMLShapeNode, IGetPhysiologyActionObj *pGetActionObj)
	{
		bool bSec = CSEvent_Defibr::explainParamsFromXML(pXMLShapeNode, &m_sAccumulateNum, &m_sDefibrEnergy);
		m_sImplementNum  = 0;
		//��ȡ��������Action
		m_pAction_Defibri  = pGetActionObj->getAction_DefibriPtr();
		return bSec ;
	}

	/*******************************************************************************/
	// ���ܣ�   �Ƿ񴥷��趨���¼�
	// ������   
	// ����ֵ: ����(TRUE)��������(FALSE)
	bool CXEvent_Defibri::IsSatisfactionEvent()
	{
		if( m_sImplementNum >= m_sAccumulateNum )
		{
			return true;
		}
		return false;
	}

	/*******************************************************************************/
	// ���ܣ�   ����¼�������صļ�¼��Ϣ
	// ������   
	// ����ֵ: 
	void CXEvent_Defibri::ClearSatisfactionInfo()
	{
		m_sImplementNum  = 0;
	}

	/*******************************************************************************/
	// ���ܣ�   �¼�����
	// ������   
	// ����ֵ: 
	void CXEvent_Defibri::DoHandleEventIrp(irp::CVirEventIrp  *pEventIrp)
	{
		if( pEventIrp->isKindOf( "CEventIrp_SimulateTrigger" ) )
		{
			irp::CEventIrp_SimulateTrigger *pSimulateTriggerEvent = (irp::CEventIrp_SimulateTrigger *)pEventIrp;
			if( pSimulateTriggerEvent->m_strTriggerEventName == CSEvent_Defibr::getEvent_Defibr_Caption() )
			{
				m_sImplementNum += 1;
			}
		}
	}

}}
