#include ".\PatientTypeRule.h"
#include ".\PatientTypeFactory.h"

namespace jysoft { namespace simulator {

	CPatientTypeRule::CPatientTypeRule(void)
	{
	}


	CPatientTypeRule::~CPatientTypeRule(void)
	{
	}

	/*******************************************************************************/
	// �������ƣ� GetSimulateRhythmRulePtr
	// ���ܣ� ���ػ����˵����ɲ����ӿ�
	// ������                           
	// ����ֵ:  
	IRhythmRule * CPatientTypeRule::GetSimulateRhythmRulePtr()
	{
		return CPatientTypeFactory::GetSimulateRhythmRulePtr();
	}
}}
