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

	//�����¸�������ʾ�ؼ��ӿ�
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
				//�����ϸ��ӿ�
				pNextInterface->SetPreviouInterfacePtr( pInterfaceVir );
			}
		}
	}

	//���ؽӿ������ͷ
	IBedirecteLinksVir * IBedirecteLinksVir::GetHeaderInterfacePtr()
	{
		IBedirecteLinksVir *pInterfaceVir = this;
		while(pInterfaceVir->GetPreviouInterfacePtr() != NULL)
		{
			pInterfaceVir = pInterfaceVir->GetPreviouInterfacePtr();
		}
		return pInterfaceVir;
	}

	//�Ƴ��ƶ��Ľӿ�
	IBedirecteLinksVir * IBedirecteLinksVir::RemoveInterfacePtr(IBedirecteLinksVir *pOrgInterfacePtr, IBedirecteLinksVir *pRmvInterface)
	{
		if( pOrgInterfacePtr == NULL || pRmvInterface == NULL )
		{
			return pOrgInterfacePtr;
		}
		IBedirecteLinksVir *pHeadInterface = pOrgInterfacePtr->GetHeaderInterfacePtr();
		//�ж��Ƴ���ָ���Ƿ�������������
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
		//�Ƴ�ָ�����
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
		//����ͷָ��
		return pPreShowInterface->GetHeaderInterfacePtr();
	}
}
