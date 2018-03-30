#include ".\patienttypefactory.h"

namespace jysoft { namespace simulator {

	SimulatePatientType CPatientTypeFactory::m_ePatientType = SPT_Adult;
	CAdultPatient CPatientTypeFactory::m_cAdultPatient;
	//-------------------------------------------------------------------------------------------------
	CPatientTypeFactory::CPatientTypeFactory(void)
	{

	}

	CPatientTypeFactory::~CPatientTypeFactory(void)
	{
	}

	std::string CPatientTypeFactory::GetSimulatePatientTypeString()
	{
		return "Adult";
	}

	SimulatePatientType CPatientTypeFactory::GetSimulatePatientType()
	{
		return SPT_Adult;
	}

	/*******************************************************************************/
	//���ܣ����ļ��м�����ص�����������Ϣ
	//������
	//          SimulatePatientType eType:
	//          const CString &strConfiguePath��
	//����ֵ:  
	void CPatientTypeFactory::InitialPatientSymptomInfo(SimulatePatientType eType, const std::string &strConfiguePath)
	{
		m_ePatientType  = eType;
		m_cAdultPatient.initialPatient( strConfiguePath );
	}

	IRhythmRule * CPatientTypeFactory::GetSimulateRhythmRulePtr()
	{
		IRhythmRule *pRhythmRule = dynamic_cast<IRhythmRule *>(&m_cAdultPatient);
		return pRhythmRule;
	}

	IRespRule   * CPatientTypeFactory::GetSimulateRespRulePtr()
	{
		IRespRule *pRespRule = dynamic_cast<IRespRule *>(&m_cAdultPatient);
		return pRespRule;
	}
}}
