#pragma once
#include <string>
#include ".\VirEventIrp.h"
#include ".\SimulateBaseGlobal.h"

#include "..\common\OpInterfaceVir.h"
#include "..\common\CommonGlobal.h"

namespace jysoft{  namespace log {

    class SIMULATORBASESHARED_EXPORT COpLogInterface :  public COpInterfaceVir
	{
	public:
		COpLogInterface(void);
		virtual ~COpLogInterface(void);
	protected:
        unsigned long                         m_uLogTime;                 //日志时间
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		/*******************************************************************************/
		// 函数名称： OnResetScenarioLog
		// 功能：   重置脚本
		// 参数：   
		// 返回值: 
		virtual void OnResetScenarioLog() = 0;
		/*******************************************************************************/
		// 函数名称： OnEventHandleLog
		// 功能：   时间日志
		// 参数：   
		//          const CString &strTime:       场景时间
		//          VirEventIrp *pVirEventIrp: 
		// 返回值: 
		virtual void OnEventHandleLog(const std::string &strTime, irp::CVirEventIrp *pVirEventIrp) = 0;
		//删除指定的log
		virtual void DeleteLog(_EventLog_struct *pLog) = 0;
	public:
		/*******************************************************************************/
		// 函数名称： GetScriptRunTime
		// 功能：   返回脚本运行时间（单位：秒)
		// 参数：   
		// 返回值: 
        inline unsigned long GetScriptRunTime() { return m_uLogTime; };
        inline void SetScriptRunTime(unsigned long uLogTime) { m_uLogTime = uLogTime; };
	};

}}
