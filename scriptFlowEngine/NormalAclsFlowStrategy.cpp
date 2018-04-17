#include <boost/foreach.hpp>
#include ".\normalaclsflowstrategy.h"
#include ".\XLineLinkScenarioObj.h"


namespace jysoft { namespace flowEngine 
{
	CNormalAclsFlowStrategy::CNormalAclsFlowStrategy(transLayer::ITransportOrderIrpToUp *pTransportUpInterface, pugi::xml_node *pxmlRootElement, IHandleIrpsCollect *pHandleIrpsCollect, IGetPhysiologyActionObj *pGetActionObj)
							 : IAclsFlowStrategy(pxmlRootElement, pHandleIrpsCollect, pGetActionObj)
	{
		m_pTransportUpInterface  =  pTransportUpInterface;
	}

	CNormalAclsFlowStrategy::~CNormalAclsFlowStrategy(void)
	{
	}

	/*******************************************************************************/
	//功能：根据策略，驱动场景
	//参数：
	//      IXMLDOMNode *pFrameElement：
	//      eEventSign eEvent:
	//返回值:  后续不再处理事件（FALSE);
	bool CNormalAclsFlowStrategy::OnFlowStrategy(pugi::xml_node *pFrameElement, eEventSign eEvent/*=ES_Normal*/)
	{
		bool   bContinueHandleEvent = true;
		CreateLineLinks( pFrameElement );
		//根据策略选择满足转移条件的下个场景
		CXLineLinkScenarioObj *pSelScenarioLineLink = SelectNextScenarioFromStrategy();
		if( pSelScenarioLineLink )
		{
			//创建场景框选择Irp
			irp::CFrameFlowIrp  *pFlowIrp  = pSelScenarioLineLink->GetFrameFlowIrp( eEvent );
			//将Irp发送到通信层
			if( m_pTransportUpInterface != NULL )
			{
				m_pTransportUpInterface->OnTranslateUpIrp( pFlowIrp );
			}
			bContinueHandleEvent = false;
		}
		else
		{
			if( m_lstLineLinks.size() != 0 )
			{
				bContinueHandleEvent = true;
			}
		}
		//清空被删除的连接
		EmptyDeletedLineLinks();
		return bContinueHandleEvent;
	}

	//根据策略选择满足转移条件的下个场景
	CXLineLinkScenarioObj * CNormalAclsFlowStrategy::SelectNextScenarioFromStrategy()
	{
		std::list<CXLineLinkScenarioObj *> lstLineLinkScenarioes;
		BOOST_FOREACH(auto pVirLink, m_lstLineLinks)
		{
			if( pVirLink->isKindOf( "CXLineLinkScenarioObj" ) )
			{
				CXLineLinkScenarioObj  *pLineLinkScenario = (CXLineLinkScenarioObj *)pVirLink;
				lstLineLinkScenarioes.push_back( pLineLinkScenario );
			}
		}
		//随即选择下个场景
		CXLineLinkScenarioObj   *pNextScenarioAim = NULL;
		int  nLinkCount = lstLineLinkScenarioes.size();
		if( nLinkCount > 0 )
		{
			srand( (unsigned)time( NULL ) );
			int nSel = rand() % nLinkCount;
			BOOST_FOREACH(auto x, lstLineLinkScenarioes)
			{
				--nSel;
				if( nSel < 0 )
				{
					pNextScenarioAim = x;
				}
			}
		}
		return pNextScenarioAim;
	}
}}
