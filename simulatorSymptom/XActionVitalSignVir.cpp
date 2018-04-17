#include ".\xactionvitalsignvir.h"


namespace jysoft { namespace simulator 
{
	CXActionVitalSignVir::CXActionVitalSignVir(void)
	{
	}

	CXActionVitalSignVir::~CXActionVitalSignVir(void)
	{
	}

	bool CXActionVitalSignVir::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXActionVitalSignVir" )
		{
			return true;
		}
		return CXActionVirtual::isKindOf( strClassName );
	}
}}
