#pragma once
#include <list>
#include ".\simulatorbase_global.h"

#include "..\Common\CommonGlobal.h"
#include "..\common\iupdateshowvir.h"


namespace jysoft{  namespace log 
{
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     日志显示接口接口类
	创建人：	 lcm
	创建时间：   2017/2/12
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT IUpdateLogDataInterface : public IUpdateShowVir
	{
	public:
		IUpdateLogDataInterface(void);
		~IUpdateLogDataInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	protected:
		//对接显示后通知
		virtual void doLinkLogDataUpdateShow() { };
		//断开显示后通知
		virtual void cutLinkLogDataUpdateShow() { };
	public:
		/*******************************************************************************/
		// 函数名称： OnUpdateEventLogData
		// 功能：   更新新的日志条目
		// 参数：   
		//      _EventLog_struct *pEventLog: 
		//      BOOL bSafeShow：                是否为线程安全的模式添加显示
		// 返回值: 
		void OnUpdateEventLogData(_EventLog_struct *pEventLog, bool bSafeShow = true);
		/*******************************************************************************/
		// 函数名称： OnUpdateEventLogData
		// 功能：   更新所有日志条目
		// 参数：   
		//          std::list<_EventLog_struct *> *list: 
		// 返回值: 
		void OnUpdateEventLogData(std::list<_EventLog_struct *> *plstEentLogs);
		/*******************************************************************************/
		// 函数名称： OnResetLogData
		// 功能：   重置（清除）日志数据
		// 参数：   
		// 返回值: 
		void OnResetLogData();
	protected:
		/*******************************************************************************/
		// 函数名称： UpdateEventLogData
		// 功能：   更新所有日志条目
		// 参数：   
		//      CList<_EventLog_struct *, _EventLog_struct *> *list: 
		// 返回值: 
		virtual void UpdateEventLogData(std::list<_EventLog_struct *> *plstEentLogs) = 0;
		/*******************************************************************************/
		// 函数名称： UpdateEventLogData
		// 功能：   更新新的日志条目
		// 参数：   
		//      _EventLog_struct *pEventLog:
		//      bool bSafeShow：                是否为线程安全的模式添加显示
		// 返回值: 
		virtual void UpdateEventLogData( _EventLog_struct *pEventLog, bool bSafeShow  ) = 0;
		/*******************************************************************************/
		// 函数名称： ResetLogData
		// 功能：   重置（清除）日志数据
		// 参数：   
		// 返回值: 
		virtual void ResetLogData() = 0;
	};

}}
