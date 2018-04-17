#pragma once
#include ".\xeventvirtual.h"


namespace jysoft { namespace flowEngine 
{
	class CXEvent_Defibri : public CXEventVirtual
	{
	public:
		CXEvent_Defibri(void);
		virtual ~CXEvent_Defibri(void);
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
	protected:
		short               m_sAccumulateNum;   //�����ۼƴ���
		short               m_sDefibrEnergy;    //������ѹ��С
	private:
		short               m_sImplementNum;    //ʵʩ�¼����ۻ�����
		simulator::CXAction_Defibri   *m_pAction_Defibri;
	};
}}
