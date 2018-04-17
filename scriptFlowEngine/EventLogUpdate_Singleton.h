#pragma once
#include <string>
#include <boost/serialization/singleton.hpp>

#include "..\SimulatorBase\VirEventIrp.h"
#include "..\SimulatorBase\EventIrp_SimulateTrigger.h"


using boost::serialization::singleton;


namespace jysoft{  namespace log 
{
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �¼���־��ʽ��������
	�����ˣ�	 hjg
	����ʱ�䣺   2017/9/30
	//-----------------------------------------------------------------------------------------------------------------*/
	class CEventLogUpdate_Singleton : public singleton<CEventLogUpdate_Singleton>
	{
	public:
		//�¼���־��ʽ��
		//strTime:  ����ʱ��
		//pVirEventIrp: Ŀ���¼�������
		BOOST_DLLEXPORT _EventLog_struct *getIrpLogMessage(const std::string &strTime, irp::CVirEventIrp *pVirEventIrp) const;
	protected:
		bool getSimulateTriggerIrpLog(_EventLog_struct *pLogStruct, irp::CEventIrp_SimulateTrigger* pTriggerEventIrp) const;
	};
}}

