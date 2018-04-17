#pragma once
#include ".\xactionvirtual.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �ű�����ʱ�����
	�����ˣ�	 hjg
	����ʱ�䣺   2013/8/23
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORSYMPTOMSHARED_EXPORT CXAction_ScriptRunTime : public CXActionVirtual
	{
	public:
		CXAction_ScriptRunTime(void);
		virtual ~CXAction_ScriptRunTime(void);
	public:
		virtual bool isKindOf(const std::string &strClassName);
		/*******************************************************************************/
		// �������ƣ� GetActionCaption
		// ���ܣ�   ����������ʶ��
		// ������   
		// ����ֵ: 
		virtual std::string getActionCaption() const;
		/*******************************************************************************/
		// �������ƣ� Parse_ActionFromXml
		// ���ܣ�   ����������������
		// ������   IXMLDOMNode *pXMLShapeNode:
		// ����ֵ: 
		virtual bool Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode);
		/*******************************************************************************/
		// �������ƣ� CombineActionParam
		// ���ܣ�   �����������ò���
		// ������   CXActionVirtual *pDstActionVir:
		// ����ֵ: 
		virtual void CombineActionParam(CXActionVirtual *pDstActionVir);
		/*******************************************************************************/
		// �������ƣ� CloneAction
		// ���ܣ�   ������������
		// ������   
		// ����ֵ: 
		virtual CXActionVirtual * CloneAction();
	public:
		inline  long GetValue_SceneRunTime() { return m_lSceneRunTime; };
		inline  void SetValue_SceneRunTime(long lTime) { m_lSceneRunTime = lTime; };
	protected:
		long               m_lSceneRunTime;     //�ű�����ʱ��
	};
}}
