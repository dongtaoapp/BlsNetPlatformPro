#include ".\opecgbuildinterface.h"
#include ".\ShowECGUpdateInterface.h"

namespace jysoft { namespace simulator { namespace base {

	COpECGBuildInterface::COpECGBuildInterface(void)
	{
		m_pShowECGUpdate  = NULL;
		m_pSyncPnPFacilities    = NULL;
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
	// 参数： CECGParams *pECGParams:       
	// 返回值:  
	void COpECGBuildInterface::OnModifyECGHandle(CECGParams *pECGParams)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->ModifyECGHandle( pECGParams );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// 函数名称： OnDirectModifyECGHandle
	// 功能： 直接修改心电图
	// 参数： CECGParams *pECGParams
	//注： 对心电图Build初始化构造时也用此函数
	// 返回值:  
	void COpECGBuildInterface::OnDirectModifyECGHandle(CECGParams *pECGParams)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->DirectModifyECGHandle( pECGParams );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// 函数名称： OnManualBuildExtrasystHandle
	// 功能： 手动生成一个早波
	// 参数：       
	// 返回值:  
	void COpECGBuildInterface::OnManualBuildExtrasystHandle()
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->ManualBuildExtrasystHandle( );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}
	/*******************************************************************************/
	// 函数名称： OnModifyECGInDefibrEventHandle
	// 功能： 因为除颤而修改波形
	// 参数： CECGParams *pECGParams
	// 返回值:  
	void COpECGBuildInterface::OnModifyECGInDefibrEventHandle(CECGParams *pECGParams)
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
	// 函数名称： OnStartPacingHandle
	// 功能： 启动起搏
	// 参数： 
	// 返回值:  
	void COpECGBuildInterface::OnStartPacingHandle(short sPaceHR)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->StartPacingHandle( sPaceHR );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}
	/*******************************************************************************/
	// 函数名称： OnStartPacingHandle
	// 功能： 修改起搏频率
	// 参数： 
	// 返回值:  
	void COpECGBuildInterface::OnModifyPacingRateHandle(long nPaceRate)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->ModifyPacingRateHandle( nPaceRate );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
		m_cInterfaceMutex.Lock();
		if( m_pShowECGUpdate != NULL )
		{
			m_pShowECGUpdate->OnShowECGRate( (int)nPaceRate );
		}
		m_cInterfaceMutex.Unlock();
	}
	/*******************************************************************************/
	// 函数名称： OnStopPacingHandle
	// 功能： 停止起搏
	// 参数： 
	// 返回值: 
	void COpECGBuildInterface::OnStopPacingHandle()
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpECGBuildInterface" ) )
			{
				COpECGBuildInterface *pOpECGBuildInterface = (COpECGBuildInterface *)pInterfaceVir;
				pOpECGBuildInterface->StopPacingHandle( );
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

	/*******************************************************************************/
	// 函数名称： OnModifyPnPFacility
	// 功能： 改变热插拔设备
	// 参数： CSyncPnpFacilities *pSyncPnPFacilities: 
	// 返回值:  
	void COpECGBuildInterface::OnModifyPnPFacility(pnp::CSyncPnpFacilities *pSyncPnPFacilities)
	{
		if( pSyncPnPFacilities != NULL )
		{
			m_pSyncPnPFacilities = pSyncPnPFacilities;
		}
	}

	void COpECGBuildInterface::ModifyTransmitAddress(/*out*/short &sAddress)
	{
		if( m_pSyncPnPFacilities != NULL )
		{
			//同步管理修改通讯指令的转发地址
            m_pSyncPnPFacilities->SyncModifyTransmitAddress(/*out*/sAddress, "Cardiogram_RealTimeData" );
		}
	}

}}}
