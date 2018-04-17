#pragma once
#include <list>
#include <pugixml.hpp>
#include ".\scriptflowengine_global.h"

#include "..\SimulatorSymptom\XVirtualComponent.h"
#include "..\SimulatorSymptom\XActionVirtual.h"


namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ���������еĳ����������
	�����ˣ�	 hjg
	����ʱ�䣺   2017/3/25
	//-----------------------------------------------------------------------------------------------------------------*/
    class SCRIPTFLOWENGINESHARED_EXPORT CXScenario : public simulator::CXVirtualComponent
	{
	public:
		CXScenario(void);
		virtual ~CXScenario(void);
	public:
		std::string                 m_strSceneType;               //InitialScenarioFrame:��ʼ������ScenarioFrame:һ�㳡����SceneActFrame:�龰��
		std::string                 m_strSceneName;               //��������
		std::string                 m_strSceneRemarks;            //������ע
	public:
		std::list<simulator::CXActionVirtual *>  m_lstActions;
	public: //����������
		virtual bool isKindOf(const std::string &strClassName);
	public:
		//��������������������������Ϣ
		void ParseScenario(pugi::xml_node *pScenarioNode);
		//�����������ڵ���������
		void CopyActions(CXScenario *pSrcScenario);
		void EmptyActions();
		//���ص�ǰ�������õ������б�
		virtual void GetScenarioActions(std::list<simulator::CXActionVirtual *>* plstActions);
		//����ǰ�����е�����������־˳�������
		void DoActionsLogArrange();
	protected:
		//�������������������
		virtual void ParseActions(pugi::xml_node *pScenarioNode);
	};
}}
