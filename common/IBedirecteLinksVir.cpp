#include ".\ibedirectelinksvir.h"

namespace jysoft { 
	IBedirecteLinksVir::IBedirecteLinksVir(void)
	{
		m_pNextInterface  = NULL;
		m_pPreInterface   = NULL;
	}

	IBedirecteLinksVir::~IBedirecteLinksVir(void)
	{
	}

	//设置下个界面显示控件接口
	void IBedirecteLinksVir::SetNextInterfacePtr(IBedirecteLinksVir *pNextInterface)
	{
		if( pNextInterface != NULL )
		{
			IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
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
	IBedirecteLinksVir * IBedirecteLinksVir::GetHeaderInterfacePtr()
	{
		IBedirecteLinksVir *pInterfaceVir = this;
		while(pInterfaceVir->GetPreviouInterfacePtr() != NULL)
		{
			pInterfaceVir = pInterfaceVir->GetPreviouInterfacePtr();
		}
		return pInterfaceVir;
	}

	//移除制定的接口
	IBedirecteLinksVir * IBedirecteLinksVir::RemoveInterfacePtr(IBedirecteLinksVir *pOrgInterfacePtr, IBedirecteLinksVir *pRmvInterface)
	{
		if( pOrgInterfacePtr == NULL || pRmvInterface == NULL )
		{
			return pOrgInterfacePtr;
		}
		IBedirecteLinksVir *pHeadInterface = pOrgInterfacePtr->GetHeaderInterfacePtr();
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
			IBedirecteLinksVir  *pNextUpdateShow = pRmvInterface->GetNextInterfacePtr();
			if( pNextUpdateShow != NULL )
			{
				pNextUpdateShow->m_pPreInterface     = NULL;
			}
			pRmvInterface->m_pNextInterface      = NULL;
			return pNextUpdateShow;
		}
		IBedirecteLinksVir  *pPreShowInterface = pRmvInterface->GetPreviouInterfacePtr();
		pPreShowInterface->m_pNextInterface    = pRmvInterface->m_pNextInterface;
		pRmvInterface->m_pPreInterface        = NULL;
		pRmvInterface->m_pNextInterface       = NULL;
		//返回头指针
		return pPreShowInterface->GetHeaderInterfacePtr();
	}
}
