#pragma once
#include ".\xeventvirtual.h"


namespace jysoft { namespace flowEngine 
{
	class CXEvent_CPR : public CXEventVirtual
	{
	public:
		CXEvent_CPR(void);
		virtual ~CXEvent_CPR(void);
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
		// ���ܣ�   ����¼�������ص���Ϣ
		// ������   
		// ����ֵ: 
		virtual void ClearSatisfactionInfo();
		/*******************************************************************************/
		// ���ܣ�   �¼�����
		// ������   
		// ����ֵ: 
		virtual void DoHandleEventIrp(irp::CVirEventIrp  *pEventIrp);
	private:
		//�����ۻ�ʱ��
		void AddCaculateTime(short sSecond);
		//�����Ƿ��ܽ����ۻ�ʱ�����
		void SetEnableCaculateTime(bool bEnable, bool bClearCalcTime);
	protected:
		short                  m_sAccumulateTime;       //CPR�����ۼ�ʱ��
		short                  m_sAccumulateNum;        //CPR����ۼƴ���
		//-------------------------------------------------------------------
		//0��   �ķθ��ղ�����ʼ�������������ۻ�����
		//1��   �ķθ��ղ��������������������ۻ�����
		//2��   �ķθ��ղ���ģʽ
		//3��   ��׼�ķθ��ղ���ģʽ�������������ɹ��ۻ�����
		short                  m_sOpMode;               // ��ǰ������״̬
	private:
		short                  m_sImplementNum;         //ʵʩ�¼����ۻ�����
		cpr::CCPRMessageCollect    *m_pCPMessageCollect;     
		//--------------------------------------------------------------------
		bool                   m_bEnableCaculateTime;   //�Ƿ��ܽ���ʱ�����
		short                  m_sCaculateTimeValue;    //ʱ�����ֵ
	};
}}
