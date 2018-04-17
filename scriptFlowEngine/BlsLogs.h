#pragma once
#include <list>
#include ".\scriptflowengine_global.h"

#include "..\common\CommonGlobal.h"

#include "..\SimulatorBase\OpLogInterface.h"
#include "..\SimulatorBase\IUpdateLogDataInterface.h"

namespace jysoft{  namespace log 
{
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     ACLS日志存贮类
	创建人：	 hjg
	创建时间：   2017/3/27
	//-----------------------------------------------------------------------------------------------------------------*/
    class SCRIPTFLOWENGINESHARED_EXPORT CBlsLogs : public COpLogInterface
	{
	public:
		CBlsLogs();
		virtual ~CBlsLogs(void);
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		std::list<_EventLog_struct *>            m_lstEventLog;
		IUpdateLogDataInterface *                m_pUpdateLogInterface;
	public: //接口COpLogInterface函数重载
		/*******************************************************************************/
		// 函数名称： OnResetScenarioLog
		// 功能：   重置脚本
		// 参数：   
		// 返回值: 
		virtual void OnResetScenarioLog();
		/*******************************************************************************/
		// 函数名称： OnEventHandleLog
		// 功能：   时间日志
		// 参数：   
		//          const CString &strTime:       场景时间
		//          VirEventIrp *pVirEventIrp: 
		// 返回值: 
		virtual void OnEventHandleLog(const std::string &strTime, irp::CVirEventIrp *pVirEventIrp);
		//删除指定的log
		virtual void DeleteLog(_EventLog_struct *pLog);
	public:
		/*******************************************************************************/
		// 函数名称： StartLinkLogShowInterface
		// 功能： 初始化连接日志显示接口
		// 参数： 
		//        IUpdateLogDataInterface *pUpdateLogInterface:      
		// 返回值:  
		void StartLinkLogShowInterface(IUpdateLogDataInterface *pUpdateLogInterface);
		/*******************************************************************************/
		// 函数名称： UnLinkLogShowInterface
		// 功能： 断开连接日志显示接口
		// 参数： 
		//        IUpdateLogDataInterface *pUpdateLogInterface:      
		// 返回值:  
		void UnLinkLogShowInterface(IUpdateLogDataInterface *pUpdateLogInterface);
	private:
		//清空日志信息
		void EmptyLogs();
	};
}}
