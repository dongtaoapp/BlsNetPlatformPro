#include ".\BlsMainFlowVirtual.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>
#include ".\XSceneActFrame.h"
#include ".\blsmainflowvirtual.h"
#include ".\BlsSimulateCase.h"

#include "..\Common\DecodeUtil.h"

#include "..\elementParse\SEvent_Intubate.h"

#include "..\SimulatorBase\SimulatorOrderIrp.h"
#include "..\SimulatorBase\EventIrp_ClockTime.h"
#include "..\SimulatorBase\CPRStatIrp.h"

#include "..\SimulatorSymptom\Symptom_FrameTime.h"

#include "crtdbg.h"
inline void enableMemLeakCheck()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

using namespace jysoft::irp;
using namespace jysoft::simulator;
using namespace jysoft::simulator::base;
namespace jysoft { namespace flowEngine 
{
	//时钟线程函数
	void  CBlsMainFlowVirtual::_ThrdTimeFunc()
	{
		enableMemLeakCheck();
		//时钟加一秒
		CEventIrp_ClockTime  *pClockIrp = CEventIrp_ClockTime::CreateEvent_ClockIrp();
		if( m_pFormatTransport != NULL )
		{
			m_pFormatTransport->DecreaseFilterTransUpIrpTime( 1 );
		}
		boost::mutex::scoped_lock lock(muPackage);
		AddNeedHandleIrp( pClockIrp );
	}

	//从下端接收信息包
	void CBlsMainFlowVirtual::_ThrdReceiveIrpFunc()
	{
		try
		{
			while(1)
			{
				{
					boost::mutex::scoped_lock lock(muPackage);
					cond_IrpRecv.wait(lock, boost::bind(&CBlsMainFlowVirtual::isTransInUpIrps, this));
					//获取新的处理包
					CVirtualIrp *pVirIrp = m_pFormatTransport->TransportIrpInUplst();
					AddNeedHandleIrp( pVirIrp );
				}
				boost::this_thread::interruption_point();
			}
		}
		catch (boost::thread_interrupted &)
		{
			//std::cout << "interrupt irp handle" << std::endl;
		}
	}
	//消息包处理线程
	void CBlsMainFlowVirtual::_ThrdHandleIrpFunc()
	{
		try
		{
			while(1)
			{
				CVirtualIrp *pCurrIrp = NULL;
				{
					boost::mutex::scoped_lock lock(muPackage);
					cond_IrpHandle.wait(lock, boost::bind(&CBlsMainFlowVirtual::isCanPackageHandle, this));
					//先进先出处理接收包, 获取第一个包
					if( m_IrpList.size() > 0 )
					{
						pCurrIrp = *m_IrpList.begin();
						m_IrpList.pop_front();
					}
				}
				boost::this_thread::interruption_point();
				if( pCurrIrp != NULL )
				{
					OnHandleIrp( pCurrIrp );
					delete pCurrIrp;
				}
				boost::this_thread::interruption_point();
			}
		}
		catch (boost::thread_interrupted &)
		{
			;
		}
	}

	CBlsMainFlowVirtual::CBlsMainFlowVirtual(CBlsSimulateCase  *pSimulateCase, transLayer::CFormatTransport* pTransport)
	{
		m_pBlsSimulateCase   = pSimulateCase;
		//设置SimulateSymptomsCollect指针
		CSimulateSymptomsCollect  *pCollect = pSimulateCase->getSimulateSymptomsCollectPtr();
		m_cRunFramework.setSimulateSymptomsCollectPtr( pCollect );
		m_cRunFramework.Set_CPRMessageCollectPtr( pSimulateCase->getCPRMessageCollect() );
		secondEumlate = NULL;
		m_pAclsFlowStrategy       = NULL;
		m_pShowEventSignInterface = NULL;
		m_eState   = eFlowNone;
		//---------------------------------------------------------------------------------------
		m_pFormatTransport = pTransport;
		m_pFormatTransport->SetReceivePackageIrpHandlePtr( &cond_IrpRecv );
	}

	CBlsMainFlowVirtual::~CBlsMainFlowVirtual(void)
	{
		if( secondEumlate != NULL )
		{
			delete secondEumlate;
		}
		secondEumlate = NULL;
		tg.interrupt_all();
		tg.join_all();
		//------------------------------------------------------------
		if( m_pAclsFlowStrategy != NULL )
		{
			delete m_pAclsFlowStrategy;
		}
		m_pAclsFlowStrategy = NULL;
	}

	//是否能处理Irp
	bool CBlsMainFlowVirtual::isCanPackageHandle()
	{
		if( m_eState == eFlowRun )
		{
			//boost::mutex::scoped_lock lockIrp(muPackage);
			if( m_IrpList.begin() == m_IrpList.end() || m_IrpList.size() == 0 )
			{
				return false;
			}
			return true;
		}
		return false;
	}

	//是否有通信层上传的Irp包
	bool CBlsMainFlowVirtual::isTransInUpIrps()
	{
		if( m_pFormatTransport != NULL )
		{
			return m_pFormatTransport->isTransUpIrps();
		}
		return false;
	}

	//创建流程线程
	bool CBlsMainFlowVirtual::CreateFlowThreads()
	{
		BOOST_ASSERT(secondEumlate == NULL);

        foreach(auto x, m_IrpList)
		{
			delete x;
		}
		m_IrpList.clear();
		//按缺剩设置界面
		m_eState = eFlowPause;
		//=======创建线程==============
		tg.create_thread( boost::bind(&CBlsMainFlowVirtual::_ThrdHandleIrpFunc, this) );
		tg.create_thread( boost::bind(&CBlsMainFlowVirtual::_ThrdReceiveIrpFunc, this) );
		//启动传输层的传输
		m_pFormatTransport->StartTransportData();
		return true;
	}

	/*******************************************************************************/
	// 函数名称： ResetScenario
	// 功能： 重置ACLS流程处理中心
	// 参数： 
	// 返回值:  
	pugi::xml_node CBlsMainFlowVirtual::ResetScenario()
	{
		//清除当前的执行位置框
		m_cRunFramework.ClearRunFramework();
		pugi::xml_node xmlElement = m_pBlsSimulateCase->getScriptXMLElement();
		//解析启动场景
		pugi::xml_node scenarioNode = m_cRunFramework.parseStartScenario( &xmlElement, 0);
		if( !scenarioNode.empty() )
		{
			//---------------------------------------------------------------------------------------
			//初始化执行当前的解析Actions
			ExecInitialFramework( SPT_Adult );
			//重置场景框存在时间
			CSymptom_FrameTime *pScenarioFrameTime = m_cRunFramework.getFrameTimeSymptomPtr();
			pScenarioFrameTime->ResetFrameTimeToZero();
			//设置流程策略
			m_pAclsFlowStrategy->CreateLineLinks( &scenarioNode );

			//控制模拟人体征
			IModifiedSymptomsOp  *pModifiedSymptomsOp = m_pBlsSimulateCase->getModifiedSymptomsOpPtr();
			pModifiedSymptomsOp->TransmitSimulatorOrders(  );
		}
		return scenarioNode;
	}

	/*******************************************************************************/
	// 函数名称： DoFlowNextScenario
	// 功能： 执行下个场景框
	// 参数： 
	//       DWORD  dwFrameID:      场景框的标识值
	// 返回值:  
	pugi::xml_node CBlsMainFlowVirtual::DoFlowNextScenario(unsigned short  dwFrameID, eEventSign eEvent/*=ES_Normal*/)
	{
		std::string  strFrameID = boost::lexical_cast<std::string>(dwFrameID);
		//1.1解析下个场景
		pugi::xml_node xmlElement = m_pBlsSimulateCase->getScriptXMLElement();
        pugi::xml_node scenarioNode = m_cRunFramework.parseNextScenario(&xmlElement, strFrameID, "ScenarioFrame");
		if( !scenarioNode.empty() )
		{
			//执行当前的解析Actions
			ExecNextFramework( eEvent );
			//重置场景框存在时间
			CSymptom_FrameTime *pScenarioFrameTime = m_cRunFramework.getFrameTimeSymptomPtr();
			pScenarioFrameTime->ResetFrameTimeToZero();

			m_pAclsFlowStrategy->CreateLineLinks( &scenarioNode );

			//控制模拟人体征
			IModifiedSymptomsOp  *pModifiedSymptomsOp = m_pBlsSimulateCase->getModifiedSymptomsOpPtr();
			pModifiedSymptomsOp->TransmitSimulatorOrders( );
			pModifiedSymptomsOp->ModifiedSymptomsUpdateShow( false );
		}
		return scenarioNode;
	}

	/*******************************************************************************/
	// 函数名称： DoFlowNextScenario
	// 功能： 执行下个场景框
	// 参数： 
	//       IXMLDOMNode *pScenarioNode:      场景框的Node
	//       eEventSign eEvent:     
	// 返回值:  
	pugi::xml_node  CBlsMainFlowVirtual::DoFlowNextScenario(pugi::xml_node  *pScenarioNode, eEventSign eEvent /*= ES_Normal*/)
	{
		pugi::xml_node scenarioNode = m_cRunFramework.parseNextScenario( pScenarioNode );
		if( !scenarioNode.empty() )
		{
			//执行当前的解析Actions
			ExecNextFramework( eEvent );
			//重置场景框存在时间
			CSymptom_FrameTime *pScenarioFrameTime = m_cRunFramework.getFrameTimeSymptomPtr();
			pScenarioFrameTime->ResetFrameTimeToZero();

			m_pAclsFlowStrategy->CreateLineLinks( pScenarioNode );

			//控制模拟人体征
			IModifiedSymptomsOp  *pModifiedSymptomsOp = m_pBlsSimulateCase->getModifiedSymptomsOpPtr();
			/*pModifiedSymptomsOp->TransmitSimulatorOrders( );*/
			pModifiedSymptomsOp->ModifiedSymptomsUpdateShow( false );
		}
		return scenarioNode;
	}

	/*******************************************************************************/
	// 函数名称： DoFlowSceneActRun
	// 功能： 执行情景框框
	// 参数： 
	//       DWORD dwSceneActFrameID:      情景框的标识值
	//       BOOL bLogoutFlow:             是否退出主流程
	//       eEventSign eEvent:     
	// 返回值:  
	CXSceneActFrame * CBlsMainFlowVirtual::DoFlowSceneActRun(unsigned short dwSceneActFrameID, bool bLogoutFlow, eEventSign eEvent/*=ES_Normal*/)
	{
		CXSceneActFrame *pDstSceneActFrame = NULL;
		CSceneActsCollect *pSceneActsCollect = m_pBlsSimulateCase->getSceneActsCollectPtr();
		if( pSceneActsCollect != NULL )
		{
			pDstSceneActFrame = pSceneActsCollect->SearchSceneActFramePtr( dwSceneActFrameID );
		}
		if( pDstSceneActFrame != NULL )
		{
			CXScenario   *pScenarioPtr = m_cRunFramework.GetScenarioPtr();
			pScenarioPtr->EmptyActions();
			//拷贝修改的体征项
			pScenarioPtr->CopyActions( pDstSceneActFrame );
			//执行当前的Actions
			ExecNextFramework( eEvent );

			if( bLogoutFlow )
			{
				//退出主流程
				m_pAclsFlowStrategy->DeleteAllLineLinks();
			}

			//控制模拟人体征
			IModifiedSymptomsOp  *pModifiedSymptomsOp = m_pBlsSimulateCase->getModifiedSymptomsOpPtr();
			/*pModifiedSymptomsOp->TransmitSimulatorOrders( );*/
			pModifiedSymptomsOp->ModifiedSymptomsUpdateShow( false );
		}
		return pDstSceneActFrame;
	}

	//执行当前的解析Actions
	void CBlsMainFlowVirtual::ExecNextFramework(eEventSign eEvent /*= ES_Normal*/)
	{
		CXScenario   *pScenarioPtr = m_cRunFramework.GetScenarioPtr();
		//修改CSimulateSymptomsCollect
		std::list<CXActionVirtual *>   lstActions;
		pScenarioPtr->GetScenarioActions( &lstActions );
		ISetSimulateSymptoms  *pSetSimulateSymptomsPtr = m_pBlsSimulateCase->getSetSimulateSymptomsPtr();
		pSetSimulateSymptomsPtr->modifyScenarioSet(&lstActions, eEvent, false);
		//组合生理体征,并清空CXScenario中的生理体征列表项
		m_cRunFramework.CombineCurrentActions( true );
	}

	// 将需要处理的IRP发到处理队列或其它相应的处理
	bool CBlsMainFlowVirtual::AddNeedHandleIrp(CVirtualIrp * pVirIrp)
	{
		//判断其是否需要其它相应的处理
		if(m_eState == eFlowRun)
		{
			m_IrpList.push_back(pVirIrp);
			cond_IrpHandle.notify_one();
		}
		else
			delete pVirIrp;
		return false;//不忽略
	}

	//处理消息包
	void CBlsMainFlowVirtual::OnHandleIrp(CVirtualIrp *pVirIrp)
	{
		m_cHandleActionIrpMutex.Lock();
		if( pVirIrp != NULL )
		{
			IHandleIrpsCollect::OnHandleIrp( pVirIrp );
			//记录事件日志
			if( pVirIrp->isKindOf( "CVirEventIrp" ) && !pVirIrp->isKindOf( "CEventIrp_ClockTime" ) )
			{
				CVirEventIrp  *pVirEventIrp = (CVirEventIrp *)pVirIrp;
				//设置CPR事件的操作模式为当前模式【注：影响CPR日志的表述】
				FilterCPREventIrp(pVirEventIrp, m_pBlsSimulateCase);
				//记录事件日志
				std::string  strCurrentRunTime = m_pBlsSimulateCase->CurrentTimeFormat();
				log::COpLogInterface  *pLogInterface = m_pBlsSimulateCase->getOpLogMessagePtr();
				pLogInterface->OnEventHandleLog(strCurrentRunTime, pVirEventIrp);
				//显示事件界面效果
				DoUpdateEventSignShow(pVirEventIrp, m_pShowEventSignInterface, m_pBlsSimulateCase);
			}
		}
		m_cHandleActionIrpMutex.Unlock();
	}

	// 开始运行场景
	void CBlsMainFlowVirtual::StartCurrScenario( )
	{
		m_eState = eFlowRun;
		if( secondEumlate != NULL )
		{
			delete secondEumlate;
			secondEumlate = NULL;
		}
		secondEumlate = new utility::CEmulateTimer(1000, boost::bind(&CBlsMainFlowVirtual::_ThrdTimeFunc, this));
		secondEumlate->startTimer();
		
		if( m_pFormatTransport != NULL )
		{
			CSimulatorOrderIrp *pOrderIrp = CSimulatorOrderIrp::createSimulatorOrderIrp(0x20, 0x20);;
			m_pFormatTransport->OnTransportDownOrderToSimulater( pOrderIrp );
		}
		cond_IrpHandle.notify_one();
	}

	// 暂停目前运行的场景
	void CBlsMainFlowVirtual::PauseCurrScenario( bool bClearSimulator )
	{
		m_eState = eFlowPause;
		if( secondEumlate != NULL )
		{
			secondEumlate->killTimer();
		}
		//发送系统总清指令
		if( bClearSimulator && m_pFormatTransport != NULL )
		{
			CSimulatorOrderIrp *pOrderIrp = CSimulatorOrderIrp::createSimulatorOrderIrp(0x50, 0x50);;
			m_pFormatTransport->OnTransportDownOrderToSimulater( pOrderIrp );
		}
	}

	/*******************************************************************************/
	// 函数名称： ExecuteAction
	// 功能： 执行体征的设置
	// 参数： 
	//       IXMLDOMElement *pRootElement: 
	// 返回值:  
	void CBlsMainFlowVirtual::ExecuteActions(std::list<CXActionVirtual *> *plstVirActions, short sTransferTime/*=0*/)
	{
		m_cHandleActionIrpMutex.Lock();
		ISetSimulateSymptoms  *pSetSimulateSymptomsPtr = m_pBlsSimulateCase->getSetSimulateSymptomsPtr();
		pSetSimulateSymptomsPtr->modifyScenarioSet(plstVirActions, ES_Normal, false, sTransferTime);
		//组合生理体征
		m_cRunFramework.CombineCurrentActions( plstVirActions );

		m_cHandleActionIrpMutex.Unlock();
	}

	/*******************************************************************************/
	// 函数名称： StartLinkEventSignShowInterfaces
	// 功能： 初始化连接事件显示接口
	// 参数： 
	//        CModularBarsShowInterfacesAggregate *pShowAggregate:      
	// 返回值:  
	void CBlsMainFlowVirtual::StartLinkEventSignShowInterfaces(CShowEventSignUpdateInterface *pShowInterface)
	{
		if( m_pShowEventSignInterface == NULL )
		{
			m_pShowEventSignInterface  = pShowInterface;
		}
		else if( pShowInterface != NULL )
		{
			m_pShowEventSignInterface->SetNextInterfacePtr( pShowInterface );
		}
		if( pShowInterface != NULL )
		{
			pShowInterface->LinkUpdateShow();
		}
	}

	/*******************************************************************************/
	// 函数名称： UnLinkModularBarShowInterfaces
	// 功能： 断开连接事件显示接口
	// 参数： 
	//        CModularBarsShowInterfacesAggregate *pShowAggregate:      
	// 返回值:  
	void CBlsMainFlowVirtual::UnLinkEventSignShowInterfaces(CShowEventSignUpdateInterface *pShowInterface)
	{
		if( pShowInterface != NULL )
		{
			m_pShowEventSignInterface = (CShowEventSignUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowEventSignInterface, pShowInterface);
			pShowInterface->UnLinkUpdateShow();
		}
	}

	/*******************************************************************************/
	// 函数名称： DoManualDispatchEventFlow
	// 功能： 手动跳转事件框
	// 参数：      
	// 返回值: 
	void CBlsMainFlowVirtual::DoManualDispatchEventFlow(pugi::xml_node *pEventXMLNode)
	{
		m_pAclsFlowStrategy->OnFlowStrategy(pEventXMLNode);
	}

	//设置CPR事件的操作模式为当前模式
	void CBlsMainFlowVirtual::FilterCPREventIrp(CVirEventIrp *pVirEventIrp, CBlsSimulateCase *pBlsCase)
	{
        if( pVirEventIrp->isKindOf( "CCPRStatIrp" ) && pBlsCase )
		{
			irp::CCPRStatIrp  *pCPREventIrp = (irp::CCPRStatIrp *)pVirEventIrp;
			cpr::CCPRSimulateJudgeOp *pCPRJudgeOp = pBlsCase->getCPRMessageCollect()->getCPRSimulateJudgeOp();
			if( pCPRJudgeOp != NULL && pCPREventIrp->Get_eCPRMode() == eNoneDefine )
			{
				_CPRManageState  eCPRSate = pCPRJudgeOp->get_eCPRState();
				pCPREventIrp->Set_eCPRMode( eCPRSate );
			}
		}
	}

	/*******************************************************************************/
	// 函数名称： DoUpdateEventSignShow
	// 功能： 显示事件界面效果
	// 参数：  
	//         CVirEventIrp *pVirEventIrp: 
	//         CShowEventSignUpdateInterface  *pShowEventSignInterface:
	// 返回值:  
	void CBlsMainFlowVirtual::DoUpdateEventSignShow(CVirEventIrp *pVirEventIrp, CShowEventSignUpdateInterface  *pShowEventSignInterface, CBlsSimulateCase *pBlsCase)
	{
		CSimulateBuildAggregate *pBuildAggregate = pBlsCase->getSimulateBuildAggregatePtr();
		//模拟人侦测事件（包括：除颤,起搏,气管插管,CPR等）显示
		if( pVirEventIrp->isKindOf( "CEventIrp_SimulateTrigger" ) )
		{
			CEventIrp_SimulateTrigger *pSimulateEventIrp = (CEventIrp_SimulateTrigger *)pVirEventIrp;
			if( pSimulateEventIrp->getName_TriggerEvent() == CSEvent_Intubate::getEvent_Intubate_Caption() )
			{
				//插管信息
				short   sAct, sPosition;
				pSimulateEventIrp->explainSimulateTrigger_IntubateEventIrp(/*out*/sPosition, /*out*/sAct);
				bool   bIntubate = false;
				if( sAct == 0x11 && sPosition == 0x02 )
				{
					bIntubate = true;
				}
				pBuildAggregate->Set_EtCO2WatchLinkState( bIntubate );
			}
		}
	}

}}
