#include <boost/foreach.hpp>
#include ".\SceneActsCollect.h"

#include "..\SimulatorBase\FrameFlowIrp.h"


using namespace jysoft::irp;
namespace jysoft { namespace flowEngine 
{
	CSceneActsCollect::CSceneActsCollect()
	{
		m_pTransOrderIrpToUp = NULL;
	}

	CSceneActsCollect::~CSceneActsCollect(void)
	{
		BOOST_FOREACH(auto x, m_lstSceneActFrames)
		{
			delete x;
		}
	}

	/*******************************************************************************/
	//���ܣ���������龰��
	//������
	//����ֵ: 
	void CSceneActsCollect::ClearSceneActs()
	{
		BOOST_FOREACH(auto x, m_lstSceneActFrames)
		{
			delete x;
		}
		m_lstActiveSceneActs.clear();
		m_pTransOrderIrpToUp  = NULL;
	}

	/*******************************************************************************/
	//���ܣ��������¼�IRP����
	//������
	//      CVirtualIrp *pCurrIrp��
	//����ֵ:  �������ٴ���FALSE);
	bool CSceneActsCollect::doHandleCustomEventIrpOp(CVirtualIrp *pCurrIrp)
	{
        if( pCurrIrp && pCurrIrp->isKindOf("CVirEventIrp") )
		{
			CVirEventIrp *pVirEventIrp = (CVirEventIrp *)pCurrIrp;
			//-----------------------------------------------------------------------------------------
			BOOST_FOREACH(auto pSceneActRunOp, m_lstActiveSceneActs)
			{
				_ScheduleSceneState    eSceneState;
				if( pSceneActRunOp->DoHandleEventIrp(pVirEventIrp, /*out*/eSceneState) )
				{
					//������ص��龰����
					if( m_pTransOrderIrpToUp != NULL )
					{
						eEventSign eEvent = pVirEventIrp->Get_EventSign();
						unsigned short dwFrameSignId = pSceneActRunOp->Get_SceneActFrameId();
						CFrameFlowIrp *pFrameFlowIrp = CFrameFlowIrp::CreateEventIrp_SceneActFlow(dwFrameSignId, eSceneState, eEvent);
						m_pTransOrderIrpToUp->OnTranslateUpIrp( pFrameFlowIrp );
					}
					//���������龰��Ϊ����״̬
					pSceneActRunOp->DoStateActiveSceneFrame( true );
					if( eSceneState == DSS_Logouted )
					{
						return false;
					}
				}
			}
		}
		return true;
	}

	/*******************************************************************************/
	//���ܣ�����ʱ���¼�IRP����
	//������
	//      CVirtualIrp *pCurrIrp��
	//����ֵ:  �������ٴ���FALSE);
	bool CSceneActsCollect::doHandleClockIrpOp(CVirtualIrp *pCurrIrp)
	{
        if( pCurrIrp && pCurrIrp->isKindOf( "CEventIrp_ClockTime" ) )
		{
			CEventIrp_ClockTime *pClockTimeIrp = (CEventIrp_ClockTime *)pCurrIrp;
			//-----------------------------------------------------------------------------------------
			BOOST_FOREACH(auto pSceneActRunOp, m_lstActiveSceneActs)
			{
				_ScheduleSceneState    eSceneState;
				if( pSceneActRunOp->DoHandleClockIrpOp(pClockTimeIrp, /*out*/eSceneState) )
				{
					//������ص��龰����
					if( m_pTransOrderIrpToUp != NULL )
					{
						unsigned short dwFrameSignId = pSceneActRunOp->Get_SceneActFrameId();
						CFrameFlowIrp *pFrameFlowIrp = CFrameFlowIrp::CreateEventIrp_SceneActFlow(dwFrameSignId, eSceneState, ES_Normal);
						m_pTransOrderIrpToUp->OnTranslateUpIrp( pFrameFlowIrp );
					}
					//���������龰��Ϊ����״̬
                    pSceneActRunOp->DoStateActiveSceneFrame( true );
					if( eSceneState == DSS_Logouted )
					{
						return false;
					}
				}
			}
		}
		return true;
	}

	/*******************************************************************************/
	//���ܣ�����Ĭ�ϵ��龰��
	//������
	//      const CString &strUnzipCataloguePath����ѹ��Ŀ��·��
	//����ֵ:  
	void CSceneActsCollect::LoadDefaultSceneActsFile(const std::string &strUnzipCataloguePath)
	{

	}

	/*******************************************************************************/
	//���ܣ����ؽű��ڶ�����龰��
	//������
	//      rootElement��
	//      pTransOrderIrpToUp:
	//����ֵ:
	void CSceneActsCollect::InitialScriptSceneActs(pugi::xml_node rootElement, IGetPhysiologyActionObj *pGetActionObj, transLayer::ITransportOrderIrpToUp *pTransOrderIrpToUp)
	{
		m_pTransOrderIrpToUp  = pTransOrderIrpToUp;
		//-------------------------------------------------------------------------
	}

	/*******************************************************************************/
	//���ܣ�����ȫ���龰��
	//������
	//����ֵ: 
	void CSceneActsCollect::ActiveSceneActsRun()
	{
		m_lstActiveSceneActs.clear();
		//���¼�������ȫ���龰��
		BOOST_FOREACH(auto pSceneActRunOp, m_lstSceneActFrames)
		{
			//�����龰��Ϊ����״̬
			pSceneActRunOp->DoStateActiveSceneFrame( false );
			m_lstActiveSceneActs.push_back( pSceneActRunOp );
		}
	}

	CXSceneActFrame * CSceneActsCollect::SearchSceneActFramePtr(unsigned short dwSignID)
	{
		BOOST_FOREACH(auto pSceneActFrame, m_lstSceneActFrames)
		{
			if( pSceneActFrame->Get_SceneActFrameId() == dwSignID )
			{
				return pSceneActFrame;
			}
		}
		return NULL;
	}
}}
