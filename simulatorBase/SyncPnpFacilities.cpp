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
	// �������ƣ� SyncAddPnpInstrument
	// ���ܣ�   ͬ����������µ�Pnp�豸
	// ������   
	//      IPnPFacility *pNewPnPFacility: 
	// ����ֵ: 
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
	// �������ƣ� SyncRemovePnpInstrument
	// ���ܣ�   ͬ�������Ƴ�Pnp�豸
	// ������   
	//      IPnPFacility *pRmvPnPFacility: 
	// ����ֵ: 
    bool CSyncPnpFacilities::SyncRemovePnpInstrument( IPnPFacility  *pRmvPnPFacility )
	{
        bool   bSecRmv = false;
        m_cPnpMutex.Lock();
		if( m_pPnPFacilities != NULL && pRmvPnPFacility != NULL )
		{
			//�Ƴ����豸
			m_pPnPFacilities = IPnPFacility::RemoveInterfacePtr( m_pPnPFacilities, pRmvPnPFacility );
            bSecRmv   = true;
		}
        m_cPnpMutex.Unlock();
	#ifdef  _DEBUG
		//����Pnp�豸�б�
		IPnPFacility  *pPnPFacility = m_pPnPFacilities;
		while( pPnPFacility != NULL )
		{
			short sPnpAddress = pPnPFacility->Get_PnPId();
			pPnPFacility = pPnPFacility->GetNextInterfacePtr();
		}
	#endif
		//ɾ��Pnp�豸
		delete pRmvPnPFacility;
		return bSecRmv;
	}

	/*******************************************************************************/
	// �������ƣ� SyncRemovePnpInstrument
	// ���ܣ�   ͬ�������Ƴ�Pnp�豸
	// ������   
	//      short sPort: 
	// ����ֵ: 
    bool CSyncPnpFacilities::SyncRemovePnpInstrument( short sPnpID )
	{
		IPnPFacility  *pRmvPnPFacility = NULL;
		//����Pnp�豸�б�
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
	// �������ƣ� SyncModifyTransmitAddress
	// ���ܣ�   ͬ�������޸�ͨѶָ���ת����ַ
	// ������   
	//      /*out*/short &sAddress: 
	// ����ֵ: 
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
	// �������ƣ� RemoveAllPnpInstrument
	// ���ܣ�   ������е�Pnp�豸
	// ������   
	//      
	// ����ֵ: 
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
