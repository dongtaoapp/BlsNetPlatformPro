#include ".\iupdateshowvir.h"

namespace jysoft {
	IUpdateShowVir::IUpdateShowVir(void)
	{

	}

	IUpdateShowVir::~IUpdateShowVir(void)
	{
	}

	bool IUpdateShowVir::isKindOf(const std::string &className)
	{
		if( className == "IUpdateShowVir" )
		{
			return true;
		}
		return false;
	}

	void IUpdateShowVir::OnAllUnLinkUpdateShow()
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while(pInterfaceVir != NULL)
		{
			if( pInterfaceVir->isKindOf("IUpdateShowVir") )
			{
				IUpdateShowVir  *pUpdateShowInterface = (IUpdateShowVir *)pInterfaceVir;
				pUpdateShowInterface->UnLinkUpdateShow();
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	void IUpdateShowVir::OnAllLinkUpdateShow()
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while(pInterfaceVir != NULL)
		{
			if( pInterfaceVir->isKindOf("IUpdateShowVir") )
			{
				IUpdateShowVir  *pUpdateShowInterface = (IUpdateShowVir *)pInterfaceVir;
				pUpdateShowInterface->LinkUpdateShow();
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

}
