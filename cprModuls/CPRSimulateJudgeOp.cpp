#include <boost/assert.hpp>
#include ".\CPRSimulateJudgeOp.h"
#include ".\Collates.h"

#include "..\Common\ParseCPRData_Singleton.h"


namespace jysoft{  namespace cpr 
{
	CCPRSimulateJudgeOp::CCPRSimulateJudgeOp(_CPRManageState eManageState)
	{
		m_eManageState        = eManageState;
		//常规CPR
		m_cCPRRule.setDefaultCPRRule();

		m_cRunCPRRule.copy(&m_cCPRRule);
		m_pCurrDetail = m_cRunCPRRule.detailRules;
		assert( m_pCurrDetail != NULL );
		m_bComplete  = false;
		//------------------------------------------------------------------------------------------------------------
		resetSimulateParam();
	}

	CCPRSimulateJudgeOp::~CCPRSimulateJudgeOp(void)
	{
	}

	//重设置模拟人的状态
	void CCPRSimulateJudgeOp::resetSimulateParam()
	{
		//常规CPR
		m_cCPRRule.setDefaultCPRRule();

		m_cRunCPRRule.copy(&m_cCPRRule);
		m_pCurrDetail = m_cRunCPRRule.detailRules;
		assert( m_pCurrDetail != NULL );
		m_bComplete  = false;
		//------------------------------------------------------------------
		m_nPressureNum = 0;
		m_nBreathNum   = 0;
		m_bBreathAccessJam = false;  //阻塞
	}

	void CCPRSimulateJudgeOp::resetSimulateParam(_CPRManageState eManageState, _CPRRuleStruct *pCPRRule)
	{
		m_eManageState = eManageState;
		resetSimulateParam();
		if( pCPRRule != NULL)
		{
			m_cCPRRule.copy(pCPRRule);
			//设置开始位置
			m_cRunCPRRule.copy(&m_cCPRRule);
			m_pCurrDetail = m_cRunCPRRule.detailRules;
			assert( m_pCurrDetail != NULL );
		}
	}

	//重设当前用的判断规则
	void CCPRSimulateJudgeOp::resetCurrentSimulateParam()
	{
		m_cRunCPRRule.copy(&m_cCPRRule);
		m_pCurrDetail = m_cRunCPRRule.detailRules;
		assert( m_pCurrDetail != NULL );
		m_bComplete  = false;
		//------------------------------------------------------------------
		m_nPressureNum = 0;
		m_nBreathNum   = 0;
		m_bBreathAccessJam = false;  //阻塞
	}

	//转到下一个Detail
	bool CCPRSimulateJudgeOp::transportNextDetail()
	{
		bool  bComplete = m_bComplete;
		_CPRRule_DetailStruct *pNextDetail = m_pCurrDetail->getNextDetailRule();
		if(pNextDetail == NULL )
		{//到尾部，转到开始位置
			m_cRunCPRRule.m_nCycle -= 1;
			if( m_cRunCPRRule.m_nCycle <= 0 )
			{
				m_bComplete = true;
			}
			m_pCurrDetail = m_cRunCPRRule.detailRules;
		}
		else
		{
			m_pCurrDetail = pNextDetail;
		}
		return m_bComplete;
	}

	/*******************************************************************************/
	// 函数名称： JudgeCPRData
	// 功能： 结合CPR操作规则，对用户的操作进行判断
	// 参数： const _CPRData &cprData: CPR数据
	//        CPressureCollate *pPressureCollate:
	//        CBreathCollate *pBreathCollate:
	//        UINT &uLackNum: 
	//        boost::optional<int> &cycleNum:   循环次数
	//        _eCPRErrorSign &ePractiseExtendSign:    实战方式时，延伸出的判断
	// 返回值: 
    _eCPRErrorSign CCPRSimulateJudgeOp::judgeCPRData(const _CPRData &cprData, const CPressureCollate *pPressureCollate, const CBreathCollate *pBreathCollate, /*out*/short &uLackNum, /*out*/_eCPRErrorSign &ePractiseExtendSign, /*in,out*/boost::optional<int> &cycleNum)
	{
		uLackNum = 0;
		_eCPRErrorSign   eRtnSign;
		ePractiseExtendSign   = CS_None;
		if(m_cCPRRule.m_eRuleType == eCPROnlyBreathType)
		{
			cycleNum = boost::none;
			eRtnSign = singleBreathJudfeCPRData(cprData, pBreathCollate);
		}
		else if(m_cCPRRule.m_eRuleType == eCPROnlyPressureType)
		{
			eRtnSign = singlePressureJudfeCPRData(cprData, pPressureCollate, cycleNum);
		}
		else
		{
			//注：按照CPR操作规则完成后，继续后续操作进行判断 <2017/1/8 hjg 修改>
			switch(m_eManageState)
			{
			case aCPRPopularMode:
			case aCPRPractiseMode:
				{
					eRtnSign = practiseJudgeCPRData(cprData, pPressureCollate, pBreathCollate, /*out*/uLackNum, /*out*/ePractiseExtendSign, /*in,out*/cycleNum);
					break;
				}
			}
		}
		return eRtnSign;
	}

    //实战练习模式
    _eCPRErrorSign CCPRSimulateJudgeOp::practiseJudgeCPRData(const _CPRData &cprData, const CPressureCollate *pPressureCollate, const CBreathCollate *pBreathCollate, short &uLackNum, _eCPRErrorSign &ePractiseExtendSign, /*in,out*/boost::optional<int> &cycleNum)
	{
		//初始设置
		uLackNum = 0;
		_eCPRErrorSign  eRtnSign = CS_None;
		ePractiseExtendSign   = CS_None;
		const CParseCPRData_Singleton *pCPRParse = &CParseCPRData_Singleton::get_const_instance();
		if( pCPRParse->isCPRScopeOrder(cprData, true) )
		{//按压的幅度
			if( m_pCurrDetail->m_bBreath && (m_nPressureNum > 0 || m_nBreathNum == 0) )
			{
				eRtnSign  = CS_PressureNumOver;
			}
			else 
			{
				if( m_pCurrDetail->m_bBreath )
				{
					eRtnSign = CS_BreathNumLack;  //吹气次数太少
					if( m_pCurrDetail->m_nNumber > m_nBreathNum)
					{
						uLackNum = m_pCurrDetail->m_nNumber - m_nBreathNum;
					}
					//转到下一个Detail
					m_bComplete = transportNextDetail();
					//统计循环次数 2017.4.26 add
					cycleNum = (cycleNum == boost::none ? 0 : *cycleNum) + 1;
				}
				else if( cycleNum == boost::none )
				{
					cycleNum = 1;
				}
				else if( m_nBreathNum > 0 )
				{
					cycleNum = *cycleNum + 1;
				}
				if( pPressureCollate->isIncompleteError(cprData) )
				{
					//释放不足
					if( eRtnSign == CS_BreathNumLack )
					{
						ePractiseExtendSign = CS_PressureIncompleteErr;
					}
					else
					{
						eRtnSign = CS_PressureIncompleteErr;
					}
				}
				else if( pPressureCollate->isPressurePositionError( cprData ) )
				{//按压位置错误
					if( eRtnSign == CS_BreathNumLack )
					{
						ePractiseExtendSign = CS_PressurePosErr;
					}
					else
					{
						eRtnSign = CS_PressurePosErr;
					}
				}
				else if( pPressureCollate->judgeIsLower(cprData) )
				{//过小
					if( eRtnSign == CS_BreathNumLack )
					{
						ePractiseExtendSign = CS_PressureLack;
					}
					else
					{
						eRtnSign = CS_PressureLack;
					}
				}
				else if( pPressureCollate->judgeIsOver( cprData ) )
				{//过大
					if( eRtnSign == CS_BreathNumLack )
					{
						ePractiseExtendSign = CS_PressureOverBig;
					}
					else
					{
						eRtnSign = CS_PressureOverBig;
					}
				}
				else
				{
					if( eRtnSign == CS_BreathNumLack )
					{
						ePractiseExtendSign = CS_Pressure_Right;
					}
					else
					{
						eRtnSign = CS_Pressure_Right;
					}
				}

				m_nBreathNum = 0;
				m_nPressureNum += 1;
				if(m_pCurrDetail->m_nNumber == m_nPressureNum)
				{//转到下一个Detail
					m_bComplete = transportNextDetail();
				}
			}
		}
		else if( pCPRParse->isCPRScopeOrder(cprData, false) )
		{//吹气的幅度
			if( m_pCurrDetail->m_bBreath == false && (m_nBreathNum > 0 || m_nPressureNum == 0) )
			{
				//还在吹气
				eRtnSign = CS_BreathNumOver;
			}
			else 
			{
				if( m_pCurrDetail->m_bBreath == false )
				{
					eRtnSign = CS_PressureNumLack; //按压次数太少
					if( m_pCurrDetail->m_nNumber > m_nPressureNum )
					{
						uLackNum = m_pCurrDetail->m_nNumber - m_nPressureNum;
					}
					//转到下一个Detail
					m_bComplete = transportNextDetail();
				}
				m_nPressureNum = 0;
				//判断数据是否在正确的范围内
				if( pBreathCollate->judgeIsLower( cprData ) )
				{//过小
					if( eRtnSign == CS_PressureNumLack )
					{
						ePractiseExtendSign  = CS_BreathLack;
					}
					else
					{
						eRtnSign = CS_BreathLack;
					}
				}
				else if( pBreathCollate->judgeIsOver( cprData ) )
				{//过大
					if( pBreathCollate->isToStomach( cprData ) )
					{//过大，就表示为进胃
						if( eRtnSign == CS_PressureNumLack )
						{
							ePractiseExtendSign  = CS_BreathInStomach;
						}
						else
						{
							eRtnSign = CS_BreathInStomach;
						}
					}
					else
					{
						if( eRtnSign == CS_PressureNumLack )
						{
							ePractiseExtendSign  = CS_BreathOverBig;//过大
						}
						else
						{
							eRtnSign = CS_BreathOverBig;//过大
						}
					}
				}
				else if( pBreathCollate->judgeIsRespTimeOver(cprData) ) 
				{//通气多长
					if( eRtnSign == CS_PressureNumLack )
					{
						ePractiseExtendSign  = CS_RespTimeOver;
					}
					else
					{
						eRtnSign = CS_RespTimeOver;
					}
				}
				else if( pBreathCollate->judgeIsRespTimeLower(cprData) ) 
				{//通气多短
					if( eRtnSign == CS_PressureNumLack )
					{
						ePractiseExtendSign  = CS_RespTimeLower;
					}
					else
					{
						eRtnSign = CS_RespTimeLower;
					}
				}
				else
				{
					if( eRtnSign == CS_PressureNumLack )
					{
						ePractiseExtendSign  = CS_Breath_Right;
					}
					else
					{
						eRtnSign = CS_Breath_Right;
					}
				}

				m_nBreathNum += 1;
				if(m_pCurrDetail->m_nNumber == m_nBreathNum)
				{//转到下一个Detail
					m_bComplete = transportNextDetail();
				}
			}
			//统计循环次数 2017.4.26 add
			if( cycleNum == boost::none )
			{
				cycleNum = 1;
			}
		}
		return eRtnSign;
	}

	//标准训练模式
	_eCPRErrorSign CCPRSimulateJudgeOp::exerciseJudgeCPRData(const _CPRData &cprData, const CPressureCollate *pPressureCollate, const CBreathCollate *pBreathCollate, /*in,out*/boost::optional<int> &cycleNum)
	{
		//初始设置
		_eCPRErrorSign eRtnSign = CS_None;
		const CParseCPRData_Singleton *pCPRParse = &CParseCPRData_Singleton::get_const_instance();
		if( pCPRParse->isCPRScopeOrder(cprData, true) )
		{//按压的幅度
			if( m_pCurrDetail->m_bBreath)
			{//吹气没做完
				if( m_nBreathNum == 0)
					eRtnSign = CS_PressureNumOver;
				else
					eRtnSign = CS_BreathNumLack;  //吹气次数太少
			}
			else
			{
				if( pPressureCollate->isIncompleteError(cprData) )
				{
					//释放不足
					eRtnSign = CS_PressureIncompleteErr;
				}
				else if( pPressureCollate->isPressurePositionError( cprData ) )
				{//按压位置错误
					eRtnSign = CS_PressurePosErr;
				}
				else if( pPressureCollate->judgeIsLower(cprData) )
				{//过小
					eRtnSign = CS_PressureLack;
				}
				else if( pPressureCollate->judgeIsOver(cprData) )
				{//过大
					eRtnSign = CS_PressureOverBig;
				}
				else
				{
					eRtnSign = CS_Pressure_Right;
				}

				if(eRtnSign == CS_Pressure_Right)
				{
					m_nPressureNum += 1;
					if(m_pCurrDetail->m_nNumber == m_nPressureNum)
					{
						//转到下一个Detail
						m_bComplete = transportNextDetail();
					}
				}
				m_nBreathNum = 0;
				//统计循环次数 2017.4.26 add
				cycleNum = (cycleNum == boost::none ? 0 : cycleNum.get()) + 1;
			}
		}
		else if( pCPRParse->isCPRScopeOrder(cprData, false) )
		{//吹气的幅度
			if( m_pCurrDetail->m_bBreath == false)
			{
				if( m_nPressureNum == 0 )
					eRtnSign = CS_BreathNumOver;
				else
					eRtnSign = CS_PressureNumLack;//按压次数太少
			}
			else
			{
				m_nPressureNum = 0;
				//判断数据是否在正确的范围内
				if( pBreathCollate->judgeIsLower( cprData ) )
				{//过小
					eRtnSign = CS_BreathLack;
				}
				else if( pBreathCollate->judgeIsOver( cprData ) )
				{//过大
					if( pBreathCollate->isToStomach( cprData ) )
					{//过大，就表示为进胃
						eRtnSign = CS_BreathInStomach;
					}
					else
					{
						eRtnSign = CS_BreathOverBig;//过大
					}
				}
				else
				{
					eRtnSign = CS_Breath_Right;
				}

				if(eRtnSign == CS_Breath_Right)
				{
					m_nBreathNum += 1;
					if( m_pCurrDetail->m_nNumber == m_nBreathNum)
					{
						//转到下一个Detail
						m_bComplete = transportNextDetail();
					}
				}
			}
			//统计循环次数 2017.4.26 add
			if( cycleNum == boost::none )
			{
				cycleNum = 1;
			}
		}
		return eRtnSign;
	}

	//且吹气模式
	_eCPRErrorSign CCPRSimulateJudgeOp::singleBreathJudfeCPRData(const _CPRData &cprData, const CBreathCollate *pBreathCollate)
	{
		_eCPRErrorSign eRtnSign = CS_None;
		const CParseCPRData_Singleton *pCPRParse = &CParseCPRData_Singleton::get_const_instance();
		if( pCPRParse->isCPRScopeOrder(cprData, false) )
		{//吹气的幅度
			//判断数据是否在正确的范围内
			if( pBreathCollate->judgeIsLower( cprData ) )
			{//过小
				eRtnSign = CS_BreathLack;
			}
			else if( pBreathCollate->judgeIsOver( cprData ) )
			{//过大
				if( pBreathCollate->isToStomach( cprData ) )
				{//过大，就表示为进胃
					eRtnSign = CS_BreathInStomach;
				}
				else
				{
					eRtnSign = CS_BreathOverBig;//过大
				}
			}
			else
			{
				eRtnSign = CS_Breath_Right;
			}

			if(m_nBreathNum == -1)
				m_nBreathNum = 1;
			else
				m_nBreathNum += 1;
		}
		else if( pCPRParse->isCPRScopeOrder(cprData, true) )
		{
			eRtnSign = CS_BreathNumLack;  //吹气次数太少
		}
		return eRtnSign;
	}

	//且胸外按压模式
	_eCPRErrorSign CCPRSimulateJudgeOp::singlePressureJudfeCPRData(const _CPRData &cprData, const CPressureCollate *pPressureCollate, /*out*/boost::optional<int> &cycleNum)
	{
		_eCPRErrorSign eRtnSign = CS_None;
		const CParseCPRData_Singleton *pCPRParse = &CParseCPRData_Singleton::get_const_instance();
		if( pCPRParse->isCPRScopeOrder(cprData, true) )
		{//按压的幅度
			if( pPressureCollate->isIncompleteError(cprData) )
			{
				//释放不足
				eRtnSign = CS_PressureIncompleteErr;
			}
			else if( pPressureCollate->isPressurePositionError( cprData ) )
			{//按压位置错误
				eRtnSign = CS_PressurePosErr;
			}
			else if( pPressureCollate->judgeIsLower( cprData ) )
			{//过小
				eRtnSign = CS_PressureLack;
			}
			else if( pPressureCollate->judgeIsOver( cprData ) )
			{//过大
				eRtnSign = CS_PressureOverBig;
			}
			else
			{
				eRtnSign = CS_Pressure_Right;
			}
			if(m_nPressureNum == -1)
				m_nPressureNum = 1;
			else
				m_nPressureNum += 1;
			cycleNum = m_nPressureNum / 30 + 1;
		}
		else if( pCPRParse->isCPRScopeOrder(cprData, false) )
		{
			eRtnSign = CS_PressureNumLack; //按压次数太少
			//统计循环次数 2017.4.26 add
			if( cycleNum == boost::none )
			{
				cycleNum = 1;
			}
		}
		return eRtnSign;
	}

}}
