#include ".\showecgupdateinterface.h"

namespace jysoft { namespace simulator { namespace base {

	CShowECGUpdateInterface::CShowECGUpdateInterface(void)
	{
	}

	CShowECGUpdateInterface::~CShowECGUpdateInterface(void)
	{
	}

	bool CShowECGUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowECGUpdateInterface" )
			return true;
		return IUpdateShowVir::isKindOf(className);
	}

	void CShowECGUpdateInterface::UnLinkUpdateShow()
	{
		//断开显示后通知
		cutLinkECGUpdateShow();
	}

	void CShowECGUpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkECGUpdateShow();
	}

	/*******************************************************************************/
	// 函数名称： OnShowECGName
	// 功能： 显示心电图名称
	// 参数： CString  strQRS:            QRS类型
	//        CString strRhythm:          基本心律名称
	//        CString strExtrasyst:       早搏    
	//        int nHR:             心率
	//        BOOL bEMD: 
	//注：  参数的内容为内置名称，显示时再转换为显示名称
	// 返回值:  
    void CShowECGUpdateInterface::OnShowECGName(const std::string &strRhythm, const std::string &strExtrasyst, int nHR, bool bEMD)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowECGUpdateInterface" ) )
			{
				CShowECGUpdateInterface *pShowECGInterface = (CShowECGUpdateInterface *)pInterface;
				pShowECGInterface->ShowECGName(strRhythm, strExtrasyst, nHR, bEMD);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// 函数名称： OnShowECGRateRange
	// 功能： 显示正确心率的范围
	// 参数： int nMinRate:               最小心率（单位：次/分钟）
	//        int nMaxRate:               最大心率（单位：次/分钟）  
	// 返回值:  
	void CShowECGUpdateInterface::OnShowECGRateRange(int nMinRate, int nMaxRate)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowECGUpdateInterface" ) )
			{
				CShowECGUpdateInterface *pShowECGInterface = (CShowECGUpdateInterface *)pInterface;
				pShowECGInterface->ShowECGRateRange(nMinRate, nMaxRate);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// 函数名称： OnShowECGRate
	// 功能： 显示当前的心率值
	// 参数： int nHR:                    心率值（单位：次/分钟）
	// 返回值:  
	void CShowECGUpdateInterface::OnShowECGRate(int nHR)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowECGUpdateInterface" ) )
			{
				CShowECGUpdateInterface *pShowECGInterface = (CShowECGUpdateInterface *)pInterface;
				pShowECGInterface->ShowECGRate(nHR);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// 函数名称： OnShowECGNameInDefib
	// 功能： 因除颤而修改心电图名称
	// 参数： CString  strQRS:            QRS类型
	//        CString strRhythm:          基本心律名称
	//        CString strExtrasyst:       早搏    
	//        int nHR:             心率
	//        BOOL bEMD: 
	//注：  参数的内容为内置名称，显示时再转换为显示名称
	// 返回值:  
    void CShowECGUpdateInterface::OnShowECGNameInDefib(const std::string &strRhythm, const std::string &strExtrasyst, int nHR, bool bEMD, int nMillDelayTime)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowECGUpdateInterface" ) )
			{
				CShowECGUpdateInterface *pShowECGInterface = (CShowECGUpdateInterface *)pInterface;
				pShowECGInterface->ShowECGNameInDefib(strRhythm, strExtrasyst, nHR, bEMD, nMillDelayTime);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// 函数名称： OnShowECGRate
	// 功能： 因除颤而修改当前的心率值
	// 参数： int nHR:                    心率值（单位：次/分钟）
	// 返回值: 
	void CShowECGUpdateInterface::OnShowECGRateInDefib(int nHR, int nMillDelayTime)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowECGUpdateInterface" ) )
			{
				CShowECGUpdateInterface *pShowECGInterface = (CShowECGUpdateInterface *)pInterface;
				pShowECGInterface->ShowECGRateInDefib(nHR, nMillDelayTime);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
