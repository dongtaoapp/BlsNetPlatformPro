#include <algorithm>
#include <boost/foreach.hpp>
#include ".\xscenario.h"
#include ".\ParseShapeFactory.h"

#include "..\SimulatorSymptom\XAction_FrameTime.h"



using namespace jysoft::simulator;
namespace jysoft { namespace flowEngine 
{
	CXScenario::CXScenario(void)
	{
	}

	CXScenario::~CXScenario(void)
	{
		BOOST_FOREACH(auto x, m_lstActions)
		{
			delete x;
		}
	}

	bool CXScenario::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXScenario" )
		{
			return true;
		}
		return false;
	}

	void CXScenario::ParseActions(pugi::xml_node *pScenarioNode)
	{
		BOOST_FOREACH(auto x, m_lstActions)
		{
			delete x;
		}
		m_lstActions.clear();
		//---------------------------------------------------------------------
		//解析生理体征参数
		for (pugi::xml_node_iterator it = pScenarioNode->begin(); it != pScenarioNode->end(); ++it)
		{
			std::string  nodeName( it->name() );
			if( nodeName == "actions" )
			{
				for (pugi::xml_node_iterator actionNode = it->begin(); actionNode != it->end(); ++actionNode)
				{
					//解析对应的生理体征
					std::list<CXActionVirtual *>  lstActions;
					CParseShapeFactory::get_const_instance().ParseActionObject(&(*actionNode), &lstActions);
					//添加到属性列表中
					BOOST_FOREACH(auto pVirAction, lstActions)
					{
						m_lstActions.push_back( pVirAction );
					}
				}
				break;
			}
		}
		//添加场景时间Action
		CXAction_FrameTime   *pAction_FrameTime = new CXAction_FrameTime();
		m_lstActions.push_back( pAction_FrameTime );
	}

	//解析场景框的所有体征及相关信息
	void CXScenario::ParseScenario(pugi::xml_node *pScenarioNode)
	{
		//解析场景框的相关信息
		m_strSceneType = pScenarioNode->attribute("type").as_string();

		//解析场景框的所有体征
		ParseActions( pScenarioNode );
	}

	//拷贝场景框内的所有体征
	void CXScenario::CopyActions(CXScenario *pSrcScenario)
	{
		std::list<CXActionVirtual *>  lstActions;
		pSrcScenario->GetScenarioActions( &lstActions );
	
		BOOST_FOREACH(auto pVirAction, lstActions)
		{
			CXActionVirtual *pCloneAction = pVirAction->CloneAction();
			m_lstActions.push_back( pCloneAction );
		}
	}

	//处理当前场景中的生理体征日志顺序的排列
	void CXScenario::DoActionsLogArrange()
	{

	}

	void CXScenario::EmptyActions()
	{
		BOOST_FOREACH(auto pVirAction, m_lstActions)
		{
			delete pVirAction;
		}
		m_lstActions.clear();
	}

	//返回当前场景设置的体征列表
	void CXScenario::GetScenarioActions(std::list<CXActionVirtual *> *plstActions)
	{
		BOOST_FOREACH(auto pVirAction, m_lstActions)
		{
			if( !pVirAction->isKindOf( "CXAction_Trendset" ) )
			{
				plstActions->push_back( pVirAction );
			}
		}
	}
}}
