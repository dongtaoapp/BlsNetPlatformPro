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
	//功能：清除所有情景框
	//参数：
	//返回值: 
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
	//功能：处理场景事件IRP函数
	//参数：
	//      CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
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
					//处理相关的情景体征
					if( m_pTransOrderIrpToUp != NULL )
					{
						eEventSign eEvent = pVirEventIrp->Get_EventSign();
						unsigned short dwFrameSignId = pSceneActRunOp->Get_SceneActFrameId();
						CFrameFlowIrp *pFrameFlowIrp = CFrameFlowIrp::CreateEventIrp_SceneActFlow(dwFrameSignId, eSceneState, eEvent);
						m_pTransOrderIrpToUp->OnTranslateUpIrp( pFrameFlowIrp );
					}
					//重新设置情景框为激活状态
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
	//功能：处理时钟事件IRP函数
	//参数：
	//      CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
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
					//处理相关的情景体征
					if( m_pTransOrderIrpToUp != NULL )
					{
						unsigned short dwFrameSignId = pSceneActRunOp->Get_SceneActFrameId();
						CFrameFlowIrp *pFrameFlowIrp = CFrameFlowIrp::CreateEventIrp_SceneActFlow(dwFrameSignId, eSceneState, ES_Normal);
						m_pTransOrderIrpToUp->OnTranslateUpIrp( pFrameFlowIrp );
					}
					//重新设置情景框为激活状态
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
	//功能：加载默认的情景框
	//参数：
	//      const CString &strUnzipCataloguePath：解压包目标路径
	//返回值:  
	void CSceneActsCollect::LoadDefaultSceneActsFile(const std::string &strUnzipCataloguePath)
	{

	}

	/*******************************************************************************/
	//功能：加载脚本内定义的情景框
	//参数：
	//      rootElement：
	//      pTransOrderIrpToUp:
	//返回值:
	void CSceneActsCollect::InitialScriptSceneActs(pugi::xml_node rootElement, IGetPhysiologyActionObj *pGetActionObj, transLayer::ITransportOrderIrpToUp *pTransOrderIrpToUp)
	{
		m_pTransOrderIrpToUp  = pTransOrderIrpToUp;
		//-------------------------------------------------------------------------
	}

	/*******************************************************************************/
	//功能：激活全局情景框
	//参数：
	//返回值: 
	void CSceneActsCollect::ActiveSceneActsRun()
	{
		m_lstActiveSceneActs.clear();
		//重新加载所有全局情景框
		BOOST_FOREACH(auto pSceneActRunOp, m_lstSceneActFrames)
		{
			//设置情景框为激活状态
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
