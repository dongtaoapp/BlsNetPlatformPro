#include ".\CPRPhaseStatistic.h"
#include <boost/foreach.hpp>

#include "..\Common\ParseCPRData_Singleton.h"


using namespace boost;
namespace jysoft{  namespace cpr {

	ICPRPhaseStatistic::ICPRPhaseStatistic(void)
	{
		delayTime                  = 0;
		buffTimeEvent              = 0;
		transEvent                 = 0;
		loopBuff.InitializeBuff(30);
		
		m_pEventLogInterface = NULL;
		actCPRDetailShowInterface  = NULL;
	}


	ICPRPhaseStatistic::~ICPRPhaseStatistic(void)
	{
		resetPhaseStatistic();
	}

	//重置内容
	void ICPRPhaseStatistic::resetPhaseStatistic()
	{
		BOOST_FOREACH(auto x, phaseStatSegs)
		{
			delete x;
		}
		phaseStatSegs.clear();
		loopBuff.Empty();
		delayTime      = 0;
		buffTimeEvent  = 0;
		transEvent     = 0;
	}

	//设置显示接口
	void ICPRPhaseStatistic::setShowCPRDetailActInterfacePtr(CShowCPRActUpdateInterface *pInterface)
	{
		if( pInterface != NULL )
		{
			IBedirecteLinksVir *pHeadInterface = pInterface->GetHeaderInterfacePtr();
			while( pHeadInterface )
			{
				if(pHeadInterface != actCPRDetailShowInterface && pHeadInterface->isKindOf("CShowCPRActUpdateInterface") )
				{
					actCPRDetailShowInterface = (CShowCPRActUpdateInterface *)pHeadInterface;
					return;
				}
				pHeadInterface = pHeadInterface->GetNextInterfacePtr();
			}
			actCPRDetailShowInterface = NULL;
		}
	}

	//-------------------------------------------------------------------------------------------
	////按压阶段类
	CPressurePhaseStatistic::CPressurePhaseStatistic()
	{

	}

	CPressurePhaseStatistic::~CPressurePhaseStatistic()
	{

	}

	/*******************************************************************************/
	// 函数名称： cprPressureRealTimeDataHandle
	// 功能： CPR操作数据处理函数 
	// 参数： 
	// 返回值:  
	void CPressurePhaseStatistic::cprPressureRealTimeDataHandle(const _CPRData *lptrCPRDatas, int nLength, const CPressureCollate *pPressureColl)
	{//按压幅度：0x2X
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		for (int nStep = 0; nStep < nLength; ++nStep)
		{
			if( cCPRParse.isCPRScopeOrder(lptrCPRDatas[nStep], true) && pPressureColl->getLogicalValue(lptrCPRDatas[nStep]) > 2 )
			{//小于2mm时也不修改m_iDelayTime
				delayTime = 0;
			}
		}
		if(buffTimeEvent == 0 && transEvent == 0)
		{
			if( !cCPRParse.isCPRScopeOrder(lptrCPRDatas[0], true) )
				return;
		}
		loopBuff.WriteData(lptrCPRDatas, nLength);
		if(transEvent == 0 && buffTimeEvent == 0)
		{
			buffTimeEvent = 3; //SetTimer(2,300,NULL);
		}
	}

	/*******************************************************************************/
	// 函数名称： intervalTicktimeHandle
	// 功能： 间隔100毫秒时间处理函数
	// 参数： 
	//        
	// 返回值:  
	void CPressurePhaseStatistic::intervalTicktimeHandle(const CPressureCollate *pPressureColl, const CBreathCollate *pBreathColl)
	{
		CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_mutable_instance();
		if( transEvent == 1 )
		{//缓冲数据小于6个，每次传一个数据；缓冲数据大于6个小于10个，每次传两个数据；缓冲数据大于10个，每次传三个数据
			++delayTime;
			int i = 1;
			if(loopBuff.GetCurrBufferNum() > 6 || loopBuff.GetCurrBufferNum() < 10)
				i = 2;
			else if(loopBuff.GetCurrBufferNum() >= 10)
				i = 3;
			for(;i>0;--i)
			{
				while(1)
				{
					_CPRData  cCPRData[1];
                    short     dwActiveSize = 0;
					if( loopBuff.ReadDataMovePtr(cCPRData, 1, &dwActiveSize) == false)
					{
						dwActiveSize = 0;
					}
					if(delayTime == 15)
					{
						//插入Pressure结束
						cCPRData[0] = cCPRParse.createPressurePhaseData( false );
						dwActiveSize = 1;
						//--------------------------------------------------------------------
						if( actCPRDetailShowInterface != NULL )
						{
							actCPRDetailShowInterface->OnPressureStateAct( false );
						}
						delayTime += 1;
						transEvent = 0;
					}
					if(dwActiveSize == 1)
					{
						if( cCPRParse.isCPROrder(cCPRData[0]) )
						{//对幅度和命令的数据加入到m_pwndCPR
							cprRealTimePhaseStatisticHandle(cCPRData[0], pPressureColl);
							break;//不处理实时数据
						}
					}
					else
					{
						i = 0;
						break;
					}
				}
			}
		}
		if( buffTimeEvent == 3 )
		{//缓冲计数器
			buffTimeEvent = 0;
			delayTime = 0;   //设置Delay计数器为0
			transEvent = 1;  //SetTimer(1,100,NULL);
			//插入Pressure开始
			_CPRData  cCPRData = cCPRParse.createPressurePhaseData( true );
			cprRealTimePhaseStatisticHandle(cCPRData, pPressureColl);
			//--------------------------------------------------------------------
			if( actCPRDetailShowInterface != NULL )
			{
				actCPRDetailShowInterface->OnPressureStateAct( true );
			}
		}
	}

	/*******************************************************************************/
	// 函数名称： increaseSecondTickNotify
	// 功能： 每一秒时钟事件通知
	// 参数： 
	//        scriptRunTime:   场景运行时间
	// 返回值:
	void CPressurePhaseStatistic::increaseSecondTickNotify(const time_duration &scriptRunTime)
	{
		if( !currentSegStat.bValidate )
		{
			currentSegStat.segBeginTime = scriptRunTime;
			currentSegStat.segPeriod = seconds(0);
		}
		else
		{
			currentSegStat.segPeriod += seconds(1);
		}
		//中断时间判断
		if( !currentSegStat.bValidate && phaseStatSegs.size() > 0)
		{
			interruptTime += seconds(1);
			accumInterruptTime += 1;
		}
		else
		{
			interruptTime = seconds(0);
		}
	}

	/*******************************************************************************/
	// 函数名称： OnCPRRealTimePhaseStatisticHandle
	// 功能： CPR阶段性操作统计处理函数 
	// 参数： 
	//        const _CPRData &cCPRData: 幅度或命令指令
	// 返回值:  
	void CPressurePhaseStatistic::cprRealTimePhaseStatisticHandle(const _CPRData &cCPRData, const CPressureCollate *pPressureColl)
	{
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		if( cCPRParse.judgeCPRPhaseStartOrFinishOrder(cCPRData, true, indeterminate) )
		{
			if( cCPRParse.judgeCPRPhaseStartOrFinishOrder(cCPRData, true, true) )
			{
				//按压阶段开始
				currentSegStat.bValidate = true;
				currentSegStat.segPeriod = seconds(0);
			}
			else
			{
				//按压阶段结束，拷贝当前的统计到备份列表
				if( currentSegStat.sumNum > 0 )
				{
					_StatPressueSeg *pBackupsSegStat = new _StatPressueSeg;
					*pBackupsSegStat = currentSegStat;
					phaseStatSegs.push_back( pBackupsSegStat );
					//按压阶段统计日志
					logPressurePhaseStatistic( pBackupsSegStat, m_pEventLogInterface );
				}
				currentSegStat.reset();
			}
		}
		else if( cCPRParse.isCPRScopeOrder(cCPRData, true) )
		{
			currentSegStat.average += pPressureColl->getLogicalValue(cCPRData);
			//按压幅度
			if( pPressureColl->judgeIsOver( cCPRData ) )
			{
				currentSegStat.overNum += 1;
			}
			else if( pPressureColl->judgeIsLower( cCPRData ) )
			{
				currentSegStat.lackNum += 1;
			}
		}
		else if( cCPRParse.isRateOrder( cCPRData, true) )
		{
			//正确频率范围(100~120/分钟)内的个数
			int  nRate = 0;
			boost::tie(nRate, boost::tuples::ignore) = cCPRParse.getPressureRateValue( cCPRData );
			if( nRate <= 120 && nRate >= 100 )
			{
				currentSegStat.rateRightSum += 1;
			}
		}
	}

	/*******************************************************************************/
	// 函数名称： cprPhaseStatisticHandle
	// 功能： CPR阶段性操作统计处理函数 
	// 参数： 
	//       cprData:
	// 返回值:  
    void CPressurePhaseStatistic::cprPhaseStatisticHandle(const _CPRData &cprData, _eCPRErrorSign  eErrorSign, short uLackNum, _eCPRErrorSign ePractiseExtendSign, _CPRManageState eState)
	{
		_eCPRErrorSign    eCPRSigns[2];
		eCPRSigns[0]  = eErrorSign;
		eCPRSigns[1]  = ePractiseExtendSign;
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		for ( int nStep = 0; nStep < 2; ++nStep )
		{
			switch( eCPRSigns[nStep] )
			{
			case CS_Pressure_Right:
				{
					currentSegStat.rightNum += 1;
					break;
				}
			case CS_PressureNumOver:
				{
					currentSegStat.sumErrorNum += 1;
					currentSegStat.overSumNum += 1;
					break;
				}
			case CS_PressureNumLack:
				{
					currentSegStat.sumErrorNum += uLackNum;
					currentSegStat.lackSumNum += uLackNum;
					break;
				}
			default:
				{
					if( eCPRSigns[nStep] != CS_None && cCPRParse.isCPRScopeOrder(cprData, true) )
					{
						currentSegStat.sumErrorNum += 1;
					}
					break;
				}
			}
		}
		if( cCPRParse.isCPRScopeOrder(cprData, true) )
		{
			currentSegStat.sumNum += 1;
			//-----------------------------------------------------------------------------
			bool completeRight = true;
			boost::dynamic_bitset<>  pos(_CPR_ORDER_L, 0x00);
			//按压位置错误
			boost::tie(boost::tuples::ignore, pos, completeRight) = cCPRParse.getPressureScopeValue(cprData);
			if(  !pos.none() )
			{
				currentSegStat.posErrorNum += 1;
				//按压位置点
				if( pos[0] )
				{
					//按压位置太左
					currentSegStat.posErr_left += 1;
				}
				else if( pos[1] )
				{
					//按压位置太右
					currentSegStat.posErr_right += 1;
				}
				else if( pos[2] )
				{
					//按压位置太高
					currentSegStat.posErr_high += 1;
				}
				else if( pos[3] )
				{
					//按压位置太低
					currentSegStat.posErr_low += 1;
				}
			}
			//按压未释放正确
			if( !completeRight )
			{
				currentSegStat.incompleteNum += 1;
			}
		}
	}

	//重置内容
	void CPressurePhaseStatistic::resetPhaseStatistic()
	{
		accumInterruptTime = 0;
		interruptTime = time_duration(0,0,0);
		currentSegStat.reset();
		__super::resetPhaseStatistic();
	}

	void CPressurePhaseStatistic::logPressurePhaseStatistic(const _StatPressueSeg *pPressureSeg, log::COpLogInterface* pLogInterface)
	{
        /*if( pLogInterface != NULL && pPressureSeg->sumNum > 0 )
		{
			short sRightNum, sErrorNum, sPressureRate, sLogicDepth;
			sRightNum  = pPressureSeg->rightNum;
			sErrorNum  = pPressureSeg->getSumErrorsNum();
			sPressureRate = pPressureSeg->getAverageRate();
			sLogicDepth  = pPressureSeg->getAverageValue();
			pLogInterface->OnPressurePhaseDetailStaticLog((int)sRightNum, (int)sErrorNum, (int)sPressureRate, (int)sLogicDepth);
        }*/
	}

	//按压总次数
	short  CPressurePhaseStatistic::getPressureSumNum()
	{
		short  uSumNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatPressueSeg *pressueSeg = (_StatPressueSeg *)item;
			uSumNum += pressueSeg->sumNum;
		}
		uSumNum += currentSegStat.sumNum;
		return uSumNum;
	}

	//按压正确次数
	short  CPressurePhaseStatistic::getPressureSumRightNum()
	{
		short  uSumRightNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatPressueSeg *pressueSeg = (_StatPressueSeg *)item;
			uSumRightNum += pressueSeg->rightNum;
		}
		uSumRightNum += currentSegStat.rightNum;
		return uSumRightNum;
	}

	//按压错误次数
	short  CPressurePhaseStatistic::getPressureSumErrorsNum()
	{
		short  uSumErrorsNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatPressueSeg *pressueSeg = (_StatPressueSeg *)item;
			uSumErrorsNum += pressueSeg->getSumErrorsNum();
		}
		uSumErrorsNum += currentSegStat.getSumErrorsNum();
		return uSumErrorsNum;
	}

	//按压释放不出次数
	short  CPressurePhaseStatistic::getPressureSumIncomplete()
	{
		short uSumIncomplete = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatPressueSeg *pressueSeg = (_StatPressueSeg *)item;
			uSumIncomplete += pressueSeg->incompleteNum;
		}
		uSumIncomplete += currentSegStat.incompleteNum;
		return uSumIncomplete;
	}

	////按压位置错误次数
	short  CPressurePhaseStatistic::getPressurePosErrorNum(short *pos_low/*=NULL*/, short *pos_high/*=NULL*/, short *pos_left/*=NULL*/, short *pos_Right/*=NULL*/)
	{
		short  uPosEorroNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatPressueSeg *pressueSeg = (_StatPressueSeg *)item;
			uPosEorroNum += pressueSeg->posErrorNum;
			//按压位置太低
			if( pos_low != NULL )
			{
				*pos_low += pressueSeg->posErr_low;
			}
			//按压位置太高
			if( pos_high != NULL )
			{
				*pos_high += pressueSeg->posErr_high;
			}
			 //按压位置太左
			if( pos_left != NULL )
			{
				*pos_left += pressueSeg->posErr_left;
			}
			//按压位置太右
			if( pos_Right != NULL )
			{
				*pos_Right += pressueSeg->posErr_right;
			}
		}
		uPosEorroNum += currentSegStat.posErrorNum;
		//按压位置太低
		if( pos_low != NULL )
		{
			*pos_low += currentSegStat.posErr_low;
		}
		//按压位置太高
		if( pos_high != NULL )
		{
			*pos_high += currentSegStat.posErr_high;
		}
		//按压位置太左
		if( pos_left != NULL )
		{
			*pos_left += currentSegStat.posErr_left;
		}
		//按压位置太右
		if( pos_Right != NULL )
		{
			*pos_Right += currentSegStat.posErr_right;
		}
		return uPosEorroNum;
	}

	//按压过大
	short  CPressurePhaseStatistic::getPressureOverNum()
	{
		short  uOverNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatPressueSeg *pressueSeg = (_StatPressueSeg *)item;
			uOverNum += pressueSeg->overNum;
		}
		uOverNum += currentSegStat.overNum;
		return uOverNum;
	}

	//按压过小
	short  CPressurePhaseStatistic::getPressureLackNum()
	{
		short  uLackNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatPressueSeg *pressueSeg = (_StatPressueSeg *)item;
			uLackNum += pressueSeg->lackNum;
		}
		uLackNum += currentSegStat.lackNum;
		return uLackNum;
	}

	//按压深度正确
	short  CPressurePhaseStatistic::getPressureDepthRightNum()
	{
		short  uRightNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatPressueSeg *pressueSeg = (_StatPressueSeg *)item;
			uRightNum += pressueSeg->getRightDepthNum();
		}
		uRightNum += currentSegStat.getRightDepthNum();
		return uRightNum;
	}

	//返回平均按压深度
	short  CPressurePhaseStatistic::getAverageDepth()
	{
		short  uDepthSum = 0, uSumNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			uDepthSum += item->getAverageValue() * item->getSumCount();
			uSumNum += item->getSumCount();
		}
		uDepthSum += currentSegStat.getAverageValue() * currentSegStat.getSumCount();
		uSumNum += currentSegStat.getSumCount();
		return short(uSumNum > 0 ? uDepthSum/uSumNum : 0);
	}

	//返回平均频率
	short  CPressurePhaseStatistic::getAverageRate()
	{
		short   uRates = 0, uNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			uRates += item->getAverageRate();
			uNum += 1;
		}
		return uNum > 0 ? uRates/uNum : 0;
	}
	//--------------------------------------------------------------------------------------------
	////吹气阶段类
	CBreathPhaseStatistic::CBreathPhaseStatistic()
	{

	}

	CBreathPhaseStatistic::~CBreathPhaseStatistic()
	{

	}

	/*******************************************************************************/
	// 函数名称： cprBreathRealTimeDataHandle
	// 功能： 吹气操作数据处理函数 
	// 参数： 
	// 返回值:  
	void CBreathPhaseStatistic::cprBreathRealTimeDataHandle(const _CPRData *lptrCPRDatas, int nLength, const CBreathCollate *pBreathColl)
	{//吹气幅度：0x4X
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		for (int nStep = 0; nStep < nLength; ++nStep)
		{
			if( cCPRParse.isCPRScopeOrder(lptrCPRDatas[nStep], false) && pBreathColl->getLogicalValue(lptrCPRDatas[nStep]) > 10 )
			{//小于2mm时也不修改m_iDelayTime
				delayTime = 0;
			}
		}
		if(buffTimeEvent == 0 && transEvent == 0)
		{
			if( !cCPRParse.isCPRScopeOrder(lptrCPRDatas[0], false) )
				return;
		}
		loopBuff.WriteData(lptrCPRDatas, nLength);
		if(transEvent == 0 && buffTimeEvent == 0)
		{
			buffTimeEvent = 3; //SetTimer(2,300,NULL);
		}
	}

	/*******************************************************************************/
	// 函数名称： intervalTicktimeHandle
	// 功能： 间隔100毫秒时间处理函数
	// 参数： 
	//        
	// 返回值:  
	void CBreathPhaseStatistic::intervalTicktimeHandle(const CPressureCollate *pPressureColl, const CBreathCollate *pBreathColl)
	{
		CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_mutable_instance();
		if( transEvent == 1 )
		{//缓冲数据小于6个，每次传一个数据；缓冲数据大于6个小于10个，每次传两个数据；缓冲数据大于10个，每次传三个数据
			++delayTime;
			int i = 1;
			if(loopBuff.GetCurrBufferNum() > 6 || loopBuff.GetCurrBufferNum() < 10)
				i = 2;
			else if(loopBuff.GetCurrBufferNum() >= 10)
				i = 3;
			for(;i>0;--i)
			{
				while(1)
				{
					_CPRData cCPRData;
                    short    dwActiveSize = 0;
					if(loopBuff.ReadDataMovePtr(&cCPRData,1,&dwActiveSize) == false)
					{
						dwActiveSize = 0;
					}
					if(delayTime == 30)
					{
						transEvent = 0;
						//插入Breath结束
						cCPRData = cCPRParse.createBreathPhaseData(false);
						dwActiveSize = 1;
						//--------------------------------------------------------------------
						if( actCPRDetailShowInterface != NULL )
						{
							actCPRDetailShowInterface->OnBreathStateAct( false );
						}
						delayTime += 1;
					}
					if(dwActiveSize == 1)
					{
						if( cCPRParse.isCPROrder(cCPRData) )
						{//对幅度和命令的数据处理
							cprRealTimePhaseStatisticHandle(cCPRData, pBreathColl);
							break;//不处理实时数据
						}
					}
					else
					{
						i = 0;
						break;
					}
				}
			}
		}
		if( buffTimeEvent == 3 )
		{//缓冲计数器
			buffTimeEvent = 0;
			delayTime = 0;//设置Delay计数器为0
			transEvent = 1; //SetTimer(1,100,NULL);
			//吹气开始
			_CPRData cCPRData = cCPRParse.createBreathPhaseData(true);
			cprRealTimePhaseStatisticHandle(cCPRData, pBreathColl);
			//--------------------------------------------------------------------
			if( actCPRDetailShowInterface != NULL )
			{
				actCPRDetailShowInterface->OnBreathStateAct( TRUE );
			}
		}
	}


	/*******************************************************************************/
	// 函数名称： increaseSecondTickNotify
	// 功能： 每一秒时钟事件通知
	// 参数： 
	//        scriptRunTime:   场景运行时间
	// 返回值:
	void CBreathPhaseStatistic::increaseSecondTickNotify(const time_duration &scriptRunTime)
	{
		if( !currentSegStat.bValidate )
		{
			currentSegStat.segBeginTime = scriptRunTime;
			currentSegStat.segPeriod = seconds(0);
		}
		else
		{
			currentSegStat.segPeriod += seconds(1);
		}
		//.....
	}

	/*******************************************************************************/
	// 函数名称： OnCPRRealTimePhaseStatisticHandle
	// 功能： CPR阶段性操作统计处理函数 
	// 参数： 
	//        _CPRData cCPRData:  幅度或指令
	// 返回值:  
	void CBreathPhaseStatistic::cprRealTimePhaseStatisticHandle(const _CPRData &cCPRData, const CBreathCollate *pBreathColl)
	{
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		if( cCPRParse.judgeCPRPhaseStartOrFinishOrder(cCPRData, false, indeterminate) )
		{
			if( cCPRParse.judgeCPRPhaseStartOrFinishOrder(cCPRData, false, true) )
			{
				//吹气阶段开始
				currentSegStat.bValidate = true;
				currentSegStat.segPeriod = seconds(0);
			}
			else
			{
				//吹气阶段结束，拷贝当前的统计到备份列表
				if( currentSegStat.sumNum > 0 )
				{
					_StatBreathSeg *pBackupsSegStat = new _StatBreathSeg;
					*pBackupsSegStat = currentSegStat;
					phaseStatSegs.push_back( pBackupsSegStat );
					//吹气阶段统计日志
					logBreathPhaseStatistic( pBackupsSegStat, m_pEventLogInterface );
				}
				currentSegStat.reset();
			}
		}
		else if( cCPRParse.isCPRScopeOrder(cCPRData, false) )
		{
			currentSegStat.average += pBreathColl->getLogicalValue(cCPRData);
			//吹气幅度
			if( pBreathColl->judgeIsOver( cCPRData ) )
			{
				currentSegStat.overNum += 1;
			}
			else if( pBreathColl->judgeIsOver( cCPRData ) )
			{
				currentSegStat.lackNum += 1;
			}
			//通气时间
			if( pBreathColl->judgeIsRespTimeOver( cCPRData ) )
			{
				currentSegStat.ventiOverTimeNum += 1;
			}
			else if( pBreathColl->judgeIsRespTimeLower( cCPRData ) )
			{
				currentSegStat.ventiLowerTimeNum += 1;
			}
		}
	}

	/*******************************************************************************/
	// 函数名称： cprPhaseStatisticHandle
	// 功能： CPR阶段性操作统计处理函数 
	// 参数： 
	//       cprData:
	// 返回值:  
    void CBreathPhaseStatistic::cprPhaseStatisticHandle(const _CPRData &cprData, _eCPRErrorSign  eErrorSign, short uLackNum, _eCPRErrorSign ePractiseExtendSign, _CPRManageState eState)
	{
		_eCPRErrorSign    eCPRSigns[2];
		eCPRSigns[0]  = eErrorSign;
		eCPRSigns[1]  = ePractiseExtendSign;
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		for ( int nStep = 0; nStep < 2; ++nStep )
		{
			switch( eCPRSigns[nStep] )
			{
			case CS_Breath_Right:
				{
					currentSegStat.rightNum += 1;
					break;
				}
			case CS_BreathNumLack:
				{
					currentSegStat.sumErrorNum += uLackNum;
					currentSegStat.lackSumNum += uLackNum;
					break;
				}
			case CS_BreathNumOver:
				{
					currentSegStat.sumErrorNum += 1;
					currentSegStat.overSumNum += 1;
					break;
				}
			default:
				{
					if( eCPRSigns[nStep] != CS_None && cCPRParse.isCPRScopeOrder(cprData, false) )
					{
						currentSegStat.sumErrorNum += 1;
					}
					break;
				}
			}
		}
		if( cCPRParse.isCPRScopeOrder(cprData, false) )
		{
			currentSegStat.sumNum += 1;
		}
	}

	//重置内容
	void CBreathPhaseStatistic::resetPhaseStatistic()
	{
		currentSegStat.reset();
		__super::resetPhaseStatistic();
	}

	//统计吹气阶段性操作数据量
	void CBreathPhaseStatistic::logBreathPhaseStatistic(const _StatBreathSeg *pBreathSeg,  log::COpLogInterface* pLogInterface)
	{
        /*if( pLogInterface != NULL && pBreathSeg->getSumCount() > 0 )
		{
			short sRightNum, sErrorNum, sBreathRate, sLogicDepth;
			sRightNum  = pBreathSeg->rightNum;
			sErrorNum  = pBreathSeg->getSumErrorsNum();
			sBreathRate = pBreathSeg->getAverageRate();
			sLogicDepth  = pBreathSeg->getAverageValue();
			pLogInterface->OnBreathPhaseDetailStaticLog((int)sRightNum, (int)sErrorNum, (float)sBreathRate, (int)sLogicDepth);
        }*/
	}

    //吹气总次数
	short  CBreathPhaseStatistic::getBreathSumNum()
	{
		short  uSumNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uSumNum += breathSeg->sumNum;
		}
		uSumNum += currentSegStat.sumNum;
		return uSumNum;
	}

	//吹气正确次数
	short  CBreathPhaseStatistic::getBreathSumRightNum()
	{
		short  uSumRightNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uSumRightNum += breathSeg->rightNum;
		}
		uSumRightNum += currentSegStat.rightNum;
		return uSumRightNum;
	}

	//吹气错误次数
	short  CBreathPhaseStatistic::getBreathSumErrorsNum()
	{
		short uSumErrorsNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uSumErrorsNum += breathSeg->getSumErrorsNum();
		}
		uSumErrorsNum += currentSegStat.getSumErrorsNum();
		return uSumErrorsNum;
	}

	short  CBreathPhaseStatistic::getBreathOverNum()
	{
		short uOverNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uOverNum += breathSeg->overNum;
		}
		uOverNum += currentSegStat.overNum;
		return uOverNum;
	}

	short  CBreathPhaseStatistic::getBreathLackNum()
	{
		short uLackNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uLackNum += breathSeg->lackNum;
		}
		uLackNum += currentSegStat.lackNum;
		return uLackNum;
	}

	short  CBreathPhaseStatistic::getBreathInStomachNum()
	{
		short uInStomachNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uInStomachNum += breathSeg->stomachNum;
		}
		uInStomachNum += currentSegStat.stomachNum;
		return uInStomachNum;
	}

	short  CBreathPhaseStatistic::getBreathPipeCloseNum()
	{
		short uPipeCloseNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uPipeCloseNum += breathSeg->pipeCloseNum;
		}
		uPipeCloseNum += currentSegStat.pipeCloseNum;
		return uPipeCloseNum;
	}

	//返回平均吹气量
	short  CBreathPhaseStatistic::getAverageVolume()
	{
		short  uVolumeSum = 0, uSumNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			uVolumeSum += item->getAverageValue() * item->getSumCount();
			uSumNum += item->getSumCount();
		}
		uVolumeSum += currentSegStat.getAverageValue() * currentSegStat.getSumCount();
		uSumNum += currentSegStat.getSumCount();
		return short(uSumNum > 0 ? uVolumeSum/uSumNum : 0);
	}

	//通气时间过长
	short CBreathPhaseStatistic::getVentiOverTimeNum()
	{
		short uOverTimeNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uOverTimeNum += breathSeg->ventiOverTimeNum;
		}
		uOverTimeNum += currentSegStat.ventiOverTimeNum;
		return uOverTimeNum;
	}

	//通气时间过短
	short CBreathPhaseStatistic::getVentiLowerTimeNum()
	{
		short uLowerTimeNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uLowerTimeNum += breathSeg->ventiLowerTimeNum;
		}
		uLowerTimeNum += currentSegStat.ventiLowerTimeNum;
		return uLowerTimeNum;
	}
}}
