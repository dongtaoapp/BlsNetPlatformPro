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
	类说明：     在场景流程中当前的执行位置框
	创建人：	 hjg
	创建时间：   2017/3/25
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
		pugi::xml_node         m_xmlScenarioFrameNode;     //当前场景位置
	public: //接口IGetPhysiologyActionObj函数重载
		//获取除颤设置属性
		virtual simulator::CXAction_Defibri * getAction_DefibriPtr();
		//获取场景框持续时间
		virtual simulator::CSymptom_FrameTime * getFrameTimeSymptomPtr();
	protected:
		//返回生理体征对象指针
		virtual simulator::CXActionVirtual  * getPhysiologyActionPtr(const std::string &strClassName);
	public:
		inline CXScenario * GetScenarioPtr() { return &m_cScenario; };
		void setSimulateSymptomsCollectPtr(simulator::CSimulateSymptomsCollect *pCollect);
	public:
		//解析启动场景
		pugi::xml_node parseStartScenario(pugi::xml_node *pxmlRootElement, int nStartScenarioId=0);
		//解析下个场景
		pugi::xml_node parseNextScenario(pugi::xml_node *pxmlRootElement, const std::string &strId, const std::string &strType);
		pugi::xml_node parseNextScenario(pugi::xml_node *pScenarioXMLNode);
		//组合生理体征
		void CombineCurrentActions(bool bEmptied);
		//组合生理体征
		void CombineCurrentActions(std::list<simulator::CXActionVirtual *> *plstVirActions);
		//清除当前的执行位置框
		void ClearRunFramework();
	public: 
		//返回脚本内容节点
		static pugi::xml_node getScenarioXMLDOMNodePtr(pugi::xml_node *pxmlRootElement);
		//查找指定的场景
		static pugi::xml_node searchFrameXMLDOMNodePtr(pugi::xml_node *pxmlRootElement, const std::string &strId, const std::string &strType);
	};
}}