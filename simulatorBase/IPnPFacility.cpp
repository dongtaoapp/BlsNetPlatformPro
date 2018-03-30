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

	//�����¸����弴���豸�ӿ���
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
				//�����ϸ��ӿ�
				pNextInterface->SetPreviouInterfacePtr( pInterfaceVir );
			}
		}
	}

	//���ؽӿ������ͷ
	IPnPFacility * IPnPFacility::GetHeaderInterfacePtr()
	{
		IPnPFacility *pInterfaceVir = this;
		while(pInterfaceVir->GetPreviouInterfacePtr() != NULL)
		{
			pInterfaceVir = pInterfaceVir->GetPreviouInterfacePtr();
		}
		return pInterfaceVir;
	}

	//�Ƴ��ƶ��Ľӿ�
	IPnPFacility * IPnPFacility::RemoveInterfacePtr(IPnPFacility *pOrgInterfacePtr, IPnPFacility *pRmvInterface)
	{
		IPnPFacility *pHeadInterface = pOrgInterfacePtr->GetHeaderInterfacePtr();
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
		//����ͷָ��
		return pPrePnPFacility->GetHeaderInterfacePtr();
	}

	/*******************************************************************************/
	// �������ƣ� OnModifyTransmitAddress
	// ���ܣ�   �޸�ͨѶָ���ת����ַ
	// ������   
	//      /*out*/short &sAddress: 
	// ����ֵ: 
	void IPnPFacility::OnModifyTransmitAddress(/*out*/short &sAddress, const std::string &symptomCaption)
	{
		if( isModifyTransmitAddress( symptomCaption) )
		{
			sAddress |= m_sPnPAddress;
		}
	}

}}
