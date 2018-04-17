#pragma once
#include <list>
#include <pugixml.hpp>
#include ".\scriptflowengine_global.h"

#include "..\SimulatorSymptom\XVirtualComponent.h"
#include "..\SimulatorSymptom\XActionVirtual.h"


namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     场景流程中的场景框解析类
	创建人：	 hjg
	创建时间：   2017/3/25
	//-----------------------------------------------------------------------------------------------------------------*/
    class SCRIPTFLOWENGINESHARED_EXPORT CXScenario : public simulator::CXVirtualComponent
	{
	public:
		CXScenario(void);
		virtual ~CXScenario(void);
	public:
		std::string                 m_strSceneType;               //InitialScenarioFrame:起始场景；ScenarioFrame:一般场景；SceneActFrame:情景框
		std::string                 m_strSceneName;               //场景名称
		std::string                 m_strSceneRemarks;            //场景备注
	public:
		std::list<simulator::CXActionVirtual *>  m_lstActions;
	public: //基函数重载
		virtual bool isKindOf(const std::string &strClassName);
	public:
		//解析场景框的所有体征及相关信息
		void ParseScenario(pugi::xml_node *pScenarioNode);
		//拷贝场景框内的所有体征
		void CopyActions(CXScenario *pSrcScenario);
		void EmptyActions();
		//返回当前场景设置的体征列表
		virtual void GetScenarioActions(std::list<simulator::CXActionVirtual *>* plstActions);
		//处理当前场景中的生理体征日志顺序的排列
		void DoActionsLogArrange();
	protected:
		//解析场景框的所有体征
		virtual void ParseActions(pugi::xml_node *pScenarioNode);
	};
}}
