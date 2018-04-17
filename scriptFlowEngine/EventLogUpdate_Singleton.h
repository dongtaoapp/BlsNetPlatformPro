#pragma once
#include <string>
#include <boost/serialization/singleton.hpp>

#include "..\SimulatorBase\VirEventIrp.h"
#include "..\SimulatorBase\EventIrp_SimulateTrigger.h"


using boost::serialization::singleton;


namespace jysoft{  namespace log 
{
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     事件日志格式化单件类
	创建人：	 hjg
	创建时间：   2017/9/30
	//-----------------------------------------------------------------------------------------------------------------*/
	class CEventLogUpdate_Singleton : public singleton<CEventLogUpdate_Singleton>
	{
	public:
		//事件日志格式化
		//strTime:  操作时间
		//pVirEventIrp: 目标事件包基类
		BOOST_DLLEXPORT _EventLog_struct *getIrpLogMessage(const std::string &strTime, irp::CVirEventIrp *pVirEventIrp) const;
	protected:
		bool getSimulateTriggerIrpLog(_EventLog_struct *pLogStruct, irp::CEventIrp_SimulateTrigger* pTriggerEventIrp) const;
	};
}}

