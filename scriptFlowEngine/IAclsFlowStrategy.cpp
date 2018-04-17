#include <algorithm>
#include <boost/assert.hpp>
#include ".\XLineLink.h"
#include ".\iaclsflowstrategy.h"
#include ".\XLineLinkEventObj.h"
#include ".\XLineLinkScenarioObj.h"


namespace jysoft { namespace flowEngine 
{
	IAclsFlowStrategy::IAclsFlowStrategy(pugi::xml_node *pxmlRootElement, IHandleIrpsCollect *pHandleIrpsCollect, IGetPhysiologyActionObj *pGetActionObj)
	{
		m_xmlRootElement       = *pxmlRootElement;
		m_pHandleIrpsCollect = pHandleIrpsCollect;
		m_pGetPhysiologyActionObj  = pGetActionObj;
	}

	IAclsFlowStrategy::~IAclsFlowStrategy(void)
	{
        foreach(auto x, m_lstLineLinks)
		{
			delete x;
		}
		//清空被删除的连接
		EmptyDeletedLineLinks();
	}

	//返回脚本内容节点
	pugi::xml_node IAclsFlowStrategy::getScenarioXMLDOMNodePtr()
	{
		 pugi::xml_node xmlScenarioRoot;
		 if( !m_xmlRootElement.empty() )
		 {
			 for (pugi::xml_node_iterator it = m_xmlRootElement.begin(); it != m_xmlRootElement.end(); ++it)
			 {
				 if( it->name() == "scenario" )
				 {
					 xmlScenarioRoot = *it;
					 break;
				 }
			 }
		 }
		 return xmlScenarioRoot;
	}

	//生成无条件连接对象
	CXLineLink * IAclsFlowStrategy::CreateLineLink(pugi::xml_node *pLinkNodePtr)
	{
		pugi::xml_node    xmlScenarioRoot = getScenarioXMLDOMNodePtr();
        BOOST_ASSERT(!xmlScenarioRoot.empty());
		
		CXLineLink*        pLineLink = NULL;
		//解析连接的类型及目标对象
		std::string  strAimType = pLinkNodePtr->attribute("aim-Type").as_string();
		std::string  strObjId = pLinkNodePtr->attribute("link-ObjId").as_string();
        if( strAimType == "event-Frame" )
		{
			pLineLink = new CXLineLinkEventObj( );
		}
        else if( strAimType == "frame" )
		{
			pLineLink = new CXLineLinkScenarioObj( );
		}
		//解析目标对象
		if( pLineLink && !pLineLink->InitialLineLink(strObjId, &xmlScenarioRoot, this))
		{
			delete pLineLink;
			pLineLink  = NULL;
		}
		return pLineLink; 
	}

	//清空被删除的连接
	void IAclsFlowStrategy::EmptyDeletedLineLinks()
	{
        foreach(auto x, m_lstDeletedLineLinks)
		{
			delete x;
		}
		m_lstDeletedLineLinks.clear();
	}

	//删除所有生成的连接对象
	void IAclsFlowStrategy::DeleteAllLineLinks()
	{
        foreach(auto pVirtualLink, m_lstLineLinks)
		{
			//移除连接对象，不处理Irp
			pVirtualLink->RemoveLinkObjFromHandleIrpCollect(m_pHandleIrpsCollect);
			//加入到临时队列
			m_lstDeletedLineLinks.push_back( pVirtualLink );
		}
		m_lstLineLinks.clear();
	}

	void IAclsFlowStrategy::CreateLineLinks(pugi::xml_node *pFrameElement)
	{
		//删除所有生成的连接对象
		DeleteAllLineLinks();
		//查找连接接点
		pugi::xml_node  linksNode = pFrameElement->child("links");
		if( !linksNode.empty() )
		{
			for (pugi::xml_node_iterator it = linksNode.begin(); it != linksNode.end(); ++it)
			{
				CXVirtualLink *pNewLineLink = NULL;
				if( it->name() == "link" )
				{
					//直接连接
					pNewLineLink = CreateLineLink( &(*it) );
				}
				if( pNewLineLink != NULL )
				{
					//添加Irp处理队列中
					pNewLineLink->AddLinkObjToHandleIrpCollect( m_pHandleIrpsCollect );
					//添加Irp处理队列中
					m_lstLineLinks.push_back( pNewLineLink );
				}
			}
		}
	}
}}
