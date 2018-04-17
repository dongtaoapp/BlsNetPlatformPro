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
		//����������������
		for (pugi::xml_node_iterator it = pScenarioNode->begin(); it != pScenarioNode->end(); ++it)
		{
			std::string  nodeName( it->name() );
			if( nodeName == "actions" )
			{
				for (pugi::xml_node_iterator actionNode = it->begin(); actionNode != it->end(); ++actionNode)
				{
					//������Ӧ����������
					std::list<CXActionVirtual *>  lstActions;
					CParseShapeFactory::get_const_instance().ParseActionObject(&(*actionNode), &lstActions);
					//��ӵ������б���
					BOOST_FOREACH(auto pVirAction, lstActions)
					{
						m_lstActions.push_back( pVirAction );
					}
				}
				break;
			}
		}
		//��ӳ���ʱ��Action
		CXAction_FrameTime   *pAction_FrameTime = new CXAction_FrameTime();
		m_lstActions.push_back( pAction_FrameTime );
	}

	//��������������������������Ϣ
	void CXScenario::ParseScenario(pugi::xml_node *pScenarioNode)
	{
		//����������������Ϣ
		m_strSceneType = pScenarioNode->attribute("type").as_string();

		//�������������������
		ParseActions( pScenarioNode );
	}

	//�����������ڵ���������
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

	//����ǰ�����е�����������־˳�������
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

	//���ص�ǰ�������õ������б�
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
