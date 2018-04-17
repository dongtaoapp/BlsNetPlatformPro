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
	// 函数名称： OnModifySpO2ValuePrecent
	// 功能： 修改血氧的百分比浓度
	// 参数：  int nSpO2Value:            血氧百分比浓度值
	// 返回值:  
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
	// 函数名称： SetRelateSpO2ShowInterface
	// 功能： 联接SpO2显示接口
	// 参数： CShowSpO2UpdateInterface *pShowInterface:       
	// 返回值:  
	//注： 通过CShowSpO2UpdateInterface的串联指针，可连接相关的多个SpO2显示接口
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

	//断开指定的SpO2显示接口
	void COpSpO2BuildInterface::RemoveRelateSpO2ShowInterface(CShowSpO2UpdateInterface *pRmvShowInterface)
	{
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowSpO2Update != NULL )
		{
			m_pShowSpO2Update = (CShowSpO2UpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowSpO2Update, pRmvShowInterface);
		}
	}

}}}
