#include <boost/assert.hpp>
#include ".\CPRSimulateJudgeOp.h"
#include ".\Collates.h"

#include "..\Common\ParseCPRData_Singleton.h"


namespace jysoft{  namespace cpr 
{
	CCPRSimulateJudgeOp::CCPRSimulateJudgeOp(_CPRManageState eManageState)
	{
		m_eManageState        = eManageState;
		//����CPR
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

	//������ģ���˵�״̬
	void CCPRSimulateJudgeOp::resetSimulateParam()
	{
		//����CPR
		m_cCPRRule.setDefaultCPRRule();

		m_cRunCPRRule.copy(&m_cCPRRule);
		m_pCurrDetail = m_cRunCPRRule.detailRules;
		assert( m_pCurrDetail != NULL );
		m_bComplete  = false;
		//------------------------------------------------------------------
		m_nPressureNum = 0;
		m_nBreathNum   = 0;
		m_bBreathAccessJam = false;  //����
	}

	void CCPRSimulateJudgeOp::resetSimulateParam(_CPRManageState eManageState, _CPRRuleStruct *pCPRRule)
	{
		m_eManageState = eManageState;
		resetSimulateParam();
		if( pCPRRule != NULL)
		{
			m_cCPRRule.copy(pCPRRule);
			//���ÿ�ʼλ��
			m_cRunCPRRule.copy(&m_cCPRRule);
			m_pCurrDetail = m_cRunCPRRule.detailRules;
			assert( m_pCurrDetail != NULL );
		}
	}

	//���赱ǰ�õ��жϹ���
	void CCPRSimulateJudgeOp::resetCurrentSimulateParam()
	{
		m_cRunCPRRule.copy(&m_cCPRRule);
		m_pCurrDetail = m_cRunCPRRule.detailRules;
		assert( m_pCurrDetail != NULL );
		m_bComplete  = false;
		//------------------------------------------------------------------
		m_nPressureNum = 0;
		m_nBreathNum   = 0;
		m_bBreathAccessJam = false;  //����
	}

	//ת����һ��Detail
	bool CCPRSimulateJudgeOp::transportNextDetail()
	{
		bool  bComplete = m_bComplete;
		_CPRRule_DetailStruct *pNextDetail = m_pCurrDetail->getNextDetailRule();
		if(pNextDetail == NULL )
		{//��β����ת����ʼλ��
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
	// �������ƣ� JudgeCPRData
	// ���ܣ� ���CPR�������򣬶��û��Ĳ��������ж�
	// ������ const _CPRData &cprData: CPR����
	//        CPressureCollate *pPressureCollate:
	//        CBreathCollate *pBreathCollate:
	//        UINT &uLackNum: 
	//        boost::optional<int> &cycleNum:   ѭ������
	//        _eCPRErrorSign &ePractiseExtendSign:    ʵս��ʽʱ����������ж�
	// ����ֵ: 
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
			//ע������CPR����������ɺ󣬼����������������ж� <2017/1/8 hjg �޸�>
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

    //ʵս��ϰģʽ
    _eCPRErrorSign CCPRSimulateJudgeOp::practiseJudgeCPRData(const _CPRData &cprData, const CPressureCollate *pPressureCollate, const CBreathCollate *pBreathCollate, short &uLackNum, _eCPRErrorSign &ePractiseExtendSign, /*in,out*/boost::optional<int> &cycleNum)
	{
		//��ʼ����
		uLackNum = 0;
		_eCPRErrorSign  eRtnSign = CS_None;
		ePractiseExtendSign   = CS_None;
		const CParseCPRData_Singleton *pCPRParse = &CParseCPRData_Singleton::get_const_instance();
		if( pCPRParse->isCPRScopeOrder(cprData, true) )
		{//��ѹ�ķ���
			if( m_pCurrDetail->m_bBreath && (m_nPressureNum > 0 || m_nBreathNum == 0) )
			{
				eRtnSign  = CS_PressureNumOver;
			}
			else 
			{
				if( m_pCurrDetail->m_bBreath )
				{
					eRtnSign = CS_BreathNumLack;  //��������̫��
					if( m_pCurrDetail->m_nNumber > m_nBreathNum)
					{
						uLackNum = m_pCurrDetail->m_nNumber - m_nBreathNum;
					}
					//ת����һ��Detail
					m_bComplete = transportNextDetail();
					//ͳ��ѭ������ 2017.4.26 add
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
					//�ͷŲ���
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
				{//��ѹλ�ô���
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
				{//��С
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
				{//����
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
				{//ת����һ��Detail
					m_bComplete = transportNextDetail();
				}
			}
		}
		else if( pCPRParse->isCPRScopeOrder(cprData, false) )
		{//�����ķ���
			if( m_pCurrDetail->m_bBreath == false && (m_nBreathNum > 0 || m_nPressureNum == 0) )
			{
				//���ڴ���
				eRtnSign = CS_BreathNumOver;
			}
			else 
			{
				if( m_pCurrDetail->m_bBreath == false )
				{
					eRtnSign = CS_PressureNumLack; //��ѹ����̫��
					if( m_pCurrDetail->m_nNumber > m_nPressureNum )
					{
						uLackNum = m_pCurrDetail->m_nNumber - m_nPressureNum;
					}
					//ת����һ��Detail
					m_bComplete = transportNextDetail();
				}
				m_nPressureNum = 0;
				//�ж������Ƿ�����ȷ�ķ�Χ��
				if( pBreathCollate->judgeIsLower( cprData ) )
				{//��С
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
				{//����
					if( pBreathCollate->isToStomach( cprData ) )
					{//���󣬾ͱ�ʾΪ��θ
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
							ePractiseExtendSign  = CS_BreathOverBig;//����
						}
						else
						{
							eRtnSign = CS_BreathOverBig;//����
						}
					}
				}
				else if( pBreathCollate->judgeIsRespTimeOver(cprData) ) 
				{//ͨ���೤
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
				{//ͨ�����
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
				{//ת����һ��Detail
					m_bComplete = transportNextDetail();
				}
			}
			//ͳ��ѭ������ 2017.4.26 add
			if( cycleNum == boost::none )
			{
				cycleNum = 1;
			}
		}
		return eRtnSign;
	}

	//��׼ѵ��ģʽ
	_eCPRErrorSign CCPRSimulateJudgeOp::exerciseJudgeCPRData(const _CPRData &cprData, const CPressureCollate *pPressureCollate, const CBreathCollate *pBreathCollate, /*in,out*/boost::optional<int> &cycleNum)
	{
		//��ʼ����
		_eCPRErrorSign eRtnSign = CS_None;
		const CParseCPRData_Singleton *pCPRParse = &CParseCPRData_Singleton::get_const_instance();
		if( pCPRParse->isCPRScopeOrder(cprData, true) )
		{//��ѹ�ķ���
			if( m_pCurrDetail->m_bBreath)
			{//����û����
				if( m_nBreathNum == 0)
					eRtnSign = CS_PressureNumOver;
				else
					eRtnSign = CS_BreathNumLack;  //��������̫��
			}
			else
			{
				if( pPressureCollate->isIncompleteError(cprData) )
				{
					//�ͷŲ���
					eRtnSign = CS_PressureIncompleteErr;
				}
				else if( pPressureCollate->isPressurePositionError( cprData ) )
				{//��ѹλ�ô���
					eRtnSign = CS_PressurePosErr;
				}
				else if( pPressureCollate->judgeIsLower(cprData) )
				{//��С
					eRtnSign = CS_PressureLack;
				}
				else if( pPressureCollate->judgeIsOver(cprData) )
				{//����
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
						//ת����һ��Detail
						m_bComplete = transportNextDetail();
					}
				}
				m_nBreathNum = 0;
				//ͳ��ѭ������ 2017.4.26 add
				cycleNum = (cycleNum == boost::none ? 0 : cycleNum.get()) + 1;
			}
		}
		else if( pCPRParse->isCPRScopeOrder(cprData, false) )
		{//�����ķ���
			if( m_pCurrDetail->m_bBreath == false)
			{
				if( m_nPressureNum == 0 )
					eRtnSign = CS_BreathNumOver;
				else
					eRtnSign = CS_PressureNumLack;//��ѹ����̫��
			}
			else
			{
				m_nPressureNum = 0;
				//�ж������Ƿ�����ȷ�ķ�Χ��
				if( pBreathCollate->judgeIsLower( cprData ) )
				{//��С
					eRtnSign = CS_BreathLack;
				}
				else if( pBreathCollate->judgeIsOver( cprData ) )
				{//����
					if( pBreathCollate->isToStomach( cprData ) )
					{//���󣬾ͱ�ʾΪ��θ
						eRtnSign = CS_BreathInStomach;
					}
					else
					{
						eRtnSign = CS_BreathOverBig;//����
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
						//ת����һ��Detail
						m_bComplete = transportNextDetail();
					}
				}
			}
			//ͳ��ѭ������ 2017.4.26 add
			if( cycleNum == boost::none )
			{
				cycleNum = 1;
			}
		}
		return eRtnSign;
	}

	//�Ҵ���ģʽ
	_eCPRErrorSign CCPRSimulateJudgeOp::singleBreathJudfeCPRData(const _CPRData &cprData, const CBreathCollate *pBreathCollate)
	{
		_eCPRErrorSign eRtnSign = CS_None;
		const CParseCPRData_Singleton *pCPRParse = &CParseCPRData_Singleton::get_const_instance();
		if( pCPRParse->isCPRScopeOrder(cprData, false) )
		{//�����ķ���
			//�ж������Ƿ�����ȷ�ķ�Χ��
			if( pBreathCollate->judgeIsLower( cprData ) )
			{//��С
				eRtnSign = CS_BreathLack;
			}
			else if( pBreathCollate->judgeIsOver( cprData ) )
			{//����
				if( pBreathCollate->isToStomach( cprData ) )
				{//���󣬾ͱ�ʾΪ��θ
					eRtnSign = CS_BreathInStomach;
				}
				else
				{
					eRtnSign = CS_BreathOverBig;//����
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
			eRtnSign = CS_BreathNumLack;  //��������̫��
		}
		return eRtnSign;
	}

	//�����ⰴѹģʽ
	_eCPRErrorSign CCPRSimulateJudgeOp::singlePressureJudfeCPRData(const _CPRData &cprData, const CPressureCollate *pPressureCollate, /*out*/boost::optional<int> &cycleNum)
	{
		_eCPRErrorSign eRtnSign = CS_None;
		const CParseCPRData_Singleton *pCPRParse = &CParseCPRData_Singleton::get_const_instance();
		if( pCPRParse->isCPRScopeOrder(cprData, true) )
		{//��ѹ�ķ���
			if( pPressureCollate->isIncompleteError(cprData) )
			{
				//�ͷŲ���
				eRtnSign = CS_PressureIncompleteErr;
			}
			else if( pPressureCollate->isPressurePositionError( cprData ) )
			{//��ѹλ�ô���
				eRtnSign = CS_PressurePosErr;
			}
			else if( pPressureCollate->judgeIsLower( cprData ) )
			{//��С
				eRtnSign = CS_PressureLack;
			}
			else if( pPressureCollate->judgeIsOver( cprData ) )
			{//����
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
			eRtnSign = CS_PressureNumLack; //��ѹ����̫��
			//ͳ��ѭ������ 2017.4.26 add
			if( cycleNum == boost::none )
			{
				cycleNum = 1;
			}
		}
		return eRtnSign;
	}

}}
