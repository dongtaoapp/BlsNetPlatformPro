#include ".\opinterfacevir.h"

namespace jysoft {
	COpInterfaceVir::COpInterfaceVir(void)
	{

	}

	COpInterfaceVir::~COpInterfaceVir(void)
	{
	}

	bool COpInterfaceVir::isKindOf(const std::string &className)
	{
		if( className == "COpInterfaceVir" )
		{
			return true;
		}
		return false;
	}
}
