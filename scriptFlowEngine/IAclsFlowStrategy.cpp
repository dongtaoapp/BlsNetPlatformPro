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
		//��ձ�ɾ��������
		EmptyDeletedLineLinks();
	}

	//���ؽű����ݽڵ�
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

	//�������������Ӷ���
	CXLineLink * IAclsFlowStrategy::CreateLineLink(pugi::xml_node *pLinkNodePtr)
	{
		pugi::xml_node    xmlScenarioRoot = getScenarioXMLDOMNodePtr();
        BOOST_ASSERT(!xmlScenarioRoot.empty());
		
		CXLineLink*        pLineLink = NULL;
		//�������ӵ����ͼ�Ŀ�����
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
		//����Ŀ�����
		if( pLineLink && !pLineLink->InitialLineLink(strObjId, &xmlScenarioRoot, this))
		{
			delete pLineLink;
			pLineLink  = NULL;
		}
		return pLineLink; 
	}

	//��ձ�ɾ��������
	void IAclsFlowStrategy::EmptyDeletedLineLinks()
	{
        foreach(auto x, m_lstDeletedLineLinks)
		{
			delete x;
		}
		m_lstDeletedLineLinks.clear();
	}

	//ɾ���������ɵ����Ӷ���
	void IAclsFlowStrategy::DeleteAllLineLinks()
	{
        foreach(auto pVirtualLink, m_lstLineLinks)
		{
			//�Ƴ����Ӷ��󣬲�����Irp
			pVirtualLink->RemoveLinkObjFromHandleIrpCollect(m_pHandleIrpsCollect);
			//���뵽��ʱ����
			m_lstDeletedLineLinks.push_back( pVirtualLink );
		}
		m_lstLineLinks.clear();
	}

	void IAclsFlowStrategy::CreateLineLinks(pugi::xml_node *pFrameElement)
	{
		//ɾ���������ɵ����Ӷ���
		DeleteAllLineLinks();
		//�������ӽӵ�
		pugi::xml_node  linksNode = pFrameElement->child("links");
		if( !linksNode.empty() )
		{
			for (pugi::xml_node_iterator it = linksNode.begin(); it != linksNode.end(); ++it)
			{
				CXVirtualLink *pNewLineLink = NULL;
				if( it->name() == "link" )
				{
					//ֱ������
					pNewLineLink = CreateLineLink( &(*it) );
				}
				if( pNewLineLink != NULL )
				{
					//���Irp���������
					pNewLineLink->AddLinkObjToHandleIrpCollect( m_pHandleIrpsCollect );
					//���Irp���������
					m_lstLineLinks.push_back( pNewLineLink );
				}
			}
		}
	}
}}
