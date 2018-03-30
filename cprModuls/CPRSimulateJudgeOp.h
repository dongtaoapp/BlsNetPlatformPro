#pragma once
#include <boost/optional.hpp>
#include ".\cprmoduls_global.h"

#include "..\Common\CommonGlobal.h"


namespace jysoft{  namespace cpr 
{
	//���ܣ�����ģ���˵�״̬�����CPR��׼�����û��Ĳ��������ж�
	class CBreathCollate;
	class CPressureCollate;
    class CPRMODULSSHARED_EXPORT CCPRSimulateJudgeOp
	{
	public:
		CCPRSimulateJudgeOp(_CPRManageState eManageState);
		virtual ~CCPRSimulateJudgeOp(void);
	public:
		//������ģ���˵�״̬
		void resetSimulateParam();
		void resetSimulateParam(_CPRManageState eManageState, _CPRRuleStruct *pCPRRule);
		//���赱ǰ�õ��жϹ���
		void resetCurrentSimulateParam();
		inline int getBreathNum() { return m_nBreathNum; };
		inline _CPRManageState get_eCPRState() { return m_eManageState; };
	public:
		/*******************************************************************************/
		// �������ƣ� JudgeCPRData
		// ���ܣ� ���CPR�������򣬶��û��Ĳ��������ж�
		// ������ const _CPRData &cprData: CPR����
		//        CPressureCollate *pPressureCollate:
		//        CBreathCollate *pBreathCollate:
        //        short &uLackNum:
		//        _eCPRErrorSign &ePractiseExtendSign:    ʵս��ʽʱ����������ж�
		//        boost::optional<int> &cycleNum:   ѭ������
		// ����ֵ: 
        _eCPRErrorSign judgeCPRData(const _CPRData &cprData, const CPressureCollate *pPressureCollate, const CBreathCollate *pBreathCollate, /*out*/short &uLackNum, /*out*/_eCPRErrorSign &ePractiseExtendSign, /*in,out*/boost::optional<int> &cycleNum);
	public:
		inline bool isCompleteCurrentCPR() { return m_bComplete;};
	private:
		//ʵս��ϰģʽ
        _eCPRErrorSign practiseJudgeCPRData(const _CPRData &cprData, const CPressureCollate *pPressureCollate, const CBreathCollate *pBreathCollate, short &uLackNum, _eCPRErrorSign &ePractiseExtendSign, /*in,out*/boost::optional<int> &cycleNum);
		//��׼ѵ��ģʽ
		_eCPRErrorSign exerciseJudgeCPRData(const _CPRData &cprData, const CPressureCollate *pPressureCollate, const CBreathCollate *pBreathCollate, /*in,out*/boost::optional<int> &cycleNum);
		//�Ҵ���ģʽ
		_eCPRErrorSign singleBreathJudfeCPRData(const _CPRData &cprData, const CBreathCollate *pBreathCollate);
		//�����ⰴѹģʽ
		_eCPRErrorSign singlePressureJudfeCPRData(const _CPRData &cprData, const CPressureCollate *pPressureCollate, /*in,out*/boost::optional<int> &cycleNum);
		//ת����һ��Detail
		bool transportNextDetail();
	protected:
		int                           m_nPressureNum;          //��ѹ�Ĵ���
		int                           m_nBreathNum;            //�����Ĵ���
		bool                          m_bBreathAccessJam;      //�����Ƿ�����
		//-----------------------------------------------------------------------------
		_CPRManageState               m_eManageState;
		_CPRRuleStruct                m_cCPRRule;
	private:
		_CPRRuleStruct                m_cRunCPRRule;           //��ǰ���е�CPRѭ�����
		_CPRRule_DetailStruct*        m_pCurrDetail;
		bool                          m_bComplete;             //�Ƿ����ָ����CPRѭ��
	};
}}
