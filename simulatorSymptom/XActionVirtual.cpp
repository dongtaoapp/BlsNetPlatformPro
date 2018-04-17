#include ".\xactionvirtual.h"


namespace jysoft { namespace simulator 
{
	CXActionVirtual::CXActionVirtual(void)
	{
	}

	CXActionVirtual::~CXActionVirtual(void)
	{
	}

	bool CXActionVirtual::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXActionVirtual" )
		{
			return true;
		}
		return false;
	}

	bool CXActionVirtual::isActionNameOf(const std::string &strCaption)
	{
		if( getActionCaption() == strCaption )
		{
			return	true;
		}
		return false;
	}
}}
