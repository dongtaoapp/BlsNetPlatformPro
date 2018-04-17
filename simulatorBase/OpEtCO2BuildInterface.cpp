#include ".\opetco2buildinterface.h"
#include ".\ShowEtCO2UpdateInterface.h"

namespace jysoft { namespace simulator { namespace base {

	COpEtCO2BuildInterface::COpEtCO2BuildInterface(void)
	{
		m_pShowEtCO2Update  = NULL;
	}

	COpEtCO2BuildInterface::~COpEtCO2BuildInterface(void)
	{
	}

	bool COpEtCO2BuildInterface::isKindOf(const std::string &className)
	{
        if( className == "COpEtCO2BuildInterface" )
		{
			return true;
		}
		return COpInterfaceVir::isKindOf( className );
	}

	//�޸�CO2%
	void COpEtCO2BuildInterface::OnModifyCO2PercentValue( int nCO2Per )
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpEtCO2BuildInterface" ) )
			{
				COpEtCO2BuildInterface *pOpEtCO2BuildInterface = (COpEtCO2BuildInterface *)pInterfaceVir;
				pOpEtCO2BuildInterface->ModifyCO2PercentValue( nCO2Per );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	// ��/����¼�
	void COpEtCO2BuildInterface::OnIntubateEventOp( bool bIntubate )
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpEtCO2BuildInterface" ) )
			{
				COpEtCO2BuildInterface *pOpEtCO2BuildInterface = (COpEtCO2BuildInterface *)pInterfaceVir;
				pOpEtCO2BuildInterface->IntubateEventOp( bIntubate );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	//һ�δ����¼�
	void COpEtCO2BuildInterface::OnOnceBreathEventOp()
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpEtCO2BuildInterface" ) )
			{
				COpEtCO2BuildInterface *pOpEtCO2BuildInterface = (COpEtCO2BuildInterface *)pInterfaceVir;
				pOpEtCO2BuildInterface->OnceBreathEventOp( );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	//�׶���CPR�¼�
	void COpEtCO2BuildInterface::OnCPREventOp( bool bStop )
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpEtCO2BuildInterface" ) )
			{
				COpEtCO2BuildInterface *pOpEtCO2BuildInterface = (COpEtCO2BuildInterface *)pInterfaceVir;
				pOpEtCO2BuildInterface->CPREventOp( bStop );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// �������ƣ� SetRelateEtCO2ShowInterface
	// ���ܣ� ����EtCO2��ʾ�ӿ�
	// ������ CShowEtCO2UpdateInterface *pShowInterface:       
	// ����ֵ:  
	//ע�� ͨ��CShowEtCO2UpdateInterface�Ĵ���ָ�룬��������صĶ��EtCO2��ʾ�ӿ�
	void COpEtCO2BuildInterface::SetRelateEtCO2ShowInterface(CShowEtCO2UpdateInterface *pShowInterface)
	{
		boost::mutex::scoped_lock  lock( m_cInterfaceMutex );
		if( m_pShowEtCO2Update == NULL )
		{
			m_pShowEtCO2Update    =  pShowInterface;
		}
		else
		{
			m_pShowEtCO2Update->SetNextInterfacePtr( pShowInterface );
		}
	}

	//�Ͽ�ָ����EtCO2��ʾ�ӿ�
	void COpEtCO2BuildInterface::RemoveRelateEtCO2ShowInterface(CShowEtCO2UpdateInterface *pRmvShowEtCO2Interface)
	{
		boost::mutex::scoped_lock  lock( m_cInterfaceMutex );
		if( m_pShowEtCO2Update  !=  NULL )
		{
			m_pShowEtCO2Update = (CShowEtCO2UpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowEtCO2Update, pRmvShowEtCO2Interface);
		}
	}

}}}
