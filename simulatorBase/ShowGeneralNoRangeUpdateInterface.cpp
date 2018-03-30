#include ".\showgeneralnorangeupdateinterface.h"

namespace jysoft { namespace simulator { namespace base {

	CShowGeneralNoRangeUpdateInterface::CShowGeneralNoRangeUpdateInterface(void)
	{
	}

	CShowGeneralNoRangeUpdateInterface::~CShowGeneralNoRangeUpdateInterface(void)
	{
	}

	bool CShowGeneralNoRangeUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowGeneralNoRangeUpdateInterface" )
		{
			return true;
		}
		return IUpdateShowVir::isKindOf( className );
	}

	void CShowGeneralNoRangeUpdateInterface::UnLinkUpdateShow()
	{
		//断开显示后通知
		cutLinkGeneralNoRangeUpdateShow();
	}

	void CShowGeneralNoRangeUpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkGeneralNoRangeUpdateShow();
	}

	/*******************************************************************************/
	// 函数名称： OnShowPhystValue
	// 功能： 显示的数值
	// 参数： float fPhystValue:              值
	// 返回值:  
	void CShowGeneralNoRangeUpdateInterface::OnShowPhystValue(float fPhystValue)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowGeneralNoRangeUpdateInterface" ) )
			{
				CShowGeneralNoRangeUpdateInterface *pShowInterface = (CShowGeneralNoRangeUpdateInterface *)pInterface;
				pShowInterface->ShowPhystValue( fPhystValue );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
