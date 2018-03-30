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
        unsigned long                         m_uLogTime;                 //��־ʱ��
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		/*******************************************************************************/
		// �������ƣ� OnResetScenarioLog
		// ���ܣ�   ���ýű�
		// ������   
		// ����ֵ: 
		virtual void OnResetScenarioLog() = 0;
		/*******************************************************************************/
		// �������ƣ� OnEventHandleLog
		// ���ܣ�   ʱ����־
		// ������   
		//          const CString &strTime:       ����ʱ��
		//          VirEventIrp *pVirEventIrp: 
		// ����ֵ: 
		virtual void OnEventHandleLog(const std::string &strTime, irp::CVirEventIrp *pVirEventIrp) = 0;
		//ɾ��ָ����log
		virtual void DeleteLog(_EventLog_struct *pLog) = 0;
	public:
		/*******************************************************************************/
		// �������ƣ� GetScriptRunTime
		// ���ܣ�   ���ؽű�����ʱ�䣨��λ����)
		// ������   
		// ����ֵ: 
        inline unsigned long GetScriptRunTime() { return m_uLogTime; };
        inline void SetScriptRunTime(unsigned long uLogTime) { m_uLogTime = uLogTime; };
	};

}}
