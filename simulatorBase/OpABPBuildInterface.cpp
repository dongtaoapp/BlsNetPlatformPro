#include ".\opabpbuildinterface.h"
#include ".\ShowABPUpdateInterface.h"

namespace jysoft { namespace simulator { namespace base {

	COpABPBuildInterface::COpABPBuildInterface(void)
	{
		m_pShowABPUpdate  = NULL;
	}

	COpABPBuildInterface::~COpABPBuildInterface(void)
	{
	}

	bool COpABPBuildInterface::isKindOf(const std::string &className)
	{
		if( className == "COpABPBuildInterface" )
		{
			return true;
		}
		return COpInterfaceVir::isKindOf( className );
	}

	/*******************************************************************************/
	// 函数名称： SetRelateABPShowInterface
	// 功能： 联接ABP显示接口
	// 参数： CShowABPUpdateInterface *pShowInterface:       
	// 返回值:  
	//注： 通过CShowABPUpdateInterface的串联指针，可连接相关的多个ABP显示接口
	void COpABPBuildInterface::SetRelateABPShowInterface(CShowABPUpdateInterface *pShowInterface)
	{
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowABPUpdate == NULL )
		{
			m_pShowABPUpdate   =  pShowInterface;
		}
		else
		{
			m_pShowABPUpdate->SetNextInterfacePtr( pShowInterface );
		}
	}

	//断开指定的ABP显示接口
	void COpABPBuildInterface::RemoveRelateABPShowInterface(CShowABPUpdateInterface *pRmvShowInterface)
	{
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowABPUpdate != NULL )
		{
			m_pShowABPUpdate = (CShowABPUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowABPUpdate, pRmvShowInterface);
		}
	}

	//修改ABP的值
	void COpABPBuildInterface::OnModifyABPValue(int nShrinkValue, int nStretchValue)
	{
		IBedirecteLinksVir *pInterfaceVir = GetHeaderInterfacePtr();
		while ( pInterfaceVir != NULL )
		{
			if( pInterfaceVir->isKindOf( "COpABPBuildInterface" ) )
			{
				COpABPBuildInterface *pOpABPBuildInterface = (COpABPBuildInterface *)pInterfaceVir;
				pOpABPBuildInterface->ModifyABPValue( nShrinkValue, nStretchValue );
			}
			pInterfaceVir = pInterfaceVir->GetNextInterfacePtr();
		}
		boost::mutex::scoped_lock  lock(m_cInterfaceMutex);
		if( m_pShowABPUpdate != NULL )
		{
			m_pShowABPUpdate->OnShowABPValue(nShrinkValue, nStretchValue);
		}
	}

}}}
