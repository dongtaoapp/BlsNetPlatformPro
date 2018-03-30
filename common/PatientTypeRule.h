#pragma once
#include ".\CommonGlobal.h"
#include ".\PatientRuleInterfaceGlobal.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     通用模拟人体征规则限定
	创建人：	 hjg
	创建时间：   2016/11/23
	备注：  本类与CPatientTypeFactory配合使用，如果使用boost库的单件可舍弃;
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS CPatientTypeRule
	{
	public:
		CPatientTypeRule(void);
		virtual ~CPatientTypeRule(void);
	public:
		/*******************************************************************************/
		// 函数名称： GetSimulateRhythmRulePtr
		// 功能： 返回护理人的心律参数接口
		// 参数：                           
		// 返回值:  
		IRhythmRule * GetSimulateRhythmRulePtr();
	};

}}