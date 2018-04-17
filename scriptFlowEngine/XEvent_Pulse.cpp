#include ".\XEvent_Pulse.h"

#include "..\elementParse\SEvent_Pulse.h"


namespace jysoft { namespace flowEngine 
{
	CXEvent_Pulse::CXEvent_Pulse(void)
	{
		m_sImplementNum = 0;
	}

	CXEvent_Pulse::~CXEvent_Pulse(void)
	{
	}

	bool CXEvent_Pulse::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXEvent_Pulse" )
		{
			return true;
		}
		return CXEventVirtual::isKindOf( strClassName );
	}

	/*******************************************************************************/
	// �������ƣ� GetEventCaption
	// ���ܣ�   ����������ʶ��
	// ������   
	// ����ֵ: 
	std::string CXEvent_Pulse::getEventCaption()
	{
		return CSEvent_Pulse::getEvent_Pulse_Caption();
	}

	/*******************************************************************************/
	// �������ƣ� Parse_EventFromXml
	// ���ܣ�   ����������������
	// ������   IXMLDOMNode *pXMLShapeNode:
	// ����ֵ: 
	bool CXEvent_Pulse::Parse_EventFromXml(pugi::xml_node *pXMLShapeNode, IGetPhysiologyActionObj *pGetActionObj)
	{
		short sPulseCount, sPulseAct;
		m_sImplementNum = 0;
		return CSEvent_Pulse::explainParamsFromXML(pXMLShapeNode, &sPulseCount, &sPulseAct);
	}

	/*******************************************************************************/
	// ���ܣ�   �Ƿ񴥷��趨���¼�
	// ������   
	// ����ֵ: ����(TRUE)��������(FALSE)
	bool CXEvent_Pulse::IsSatisfactionEvent()
	{
		if( m_sImplementNum > 0 )
		{
			return true;
		}
		return false;
	}

	/*******************************************************************************/
	// ���ܣ�   ����¼�������صļ�¼��Ϣ
	// ������   
	// ����ֵ: 
	void CXEvent_Pulse::ClearSatisfactionInfo()
	{
		m_sImplementNum = 0;
	}

	/*******************************************************************************/
	// ���ܣ�   �¼�����
	// ������   
	// ����ֵ: 
	void CXEvent_Pulse::DoHandleEventIrp(irp::CVirEventIrp  *pEventIrp)
	{

	}
}}
