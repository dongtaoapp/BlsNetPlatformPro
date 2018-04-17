#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include ".\Blslogs.h"
#include ".\EventLogUpdate_Singleton.h"

#include "..\Common\EncodeConv.h"

#include "..\SimulatorBase\VirEventIrp.h"


namespace jysoft{  namespace log 
{
	CBlsLogs::CBlsLogs()
	{
		m_pUpdateLogInterface  = NULL;
	}

	CBlsLogs::~CBlsLogs(void)
	{
		EmptyLogs();
	}

	bool CBlsLogs::isKindOf(const std::string &className)
	{
		if (className == "CBlsLogs")
		{
			return true;
		}
		return COpLogInterface::isKindOf(className);
	}

	//�����־��Ϣ
	void CBlsLogs::EmptyLogs()
	{
		BOOST_FOREACH(auto x, m_lstEventLog)
		{
			delete x;
		}
		m_lstEventLog.clear();
	}

	/*******************************************************************************/
	// �������ƣ� OnResetScenarioLog
	// ���ܣ�   ���ýű�
	// ������   
	// ����ֵ: 
	void CBlsLogs::OnResetScenarioLog()
	{
		EmptyLogs();
		if( m_pUpdateLogInterface != NULL )
		{
			m_pUpdateLogInterface->OnResetLogData();
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnEventHandleLog
	// ���ܣ�   �¼���־
	// ������   
	//          const CString &strTime:       ����ʱ��
	//          VirEventIrp *pVirEventIrp: 
	// ����ֵ: 
	void CBlsLogs::OnEventHandleLog(const std::string &strTime, irp::CVirEventIrp *pVirEventIrp)
	{
		const CEventLogUpdate_Singleton &cLogUpdate = CEventLogUpdate_Singleton::get_const_instance();
		//�����¼���־
		_EventLog_struct *pNewLog  = cLogUpdate.getIrpLogMessage(strTime, pVirEventIrp);
		if( pNewLog != NULL )
		{
			m_lstEventLog.push_back( pNewLog );
			//����
			if( m_pUpdateLogInterface != NULL )
			{
                m_pUpdateLogInterface->OnUpdateEventLogData( pNewLog, false );
			}
		}
	}

	/*******************************************************************************/
	// �������ƣ� StartLinkLogShowInterface
	// ���ܣ� ��ʼ��������־��ʾ�ӿ�
	// ������ 
	//        IUpdateLogDataInterface *pUpdateLogInterface:      
	// ����ֵ:  
	void CBlsLogs::StartLinkLogShowInterface(IUpdateLogDataInterface *pUpdateLogInterface)
	{
		if( m_pUpdateLogInterface == NULL )
		{
			m_pUpdateLogInterface  = pUpdateLogInterface;
		}
		else
		{
			m_pUpdateLogInterface->SetNextInterfacePtr( pUpdateLogInterface );
		}
		if( pUpdateLogInterface != NULL )
		{
			pUpdateLogInterface->LinkUpdateShow();
			//��ʾ���е���־��Ϣ
			pUpdateLogInterface->OnUpdateEventLogData( &m_lstEventLog );
		}
	}

	/*******************************************************************************/
	// �������ƣ� UnLinkLogShowInterface
	// ���ܣ� �Ͽ�������־��ʾ�ӿ�
	// ������ 
	//        IUpdateLogDataInterface *pUpdateLogInterface:      
	// ����ֵ:  
	void CBlsLogs::UnLinkLogShowInterface(IUpdateLogDataInterface *pUpdateLogInterface)
	{
		if( pUpdateLogInterface != NULL )
		{
			m_pUpdateLogInterface = (IUpdateLogDataInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pUpdateLogInterface, pUpdateLogInterface);
			pUpdateLogInterface->UnLinkUpdateShow();
		}
	}

	void CBlsLogs::DeleteLog( _EventLog_struct *pLog )
	{
		std::list<_EventLog_struct *>::iterator pos;
		pos = m_lstEventLog.begin();
		while( pos != m_lstEventLog.end() )
		{
			_EventLog_struct* pStruct = *pos;
			if(pStruct == pLog)
			{
				m_lstEventLog.erase(pos);
				delete pStruct;
				break;
			}
			++pos;
		}
	}
}}
