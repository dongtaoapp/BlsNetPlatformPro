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

	//修改CO2%
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

	// 拔/插管事件
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

	//一次吹气事件
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

	//阶段性CPR事件
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
	// 函数名称： SetRelateEtCO2ShowInterface
	// 功能： 联接EtCO2显示接口
	// 参数： CShowEtCO2UpdateInterface *pShowInterface:       
	// 返回值:  
	//注： 通过CShowEtCO2UpdateInterface的串联指针，可连接相关的多个EtCO2显示接口
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

	//断开指定的EtCO2显示接口
	void COpEtCO2BuildInterface::RemoveRelateEtCO2ShowInterface(CShowEtCO2UpdateInterface *pRmvShowEtCO2Interface)
	{
		boost::mutex::scoped_lock  lock( m_cInterfaceMutex );
		if( m_pShowEtCO2Update  !=  NULL )
		{
			m_pShowEtCO2Update = (CShowEtCO2UpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowEtCO2Update, pRmvShowEtCO2Interface);
		}
	}

}}}
