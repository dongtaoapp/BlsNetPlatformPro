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

	//清空日志信息
	void CBlsLogs::EmptyLogs()
	{
		BOOST_FOREACH(auto x, m_lstEventLog)
		{
			delete x;
		}
		m_lstEventLog.clear();
	}

	/*******************************************************************************/
	// 函数名称： OnResetScenarioLog
	// 功能：   重置脚本
	// 参数：   
	// 返回值: 
	void CBlsLogs::OnResetScenarioLog()
	{
		EmptyLogs();
		if( m_pUpdateLogInterface != NULL )
		{
			m_pUpdateLogInterface->OnResetLogData();
		}
	}

	/*******************************************************************************/
	// 函数名称： OnEventHandleLog
	// 功能：   事件日志
	// 参数：   
	//          const CString &strTime:       场景时间
	//          VirEventIrp *pVirEventIrp: 
	// 返回值: 
	void CBlsLogs::OnEventHandleLog(const std::string &strTime, irp::CVirEventIrp *pVirEventIrp)
	{
		const CEventLogUpdate_Singleton &cLogUpdate = CEventLogUpdate_Singleton::get_const_instance();
		//更新事件日志
		_EventLog_struct *pNewLog  = cLogUpdate.getIrpLogMessage(strTime, pVirEventIrp);
		if( pNewLog != NULL )
		{
			m_lstEventLog.push_back( pNewLog );
			//更新
			if( m_pUpdateLogInterface != NULL )
			{
                m_pUpdateLogInterface->OnUpdateEventLogData( pNewLog, false );
			}
		}
	}

	/*******************************************************************************/
	// 函数名称： StartLinkLogShowInterface
	// 功能： 初始化连接日志显示接口
	// 参数： 
	//        IUpdateLogDataInterface *pUpdateLogInterface:      
	// 返回值:  
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
			//显示所有的日志信息
			pUpdateLogInterface->OnUpdateEventLogData( &m_lstEventLog );
		}
	}

	/*******************************************************************************/
	// 函数名称： UnLinkLogShowInterface
	// 功能： 断开连接日志显示接口
	// 参数： 
	//        IUpdateLogDataInterface *pUpdateLogInterface:      
	// 返回值:  
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
