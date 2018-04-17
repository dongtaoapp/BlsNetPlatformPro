#pragma once
#include ".\RespCycleDataCollects.h"
#include ".\RespCycleData.h"
#include ".\RespParamImplVir.h"

#include "..\common\criticalmutex.h"

namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ����ģʽ�ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2008/7/22
	//-----------------------------------------------------------------------------------------------------------------*/

	class CInspirationSegment;
	class CExhaleSegment;
	class IRespBuildTypeState
	{
	public:
		IRespBuildTypeState();
		virtual ~IRespBuildTypeState(void);
	protected:
		int                     m_nRespRate;    //��������/����
		CInspirationSegment    *m_pOriginInspirationSegment;
		CExhaleSegment         *m_pOriginExhaleSegment;
	protected:
		utility::CCriticalMutex   m_cMutex;
		CRespParamImplVir      *m_pRespParams;
	public:
		virtual bool isKindOf(const std::string &className) = 0;
		//���غ������
		virtual eRespMode Get_RespMode() = 0;
	public:
		inline int  Get_nRespRate() { return m_nRespRate; };
		//�����޺���ʱ��ʣ������
		virtual float GetApneaRemainVolume() ;
		/*******************************************************************************/
		// �������ƣ� InitialLoadOriginSimulateData
		// ���ܣ� ����ԭʼ��������
		// ������ 
		// ����ֵ:  
		virtual void InitialLoadOriginSimulateData(const std::string &respResoucePath, int nRespRate) = 0;
		/*******************************************************************************/
		// �������ƣ� OnModifyRespRate
		// ���ܣ� �޸ĺ�������
		// ������ int nRespRate: �µĺ�������
		// ����ֵ:  
		virtual void OnModifyRespRate(int nRespRate) = 0;
		/*******************************************************************************/
		// �������ƣ� OnCombineNextRespCycleData
		// ���ܣ� ���������ڵĺ�������
		// ������  float fCurrentRemainVolume:           ��ǰ������
		//         CRespCycleDataCollects *pRespCollect: 
		// ����ֵ:  
		virtual CRespCycleData * OnCombineNextRespCycleData(float fCurrentRemainVolume, CRespCycleDataCollects *pRespCollect) = 0;
	};
}}}