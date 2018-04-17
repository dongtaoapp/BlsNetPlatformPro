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
	//���ܣ����ݲ��ԣ���������
	//������
	//      IXMLDOMNode *pFrameElement��
	//      eEventSign eEvent:
	//����ֵ:  �������ٴ����¼���FALSE);
	bool CNormalAclsFlowStrategy::OnFlowStrategy(pugi::xml_node *pFrameElement, eEventSign eEvent/*=ES_Normal*/)
	{
		bool   bContinueHandleEvent = true;
		CreateLineLinks( pFrameElement );
		//���ݲ���ѡ������ת���������¸�����
		CXLineLinkScenarioObj *pSelScenarioLineLink = SelectNextScenarioFromStrategy();
		if( pSelScenarioLineLink )
		{
			//����������ѡ��Irp
			irp::CFrameFlowIrp  *pFlowIrp  = pSelScenarioLineLink->GetFrameFlowIrp( eEvent );
			//��Irp���͵�ͨ�Ų�
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
		//��ձ�ɾ��������
		EmptyDeletedLineLinks();
		return bContinueHandleEvent;
	}

	//���ݲ���ѡ������ת���������¸�����
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
		//�漴ѡ���¸�����
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
