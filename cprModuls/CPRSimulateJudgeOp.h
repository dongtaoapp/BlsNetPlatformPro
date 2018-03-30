#pragma once
#include <boost/optional.hpp>
#include ".\cprmoduls_global.h"

#include "..\Common\CommonGlobal.h"


namespace jysoft{  namespace cpr 
{
	//功能：根据模拟人的状态，结合CPR标准，对用户的操作进行判断
	class CBreathCollate;
	class CPressureCollate;
    class CPRMODULSSHARED_EXPORT CCPRSimulateJudgeOp
	{
	public:
		CCPRSimulateJudgeOp(_CPRManageState eManageState);
		virtual ~CCPRSimulateJudgeOp(void);
	public:
		//重设置模拟人的状态
		void resetSimulateParam();
		void resetSimulateParam(_CPRManageState eManageState, _CPRRuleStruct *pCPRRule);
		//重设当前用的判断规则
		void resetCurrentSimulateParam();
		inline int getBreathNum() { return m_nBreathNum; };
		inline _CPRManageState get_eCPRState() { return m_eManageState; };
	public:
		/*******************************************************************************/
		// 函数名称： JudgeCPRData
		// 功能： 结合CPR操作规则，对用户的操作进行判断
		// 参数： const _CPRData &cprData: CPR数据
		//        CPressureCollate *pPressureCollate:
		//        CBreathCollate *pBreathCollate:
        //        short &uLackNum:
		//        _eCPRErrorSign &ePractiseExtendSign:    实战方式时，延伸出的判断
		//        boost::optional<int> &cycleNum:   循环次数
		// 返回值: 
        _eCPRErrorSign judgeCPRData(const _CPRData &cprData, const CPressureCollate *pPressureCollate, const CBreathCollate *pBreathCollate, /*out*/short &uLackNum, /*out*/_eCPRErrorSign &ePractiseExtendSign, /*in,out*/boost::optional<int> &cycleNum);
	public:
		inline bool isCompleteCurrentCPR() { return m_bComplete;};
	private:
		//实战练习模式
        _eCPRErrorSign practiseJudgeCPRData(const _CPRData &cprData, const CPressureCollate *pPressureCollate, const CBreathCollate *pBreathCollate, short &uLackNum, _eCPRErrorSign &ePractiseExtendSign, /*in,out*/boost::optional<int> &cycleNum);
		//标准训练模式
		_eCPRErrorSign exerciseJudgeCPRData(const _CPRData &cprData, const CPressureCollate *pPressureCollate, const CBreathCollate *pBreathCollate, /*in,out*/boost::optional<int> &cycleNum);
		//且吹气模式
		_eCPRErrorSign singleBreathJudfeCPRData(const _CPRData &cprData, const CBreathCollate *pBreathCollate);
		//且胸外按压模式
		_eCPRErrorSign singlePressureJudfeCPRData(const _CPRData &cprData, const CPressureCollate *pPressureCollate, /*in,out*/boost::optional<int> &cycleNum);
		//转到下一个Detail
		bool transportNextDetail();
	protected:
		int                           m_nPressureNum;          //按压的次数
		int                           m_nBreathNum;            //吹气的次数
		bool                          m_bBreathAccessJam;      //气道是否阻塞
		//-----------------------------------------------------------------------------
		_CPRManageState               m_eManageState;
		_CPRRuleStruct                m_cCPRRule;
	private:
		_CPRRuleStruct                m_cRunCPRRule;           //当前运行的CPR循环情况
		_CPRRule_DetailStruct*        m_pCurrDetail;
		bool                          m_bComplete;             //是否完成指定的CPR循环
	};
}}
