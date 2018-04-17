#pragma once
#include ".\ExhaledCO2Segment.h"
#include ".\InspiratedCO2Segment.h"

#include "..\common\criticalmutex.h"

namespace jysoft { namespace simulator { namespace etCO2 {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��������κͺ��������ݲ����࣬����һ�����ڵ�CO2����
	�����ˣ�	 hjg
	����ʱ�䣺   2008/7/31
	//-----------------------------------------------------------------------------------------------------------------*/
	class ICO2SimulateState;
	class CCO2CycleData
	{
	public:
		CCO2CycleData(void);
		virtual ~CCO2CycleData(void);
	protected:
		CExhaledCO2Segment            m_cExhaledCO2Segment;
		CInspiratedCO2Segment         m_cInspiratedCO2Segment;
	private:
		//�������ݶ�ȡ�����¼
		resp::CVirtualRespSegment          *m_pReadSegment;
		unsigned long                         m_dwReadPos;
		utility::CCriticalMutex              m_cMutex;
	public:
		void InitialCO2CycleData( const std::string &etCO2ResoucePath, int nCO2Per );
		void ModifyCO2PerValue( int nCO2Per );
		//���غ�������
		int  GetRespRate();
		/*******************************************************************************/
		// �������ƣ� CO2SimulateSignOp
		// ���ܣ� ����ʱ��������CO2��ģ���źŴ���
		// ������  BOOL bInspiration: ����(TRUE); ����(FALSE)
		//         int nMilliChangeTime: CO2������������ʱ�䣨0.1���룩
		//         int nMilliOtherTime:  �������������������ʱ�䣨0.1���룩
		// ����ֵ:  
		void CO2SimulateSignOp(bool bInspiration, int nMilliChangeTime, int nMilliOtherTime);
		/*******************************************************************************/
		//���ܣ���ȡ���������ڵ���������
		//������
		//      int iMilliTime:                           ʱ�䣨0.1���룩
		//      ICO2SimulateState *pEtCO2SimulateState:  
		//      float *pcBuffer:                          ���ص���������
		//����ֵ:  �������ݵĳ���
		DWORD GetPhysioloySimulateData(int iMilliTime, ICO2SimulateState *pEtCO2SimulateState, /*out*/float *pcBuffer);
	};
}}}