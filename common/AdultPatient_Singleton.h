#pragma once
#include <boost/serialization/singleton.hpp>

#include ".\AdultPatient.h"

using boost::serialization::singleton;

namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ����������������(������)
	�����ˣ�	 hjg
	����ʱ�䣺   2016/2/29
	//-----------------------------------------------------------------------------------------------------------------*/
	class CAdultPatient_Singleton : public CAdultPatient
		, public singleton<CAdultPatient_Singleton>
	{
	public:
		CAdultPatient_Singleton(void);
		virtual ~CAdultPatient_Singleton(void);
	public:
		inline std::string GetSimulatePatientTypeString() { return "Adult"; };
		inline SimulatePatientType GetSimulatePatientType() { return SPT_Adult; };
	};

}}