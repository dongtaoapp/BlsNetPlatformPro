#pragma once
#include <list>
#include <pugixml.hpp>
#include ".\IGetPhysiologyActionObj.h"
#include ".\XScenario.h"

#include "..\Common\CommonGlobal.h"
#include "..\Common\EventHandleClockIrpOp.h"

#include "..\SimulatorSymptom\XActionVirtual.h"
#include "..\SimulatorSymptom\SimulateSymptomsCollect.h"


namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �ڳ��������е�ǰ��ִ��λ�ÿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2017/3/25
	//-----------------------------------------------------------------------------------------------------------------*/
	class CXRunFramework : public IGetPhysiologyActionObj
	{
	public:
		CXRunFramework(void);
		virtual ~CXRunFramework(void);
	protected:
		std::list<simulator::CXActionVirtual *>   m_lstActions;
		CXScenario                     m_cScenario;
		simulator::CSimulateSymptomsCollect*      m_pSymptomsCollect;
	private:
		pugi::xml_node         m_xmlScenarioFrameNode;     //��ǰ����λ��
	public: //�ӿ�IGetPhysiologyActionObj��������
		//��ȡ������������
		virtual simulator::CXAction_Defibri * getAction_DefibriPtr();
		//��ȡ���������ʱ��
		virtual simulator::CSymptom_FrameTime * getFrameTimeSymptomPtr();
	protected:
		//����������������ָ��
		virtual simulator::CXActionVirtual  * getPhysiologyActionPtr(const std::string &strClassName);
	public:
		inline CXScenario * GetScenarioPtr() { return &m_cScenario; };
		void setSimulateSymptomsCollectPtr(simulator::CSimulateSymptomsCollect *pCollect);
	public:
		//������������
		pugi::xml_node parseStartScenario(pugi::xml_node *pxmlRootElement, int nStartScenarioId=0);
		//�����¸�����
		pugi::xml_node parseNextScenario(pugi::xml_node *pxmlRootElement, const std::string &strId, const std::string &strType);
		pugi::xml_node parseNextScenario(pugi::xml_node *pScenarioXMLNode);
		//�����������
		void CombineCurrentActions(bool bEmptied);
		//�����������
		void CombineCurrentActions(std::list<simulator::CXActionVirtual *> *plstVirActions);
		//�����ǰ��ִ��λ�ÿ�
		void ClearRunFramework();
	public: 
		//���ؽű����ݽڵ�
		static pugi::xml_node getScenarioXMLDOMNodePtr(pugi::xml_node *pxmlRootElement);
		//����ָ���ĳ���
		static pugi::xml_node searchFrameXMLDOMNodePtr(pugi::xml_node *pxmlRootElement, const std::string &strId, const std::string &strType);
	};
}}