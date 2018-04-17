#include <boost/foreach.hpp>
#include ".\XSceneActFrame.h"
#include ".\ParseShapeFactory.h"

#include "..\simulatorSymptom\XActionVirtual.h"


using namespace jysoft::simulator;
namespace jysoft { namespace flowEngine 
{
	CXSceneActFrame::CXSceneActFrame(unsigned short dwFrameID)
	{
		m_dwFrameID      = dwFrameID;
		m_eActHandleType = SA_None;
		m_sDurationTime  = 0;
		m_pActEvent      = NULL;
		m_bExitFlow      = false;
	}

	CXSceneActFrame::~CXSceneActFrame(void)
	{
		if( m_pActEvent != NULL )
		{
			delete m_pActEvent;
		}
	}

	bool CXSceneActFrame::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXSceneActFrame" )
		{
			return true;
		}
		return CXScenario::isKindOf( strClassName );
	}

	//���ص�ǰ�������õ������б�
	void CXSceneActFrame::GetScenarioActions(std::list<simulator::CXActionVirtual *>* plstActions)
	{
		BOOST_FOREACH(auto pVirAction, m_lstActions)
		{
			plstActions->push_back( pVirAction );
		}
	}

	//�����龰������������������Ϣ
	void CXSceneActFrame::ParseSceneActFrame(pugi::xml_node *pScenarioNode, IGetPhysiologyActionObj *pGetActionObj)
	{
		//�����龰�����������
		ParseScenario( pScenarioNode );
		//�����¼�
		for (pugi::xml_node_iterator it = pScenarioNode->begin(); it != pScenarioNode->end(); ++it)
		{
			if( std::string(it->name()) == "actEvent" )
			{
				LoadActEventFromXML( &(*it), pGetActionObj );
				break;
			}
		}
	}

	void CXSceneActFrame::LoadActEventFromXML(pugi::xml_node *pXMLActChild, IGetPhysiologyActionObj *pGetActionObj)
	{
		;
	}

	//���������������������������CXAction_FrameTime� hjg 2014.2.28 add
	void CXSceneActFrame::ParseActions(pugi::xml_node *pScenarioNode)
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
	}

	/*******************************************************************************/
	//���ܣ������¼�IRP�����麯��
	//������
	//      CVirEventIrp *pCurrEventIrp��
	//      /*out*/_ScheduleSceneState &eSceneState:    
	//����ֵ:  �����¼��Ƿ�����(TURE:���㣻FALSE:������)
	bool CXSceneActFrame::DoHandleEventIrp(irp::CVirEventIrp *pCurrEventIrp, /*out*/_ScheduleSceneState &eSceneState)
	{
		if( m_pActEvent != NULL )
		{
			m_pActEvent->DoHandleEventIrp( pCurrEventIrp );
			if( m_pActEvent->IsSatisfactionEvent() )
			{
				if( m_eActHandleType == SA_Occur )
				{
					eSceneState = m_bExitFlow ? DSS_Logouted : DSS_SceneActSchedule;
					return true;
				}
				else if( m_eActHandleType == SA_UnoccurDurationTime )
				{
					m_sActTime = -1;
				}
				else if( m_sActTime == -1 )
				{
					m_sActTime = 0;
				}
			}
		}
		return false;
	}

	/*******************************************************************************/
	//���ܣ�����ʱ���¼�IRP����
	//������
	//      CVirtualIrp *pCurrIrp��
	//����ֵ:  �������ٴ���FALSE);
	bool CXSceneActFrame::DoHandleClockIrpOp(irp::CEventIrp_ClockTime *pCurrClockTimeIrp, /*out*/_ScheduleSceneState &eSceneState)
	{
		if( m_pActEvent != NULL && m_sActTime > -1 )
		{
			m_sActTime += pCurrClockTimeIrp->GetValue_ClockEvent();
			if( m_sActTime > m_sDurationTime )
			{
				eSceneState = m_bExitFlow ? DSS_Logouted : DSS_SceneActSchedule;
				return true;
			}
		}
		return false;
	}

	/*******************************************************************************/
	//���ܣ������龰��Ĵ���״̬
	//������   
	//      BOOL bReactive:     �Ƿ����¼���
	//����ֵ: 
	void CXSceneActFrame::DoStateActiveSceneFrame(bool bReactive)
	{
		if( m_pActEvent != NULL )
		{
			//����¼�������صļ�¼��Ϣ
			m_pActEvent->ClearSatisfactionInfo();
		}
		switch ( m_eActHandleType )
		{
		case SA_Occur:
		case SA_StipulatedTimeRear:
			{
				m_sActTime  = -1;
				break;
			}
		case SA_UnoccurDurationTime:
			{
				m_sActTime = !bReactive ? 0 : -1;
				break;
			}
		}
	}
}}
