#include ".\XEvent_Thump.h"

#include "..\elementParse\SEvent_Thump.h"


namespace jysoft { namespace flowEngine 
{
	CXEvent_Thump::CXEvent_Thump(void)
	{
		m_sImplementNum = 0;
	}

	CXEvent_Thump::~CXEvent_Thump(void)
	{
	}

	bool CXEvent_Thump::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXEvent_Thump" )
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
	std::string CXEvent_Thump::getEventCaption()
	{
		return CSEvent_Thump::getAction_Thump_Caption();
	}

	/*******************************************************************************/
	// �������ƣ� Parse_EventFromXml
	// ���ܣ�   ����������������
	// ������   IXMLDOMNode *pXMLShapeNode:
	// ����ֵ: 
	bool CXEvent_Thump::Parse_EventFromXml(pugi::xml_node *pXMLShapeNode, IGetPhysiologyActionObj *pGetActionObj)
	{
		bool bThump = true;
		m_sImplementNum = 0;
		return CSEvent_Thump::explainParamsFromXML(pXMLShapeNode, &bThump);
	}

	/*******************************************************************************/
	// ���ܣ�   �Ƿ񴥷��趨���¼�
	// ������   
	// ����ֵ: ����(TRUE)��������(FALSE)
	bool CXEvent_Thump::IsSatisfactionEvent()
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
	void CXEvent_Thump::ClearSatisfactionInfo()
	{
		m_sImplementNum = 0;
	}

	/*******************************************************************************/
	// ���ܣ�   �¼�����
	// ������   
	// ����ֵ: 
	void CXEvent_Thump::DoHandleEventIrp(irp::CVirEventIrp  *pEventIrp)
	{
		;
	}

}}
