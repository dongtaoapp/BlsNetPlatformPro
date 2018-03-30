#pragma once
#include ".\CommonGlobal.h"
#include ".\PatientRuleInterfaceGlobal.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ͨ��ģ�������������޶�
	�����ˣ�	 hjg
	����ʱ�䣺   2016/11/23
	��ע��  ������CPatientTypeFactory���ʹ�ã����ʹ��boost��ĵ���������;
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS CPatientTypeRule
	{
	public:
		CPatientTypeRule(void);
		virtual ~CPatientTypeRule(void);
	public:
		/*******************************************************************************/
		// �������ƣ� GetSimulateRhythmRulePtr
		// ���ܣ� ���ػ����˵����ɲ����ӿ�
		// ������                           
		// ����ֵ:  
		IRhythmRule * GetSimulateRhythmRulePtr();
	};

}}