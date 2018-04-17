#pragma once
#include ".\xeventvirtual.h"

#include "..\simulatorBase\VirEventIrp.h"


namespace jysoft { namespace flowEngine 
{
	class CXEvent_AED : public CXEventVirtual
	{
	public:
		CXEvent_AED(void);
		virtual ~CXEvent_AED(void);
	public:
		virtual bool isKindOf(const std::string &strClassName);
	public:
		/*******************************************************************************/
		// �������ƣ� GetEventCaption
		// ���ܣ�   ����������ʶ��
		// ������   
		// ����ֵ: 
		virtual std::string getEventCaption();
		/*******************************************************************************/
		// �������ƣ� Parse_EventFromXml
		// ���ܣ�   ����������������
		// ������   IXMLDOMNode *pXMLShapeNode:
		// ����ֵ: 
		virtual bool Parse_EventFromXml(pugi::xml_node *pXMLShapeNode, IGetPhysiologyActionObj *pGetActionObj);
		/*******************************************************************************/
		// ���ܣ�   �Ƿ񴥷��趨���¼�
		// ������   
		// ����ֵ: ����(TRUE)��������(FALSE)
		virtual bool IsSatisfactionEvent();
		/*******************************************************************************/
		// ���ܣ�   ����¼�������صļ�¼��Ϣ
		// ������   
		// ����ֵ: 
		virtual void ClearSatisfactionInfo();
		/*******************************************************************************/
		// ���ܣ�   �¼�����
		// ������   
		// ����ֵ: 
		virtual void DoHandleEventIrp(irp::CVirEventIrp  *pEventIrp);
	private:
		short     m_sImplementNum;    //ʵʩ�¼��ۻ�����
		bool      m_bStartupAED; 
	};
}}
