#include <boost/foreach.hpp>
#include ".\xrunframework.h"

#include "..\SimulatorSymptom\XActionVirtual.h"


using namespace jysoft::simulator;
namespace jysoft { namespace flowEngine 
{
	CXRunFramework::CXRunFramework(void)
	{
		m_pSymptomsCollect    = NULL;
	}

	CXRunFramework::~CXRunFramework(void)
	{
		BOOST_FOREACH(auto x, m_lstActions)
		{
			delete x;
		}
	}

	//获取除颤设置属性
	simulator::CXAction_Defibri * CXRunFramework::getAction_DefibriPtr()
	{
		CXAction_Defibri  *pAction_Defibr = (CXAction_Defibri *)getPhysiologyActionPtr( "CXAction_Defibri" );
		return pAction_Defibr;
	}

	//返回生理体征对象指针
	CXActionVirtual  * CXRunFramework::getPhysiologyActionPtr(const std::string &strClassName)
	{
		CXActionVirtual *pDstActionVir = NULL;
		BOOST_FOREACH(auto pVirAction, m_lstActions)
		{
			if( pVirAction->isKindOf( strClassName ) )
			{
				pDstActionVir = pVirAction;
				break;
			}
		}
		return pDstActionVir;
	}	

	//获取场景框持续时间
	simulator::CSymptom_FrameTime * CXRunFramework::getFrameTimeSymptomPtr()
	{
		return m_pSymptomsCollect->GetFrameTimeSymptomPtr();
	}

	void CXRunFramework::setSimulateSymptomsCollectPtr(CSimulateSymptomsCollect *pCollect)
	{
		m_pSymptomsCollect  = pCollect;
	}

	//清除当前的执行位置框
	void CXRunFramework::ClearRunFramework()
	{
		m_cScenario.EmptyActions();

		BOOST_FOREACH(auto x, m_lstActions)
		{
			delete x;
		}
		m_lstActions.clear();
	}

	//解析启动场景
	//int nStartScenarioId: 启动场景的SignId值
	pugi::xml_node CXRunFramework::parseStartScenario(pugi::xml_node *pxmlRootElement, int nStartScenarioId/*=0*/)
	{
		pugi::xml_node  xmlScenarioNode;
		pugi::xml_node xmlScenarioRoot = CXRunFramework::getScenarioXMLDOMNodePtr( pxmlRootElement);
		if( !xmlScenarioRoot.empty() && std::string(xmlScenarioRoot.name()) == "scenario" )
		{
			for (pugi::xml_node_iterator it = xmlScenarioRoot.begin(); it != xmlScenarioRoot.end(); ++it)
			{
				if( std::string(it->name()) == "frame" )
				{
					//读取id属性值
					int  dwSignId = it->attribute("id").as_int(-2);
					if( dwSignId == nStartScenarioId )
					{
						std::string  attrValue = it->attribute("type").as_string();
						if( attrValue == "InitialScenarioFrame" )
						{
							xmlScenarioNode = *it;
							break;
						}
					}
				}
			}
		}
		//解析场景内的生理体征设置
		if( !xmlScenarioNode.empty() )
		{
			m_cScenario.ParseScenario( &xmlScenarioNode );
			m_xmlScenarioFrameNode = xmlScenarioNode;
		}
		return xmlScenarioNode;
	}

	//解析下个场景
	pugi::xml_node CXRunFramework::parseNextScenario(pugi::xml_node *pxmlRootElement, const std::string &strId, const std::string &strType)
	{
		pugi::xml_node xmlScenarioXMLNode = CXRunFramework::searchFrameXMLDOMNodePtr(pxmlRootElement, strId, strType);
		//解析场景内的生理体征设置
		return parseNextScenario( &xmlScenarioXMLNode );
	}

	pugi::xml_node CXRunFramework::parseNextScenario(pugi::xml_node *pScenarioXMLNode)
	{
		//解析场景内的生理体征设置
		if( pScenarioXMLNode && !pScenarioXMLNode->empty() )
		{
			m_cScenario.ParseScenario(pScenarioXMLNode);
			//设置当前的场景框
			m_xmlScenarioFrameNode = *pScenarioXMLNode;
		}
		return *pScenarioXMLNode;
	}

	//组合生理体征
	//参数：BOOL bEmptied: 是否清空CXScenario中的生理体征列表项
	void CXRunFramework::CombineCurrentActions(bool bEmptied)
	{
		std::list<CXActionVirtual *>  lstModifyActions;
		m_cScenario.GetScenarioActions( &lstModifyActions );
		BOOST_FOREACH(auto pActionVir, lstModifyActions)
		{
			bool  bFind = false;
			BOOST_FOREACH(auto pOldActionVir, m_lstActions)
			{
				if( pOldActionVir->getActionCaption() == pActionVir->getActionCaption() )
				{
					bFind = true;
					pOldActionVir->CombineActionParam( pActionVir );
					break;
				}
			}
			if( !bFind )
			{
				CXActionVirtual  *pCloneAction = pActionVir->CloneAction();
				m_lstActions.push_back( pCloneAction );
			}
		}
		if( bEmptied )
		{
			m_cScenario.EmptyActions();
		}
	}

	//组合生理体征
	void CXRunFramework::CombineCurrentActions(std::list<CXActionVirtual *> *plstVirActions)
	{
		BOOST_FOREACH(auto pActionVir, *plstVirActions)
		{
			bool  bFind = false;
			BOOST_FOREACH(auto pOldActionVir, m_lstActions)
			{
				if( pOldActionVir->getActionCaption() == pActionVir->getActionCaption() )
				{
					bFind = true;
					pOldActionVir->CombineActionParam( pActionVir );
					break;
				}
			}
			if( !bFind )
			{
				CXActionVirtual  *pCloneAction = pActionVir->CloneAction();
				m_lstActions.push_back( pCloneAction );
			}
		}
	}

	//查找指定的场景
	pugi::xml_node CXRunFramework::searchFrameXMLDOMNodePtr(pugi::xml_node *pxmlRootElement, const std::string &strId, const std::string &strType)
	{
		pugi::xml_node  xmlSearchFrameNode;
		pugi::xml_node xmlScenarioRoot = CXRunFramework::getScenarioXMLDOMNodePtr( pxmlRootElement);
		if( !xmlScenarioRoot.empty() )
		{
			for (pugi::xml_node_iterator it = xmlScenarioRoot.begin(); it != xmlScenarioRoot.end(); ++it)
			{
				std::string  elemFrame =  it->name();
				if( elemFrame == "frame" )
				{
					//id
					std::string  frameId = it->attribute("id").as_string();
					//type
					std::string  frameType = it->attribute("type").as_string();
					if( frameId == strId && frameType == strType )
					{
						xmlSearchFrameNode = *it;
						break;
					}
				}
			}
		}
		return xmlSearchFrameNode;
	}

	//返回脚本内容节点
	pugi::xml_node CXRunFramework::getScenarioXMLDOMNodePtr(pugi::xml_node *pxmlRootElement)
	{
		pugi::xml_node xmlScenarioRoot;
		for (xmlScenarioRoot = pxmlRootElement->first_child(); xmlScenarioRoot; xmlScenarioRoot = pxmlRootElement->next_sibling())
		{
			std::string  elemName = xmlScenarioRoot.name();
			if( elemName == "scenario" )
			{
				break;
			}
		}
		bool bEmpty = xmlScenarioRoot.empty();
		return xmlScenarioRoot;
	}
}}
