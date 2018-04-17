#pragma once
#include <list>
#include "irespbuildtypestate.h"

#include "..\Common\CommonGlobal.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ̾��������ģʽʵ���ࣻ�ص㣺Ƶ���ؼ�������
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/29
	//-----------------------------------------------------------------------------------------------------------------*/

	class CRespSignTypeState : public IRespBuildTypeState
	{
	public:
		CRespSignTypeState( SimulatePatientType ePatientType);
		virtual ~CRespSignTypeState(void);
	public:
		bool isKindOf(const std::string &className);
		//���غ������
		virtual eRespMode Get_RespMode() { return RM_Sign; };
	protected:
		std::list<int>            m_lstRespRate;
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