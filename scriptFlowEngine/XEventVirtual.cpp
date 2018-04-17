#include ".\xeventvirtual.h"

namespace jysoft { namespace flowEngine 
{
	CXEventVirtual::CXEventVirtual(void)
	{
	}

	CXEventVirtual::~CXEventVirtual(void)
	{
	}

	bool CXEventVirtual::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXEventVirtual" )
		{
			return true;
		}
		return false;
	}

	bool CXEventVirtual::isEventNameOf(const std::string &caption)
	{
		if( getEventCaption() == caption )
		{
			return true;
		}
		return false;
	}
}}
