#include <algorithm>
#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include ".\ihandleirpscollect.h"


using namespace jysoft::irp;
namespace jysoft { namespace flowEngine 
{
	IHandleIrpsCollect::IHandleIrpsCollect(void)
	{
	}

	IHandleIrpsCollect::~IHandleIrpsCollect(void)
	{
	}

	//添加处理IRP的Obj
	void  IHandleIrpsCollect::addNewHandleIrpObj(CVirHandleIrpOp  *pPtrObj, _IrpType eType, bool bAddHead/*=FALSE*/)
	{
		m_cAddHandleIrpOpMutex.Lock();
		switch( eType )
		{
		case eClock_Event:
			{
				CEventHandleClockIrpOp  *pHandleClockIrpOp = (CEventHandleClockIrpOp  *)pPtrObj;
				if( pHandleClockIrpOp )
				{
					std::list<CEventHandleClockIrpOp *>::iterator pos;
					pos = std::find(m_lstHandleClockIrpObjs.begin(), m_lstHandleClockIrpObjs.end(), pHandleClockIrpOp);
					if(pos == m_lstHandleClockIrpObjs.end())
					{
						if( !bAddHead )
							m_lstHandleClockIrpObjs.push_back(pHandleClockIrpOp);
						else
							m_lstHandleClockIrpObjs.push_front(pHandleClockIrpOp);
					}
				}
				break;
			}
		case eABC_Event:
		case eDrug_Event:
		case eMisce_Event:
		case eOxygen_Event:
		case eSimulateTrigger_Event:
			{
				CEventHandleCustomIrpOp  *pHandleEventIrpOp = (CEventHandleCustomIrpOp  *)pPtrObj;
				if( pHandleEventIrpOp )
				{
					std::list<CEventHandleCustomIrpOp *>::iterator pos;
					pos = std::find(m_lstHandleEventIrpObjs.begin(), m_lstHandleEventIrpObjs.end(), pHandleEventIrpOp);
					if(pos == m_lstHandleEventIrpObjs.end())
					{
						if( !bAddHead )
							m_lstHandleEventIrpObjs.push_back(pHandleEventIrpOp);
						else
							m_lstHandleEventIrpObjs.push_front(pHandleEventIrpOp);
					}
				}
				break;
			}
		case eCPR_Stat:
			{
				CEventHandleCPRStatIrpOp  *pHandleCPRStatIrpOp = (CEventHandleCPRStatIrpOp  *)pPtrObj;
				if( pHandleCPRStatIrpOp )
				{
					std::list<CEventHandleCPRStatIrpOp *>::iterator pos;
					pos = std::find(m_lstHandleCPRStatIrpObjs.begin(), m_lstHandleCPRStatIrpObjs.end(), pHandleCPRStatIrpOp);
					if(pos == m_lstHandleCPRStatIrpObjs.end())
					{
						if( !bAddHead )
							m_lstHandleCPRStatIrpObjs.push_back(pHandleCPRStatIrpOp);
						else
							m_lstHandleCPRStatIrpObjs.push_front(pHandleCPRStatIrpOp);
					}
				}
				break;
			}
		case eFrameModify_Event:
			{
				CEventHandleFrameFlowIrpOp  *pHandleFrameFlowIrpOp = (CEventHandleFrameFlowIrpOp  *)pPtrObj;
				if( pHandleFrameFlowIrpOp )
				{
					std::list<CEventHandleFrameFlowIrpOp *>::iterator pos;
					pos = std::find(m_lstHandleFrameFlowIrpObjs.begin(), m_lstHandleFrameFlowIrpObjs.end(), pHandleFrameFlowIrpOp);
					if(pos == m_lstHandleFrameFlowIrpObjs.end() )
					{
						if( !bAddHead )
							m_lstHandleFrameFlowIrpObjs.push_back(pHandleFrameFlowIrpOp);
						else
							m_lstHandleFrameFlowIrpObjs.push_front(pHandleFrameFlowIrpOp);
					}
				}
				break;
			}
		case eAssist_Check:
			{
				/*CEventHandleAssistCheckIrpOp  *pHandleAssistCheckIrpOp = (CEventHandleAssistCheckIrpOp  *)pPtrObj;
				POSITION pos = m_lstHandleAssistCheckIrpObjs.Find(pHandleAssistCheckIrpOp);
				if(pos == NULL && pHandleAssistCheckIrpOp)
				{
					if( !bAddHead )
						m_lstHandleAssistCheckIrpObjs.AddTail(pHandleAssistCheckIrpOp);
					else
						m_lstHandleAssistCheckIrpObjs.AddHead(pHandleAssistCheckIrpOp);
				}*/
				break;
			}
		case eRealTimeData:
			{
				CRealTimeDataHandleIrpOp  *pHandleRealTimeDataIrpOp = (CRealTimeDataHandleIrpOp  *)pPtrObj;
				if( pHandleRealTimeDataIrpOp )
				{
					std::list<CRealTimeDataHandleIrpOp *>::iterator pos;
					pos = std::find(m_lstHandleRealTimeDataIrpObjs.begin(), m_lstHandleRealTimeDataIrpObjs.end(), pHandleRealTimeDataIrpOp);
					if(pos == m_lstHandleRealTimeDataIrpObjs.end())
					{
						if( !bAddHead )
							m_lstHandleRealTimeDataIrpObjs.push_back(pHandleRealTimeDataIrpOp);
						else
							m_lstHandleRealTimeDataIrpObjs.push_front(pHandleRealTimeDataIrpOp);
					}
				}
				break;
			}
		default:
			{
                BOOST_ASSERT( 0 );
				break;
			}
		}
		m_cAddHandleIrpOpMutex.Unlock();
	}

	//移除处理IRP的Obj
	void  IHandleIrpsCollect::removeHandleIrpObj(CVirHandleIrpOp  *pPtrObj, _IrpType eType)
	{
		m_cAddHandleIrpOpMutex.Lock();
		switch( eType )
		{
		case eClock_Event:
			{
				CEventHandleClockIrpOp  *pHandleClockIrpOp = (CEventHandleClockIrpOp  *)pPtrObj;
				m_lstHandleClockIrpObjs.remove(pHandleClockIrpOp);
				break;
			}
		case eABC_Event:
		case eOxygen_Event:
		case eDrug_Event:
		case eMisce_Event:
		case eSimulateTrigger_Event:
			{
				CEventHandleCustomIrpOp  *pHandleEventIrpOp = (CEventHandleCustomIrpOp  *)pPtrObj;
				m_lstHandleEventIrpObjs.remove(pHandleEventIrpOp);
				break;
			}
		case eCPR_Stat:
			{
				CEventHandleCPRStatIrpOp  *pHandleCPRStatIrpOp = (CEventHandleCPRStatIrpOp  *)pPtrObj;
				m_lstHandleCPRStatIrpObjs.remove(pHandleCPRStatIrpOp);
				break;
			}
		case eFrameModify_Event:
			{
				CEventHandleFrameFlowIrpOp  *pHandleFrameFlowIrpOp = (CEventHandleFrameFlowIrpOp  *)pPtrObj;
				m_lstHandleFrameFlowIrpObjs.remove(pHandleFrameFlowIrpOp);
				break;
			}
		case eAssist_Check:
			{
				/*CEventHandleAssistCheckIrpOp  *pHandleAssistCheckIrpOp = (CEventHandleAssistCheckIrpOp  *)pPtrObj;
				POSITION pos = m_lstHandleAssistCheckIrpObjs.Find( pHandleAssistCheckIrpOp );
				if(pos != NULL)
					m_lstHandleAssistCheckIrpObjs.RemoveAt(pos);*/
				break;
			}
		case eRealTimeData:
			{
				CRealTimeDataHandleIrpOp  *pHandleRealTimeDataIrpOp = (CRealTimeDataHandleIrpOp  *)pPtrObj;
				m_lstHandleRealTimeDataIrpObjs.remove(pHandleRealTimeDataIrpOp);
				break;
			}
		default:
			{
                BOOST_ASSERT( 0 );
				break;
			}
		}
		m_cAddHandleIrpOpMutex.Unlock();
	}


	void  IHandleIrpsCollect::addNewHandleEventIrpObj(CEventHandleCustomIrpOp *pPtrObj, bool bAddHead/*=FALSE*/)
	{
		m_cAddHandleIrpOpMutex.Lock();
		std::list<CEventHandleCustomIrpOp *>::iterator pos;
		pos = std::find(m_lstHandleEventIrpObjs.begin(), m_lstHandleEventIrpObjs.end(), pPtrObj);
		if(pos == m_lstHandleEventIrpObjs.end() && pPtrObj)
		{
			if( !bAddHead )
				m_lstHandleEventIrpObjs.push_back(pPtrObj);
			else
				m_lstHandleEventIrpObjs.push_front(pPtrObj);
		}
		m_cAddHandleIrpOpMutex.Unlock();
	}

	void  IHandleIrpsCollect::removeHandleEventIrpObj(CEventHandleCustomIrpOp *pPtrObj)
	{
		m_cAddHandleIrpOpMutex.Lock();
		m_lstHandleEventIrpObjs.remove(pPtrObj);
		m_cAddHandleIrpOpMutex.Unlock();
	}

	//处理消息包
	void IHandleIrpsCollect::OnHandleIrp(CVirtualIrp *pVirIrp)
	{
		bool        bStopHandle = false;
		m_cAddHandleIrpOpMutex.Lock();
		std::list<irp::CEventHandleClockIrpOp *>::iterator pos;
		pos = m_lstHandleClockIrpObjs.begin();
		while( pos != m_lstHandleClockIrpObjs.end() )
		{
			CEventHandleClockIrpOp *pClockIrpOp = *pos;
			if( pClockIrpOp->m_eIrpHandleState == IH_None )
			{
				if( !pClockIrpOp->handleIrpOp( pVirIrp ) )
				{
					//后续不处理
					bStopHandle  = true;
					break;
				}
				pos = m_lstHandleClockIrpObjs.begin();
			}
			else
			{
				++pos;
			}
		}
		//重置IRP状态
		BOOST_FOREACH(auto pClockIrpOp, m_lstHandleClockIrpObjs)
		{
			pClockIrpOp->m_eIrpHandleState = IH_None;
		}
		
		if( !bStopHandle )
		{
			std::list<irp::CEventHandleCPRStatIrpOp *>::iterator pos;
			pos = m_lstHandleCPRStatIrpObjs.begin();
			while( pos != m_lstHandleCPRStatIrpObjs.end() )
			{
				CEventHandleCPRStatIrpOp *pCPRStatIrpOp = *pos;
				if( pCPRStatIrpOp->m_eIrpHandleState == IH_None )
				{
					if( !pCPRStatIrpOp->handleIrpOp( pVirIrp ) )
					{
						//后续不处理
						bStopHandle  = true;
						break;
					}
					pos = m_lstHandleCPRStatIrpObjs.begin();
				}
				else
				{
					++pos;
				}
			}
			//重置IRP状态
			BOOST_FOREACH(auto pClockIrpOp, m_lstHandleCPRStatIrpObjs)
			{
				pClockIrpOp->m_eIrpHandleState = IH_None;
			}
		}
		//-------------------------------------------------------------------------------------------------------------------
		if( !bStopHandle )
		{
			std::list<irp::CEventHandleSimulateTriggerIrpOp *>::iterator pos;
			pos = m_lstHandleSimulateTriggerIrpObjs.begin();
			while(pos != m_lstHandleSimulateTriggerIrpObjs.end())
			{
				CEventHandleSimulateTriggerIrpOp * pSimulateTriggerIrpOp = *pos;
				if( pSimulateTriggerIrpOp->m_eIrpHandleState == IH_None )
				{
					if( !pSimulateTriggerIrpOp->handleIrpOp( pVirIrp ) )
					{
						//后续不处理
						bStopHandle  = true;
						break;
					}
					pos = m_lstHandleSimulateTriggerIrpObjs.begin();
				}
				else
				{
					++pos;
				}
			}
			//重置IRP状态
			BOOST_FOREACH(auto pSimulateTriggerIrpOp, m_lstHandleSimulateTriggerIrpObjs)
			{
				pSimulateTriggerIrpOp->m_eIrpHandleState = IH_None;
			}
		}
		if( !bStopHandle )
		{
			std::list<irp::CEventHandleCustomIrpOp *>::iterator pos;
			pos = m_lstHandleEventIrpObjs.begin();
			while( pos != m_lstHandleEventIrpObjs.end() )
			{
				CEventHandleCustomIrpOp *pCustomIrpOp = *pos;
				if( pCustomIrpOp->m_eIrpHandleState == IH_None )
				{
					if( !pCustomIrpOp->handleIrpOp( pVirIrp ) )
					{
						//后续不处理
						bStopHandle  = true;
						break;
					}
					pos = m_lstHandleEventIrpObjs.begin();
				}
				else
				{
					++pos;
				}
			}
			//重置IRP状态
			BOOST_FOREACH(auto pCustomIrpOp, m_lstHandleEventIrpObjs)
			{
				pCustomIrpOp->m_eIrpHandleState = IH_None;
			}
		}
		//-------------------------------------------------------------------------------------------------------------------
		if( !bStopHandle )
		{
			std::list<irp::CEventHandleFrameFlowIrpOp *>::iterator pos;
			pos = m_lstHandleFrameFlowIrpObjs.begin();
			while( pos != m_lstHandleFrameFlowIrpObjs.end() )
			{
				CEventHandleFrameFlowIrpOp *pFlowIrpOp = *pos;
				if( pFlowIrpOp->m_eIrpHandleState == IH_None )
				{
					if( !pFlowIrpOp->handleIrpOp( pVirIrp ) )
					{
						//后续不处理
						bStopHandle  = true;
						break;
					}
					pos = m_lstHandleFrameFlowIrpObjs.begin();
				}
				else
				{
					++pos;
				}
			}
			//重置IRP状态
			BOOST_FOREACH(auto pFlowIrpOp, m_lstHandleFrameFlowIrpObjs)
			{
				pFlowIrpOp->m_eIrpHandleState = IH_None;
			}
		}
		if( !bStopHandle )
		{
			std::list<irp::CRealTimeDataHandleIrpOp *>::iterator pos;
			pos = m_lstHandleRealTimeDataIrpObjs.begin();
			while( pos != m_lstHandleRealTimeDataIrpObjs.end() )
			{
				CRealTimeDataHandleIrpOp *pRealTimeHandleIrpOp = *pos;
				if( pRealTimeHandleIrpOp->m_eIrpHandleState == IH_None )
				{
					if( !pRealTimeHandleIrpOp->handleIrpOp( pVirIrp ) )
					{
						//后续不处理
						bStopHandle  = true;
						break;
					}
					pos = m_lstHandleRealTimeDataIrpObjs.begin();
				}
				else
				{
					++pos;
				}
			}
			//重置IRP状态
			BOOST_FOREACH(auto pRealTimeHandleIrpOp, m_lstHandleRealTimeDataIrpObjs)
			{
				pRealTimeHandleIrpOp->m_eIrpHandleState = IH_None;
			}
		}
		m_cAddHandleIrpOpMutex.Unlock();
	}

	void  IHandleIrpsCollect::addNewHandleOnlySimulateTriggerEventIrpOp(CEventHandleSimulateTriggerIrpOp *pPtrObj)
	{
		m_cAddHandleIrpOpMutex.Lock();
		if( pPtrObj )
		{
			std::list<irp::CEventHandleSimulateTriggerIrpOp *>::iterator pos;
			pos = std::find(m_lstHandleSimulateTriggerIrpObjs.begin(), m_lstHandleSimulateTriggerIrpObjs.end(), pPtrObj);
			if( pos == m_lstHandleSimulateTriggerIrpObjs.end() )
			{
				m_lstHandleSimulateTriggerIrpObjs.push_back(pPtrObj);
			}
		}
		m_cAddHandleIrpOpMutex.Unlock();
	}

	void  IHandleIrpsCollect::removeHandleOnlySimulateTriggerEventIrpOp(CEventHandleSimulateTriggerIrpOp *pPtrObj)
	{
		m_cAddHandleIrpOpMutex.Lock();
		m_lstHandleSimulateTriggerIrpObjs.remove(pPtrObj);
		m_cAddHandleIrpOpMutex.Unlock();
	}
}}
