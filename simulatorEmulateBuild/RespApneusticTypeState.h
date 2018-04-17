#pragma once
#include <list>
#include "irespbuildtypestate.h"

#include "..\Common\CommonGlobal.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��ͣ����ģʽʵ���ࣻ�ص㣺����������Ժ�����ͣ�����һ����������
	�����ˣ�	 hjg
	����ʱ�䣺   2008/7/29
	//-----------------------------------------------------------------------------------------------------------------*/

	class CRespApneusticTypeState : public IRespBuildTypeState
	{
	public:
		CRespApneusticTypeState(SimulatePatientType ePatientType);
		virtual ~CRespApneusticTypeState(void);
	public:
		bool isKindOf(const std::string &className);
		//���غ������
		virtual eRespMode Get_RespMode() { return RM_Apneustic; };
	protected:
		std::list<int>                      m_lstRespRate;
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
	protected:
		void InitialRespRateList();
	};
}}}