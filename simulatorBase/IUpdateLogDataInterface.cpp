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
		//�Ͽ���ʾ��֪ͨ
		cutLinkLogDataUpdateShow();
	}

	void IUpdateLogDataInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkLogDataUpdateShow();
	}

	/*******************************************************************************/
	// �������ƣ� OnUpdateEventLogData
	// ���ܣ�   �����µ���־��Ŀ
	// ������   
	//      _EventLog_struct *pEventLog: 
	//      bool bSafeShow��                �Ƿ�Ϊ�̰߳�ȫ��ģʽ�����ʾ
	// ����ֵ: 
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
	// �������ƣ� OnUpdateEventLogData
	// ���ܣ�   ����������־��Ŀ
	// ������   
	//          CList<_EventLog_struct *, _EventLog_struct *> *list: 
	// ����ֵ: 
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
	// �������ƣ� OnResetLogData
	// ���ܣ�   ���ã��������־����
	// ������   
	// ����ֵ: 
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
