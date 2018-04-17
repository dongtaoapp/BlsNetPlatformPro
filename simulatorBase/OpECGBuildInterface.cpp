#include ".\opecgbuildinterface.h"
#include ".\ShowECGUpdateInterface.h"

namespace jysoft { namespace simulator { namespace base {

	COpECGBuildInterface::COpECGBuildInterface(void)
	{
		m_pShowECGUpdate  = NULL;
	}

	COpECGBuildInterface::~COpECGBuildInterface(void)
	{
	}

	bool COpECGBuildInterface::isKindOf(const std::string &className)
	{
		if( className == "COpECGBuildInterface" )
			return true;
		return COpInterfaceVir::isKindOf( className );
	}

	/*******************************************************************************/
	// 函数名称： OnModifyECGHandle
	// 功能： 修改心电图
	// 参数： cECGParams:  
	// 返回值:  
	void COpECGBuildInterface::OnModifyECGHandle(const CECGParams &cECGParams)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->ModifyECGHandle( cECGParams );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// 函数名称： OnDirectModifyECGHandle
	// 功能： 直接修改心电图
	// 参数： cECGParams: 
	//注： 对心电图Build初始化构造时也用此函数
	// 返回值:  
	void COpECGBuildInterface::OnDirectModifyECGHandle(const CECGParams &cECGParams)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->DirectModifyECGHandle( cECGParams );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// 函数名称： OnModifyECGInDefibrEventHandle
	// 功能： 因为除颤而修改波形
	// 参数： cECGParams: 
	// 返回值:  
	void COpECGBuildInterface::OnModifyECGInDefibrEventHandle(const CECGParams *pECGParams)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->ModifyECGInDefibrEventHandle( pECGParams );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// 函数名称： SetRelateECGShowInterface
	// 功能： 联接心电图显示接口
	// 参数： CShowECGUpdateInterface *pShowECGInterface:       
	// 返回值:  
	//注： 通过CShowECGUpdateInterface的串联指针，可连接相关的多个心电图显示接口
	void COpECGBuildInterface::SetRelateECGShowInterface(CShowECGUpdateInterface *pShowECGInterface)
	{
		m_cInterfaceMutex.Lock();
		if( m_pShowECGUpdate == NULL )
		{
			m_pShowECGUpdate  = pShowECGInterface;
		}
		else
		{
			m_pShowECGUpdate->SetNextInterfacePtr( pShowECGInterface );
		}
		m_cInterfaceMutex.Unlock();
	}

	//断开指定的心电图显示接口
	void COpECGBuildInterface::RemoveRelateECGShowInterface(CShowECGUpdateInterface *pRmvShowECGInterface)
	{
		m_cInterfaceMutex.Lock();
		if( m_pShowECGUpdate != NULL )
		{
			m_pShowECGUpdate = (CShowECGUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowECGUpdate, pRmvShowECGInterface);
		}
		m_cInterfaceMutex.Unlock();
	}

}}}
