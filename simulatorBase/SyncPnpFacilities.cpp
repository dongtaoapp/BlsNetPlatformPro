#include ".\SyncPnpFacilities.h"


namespace jysoft { namespace pnp {

	CSyncPnpFacilities::CSyncPnpFacilities(void)
	{
		m_pPnPFacilities   = NULL;
		m_nWeepSpeedParam  = 0;
		m_nSweatSpeedParam = 0;
	}


	CSyncPnpFacilities::~CSyncPnpFacilities(void)
	{
		while ( m_pPnPFacilities != NULL )
		{
			IPnPFacility *pNextFacility = m_pPnPFacilities->GetNextInterfacePtr();
			delete m_pPnPFacilities;
			m_pPnPFacilities = pNextFacility;
		}
	}

	/*******************************************************************************/
	// 函数名称： SyncAddPnpInstrument
	// 功能：   同步管理添加新的Pnp设备
	// 参数：   
	//      IPnPFacility *pNewPnPFacility: 
	// 返回值: 
	void CSyncPnpFacilities::SyncAddPnpInstrument( IPnPFacility *pNewPnPFacility )
	{
        m_cPnpMutex.Lock();
		if( m_pPnPFacilities == NULL )
		{
			m_pPnPFacilities  = pNewPnPFacility;
		}
		else if( pNewPnPFacility != NULL )
		{
			m_pPnPFacilities->SetNextInterfacePtr( pNewPnPFacility );
		}
        m_cPnpMutex.Unlock();
	}

	/*******************************************************************************/
	// 函数名称： SyncRemovePnpInstrument
	// 功能：   同步管理移除Pnp设备
	// 参数：   
	//      IPnPFacility *pRmvPnPFacility: 
	// 返回值: 
    bool CSyncPnpFacilities::SyncRemovePnpInstrument( IPnPFacility  *pRmvPnPFacility )
	{
        bool   bSecRmv = false;
        m_cPnpMutex.Lock();
		if( m_pPnPFacilities != NULL && pRmvPnPFacility != NULL )
		{
			//移除此设备
			m_pPnPFacilities = IPnPFacility::RemoveInterfacePtr( m_pPnPFacilities, pRmvPnPFacility );
            bSecRmv   = true;
		}
        m_cPnpMutex.Unlock();
	#ifdef  _DEBUG
		//遍历Pnp设备列表
		IPnPFacility  *pPnPFacility = m_pPnPFacilities;
		while( pPnPFacility != NULL )
		{
			short sPnpAddress = pPnPFacility->Get_PnPId();
			pPnPFacility = pPnPFacility->GetNextInterfacePtr();
		}
	#endif
		//删除Pnp设备
		delete pRmvPnPFacility;
		return bSecRmv;
	}

	/*******************************************************************************/
	// 函数名称： SyncRemovePnpInstrument
	// 功能：   同步管理移除Pnp设备
	// 参数：   
	//      short sPort: 
	// 返回值: 
    bool CSyncPnpFacilities::SyncRemovePnpInstrument( short sPnpID )
	{
		IPnPFacility  *pRmvPnPFacility = NULL;
		//遍历Pnp设备列表
		IPnPFacility  *pPnPFacility = m_pPnPFacilities;
		while( pPnPFacility != NULL )
		{
			if( pPnPFacility->Get_PnPId() == sPnpID )
			{
				pRmvPnPFacility = pPnPFacility;
				break;
			}
			pPnPFacility = pPnPFacility->GetNextInterfacePtr();
		}
		return SyncRemovePnpInstrument( pRmvPnPFacility );
	}

	/*******************************************************************************/
	// 函数名称： SyncModifyTransmitAddress
	// 功能：   同步管理修改通讯指令的转发地址
	// 参数：   
	//      /*out*/short &sAddress: 
	// 返回值: 
	void CSyncPnpFacilities::SyncModifyTransmitAddress(/*out*/short &sAddress, const std::string &symptomCaption)
	{
        m_cPnpMutex.Lock();
		IPnPFacility  *pDstFacility  = m_pPnPFacilities;
		while( pDstFacility != NULL )
		{
			pDstFacility->OnModifyTransmitAddress(/*out*/sAddress, symptomCaption );
			pDstFacility  = pDstFacility->GetNextInterfacePtr();
		}
        m_cPnpMutex.Unlock();
	}

	/*******************************************************************************/
	// 函数名称： RemoveAllPnpInstrument
	// 功能：   清除所有的Pnp设备
	// 参数：   
	//      
	// 返回值: 
	void CSyncPnpFacilities::RemoveAllPnpInstrument()
	{
        m_cPnpMutex.Lock();
		while ( m_pPnPFacilities != NULL )
		{
			IPnPFacility *pNextFacility = m_pPnPFacilities->GetNextInterfacePtr();
			delete m_pPnPFacilities;
			m_pPnPFacilities = pNextFacility;
		}
        m_cPnpMutex.Unlock();
	}

	void CSyncPnpFacilities::Set_WaterSpeedParams(int nWeepSpeed, int nSeatSpeed)
	{
		m_nWeepSpeedParam  = nWeepSpeed;
		m_nSweatSpeedParam = nSeatSpeed;
	}

}}
