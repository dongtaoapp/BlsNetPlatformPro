#pragma once
#include ".\simulatorbase_global.h"

namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ����ʱ,CO2�½�������ʱ��CO2����
	�����ˣ�	 hjg
	����ʱ�䣺   2016/7/22
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT ICO2SimulateSign
	{
	public:
		ICO2SimulateSign(void);
		virtual ~ICO2SimulateSign(void);
	public:
		/*******************************************************************************/
		// �������ƣ� OnCO2SimulateSignOp
		// ���ܣ� ����ʱ��������CO2��ģ���źŴ���
		// ������  BOOL bInspiration: ����(TRUE); ����(FALSE)
		//         int nMilliChangeTime: CO2������������ʱ�䣨0.1���룩
		//         int nMilliOtherTime:  �������������������ʱ�䣨0.1���룩
		// ����ֵ:  
		virtual void OnCO2SimulateSignOp(bool bInspiration, int nMilliChangeTime, int nMilliOtherTime) = 0;
		/*******************************************************************************/
		// �������ƣ� OnStartAutoRespOp
		// ���ܣ� ����/��ͣ��������
		// ������ 
		//         BOOL bAutoResp:
		// ����ֵ:  
		virtual void OnStartAutoRespOp( bool bAutoResp ) = 0;
	};

}}
