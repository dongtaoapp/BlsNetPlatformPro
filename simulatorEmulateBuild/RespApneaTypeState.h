#pragma once
#include ".\irespbuildtypestate.h"

#include "..\Common\CommonGlobal.h"


namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ������ͣģʽʵ���ࣻ�ص㣺����������Ժ�����ͣ
	�����ˣ�	 hjg
	����ʱ�䣺   2017/7/29
	//-----------------------------------------------------------------------------------------------------------------*/

	class CRespApneaTypeState : public IRespBuildTypeState
	{
	public:
		CRespApneaTypeState(SimulatePatientType ePatientType);
		virtual ~CRespApneaTypeState(void);
	public:
		bool isKindOf(const std::string &className);
		//���غ������
		virtual eRespMode Get_RespMode() { return RM_Apnea; };
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
		virtual void OnModifyRespRate(int nRespRate) { };
		/*******************************************************************************/
		// �������ƣ� OnCombineNextRespCycleData
		// ���ܣ� ���������ڵĺ�������
		// ������ float fCurrentRemainVolume:           ��ǰ������
		//        CRespCycleDataCollects *pRespCollect: 
		// ����ֵ:  
		virtual CRespCycleData * OnCombineNextRespCycleData(float fCurrentRemainVolume, CRespCycleDataCollects *pRespCollect);
	};
}}}