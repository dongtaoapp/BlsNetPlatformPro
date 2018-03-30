#include ".\shownibpupdateinterface.h"


namespace jysoft { namespace simulator { namespace base {

	CShowNIBPUpdateInterface::CShowNIBPUpdateInterface(void)
	{
	}

	CShowNIBPUpdateInterface::~CShowNIBPUpdateInterface(void)
	{
	}

	bool CShowNIBPUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowNIBPUpdateInterface" )
			return true;
		return IUpdateShowVir::isKindOf(className);
	}

	void CShowNIBPUpdateInterface::UnLinkUpdateShow()
	{
		//断开显示后通知
		cutLinkNIBPUpdateShow();
	}

	void CShowNIBPUpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkNIBPUpdateShow();
	}

	/*******************************************************************************/
	// 函数名称： OnShowNIBPValue
	// 功能： 显示无创血压的数值
	// 参数： int nShrinkValue:              收缩压
	//        int nStretchValue:             舒张压
	// 返回值:  
	void CShowNIBPUpdateInterface::OnShowNIBPValue(int nShrinkValue, int nStretchValue)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowNIBPUpdateInterface" ) )
			{
				CShowNIBPUpdateInterface *pShowNIBPInterface = (CShowNIBPUpdateInterface *)pInterface;
				pShowNIBPInterface->ShowNIBPValue( nShrinkValue,  nStretchValue);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// 函数名称： OnShowKorotkoffVolum
	// 功能： 显示无创血压声响的数值
	// 参数： int nNIBPSoundValue:              无创血压声响的数值
	// 返回值:  
	void CShowNIBPUpdateInterface::OnShowKorotkoffVolume(int nNIBPSoundValue)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowNIBPUpdateInterface" ) )
			{
				CShowNIBPUpdateInterface *pShowNIBPInterface = (CShowNIBPUpdateInterface *)pInterface;
				pShowNIBPInterface->ShowNIBPSoundValue( nNIBPSoundValue );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
