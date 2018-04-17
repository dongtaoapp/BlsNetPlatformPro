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
	类说明：     获取当前的生理体征对象指针
	创建人：	 hjg
	创建时间：   2008/6/9
	//-----------------------------------------------------------------------------------------------------------------*/
    class SCRIPTFLOWENGINESHARED_EXPORT IGetPhysiologyActionObj
	{
	public:
		IGetPhysiologyActionObj(void);
		virtual ~IGetPhysiologyActionObj(void);
	public:
		//获取场景框持续时间
		virtual simulator::CSymptom_FrameTime * getFrameTimeSymptomPtr() = 0;
		//获取场景框时间...
		//获取起搏设置属性...
		//获取除颤设置属性
		virtual simulator::CXAction_Defibri * getAction_DefibriPtr() = 0;
	protected:
		//返回生理体征对象指针
		virtual simulator::CXActionVirtual  * getPhysiologyActionPtr(const std::string &strClassName) = 0;
	public:
		//获取血氧属性
		simulator::CXAction_Osat * getAction_OsatPtr();
		//获取心律属性
		simulator::CXAction_ECG * getAction_ECGPtr();
		//获取血压属性
		simulator::CXAction_ABP * getAction_ABPPtr();
		//获取体温属性
		simulator::CXAction_Temperature * getAction_TemperaturePtr();
		//获取EtCO2属性
		simulator::CXAction_etCO2 * getAction_EtCO2Ptr();
		//获取瞳孔大小
		simulator::CXAction_Pupil * getAction_PupilPtr();
		//获取呼吸属性
		simulator::CXAction_Resp * getAction_Resp();
	public:
		//获取心肺复苏信息集合类
		cpr::CCPRMessageCollect * Get_CPRMessageCollectPtr() { return m_pCPRMessageCollect; };
		//设置心肺复苏信息集合类
		void Set_CPRMessageCollectPtr(cpr::CCPRMessageCollect *pCPRMessageCollect) { m_pCPRMessageCollect  = pCPRMessageCollect; };
	protected:
		cpr::CCPRMessageCollect*      m_pCPRMessageCollect;
	};
}}
