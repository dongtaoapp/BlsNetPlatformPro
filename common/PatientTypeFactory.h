#pragma once
#include <string>
#include ".\CommonGlobal.h"
#include ".\AdultPatient.h"
#include ".\PatientRuleInterfaceGlobal.h"

namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     模拟人类型工厂类
	创建人：	 hjg
	创建时间：   2011/3/14
	备注：  尽量选用泛型的单件类singleton_default
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS CPatientTypeFactory
	{
	public:
		CPatientTypeFactory(void);
		virtual ~CPatientTypeFactory(void);
	private:
		static SimulatePatientType    m_ePatientType;
		//成人模拟人
		static CAdultPatient          m_cAdultPatient;     
	public:
		std::string GetSimulatePatientTypeString();
		SimulatePatientType GetSimulatePatientType();
	public:
		/*******************************************************************************/
		//功能：从文件中加载相关的体征参数信息
		//参数：
		//          SimulatePatientType eType:
		//          const CString &strConfiguePath：  路径
		//返回值:  
		static void InitialPatientSymptomInfo(SimulatePatientType eType, const std::string &strConfiguePath);
	public:  //模拟人体征接口
		static IRhythmRule * GetSimulateRhythmRulePtr();
		static IRespRule   * GetSimulateRespRulePtr();
	};
}}