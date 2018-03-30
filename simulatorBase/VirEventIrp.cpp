#include ".\vireventirp.h"

namespace jysoft { namespace irp {

	CVirEventIrp::CVirEventIrp(void)
	{
	}

	CVirEventIrp::~CVirEventIrp(void)
	{
	}
	
	bool CVirEventIrp::isKindOf(const std::string &strClass)
	{
		if( strClass == "CVirEventIrp" )
		{
			return true;
		}
		return false;
	}

}}
