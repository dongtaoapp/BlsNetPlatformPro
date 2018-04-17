#include ".\xlinelink.h"
#include ".\IAclsFlowStrategy.h"


namespace jysoft { namespace flowEngine 
{
	CXLineLink::CXLineLink()
	{
		m_pFlowStrategy   = NULL;
	}

	CXLineLink::~CXLineLink(void)
	{
		m_pFlowStrategy  = NULL;
	}

	bool CXLineLink::isKindOf(const std::string &strClassName)
	{
		if(strClassName == "CXLineLink")
		{
			return true;
		}
		return CXVirtualLink::isKindOf(strClassName);
	}
}}
