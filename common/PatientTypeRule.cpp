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
	// 函数名称： GetSimulateRhythmRulePtr
	// 功能： 返回护理人的心律参数接口
	// 参数：                           
	// 返回值:  
	IRhythmRule * CPatientTypeRule::GetSimulateRhythmRulePtr()
	{
		return CPatientTypeFactory::GetSimulateRhythmRulePtr();
	}
}}
