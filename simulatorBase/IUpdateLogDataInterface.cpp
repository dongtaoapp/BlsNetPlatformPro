#include ".\iupdatelogdatainterface.h"

namespace jysoft{  namespace log {

	IUpdateLogDataInterface::IUpdateLogDataInterface(void)
	{
	}

	IUpdateLogDataInterface::~IUpdateLogDataInterface(void)
	{
	}

	bool IUpdateLogDataInterface::isKindOf(const std::string &className)
	{
		if( className == "IUpdateLogDataInterface" )
		{
			return true;
		}
		return IUpdateShowVir::isKindOf(className);
	}

	void IUpdateLogDataInterface::UnLinkUpdateShow()
	{
		//断开显示后通知
		cutLinkLogDataUpdateShow();
	}

	void IUpdateLogDataInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkLogDataUpdateShow();
	}

	/*******************************************************************************/
	// 函数名称： OnUpdateEventLogData
	// 功能：   更新新的日志条目
	// 参数：   
	//      _EventLog_struct *pEventLog: 
	//      bool bSafeShow：                是否为线程安全的模式添加显示
	// 返回值: 
	void IUpdateLogDataInterface::OnUpdateEventLogData(_EventLog_struct *pEventLog, bool bSafeShow/*=TRUE*/)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "IUpdateLogDataInterface" ) )
			{
				IUpdateLogDataInterface *pShowLogInterface = (IUpdateLogDataInterface *)pInterface;
				pShowLogInterface->UpdateEventLogData( pEventLog, bSafeShow );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// 函数名称： OnUpdateEventLogData
	// 功能：   更新所有日志条目
	// 参数：   
	//          CList<_EventLog_struct *, _EventLog_struct *> *list: 
	// 返回值: 
	void IUpdateLogDataInterface::OnUpdateEventLogData(std::list<_EventLog_struct *> *plstEentLogs)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "IUpdateLogDataInterface" ) )
			{
				IUpdateLogDataInterface *pShowLogInterface = (IUpdateLogDataInterface *)pInterface;
				pShowLogInterface->UpdateEventLogData( plstEentLogs );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// 函数名称： OnResetLogData
	// 功能：   重置（清除）日志数据
	// 参数：   
	// 返回值: 
	void IUpdateLogDataInterface::OnResetLogData()
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "IUpdateLogDataInterface" ) )
			{
				IUpdateLogDataInterface *pShowLogInterface = (IUpdateLogDataInterface *)pInterface;
				pShowLogInterface->ResetLogData( );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}
