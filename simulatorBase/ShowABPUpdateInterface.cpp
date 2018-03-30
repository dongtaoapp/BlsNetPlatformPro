#include <boost/lexical_cast.hpp>

#include ".\showabpupdateinterface.h"

namespace jysoft { namespace simulator { namespace base {

	CShowABPUpdateInterface::CShowABPUpdateInterface(void)
	{
	}

	CShowABPUpdateInterface::~CShowABPUpdateInterface(void)
	{
	}

	bool CShowABPUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowABPUpdateInterface" )
			return true;
		return IUpdateShowVir::isKindOf(className);
	}

	void CShowABPUpdateInterface::UnLinkUpdateShow()
	{
		//断开显示后通知
		cutLinkABPUpdateShow();
	}

	void CShowABPUpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkABPUpdateShow();
	}

	//解析有创血压：nShrink：收缩压；nStretch：舒张压
	bool CShowABPUpdateInterface::ParseABPToShrinkAndnStretch(const std::string &strABP, int &nShrink, int &nStretch)
	{
		std::string::size_type nPos = strABP.find('/');
		if(nPos != -1)
		{
			//收缩压
			std::string nValue = strABP.substr(0, nPos);
			nShrink = boost::lexical_cast<int>(nValue);
			//舒张压
			nValue = strABP.substr(nPos+1);
			nStretch = boost::lexical_cast<int>(nValue);
			return true;
		}
		return false;
	}

	/*******************************************************************************/
	// 函数名称： OnShowABPValue
	// 功能： 显示有创血压的数值
	// 参数： int nShrinkValue:              收缩压
	//        int nStretchValue:             舒张压
	// 返回值:  
	void CShowABPUpdateInterface::OnShowABPValue(int nShrinkValue, int nStretchValue)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf("CShowABPUpdateInterface") )
			{
				CShowABPUpdateInterface *pShowABPInterface = (CShowABPUpdateInterface *)pInterface;
				pShowABPInterface->ShowABPValue( nShrinkValue,  nStretchValue);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	void CShowABPUpdateInterface::OnShowABPValue(const std::string &strABP)
	{
		int nShrink, nStretch;
		if( CShowABPUpdateInterface::ParseABPToShrinkAndnStretch(strABP, /*out*/nShrink, /*out*/nStretch) )
		{
			OnShowABPValue(nShrink, nStretch);
		}
	}

}}}
