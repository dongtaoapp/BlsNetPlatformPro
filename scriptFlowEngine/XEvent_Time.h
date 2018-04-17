#pragma once
#include ".\xeventvirtual.h"


namespace jysoft { namespace flowEngine 
{
	class CXEvent_Time : public CXEventVirtual
	{
	public:
		CXEvent_Time(void);
		virtual ~CXEvent_Time(void);
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
		bool         m_bTimeType;      //true:Ϊ���ʱ�䣬false:�ǲ���ʱ��
		short        m_sTimeValue;    //����ʱ����߿���г���ʱ��
	private:
		short                               m_sImplementNum;    //ʵʩ�¼��ۻ�����
		IGetPhysiologyActionObj            *m_pGetActionObjInterface;
	};
}}

