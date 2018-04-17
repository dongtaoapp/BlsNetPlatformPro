#include ".\XEvent_AED.h"

#include "..\elementParse\SEvent_AED.h"


namespace jysoft { namespace flowEngine 
{
	CXEvent_AED::CXEvent_AED(void)
	{
		m_bStartupAED = false;
		m_sImplementNum = 0;
	}
	
	CXEvent_AED::~CXEvent_AED(void)
	{
	}

	bool CXEvent_AED::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXEvent_AED" )
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
	std::string CXEvent_AED::getEventCaption()
	{
		return CSEvent_AED::getEvent_AED_Caption();
	}

	/*******************************************************************************/
	// �������ƣ� Parse_EventFromXml
	// ���ܣ�   ����������������
	// ������   IXMLDOMNode *pXMLShapeNode:
	// ����ֵ: 
	bool CXEvent_AED::Parse_EventFromXml(pugi::xml_node *pXMLShapeNode, IGetPhysiologyActionObj *pGetActionObj)
	{
		m_sImplementNum = 0;
		boost::tribool   bStartupAED = false;
		return CSEvent_AED::explainParamsFromXML(pXMLShapeNode, /*out*/&bStartupAED);
	}

	/*******************************************************************************/
	// ���ܣ�   �Ƿ񴥷��趨���¼�
	// ������   
	// ����ֵ: ����(TRUE)��������(FALSE)
	bool CXEvent_AED::IsSatisfactionEvent()
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
	void CXEvent_AED::ClearSatisfactionInfo()
	{
		m_sImplementNum = 0;
	}

	/*******************************************************************************/
	// ���ܣ�   �¼�����
	// ������   
	// ����ֵ: 
	void CXEvent_AED::DoHandleEventIrp(irp::CVirEventIrp  *pEventIrp)
	{

	}
}}
