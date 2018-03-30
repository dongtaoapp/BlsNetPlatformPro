#pragma once
#include <list>
#include ".\simulatorbase_global.h"

#include "..\Common\CommonGlobal.h"
#include "..\common\iupdateshowvir.h"


namespace jysoft{  namespace log 
{
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��־��ʾ�ӿڽӿ���
	�����ˣ�	 lcm
	����ʱ�䣺   2017/2/12
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
		//�Խ���ʾ��֪ͨ
		virtual void doLinkLogDataUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkLogDataUpdateShow() { };
	public:
		/*******************************************************************************/
		// �������ƣ� OnUpdateEventLogData
		// ���ܣ�   �����µ���־��Ŀ
		// ������   
		//      _EventLog_struct *pEventLog: 
		//      BOOL bSafeShow��                �Ƿ�Ϊ�̰߳�ȫ��ģʽ�����ʾ
		// ����ֵ: 
		void OnUpdateEventLogData(_EventLog_struct *pEventLog, bool bSafeShow = true);
		/*******************************************************************************/
		// �������ƣ� OnUpdateEventLogData
		// ���ܣ�   ����������־��Ŀ
		// ������   
		//          std::list<_EventLog_struct *> *list: 
		// ����ֵ: 
		void OnUpdateEventLogData(std::list<_EventLog_struct *> *plstEentLogs);
		/*******************************************************************************/
		// �������ƣ� OnResetLogData
		// ���ܣ�   ���ã��������־����
		// ������   
		// ����ֵ: 
		void OnResetLogData();
	protected:
		/*******************************************************************************/
		// �������ƣ� UpdateEventLogData
		// ���ܣ�   ����������־��Ŀ
		// ������   
		//      CList<_EventLog_struct *, _EventLog_struct *> *list: 
		// ����ֵ: 
		virtual void UpdateEventLogData(std::list<_EventLog_struct *> *plstEentLogs) = 0;
		/*******************************************************************************/
		// �������ƣ� UpdateEventLogData
		// ���ܣ�   �����µ���־��Ŀ
		// ������   
		//      _EventLog_struct *pEventLog:
		//      bool bSafeShow��                �Ƿ�Ϊ�̰߳�ȫ��ģʽ�����ʾ
		// ����ֵ: 
		virtual void UpdateEventLogData( _EventLog_struct *pEventLog, bool bSafeShow  ) = 0;
		/*******************************************************************************/
		// �������ƣ� ResetLogData
		// ���ܣ�   ���ã��������־����
		// ������   
		// ����ֵ: 
		virtual void ResetLogData() = 0;
	};

}}
