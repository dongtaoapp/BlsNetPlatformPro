#include ".\oprespbuildinterface.h"

#include "..\elementParse\SAction_Resp.h"

namespace jysoft { namespace simulator { namespace base {

	COpRespBuildInterface::COpRespBuildInterface(void)
	{
		m_pShowRespUpdate  = NULL;
		m_pSyncPnPFacilities = NULL;
	}

	COpRespBuildInterface::~COpRespBuildInterface(void)
	{
	}

	bool COpRespBuildInterface::isKindOf(const std::string &className)
	{
		if( className == "COpRespBuildInterface" )
		{
			return true;
		}
		return COpInterfaceVir::isKindOf( className );
	}

	/*******************************************************************************/
	// 函数名称： OnModifyRespRate
	// 功能： 修改呼吸次数
	// 参数：  int nBreathRate:            呼吸次数（单位：次/分钟）
	// 返回值:  
	void COpRespBuildInterface::OnModifyRespRate(int nBreathRate)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpRespBuildInterface" ) )
			{
				COpRespBuildInterface *pOpRespBuildInterface = (COpRespBuildInterface *)pInterfaceVir;
				pOpRespBuildInterface->ModifyRespRate( nBreathRate );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// 函数名称： OnModifyRespBuildType
	// 功能： 修改类型及次数
	// 参数：  eRespMode eMode:            呼吸类型
	//         int nBreathRate:                       呼吸次数（单位：次/分钟）
	// 返回值:  
	void COpRespBuildInterface::OnModifyRespBuildType(eRespMode eMode, int nBreathRate)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpRespBuildInterface" ) )
			{
				COpRespBuildInterface *pOpRespBuildInterface = (COpRespBuildInterface *)pInterfaceVir;
				pOpRespBuildInterface->ModifyRespBuildType( eMode, nBreathRate );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// 函数名称： SetRelateRespRateShowInterface
	// 功能： 联接呼吸次数显示接口
	// 参数： CShowRespRateUpdateInterface *pShowInterface:       
	// 返回值:  
	//注： 通过CShowRespRateUpdateInterface的串联指针，可连接相关的多个呼吸次数显示接口
	void COpRespBuildInterface::SetRelateRespRateShowInterface(CShowRespRateUpdateInterface *pShowInterface)
	{
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if ( m_pShowRespUpdate == NULL )
		{
			m_pShowRespUpdate = pShowInterface;
		}
		else
		{
			m_pShowRespUpdate->SetNextInterfacePtr( pShowInterface );
		}
	}

	//断开指定的呼吸次数显示接口
	void COpRespBuildInterface::RemoveRelateRespRateShowInterface(CShowRespRateUpdateInterface *pRmvShowInterface)
	{
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowRespUpdate != NULL )
		{
			m_pShowRespUpdate = (CShowRespRateUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowRespUpdate, pRmvShowInterface);
		}
	}

	/*******************************************************************************/
	// 函数名称： OnModifyPnPFacility
	// 功能： 改变热插拔设备
	// 参数： CSyncPnpFacilities *pSyncPnPFacilities:       
	// 返回值:  
	void COpRespBuildInterface::OnModifyPnPFacility(pnp::CSyncPnpFacilities *pSyncPnPFacilities)
	{
		if( pSyncPnPFacilities != NULL )
		{
			m_pSyncPnPFacilities = pSyncPnPFacilities;
		}
	}

	void COpRespBuildInterface::ModifyTransmitAddress(/*out*/short &sAddress)
	{
		if( m_pSyncPnPFacilities != NULL )
		{
			//同步管理修改通讯指令的转发地址
			std::string  symptomCaption = CSAction_Resp::getAction_Resp_Caption();
			m_pSyncPnPFacilities->SyncModifyTransmitAddress(/*out*/sAddress, symptomCaption );
		}
	}

}}}
