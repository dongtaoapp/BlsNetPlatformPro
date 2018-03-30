#pragma once
#include <boost/serialization/singleton.hpp>

#include ".\AdultPatient.h"

using boost::serialization::singleton;

namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     成人生理体征参数(单件类)
	创建人：	 hjg
	创建时间：   2016/2/29
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