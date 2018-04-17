#include ".\opspo2buildinterface.h"
#include ".\ShowSpO2UpdateInterface.h"


namespace jysoft { namespace simulator { namespace base {

	COpSpO2BuildInterface::COpSpO2BuildInterface(void)
	{
		m_pShowSpO2Update  = NULL;
	}

	COpSpO2BuildInterface::~COpSpO2BuildInterface(void)
	{
	}

	bool COpSpO2BuildInterface::isKindOf(const std::string &className)
	{
		if( className == "COpSpO2BuildInterface" )
			return true;
		return COpInterfaceVir::isKindOf( className );
	}

	/*******************************************************************************/
	// �������ƣ� OnModifySpO2ValuePrecent
	// ���ܣ� �޸�Ѫ���İٷֱ�Ũ��
	// ������  int nSpO2Value:            Ѫ���ٷֱ�Ũ��ֵ
	// ����ֵ:  
	void COpSpO2BuildInterface::OnModifySpO2ValuePrecent( int nSpO2Value )
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpSpO2BuildInterface" ) )
			{
				COpSpO2BuildInterface *pOpSpO2BuildInterface = (COpSpO2BuildInterface *)pInterfaceVir;
				pOpSpO2BuildInterface->ModifySpO2ValuePrecent( nSpO2Value );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowSpO2Update != NULL )
		{
			m_pShowSpO2Update->OnShowSpO2Value( nSpO2Value );
		}
	}


	/*******************************************************************************/
	// �������ƣ� SetRelateSpO2ShowInterface
	// ���ܣ� ����SpO2��ʾ�ӿ�
	// ������ CShowSpO2UpdateInterface *pShowInterface:       
	// ����ֵ:  
	//ע�� ͨ��CShowSpO2UpdateInterface�Ĵ���ָ�룬��������صĶ��SpO2��ʾ�ӿ�
	void COpSpO2BuildInterface::SetRelateSpO2ShowInterface(CShowSpO2UpdateInterface *pShowInterface)
	{
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowSpO2Update == NULL )
		{
			m_pShowSpO2Update   =  pShowInterface;
		}
		else
		{
			m_pShowSpO2Update->SetNextInterfacePtr( pShowInterface );
		}
	}

	//�Ͽ�ָ����SpO2��ʾ�ӿ�
	void COpSpO2BuildInterface::RemoveRelateSpO2ShowInterface(CShowSpO2UpdateInterface *pRmvShowInterface)
	{
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowSpO2Update != NULL )
		{
			m_pShowSpO2Update = (CShowSpO2UpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowSpO2Update, pRmvShowInterface);
		}
	}

}}}
