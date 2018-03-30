#include ".\oploginterface.h"

#include ".\VirEventIrp.h"

namespace jysoft{  namespace log {

	COpLogInterface::COpLogInterface(void)
	{
		m_uLogTime = 0;
	}

	COpLogInterface::~COpLogInterface(void)
	{
	}

	bool COpLogInterface::isKindOf(const std::string &className)
	{
		if( className == "COpLogInterface" )
		{
			return true;
		}
		return COpInterfaceVir::isKindOf( className );
	}
}}
