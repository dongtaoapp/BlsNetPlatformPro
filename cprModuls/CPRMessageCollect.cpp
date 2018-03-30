#include ".\CPRMessageCollect.h"

#include "..\Common\ParseCPRData_Singleton.h"

#include "..\SimulatorBase\CPRStatIrp.h"
#include "..\SimulatorBase\RealTimeDataIrp.h"
#include "..\SimulatorBase\EventIrp_ClockTime.h"

namespace jysoft{  namespace cpr 
{

	CCPRMessageCollect::CCPRMessageCollect(void)
	{
		m_pCPRConfigue        = NULL;
		m_pEventLogInterface  = NULL;
		m_pCPRJudgeOp   = new CCPRSimulateJudgeOp( aCPRPractiseMode );
		m_pStatisticImpl = new CCPRStatisticImplement(&m_cPressureCollate, &m_cBreathCollate);
		//--------------------------------------------------------------------
		m_pShowCPRRealTimeInteface   = NULL;
		m_pShowCPRDetailActInterface = NULL;
		m_pTransportUpOrderInterface = NULL;

		m_bEnableCompleteJudge       = false;
		m_eNextPhaseCPRState         = eNoneDefine;
	}


	CCPRMessageCollect::~CCPRMessageCollect(void)
	{
		delete  m_pCPRJudgeOp;
		delete  m_pStatisticImpl;
		//----------------------------------------------------
		m_pShowCPRRealTimeInteface  = NULL;
		m_pCPRConfigue              = NULL;
		m_pEventLogInterface        = NULL;
	}

	/*******************************************************************************/
	//功能：处理场景框转移IRP函数
	//参数：
	//      CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（false);
	bool CCPRMessageCollect::doHandleRealTimeDataIrpOp(irp::CVirtualIrp *pCurrIrp)
	{
        if( !pCurrIrp->isKindOf( "CRealTimeDataIrp" ) )
			return true;
		irp::CRealTimeDataIrp *pRealTimeIrp = (irp::CRealTimeDataIrp *)pCurrIrp;
		//CPR操作判断
		const CParseCPRData_Singleton *pCPRParse = &CParseCPRData_Singleton::get_const_instance();
		for (int nStep = 0; nStep < pRealTimeIrp->m_nLength; ++nStep)
		{
			const _CPRData &cprData = pRealTimeIrp->m_ptrCPRDatas[nStep];
			if( pCPRParse->isCPROrder(cprData) )
			{
				_eCPRErrorSign eErrorSign = doCPROrderHandle( cprData );
				//显示错误标示
				if( m_pShowCPRRealTimeInteface != NULL )
				{
					m_pShowCPRRealTimeInteface->OnAddCPRErrorSign( eErrorSign );
				}
				if( pCPRParse->judgeCPRStartOrStopOrder(cprData, true) )
				{
					//启动提示音
					startTickSound();
					if( !m_pCPRJudgeOp->isCompleteCurrentCPR() )
					{
						m_bEnableCompleteJudge  = true;
					}
				}
				else if( pCPRParse->judgeCPRStartOrStopOrder(cprData, false) )
				{
					//关闭语言提示
					stopTickSound();
				}
				if( m_pCPRJudgeOp->isCompleteCurrentCPR() && m_bEnableCompleteJudge )
				{
					//CPR操作完成处理
					doCPRCompleteHandle();
					m_bEnableCompleteJudge  = false;
				}
			}
		}
		m_pStatisticImpl->loadCPRData(pRealTimeIrp->m_ptrCPRDatas, pRealTimeIrp->m_nLength);
		//实时CPR操作曲线显示
		if( m_pShowCPRRealTimeInteface != NULL )
		{
			m_pShowCPRRealTimeInteface->OnLoadCPRSample(pRealTimeIrp->m_ptrCPRDatas, pRealTimeIrp->m_nLength);
		}
		return true;
	}

	/*******************************************************************************/
	//功能：处理时钟事件IRP函数
	//参数：
	//      CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
	bool CCPRMessageCollect::doHandleClockIrpOp(irp::CVirtualIrp *pCurrIrp)
	{
        if( pCurrIrp && pCurrIrp->isKindOf( "CEventIrp_ClockTime" ) )
		{
			irp::CEventIrp_ClockTime *pClockTimeIrp = (irp::CEventIrp_ClockTime *)pCurrIrp;
			//时间计数
			m_pStatisticImpl->doHandleSecondClockTick();
		}
		return true;
	}

	/*******************************************************************************/
	// 函数名称： initialCPR
	// 功能：    初始化
	// 参数：  
	// 返回值:  
	void CCPRMessageCollect::initialCPR(CCPRConfigue *pCPRConfigue,  transLayer::ITransportOrderIrpToUp *pTransUpInterface, log::COpLogInterface *pEventLogInterface/*=NULL*/)
	{
		m_pTransportUpOrderInterface  = pTransUpInterface;
		m_pEventLogInterface          = pEventLogInterface;
		//获取CPR系统配置
		m_pCPRConfigue                = pCPRConfigue;
		m_cPressureCollate.changeJudgeRange(pCPRConfigue->getOverPressureDepth(), pCPRConfigue->getLowerPressureDepth());
		m_cBreathCollate.changeJudgeRange( pCPRConfigue->getOverBreathVolume(), pCPRConfigue->getLowerBreathVolume() );
		//启动时间线程
		m_pStatisticImpl->setPhaseCPRLogInterfacePtr(pEventLogInterface);
		m_pStatisticImpl->initialCPRStaticImpl( );
	}

	/*******************************************************************************/
	// 函数名称： resetCPROperatorMessage
	// 功能：    重置CPR操作统计
	// 参数：  
	// 返回值:  
	void CCPRMessageCollect::resetCPROperatorMessage(_CPRManageState  eCPRState)
	{
		m_bEnableCompleteJudge  = false;
		//设置CPR规则判断类
		doCPROperatorFinishHandle( eCPRState );
		//重置内容
		m_pStatisticImpl->resetStatisticImpl();
	}

	/*******************************************************************************/
	// 函数名称： restatisticByDefibrEventHandle
	// 功能：    除颤事件引发重置CPR操作统计
	// 参数：  
	// 返回值:  
	void CCPRMessageCollect::restatisticByDefibrEventHandle()
	{
		////保存当前的统计....

		//允许重新开始统计
		m_pStatisticImpl->allowRestatisticImpl(seconds(getScriptRunTime()));
		//设置CPR规则判断类
		doCPROperatorFinishHandle( m_eNextPhaseCPRState );
		m_bEnableCompleteJudge  = true;
	}

	/*******************************************************************************/
	// 函数名称： StartLinkCPRShowInterfaces
	// 功能： 初始连接CPR显示的相关显示接口
	// 参数： CCPRShowInterfacesAggregate *pShowAggregate:        
	// 返回值:  
	void CCPRMessageCollect::startLinkCPRShowInterfaces(CCPRShowInterfacesAggregate *pShowAggregate)
	{
		m_pShowCPRRealTimeInteface = pShowAggregate->Get_ShowCPRRealTimeUpdateInterface();
		if( m_pShowCPRRealTimeInteface != NULL )
		{
			m_pShowCPRRealTimeInteface->LinkUpdateShow();
		}
		//设定CPR操作细节显示接口
		CShowCPRActUpdateInterface  *pShowCPRDetailActInterface = pShowAggregate->Get_ShowCPRDetailActUpdateInterface();
		if( m_pShowCPRDetailActInterface == NULL )
		{
			m_pShowCPRDetailActInterface = pShowCPRDetailActInterface;
		}
		else if( pShowCPRDetailActInterface != NULL )
		{
			m_pShowCPRDetailActInterface->SetNextInterfacePtr( pShowCPRDetailActInterface );
		}
		if( pShowCPRDetailActInterface != NULL )
		{
			pShowCPRDetailActInterface->LinkUpdateShow();
		}
		m_pStatisticImpl->startLinkCPRShowInterfaces( pShowAggregate );
	}

	/*******************************************************************************/
	// 函数名称： UnLinkCPRShowInterfaces
	// 功能： 断开CPR显示的相关显示接口
	// 参数： CCPRShowInterfacesAggregate *pShowAggregate:        
	// 返回值:
	void CCPRMessageCollect::unLinkCPRShowInterfaces(CCPRShowInterfacesAggregate *pShowAggregate)
	{
		CCPRRealTimeUpdateInterface *pShowCPRRealTimeInterface = pShowAggregate->Get_ShowCPRRealTimeUpdateInterface();
		if( m_pShowCPRRealTimeInteface && pShowCPRRealTimeInterface )
		{
			m_pShowCPRRealTimeInteface = (CCPRRealTimeUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowCPRRealTimeInteface, pShowCPRRealTimeInterface);
			//断开显示操作
			pShowCPRRealTimeInterface->UnLinkUpdateShow();
		}
		m_pStatisticImpl->unLinkCPRShowInterfaces( pShowAggregate );
		//移除CPR操作细节显示接口
		CShowCPRActUpdateInterface  *pShowCPRDetailActInterface = pShowAggregate->Get_ShowCPRDetailActUpdateInterface();
		if( pShowCPRDetailActInterface != NULL )
		{
			m_pShowCPRDetailActInterface = (CShowCPRActUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowCPRDetailActInterface, pShowCPRDetailActInterface);
			pShowCPRDetailActInterface->UnLinkUpdateShow();
		}
	}

	//CPR命令指令处理
	_eCPRErrorSign CCPRMessageCollect::doCPROrderHandle(const _CPRData &cprOrder)
	{
		_eCPRErrorSign eSign  = CS_None;
		_eCPRErrorSign ePractiseExtendSign  = CS_None;
		//根据幅度指令，判断CPR操作统计
        short uLackNum  = 0;
		boost::optional<int> cycleNum = m_pStatisticImpl->getCPRCycleNum();
		eSign = m_pCPRJudgeOp->judgeCPRData(cprOrder, &m_cPressureCollate, &m_cBreathCollate, /*out*/uLackNum, /*out*/ePractiseExtendSign, /*in,out*/cycleNum);
		m_pStatisticImpl->acceptAndStatisticImp(cprOrder, eSign, uLackNum, ePractiseExtendSign, cycleNum, m_pCPRJudgeOp->get_eCPRState(), m_pCPRConfigue);
		return eSign;
	}

	//CPR操作完成处理
	void CCPRMessageCollect::doCPRCompleteHandle()
	{
		_CPRManageState   eCPRMode = m_pCPRJudgeOp->get_eCPRState();
		//1. 上传五个循环操作完成指令[注：/2:    在标准模式及实战模式下，完成5个循环的CPR操作]
		if( m_pTransportUpOrderInterface != NULL )
		{	
			irp::CCPRStatIrp  *pCPRStatIrp = irp::CCPRStatIrp::CreateEvent_CPRIrp(eCPRMode, 2);
			m_pTransportUpOrderInterface->OnTranslateUpIrpNoNetwork( pCPRStatIrp );
		}
		//2. 显示更新
		if( m_pShowCPRDetailActInterface != NULL )
		{
			m_pShowCPRDetailActInterface->OnFiveCycleCompleteAct();
		}
	}

	//CPR操作结束处理
	void CCPRMessageCollect::doCPROperatorFinishHandle(_CPRManageState  eCPRState)
	{
		//判断是否需要设定下次CPR操作的规则[注：m_eNextPhaseCPRState为eNoneDefine不修改规则]
		if( eCPRState != eNoneDefine )
		{
			//重置统计记录
			m_pStatisticImpl->resetStatisticImpl(true);
			///设置下次CPR操作的规则
			_CPRRuleStruct *pCPRRule  = NULL;
			switch( eCPRState )
			{
			case aCPRPopularMode:
			case aCPRPractiseMode:
				{
					pCPRRule  = new _CPRRuleStruct();
					if( m_pCPRConfigue->isSpecialityMemberOp() )
					{
						pCPRRule->setDefaultCPRRule( m_pCPRConfigue->isFiveCycleRule() ? 5 : 3 );
					}
					else
					{
						//按压操作
						pCPRRule->setOnlyPressure( m_pCPRConfigue->getSumPressureNumber() );
					}
					break;
				}
			default:
				{
					pCPRRule  = NULL;
					break;
				}
			}
			m_pCPRJudgeOp->resetSimulateParam( eCPRState, pCPRRule );
			m_eNextPhaseCPRState  = eNoneDefine;
		}
		else 
		{
			m_pCPRJudgeOp->resetSimulateParam();
			m_pStatisticImpl->resetStatisticImpl();
		}
	}

	//设置下阶段的CPR操作模式
	void CCPRMessageCollect::setNextPhaseCPROperatorMode(_CPRManageState  eCPRState)
	{
		if( m_pStatisticImpl->isCPROperatoring() )
		{
			m_eNextPhaseCPRState  = eCPRState;
		}
		else
		{
			doCPROperatorFinishHandle(eCPRState);
		}
	}

	/*******************************************************************************/
	// 函数名称： DoModifyCPRJudgeRange
	// 功能： 修改心肺复苏操作时，吹气与按压的范围
	// 参数：     
	// 返回值:  
	void CCPRMessageCollect::modifyCPRJudgeRange(int nLowerDepth, int nOverDepth, int nLowerVolume, int nOverVolume)
	{
		m_cPressureCollate.changeJudgeRange( nOverDepth,  nLowerDepth);
		m_cBreathCollate.changeJudgeRange( nOverVolume, nLowerVolume );
	}

	//启动滴答音
	void CCPRMessageCollect::startTickSound()
	{
		
	}

	//停止滴答音
	void CCPRMessageCollect::stopTickSound()
	{
		
	}

	//返回脚本当前时间
	UINT CCPRMessageCollect::getScriptRunTime()
	{
		UINT  uScriptTime = 0;
		if( m_pEventLogInterface != 0 )
		{
			uScriptTime = m_pEventLogInterface->GetScriptRunTime();
		}
		return uScriptTime;
	}

}}
