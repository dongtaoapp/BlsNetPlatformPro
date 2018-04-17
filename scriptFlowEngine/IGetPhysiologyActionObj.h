#pragma once
#include ".\scriptflowengine_global.h"

#include "..\SimulatorSymptom\XAction_Defibri.h"
#include "..\SimulatorSymptom\XAction_Osat.h"
#include "..\SimulatorSymptom\XAction_ECG.h"
#include "..\SimulatorSymptom\XAction_ABP.h"
#include "..\SimulatorSymptom\XAction_Temperature.h"
#include "..\SimulatorSymptom\XAction_etCO2.h"
#include "..\SimulatorSymptom\XAction_Pupil.h"
#include "..\SimulatorSymptom\XAction_Resp.h"
#include "..\SimulatorSymptom\Symptom_FrameTime.h"

#include "..\cprModuls\CPRMessageCollect.h"


namespace jysoft { namespace flowEngine {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��ȡ��ǰ��������������ָ��
	�����ˣ�	 hjg
	����ʱ�䣺   2008/6/9
	//-----------------------------------------------------------------------------------------------------------------*/
    class SCRIPTFLOWENGINESHARED_EXPORT IGetPhysiologyActionObj
	{
	public:
		IGetPhysiologyActionObj(void);
		virtual ~IGetPhysiologyActionObj(void);
	public:
		//��ȡ���������ʱ��
		virtual simulator::CSymptom_FrameTime * getFrameTimeSymptomPtr() = 0;
		//��ȡ������ʱ��...
		//��ȡ����������...
		//��ȡ������������
		virtual simulator::CXAction_Defibri * getAction_DefibriPtr() = 0;
	protected:
		//����������������ָ��
		virtual simulator::CXActionVirtual  * getPhysiologyActionPtr(const std::string &strClassName) = 0;
	public:
		//��ȡѪ������
		simulator::CXAction_Osat * getAction_OsatPtr();
		//��ȡ��������
		simulator::CXAction_ECG * getAction_ECGPtr();
		//��ȡѪѹ����
		simulator::CXAction_ABP * getAction_ABPPtr();
		//��ȡ��������
		simulator::CXAction_Temperature * getAction_TemperaturePtr();
		//��ȡEtCO2����
		simulator::CXAction_etCO2 * getAction_EtCO2Ptr();
		//��ȡͫ�״�С
		simulator::CXAction_Pupil * getAction_PupilPtr();
		//��ȡ��������
		simulator::CXAction_Resp * getAction_Resp();
	public:
		//��ȡ�ķθ�����Ϣ������
		cpr::CCPRMessageCollect * Get_CPRMessageCollectPtr() { return m_pCPRMessageCollect; };
		//�����ķθ�����Ϣ������
		void Set_CPRMessageCollectPtr(cpr::CCPRMessageCollect *pCPRMessageCollect) { m_pCPRMessageCollect  = pCPRMessageCollect; };
	protected:
		cpr::CCPRMessageCollect*      m_pCPRMessageCollect;
	};
}}
