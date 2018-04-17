#include <algorithm>
#include <fstream>
#include <boost/assert.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include ".\BlsSimulateCase.h"
#include ".\BlsMainFlowVirtual.h"
#include ".\BlsMainFlowOwn.h"
#include ".\BlsMainFlowWatch.h"
#include ".\ParseShapeFactory.h"

#include "..\simulatorBase\EventIrp_ClockTime.h"
#include "..\simulatorBase\FrameFlowIrp.h"


#include "..\common\CommonGlobal.h"
#include "..\common\EventHandleCPRStatIrpOp.h"


using namespace jysoft::irp;
using namespace jysoft::network;
using namespace jysoft::utility;
using namespace jysoft::transLayer;
namespace jysoft { namespace flowEngine 
{
	CBlsSimulateCase::CBlsSimulateCase(CSceneActsCollect *pSceneActsCollect/*=NULL*/)
	{
		m_pBlsFlowEnginer = NULL;
		m_pFormatTransport   = NULL;;
		//------------------------------------------------------------------------
		m_pShowScenarioRunTimeInterface  = NULL;
		m_pShowFrameNameInterface        = NULL;

		m_uLogTime           = 0;
		m_dwCurrentFrameId   = 0;
		m_pSceneActsCollect  = pSceneActsCollect;
		//默认为V1.0版本通信协议
		m_pFormatTransport   = new CFormatTransport( 10 );
	}

	CBlsSimulateCase::~CBlsSimulateCase(void)
	{
		m_cBuildAggregate.ClosePhysBuilds();
		if( m_pBlsFlowEnginer != NULL )
		{
			delete m_pBlsFlowEnginer;
		}
		//-----------------------------------------------
		delete m_pFormatTransport;
	}

	/*******************************************************************************/
	// 函数名称： isValidateRightScenario
	// 功能： 解析加载的脚本文件，判断文件格式及版本
	// 参数： 
	// 返回值:  string *pstrError：错误信息提示
	bool CBlsSimulateCase::isValidateRightScenario(const std::string &strFilePath, /*out*/std::string *pstrError)
	{
		std::ifstream stream( strFilePath.c_str() );
		pugi::xml_parse_result result = m_xmlScriptDoc.load(stream);
		//验证脚本文件...
		if( result == true)
		{
			;
		}
		return true;
	}

	/*******************************************************************************/
	// 函数名称： initialAclsScenario
	// 功能： 根据场景脚本文件，初始化ACLS场景训练的运行案例
	// 参数： 
	// 返回值:  
	bool CBlsSimulateCase::initialAclsScenario(const std::string &resourcePath, const std::string &commonPath, bool bAsyncWatch/*=false*/)
	{
		bool                 bInitialSec  = false;
		//解析脚本配置信息
		parseACLSScriptConfigue( commonPath );
		//初始化CPR信息收集类
		boost::format fmt("%s\\configure\\scriptCPRRule.config");
		fmt % commonPath;
		InitialCPR( fmt.str(), commonPath );
		//创建模拟人体征、趋势、体征模拟器、日志及CPR操作数据等单元
		if( !bAsyncWatch )
		{
			m_pBlsFlowEnginer  = new CBlsMainFlowOwn( this, m_pFormatTransport );
		}
		else
		{
			m_pBlsFlowEnginer  = new CBlsMainFlowWatch( this, m_pFormatTransport );
		}
		
		//设置生理体征间的相互约束关系
		m_cSymotomsCollect.LoadSymptomsRelateRestrict();
		//设置各单元相互的关系
		SetUnitsRelate();
		//初始化体征构造器相关的指针设定
		m_cBuildAggregate.InitialPhysBuildsRelationAndResources(resourcePath);
		//创建BLS流程处理中心
		pugi::xml_node xmlScenarioNode = m_pBlsFlowEnginer->CreateScenario( getScriptXMLElement() );
		if( !xmlScenarioNode.empty() )
		{
			m_cSymotomsCollect.initialSimulateSymptomsBuild( SPT_Adult );
			//启动模拟器
			m_cBuildAggregate.StartSimulateBuild();
			bInitialSec  = true;
		}
		//加载脚本的情景框
		if( m_pSceneActsCollect != NULL )
		{
			IGetPhysiologyActionObj *pIGetActionObj = getPhysiologyActionInterfacePtr();
			m_pSceneActsCollect->InitialScriptSceneActs( getScriptXMLElement(), pIGetActionObj, m_pFormatTransport);
			//激活全局情景框
			m_pSceneActsCollect->ActiveSceneActsRun();
		}
		//清除被修改体征的标识
		IModifiedSymptomsOp  *pModifiedSymptomsOp = getModifiedSymptomsOpPtr();
		pModifiedSymptomsOp->emptyModifiedSymptomsFlag( );
		m_uLogTime  = 0;
		//通用资源路径
		m_strCommonResourcePath = commonPath;
		return bInitialSec;
	}

	//解析脚本配置信息
	void CBlsSimulateCase::parseACLSScriptConfigue( const std::string &strCommonResourcePath)
	{
		boost::format fmtCommon("%s\\configure\\blsConfig.ini");
		fmtCommon % strCommonResourcePath;
		m_cBlsConfigue.parseBLSConfigue(fmtCommon.str());
	}

	//初始化CPR信息收集类
	void CBlsSimulateCase::InitialCPR( const std::string &strCPRConfigueFile, const std::string &strCommonResourcePath )
	{
		//解析CPR配置信息
		m_cCPRConfigue.loadCPRConfigue( strCPRConfigueFile );
		//初始化CCPRMessageCollect
		transLayer::ITransportOrderIrpToUp  *pTransUpOrderInterface = (transLayer::ITransportOrderIrpToUp *)m_pFormatTransport;
		m_cCPRMessageCollect.initialCPR( &m_cCPRConfigue, pTransUpOrderInterface, &m_cBlsLogs);
	}

	//设置模拟人体征、趋势、体征模拟器、日志及CPR操作数据等单元的关系
	void CBlsSimulateCase::SetUnitsRelate()
	{
		//设置生理体征与征模拟器集合类的关系
		COpPhysBuildInterfacesAggregate *pPhysBuildInterfacesAggregate = (COpPhysBuildInterfacesAggregate *)&m_cBuildAggregate;
		m_cSymotomsCollect.LinkSimulateBuildInterfaces( pPhysBuildInterfacesAggregate );
		//设置通信接口指针
		ITransportOrderIrpToSimulator *pTransportInterface = m_pBlsFlowEnginer->GetTransportOrderIrpToSimulatorInterface();
		m_cSymotomsCollect.set_TransportOrderIrpToSimulatorInterface(  pTransportInterface );
		//设置体征设置处理接口
		CEventHandleClockIrpOp *pAclsCaseHandleClockIrpOp = (CEventHandleClockIrpOp *)this;
		m_pBlsFlowEnginer->addNewHandleIrpObj(pAclsCaseHandleClockIrpOp, eClock_Event);
		CEventHandleFrameFlowIrpOp *pAclsCaseFrameFlowHandleIrpOp = (CEventHandleFrameFlowIrpOp *)this;
		m_pBlsFlowEnginer->addNewHandleIrpObj(pAclsCaseFrameFlowHandleIrpOp, eFrameModify_Event);
		//设置CPR实时采用处理接口
		CRealTimeDataHandleIrpOp *pRealTimeInterface = (CRealTimeDataHandleIrpOp *)&m_cCPRMessageCollect;
		m_pBlsFlowEnginer->addNewHandleIrpObj(pRealTimeInterface, eRealTimeData);
		CEventHandleClockIrpOp *pCPRClockIrpOp = (CEventHandleClockIrpOp *)&m_cCPRMessageCollect;
		m_pBlsFlowEnginer->addNewHandleIrpObj(pCPRClockIrpOp, eClock_Event);
		pRealTimeInterface = (CRealTimeDataHandleIrpOp *)&m_cSymotomsCollect;
		m_pBlsFlowEnginer->addNewHandleIrpObj(pRealTimeInterface, eRealTimeData);
		//CPR状态事件，hjg 添加于2010.11.30
		CEventHandleCPRStatIrpOp  *pCPRStatIrpOp = (CEventHandleCPRStatIrpOp *)&m_cSymotomsCollect;
		m_pBlsFlowEnginer->addNewHandleIrpObj(pCPRStatIrpOp, eCPR_Stat);
		//设置体征参数集合管理类的Irp处理
		CEventHandleClockIrpOp *pSymptomsHandleClockIrpOp = (CEventHandleClockIrpOp *)&m_cSymotomsCollect;
		m_pBlsFlowEnginer->addNewHandleIrpObj(pSymptomsHandleClockIrpOp, eClock_Event);
		CEventHandleCustomIrpOp *pCustomEventIrpOp = (CEventHandleCustomIrpOp *)&m_cSymotomsCollect;
		m_pBlsFlowEnginer->addNewHandleEventIrpObj( pCustomEventIrpOp );

		//设置情景框集合管理类的Irp处理  hjg 2013.12.6
		if( m_pSceneActsCollect != NULL )
		{
			CEventHandleClockIrpOp *pSceneActHandleClockIrpOp = m_pSceneActsCollect;
			m_pBlsFlowEnginer->addNewHandleIrpObj( pSceneActHandleClockIrpOp, eClock_Event, true );
			CEventHandleCustomIrpOp *pCustomSceneActEventIrpOp = m_pSceneActsCollect;
			m_pBlsFlowEnginer->addNewHandleEventIrpObj( pCustomSceneActEventIrpOp, true );
		}
	}

	/*******************************************************************************/
	// 函数名称： StartLinkWatchBarsShowInterfaces
	// 功能： 初始连接模拟监控面板的相关显示接口
	// 参数： 
	//        CWatchBarsShowInterfacesAggregate *pShowAggregate:      
	//        IWatchBarsHandle *pWatchBarsHandle:
	// 返回值:  
	void CBlsSimulateCase::StartLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate, controls::IWatchBarsHandle *pWatchBarsHandle)
	{
		//监控模拟体征数值
		m_cSymotomsCollect.StartLinkWatchBarsShowInterfaces( pShowAggregate );
		//监控模拟器数据
		COpPhysBuildInterfacesAggregate  *pOpPhysBuilds = (COpPhysBuildInterfacesAggregate *)&m_cBuildAggregate;
		pWatchBarsHandle->OnDefineWatchedSimulateTypeHandle(SPT_Adult, pOpPhysBuilds);
		pWatchBarsHandle->OnStartWatchPhysBuilds( pOpPhysBuilds );
	}

	/*******************************************************************************/
	// 函数名称： UnLinkWatchBarsShowInterfaces
	// 功能： 断开模拟监控面板的相关显示接口
	// 参数： 
	//        CWatchBarsShowInterfacesAggregate *pShowAggregate:      
	//        IWatchBarsHandle *pWatchBarsHandle:     
	// 返回值:
	void CBlsSimulateCase::UnLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate, controls::IWatchBarsHandle *pWatchBarsHandle)
	{
		//断开模拟体征数值
		m_cSymotomsCollect.UnLinkWatchBarsShowInterfaces( pShowAggregate );
		//断开模拟器数据
		COpPhysBuildInterfacesAggregate  *pOpPhysBuilds = (COpPhysBuildInterfacesAggregate *)&m_cBuildAggregate;
		pWatchBarsHandle->OnCutWatchPhysBuilds( pOpPhysBuilds );
	}

	/*******************************************************************************/
	// 函数名称： StartLinkLogShowInterface
	// 功能： 初始化连接日志显示接口
	// 参数： 
	//        IUpdateLogDataInterface *pUpdateLogInterface:      
	// 返回值:  
	void CBlsSimulateCase::StartLinkLogShowInterface(log::IUpdateLogDataInterface *pUpdateLogInterface)
	{

	}

	/*******************************************************************************/
	// 函数名称： UnLinkLogShowInterface
	// 功能： 断开连接日志显示接口
	// 参数： 
	//        IUpdateLogDataInterface *pUpdateLogInterface:      
	// 返回值:  
	void CBlsSimulateCase::UnLinkLogShowInterface(log::IUpdateLogDataInterface *pUpdateLogInterface)
	{

	}

	/*******************************************************************************/
	// 函数名称： StopDistributeSimulateData
	// 功能： 停止分发实时构造数据
	// 参数： 
	// 返回值:  
	void CBlsSimulateCase::StopDistributeSimulateData()
	{
		m_cBuildAggregate.StopSimulateBuilds();
	}

	//返回引擎指针
	CBlsMainFlowVirtual * CBlsSimulateCase::getBlsMainFlowPtr()
	{
		return m_pBlsFlowEnginer;
	}

	//返回当前对应设置的Action
	IGetPhysiologyActionObj * CBlsSimulateCase::getPhysiologyActionInterfacePtr()
	{
		if( m_pBlsFlowEnginer != NULL )
		{
			return m_pBlsFlowEnginer->Get_PhysiologyActionPtr();
		}
		return NULL;
	}

	//关闭各体征实时波形构建
	void CBlsSimulateCase::closePhysBuilds()
	{
		//停止分发实时构造数据
		StopDistributeSimulateData();
		m_cBuildAggregate.ClosePhysBuilds();
	}

	//返回吹气对照表类
	cpr::CBreathCollate * CBlsSimulateCase::getBreathCollatePtr()
	{
		return &m_cCPRMessageCollect.m_cBreathCollate;
	}

	//返回按压对照表类
	cpr::CPressureCollate * CBlsSimulateCase::getPressureCollatePtr()
	{
		return &m_cCPRMessageCollect.m_cPressureCollate;
	}

	/*******************************************************************************/
	// 函数名称： StartLinkCPROperatorShowInterfaces
	// 功能： 初始连接CPR控件的相关显示接口
	// 参数： 
	//        CCPRShowInterfacesAggregate *pShowAggregate:      
	// 返回值:  
	void CBlsSimulateCase::StartLinkCPROperatorShowInterfaces(cpr::CCPRShowInterfacesAggregate *pShowAggregate)
	{
		//添加心电图和按压事件的通知 hjg 2016.9.8 add
		cpr::CShowCPRActUpdateInterface *pShowCPRDetailAct = dynamic_cast<cpr::CShowCPRActUpdateInterface *>(&m_cBuildAggregate);
		cpr::CShowCPRActUpdateInterface *pShowCPRDetailAct2 = dynamic_cast<cpr::CShowCPRActUpdateInterface *>(&m_cSymotomsCollect);
		pShowAggregate->Set_ShowCPRDetailActUpdateInterface(pShowCPRDetailAct);
		pShowAggregate->Set_ShowCPRDetailActUpdateInterface(pShowCPRDetailAct2);
		//初始连接CPR控件的相关显示接口
		m_cCPRMessageCollect.startLinkCPRShowInterfaces( pShowAggregate );
	}

	/*******************************************************************************/
	// 函数名称： UnLinkCPROperatorShowInterfaces
	// 功能： 断开CPR控件的相关显示接口
	// 参数： 
	//        CCPRShowInterfacesAggregate *pShowAggregate:      
	// 返回值:  
	void CBlsSimulateCase::UnLinkCPROperatorShowInterfaces(cpr::CCPRShowInterfacesAggregate *pShowAggregate)
	{
		m_cCPRMessageCollect.unLinkCPRShowInterfaces( pShowAggregate );
		//移除心电图和按压事件的通知 hjg 2016.9.8 add
		cpr::CShowCPRActUpdateInterface *pShowCPRDetailAct = dynamic_cast<cpr::CShowCPRActUpdateInterface *>(&m_cBuildAggregate);
		pShowAggregate->Remove_ShowCPRDetailActUpdateInterface( pShowCPRDetailAct );
		cpr::CShowCPRActUpdateInterface *pShowCPRDetailAct2 = dynamic_cast<cpr::CShowCPRActUpdateInterface *>(&m_cSymotomsCollect);
		pShowAggregate->Remove_ShowCPRDetailActUpdateInterface( pShowCPRDetailAct2 );
	}

	/*******************************************************************************/
	//功能：处理时钟事件IRP函数
	//参数：
	//      CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
	bool CBlsSimulateCase::doHandleClockIrpOp(CVirtualIrp *pCurrIrp)
	{
#ifdef  _DEBUG
        if( !pCurrIrp->isKindOf( "CEventIrp_ClockTime" ) )
		{
            BOOST_ASSERT( 0 );
		}
#endif
		CEventIrp_ClockTime  *pEventClockTime = (CEventIrp_ClockTime *)pCurrIrp;
		m_uLogTime += pEventClockTime->GetValue_ClockEvent();
		//更新场景运行时间显示
		if( m_pShowScenarioRunTimeInterface != NULL )
		{
			m_pShowScenarioRunTimeInterface->OnShowScenarioRunTimeUpdate( m_uLogTime );
		}
		m_cBlsLogs.SetScriptRunTime( m_uLogTime );
		return true;
	}

	/*******************************************************************************/
	//功能：处理场景框转移IRP函数
	//参数：
	//      CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
	bool CBlsSimulateCase::doHandleFrameFlowIrpOp(CVirtualIrp *pCurrIrp)
	{	
#ifdef  _DEBUG
		if( !pCurrIrp->isKindOf( "CFrameFlowIrp" ) )
		{
            BOOST_ASSERT( 0 );
		}
#endif
		/*CFrameFlowIrp  *pFrameFlowEvent = (CFrameFlowIrp *)pCurrIrp;
		IXMLDOMNode *pDestScenarioNode = NULL;
		switch( pFrameFlowEvent->m_eSceneAct )
		{
		case DSS_SceneSwitch:
			{
				if( pFrameFlowEvent->m_pScenarioNode != NULL )
				{
					pDestScenarioNode = m_pAclsFlowEnginer->DoFlowNextScenario(pFrameFlowEvent->m_pScenarioNode, pFrameFlowEvent->m_eEvent);
				}
				else
				{
					pDestScenarioNode = m_pAclsFlowEnginer->DoFlowNextScenario(pFrameFlowEvent->m_dwFrameId, pFrameFlowEvent->m_eEvent);
				}
				//日志信息
				std::string  strScriptTime = CurrentTimeFormat();
				m_pLogMessages->OnRunScenarioLog(strScriptTime, pDestScenarioNode);
				//当前场景名称的显示
				if( m_pShowFrameNameInterface != NULL )
				{
					m_pShowFrameNameInterface->OnShowFrameNameUpdate( pFrameFlowEvent->m_dwFrameId );
				}
				break;
			}
		case DSS_SceneActSchedule:
		case DSS_Logouted:
			{
				BOOL  bLogoutFlow = pFrameFlowEvent->m_eSceneAct == DSS_Logouted ? TRUE : FALSE;
				//情景调度或并退出流程
				CXSceneActFrame *pDestSceneActFrame = m_pAclsFlowEnginer->DoFlowSceneActRun(pFrameFlowEvent->m_dwFrameId, bLogoutFlow, pFrameFlowEvent->m_eEvent);
				std::string    strFrameId = boost::lexical_cast<std::string>(pFrameFlowEvent->m_dwFrameId);
				IXMLDOMElement *pRootElement = NULL;
				Get_XMLDOMDocumentPtr()->get_documentElement( &pRootElement );
				pDestScenarioNode = CXRunFramework::SearchFrameXMLDOMNodePtr( pRootElement, strFrameId, _T("SceneActFrame") );
				if( pDestSceneActFrame != NULL && pDestScenarioNode )
				{
					//日志信息
					std::string  strScriptTime = CurrentTimeFormat();
					m_pLogMessages->OnRunScenarioLog(strScriptTime, pDestScenarioNode);
				}
				pRootElement->Release();
				break;
			}
		}*/
		return true;
	}

	// 将目前的日期格式化
	std::string  CBlsSimulateCase::CurrentTimeFormat(void)
	{
		boost::format fmt("%d:%02d:%02d");
		fmt % (m_uLogTime/3600) % ((m_uLogTime%3600)/60) % (m_uLogTime%60);
		return fmt.str();
	}

	// 开始脚本的运行
	void CBlsSimulateCase::OnStartScenario()
	{
		if( IsPauseScenarioRun() && m_pBlsFlowEnginer )
		{
			//启动脚本引擎的运行
			m_pBlsFlowEnginer->StartCurrScenario( );
		}
	}

	// 恢复脚本的运行
	void CBlsSimulateCase::OnResumeScenario(bool bLogTimeToZero/*=true*/)
	{
		// 暂停脚本的运行
		if( bLogTimeToZero == true )
		{
			m_uLogTime  = 0;
			if( m_pShowScenarioRunTimeInterface != NULL )
			{
				m_pShowScenarioRunTimeInterface->OnShowScenarioRunTimeUpdate( m_uLogTime );
			}
		}
		//启动脚本引擎的运行
		m_pBlsFlowEnginer->StartCurrScenario( );
	}

	// 暂停脚本的运行
	void CBlsSimulateCase::OnPauseScenario(bool bClearSimulator/*=false*/)
	{
		if( !IsPauseScenarioRun() && m_pBlsFlowEnginer )
		{
			//暂停脚本引擎的运行
			m_pBlsFlowEnginer->PauseCurrScenario( bClearSimulator );
		}
	}

	//重载当前运行的脚本
	void CBlsSimulateCase::OnResetScenario()
	{
		m_pBlsFlowEnginer->PauseCurrScenario( true );
		// 暂停脚本的运行
		m_uLogTime  = 0;
		if( m_pShowScenarioRunTimeInterface != NULL )
		{
			m_pShowScenarioRunTimeInterface->OnShowScenarioRunTimeUpdate( m_uLogTime );
		}
		//重置CPR..
		m_cCPRMessageCollect.resetCPROperatorMessage( eNoneDefine );
		//清除所有运行的趋势，并恢复初始状态
		m_cSymotomsCollect.emptyModifiedSymptomsFlag();
		//重置脚本引擎的运行
		m_pBlsFlowEnginer->ResetScenario( );
		//重置传输处理
		m_pFormatTransport->ResetTransportHandle();
		//重置日志
		m_cBlsLogs.OnResetScenarioLog();
	
		//重置模拟器
		m_cSymotomsCollect.DirectModifySymptomsBuild( true );
		//重置情景集合类 hjg 2013.12.6 add
		if( m_pSceneActsCollect != NULL )
		{
			m_pSceneActsCollect->ActiveSceneActsRun();
		}
		//清除被修改体征的标识
		IModifiedSymptomsOp  *pModifiedSymptomsOp = getModifiedSymptomsOpPtr();
		pModifiedSymptomsOp->ModifiedSymptomsUpdateShow( true );
		//当前场景框的显示
		if( m_pShowFrameNameInterface != NULL )
		{
			m_pShowFrameNameInterface->OnShowFrameNameUpdate( m_dwCurrentFrameId );
		}
	}

	//判断脚本是否暂停状态
	bool CBlsSimulateCase::IsPauseScenarioRun()
	{
		if( m_pBlsFlowEnginer != NULL )
		{
			_FlowState  eState = m_pBlsFlowEnginer->Get_eFlowState();
			if( eState == eFlowRun )
			{
				return false;
			}
		}
		return true;
	}

	/*******************************************************************************/
	// 函数名称： setCPRParameters
	// 功能： 设置CPR操作时，按压及吹气的范围
	// 参数： 
	//          long  nLowerDepth：
	//          long  nOverDepth：
	//          long nLowerVolume：
	//          long  nOverVolume：
	// 返回值: 
	void CBlsSimulateCase::setCPRParameters(long  nLowerDepth, long  nOverDepth, long nLowerVolume, long  nOverVolume)
	{
		m_cCPRConfigue.set_LowerPressureDepth( nLowerDepth );
		m_cCPRConfigue.setOverPressureDepth( nOverDepth );
		m_cCPRConfigue.setLowerBreathVolume( nLowerVolume );
		m_cCPRConfigue.setOverBreathVolume( nOverVolume );

		m_cCPRMessageCollect.modifyCPRJudgeRange((int)nLowerDepth, (int)nOverDepth, (int)nLowerVolume, (int)nOverVolume);
	}

	/*******************************************************************************/
	// 函数名称： getCPRParameters
	// 功能： 获取CPR操作时，按压及吹气的范围
	// 参数： 
	void CBlsSimulateCase::getCPRParameters(long  *nLowerDepth, long  *nOverDepth, long  *nLowerVolume, long  *nOverVolume)
	{
		//按压最小值
		*nLowerDepth   = m_cCPRConfigue.getLowerPressureDepth();
		//按压最大值
		*nOverDepth    = m_cCPRConfigue.getOverPressureDepth();
		//吹气量最小值
		*nLowerVolume  = m_cCPRConfigue.getLowerBreathVolume();
		//吹气量最大值
		*nOverVolume   = m_cCPRConfigue.getOverBreathVolume();
	}

}}
