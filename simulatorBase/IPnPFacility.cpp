#include ".\IPnPFacility.h"

namespace jysoft { namespace pnp {
	//------------------------------------------------------------------------------------------------
	//class IPnPFacility
	IPnPFacility::IPnPFacility(short sPnpID, short sPort)
	{
		m_pNextInterface  = NULL;
		m_pPreInterface   = NULL;
		m_sPnpID = sPnpID;
		m_sPnPAddress     = sPort;
	}

	IPnPFacility::~IPnPFacility(void)
	{
	}

	//设置下个即插即用设备接口类
	void IPnPFacility::SetNextInterfacePtr(IPnPFacility *pNextInterface)
	{
		if( pNextInterface != NULL )
		{
			IPnPFacility *pInterfaceVir = GetHeaderInterfacePtr();
			if( pInterfaceVir != pNextInterface )
			{
				while(pInterfaceVir->GetNextInterfacePtr() != NULL)
				{
					pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
					if( pInterfaceVir == pNextInterface )
					{
						break;
					}
				}
			}
			if(	pInterfaceVir != pNextInterface)
			{
				pInterfaceVir->m_pNextInterface = pNextInterface;
				//设置上个接口
				pNextInterface->SetPreviouInterfacePtr( pInterfaceVir );
			}
		}
	}

	//返回接口联表的头
	IPnPFacility * IPnPFacility::GetHeaderInterfacePtr()
	{
		IPnPFacility *pInterfaceVir = this;
		while(pInterfaceVir->GetPreviouInterfacePtr() != NULL)
		{
			pInterfaceVir = pInterfaceVir->GetPreviouInterfacePtr();
		}
		return pInterfaceVir;
	}

	//移除制定的接口
	IPnPFacility * IPnPFacility::RemoveInterfacePtr(IPnPFacility *pOrgInterfacePtr, IPnPFacility *pRmvInterface)
	{
		IPnPFacility *pHeadInterface = pOrgInterfacePtr->GetHeaderInterfacePtr();
		//判断移除的指针是否在链接连表里
        bool   bFindInterface = false;
		do
		{
			if( pHeadInterface == pRmvInterface )
			{
                bFindInterface = true;
				break;
			}
			pHeadInterface = pHeadInterface->GetNextInterfacePtr();
		}while( pHeadInterface );

		if( !bFindInterface )
		{
			return pOrgInterfacePtr;
		}
		//移除指针操作
		if( pRmvInterface->GetPreviouInterfacePtr() == NULL )
		{
			pRmvInterface->m_pPreInterface = NULL;
			IPnPFacility  *pNextPnPFacility = pRmvInterface->GetNextInterfacePtr();
			if( pNextPnPFacility != NULL )
			{
				pNextPnPFacility->m_pPreInterface     = NULL;
			}
			pRmvInterface->m_pNextInterface      = NULL;
			return pNextPnPFacility;
		}
		IPnPFacility  *pPrePnPFacility = pRmvInterface->GetPreviouInterfacePtr();
		pPrePnPFacility->m_pNextInterface    = pRmvInterface->m_pNextInterface;
		pRmvInterface->m_pPreInterface        = NULL;
		pRmvInterface->m_pNextInterface       = NULL;
		//返回头指针
		return pPrePnPFacility->GetHeaderInterfacePtr();
	}

	/*******************************************************************************/
	// 函数名称： OnModifyTransmitAddress
	// 功能：   修改通讯指令的转发地址
	// 参数：   
	//      /*out*/short &sAddress: 
	// 返回值: 
	void IPnPFacility::OnModifyTransmitAddress(/*out*/short &sAddress, const std::string &symptomCaption)
	{
		if( isModifyTransmitAddress( symptomCaption) )
		{
			sAddress |= m_sPnPAddress;
		}
	}

}}
