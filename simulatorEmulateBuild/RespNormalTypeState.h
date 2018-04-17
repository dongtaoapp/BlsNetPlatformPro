#pragma once
#include ".\irespbuildtypestate.h"
#include ".\RespApneaCycleData.h"

#include "..\Common\CommonGlobal.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��������ģʽʵ����
	�����ˣ�	 hjg
	����ʱ�䣺   2008/7/22
	//-----------------------------------------------------------------------------------------------------------------*/
	class CRespNormalTypeState : public IRespBuildTypeState
	{
	public:
		CRespNormalTypeState();
		CRespNormalTypeState(SimulatePatientType ePatientType);
		virtual ~CRespNormalTypeState(void);
	public:
		bool isKindOf(const std::string &className);
		//���غ������
		virtual eRespMode Get_RespMode() { return RM_Normal; };
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
		virtual void OnModifyRespRate(int nRespRate) ;
		/*******************************************************************************/
		// �������ƣ� OnCombineNextRespCycleData
		// ���ܣ� ���������ڵĺ�������
		// ������ float fCurrentRemainVolume:           ��ǰ������
		//        CRespCycleDataCollects *pRespCollect: 
		// ����ֵ:  
		virtual CRespCycleData * OnCombineNextRespCycleData(float fCurrentRemainVolume, CRespCycleDataCollects *pRespCollect);
	};
}}}