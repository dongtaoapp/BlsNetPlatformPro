#pragma once
#include "irespbuildtypestate.h"

#include "..\Common\CommonGlobal.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �ϰº���(��"��ͣ����")ģʽʵ���ࣻ�ص㣺��岻����������Ժ�����ͣ�����˺�����������
	�����ˣ�	 hjg
	����ʱ�䣺   2008/7/29
	//-----------------------------------------------------------------------------------------------------------------*/

	class CRespBiotTypeState : public IRespBuildTypeState
	{
	public:
		CRespBiotTypeState(SimulatePatientType ePatientType);
		virtual ~CRespBiotTypeState(void);
	public:
		bool isKindOf(const std::string &className);
		//���غ������
		virtual eRespMode Get_RespMode() { return RM_Biots; };
	protected:
		int                                       m_nOriginRate;
		int                                       m_nStepNum;             //����ȷ����ͣ����
		int                                       m_nSumStepNum;
	public:
		/*******************************************************************************/
		// �������ƣ� InitialLoadOriginSimulateData
		// ���ܣ� ����ԭʼ��������
		// ������ 
		// ����ֵ:  
		virtual void InitialLoadOriginSimulateData(const std::string &respResoucePath, int nRespRate) ;
		/*******************************************************************************/
		// �������ƣ� OnModifyRespRate
		// ���ܣ� �޸ĺ�������
		// ������ int nRespRate: �µĺ�������
		// ����ֵ:  
		virtual void OnModifyRespRate(int nRespRate);
		/*******************************************************************************/
		// �������ƣ� OnCombineNextRespCycleData
		// ���ܣ� ���������ڵĺ�������
		// ������ float fCurrentRemainVolume:           ��ǰ������
		//        CRespCycleDataCollects *pRespCollect: 
		// ����ֵ:  
		virtual CRespCycleData * OnCombineNextRespCycleData(float fCurrentRemainVolume, CRespCycleDataCollects *pRespCollect);
	protected:
		//��ʼ����ͣ����
		void InitialApneaStrategy(int nRespRate);
	};
}}}