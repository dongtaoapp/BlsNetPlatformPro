#pragma once
#include <string>
#include ".\CommonGlobal.h"
#include ".\AdultPatient.h"
#include ".\PatientRuleInterfaceGlobal.h"

namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ģ�������͹�����
	�����ˣ�	 hjg
	����ʱ�䣺   2011/3/14
	��ע��  ����ѡ�÷��͵ĵ�����singleton_default
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS CPatientTypeFactory
	{
	public:
		CPatientTypeFactory(void);
		virtual ~CPatientTypeFactory(void);
	private:
		static SimulatePatientType    m_ePatientType;
		//����ģ����
		static CAdultPatient          m_cAdultPatient;     
	public:
		std::string GetSimulatePatientTypeString();
		SimulatePatientType GetSimulatePatientType();
	public:
		/*******************************************************************************/
		//���ܣ����ļ��м�����ص�����������Ϣ
		//������
		//          SimulatePatientType eType:
		//          const CString &strConfiguePath��  ·��
		//����ֵ:  
		static void InitialPatientSymptomInfo(SimulatePatientType eType, const std::string &strConfiguePath);
	public:  //ģ���������ӿ�
		static IRhythmRule * GetSimulateRhythmRulePtr();
		static IRespRule   * GetSimulateRespRulePtr();
	};
}}