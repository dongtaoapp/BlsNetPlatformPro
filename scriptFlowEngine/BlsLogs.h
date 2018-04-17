#pragma once
#include <list>
#include ".\scriptflowengine_global.h"

#include "..\common\CommonGlobal.h"

#include "..\SimulatorBase\OpLogInterface.h"
#include "..\SimulatorBase\IUpdateLogDataInterface.h"

namespace jysoft{  namespace log 
{
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ACLS��־������
	�����ˣ�	 hjg
	����ʱ�䣺   2017/3/27
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
	public: //�ӿ�COpLogInterface��������
		/*******************************************************************************/
		// �������ƣ� OnResetScenarioLog
		// ���ܣ�   ���ýű�
		// ������   
		// ����ֵ: 
		virtual void OnResetScenarioLog();
		/*******************************************************************************/
		// �������ƣ� OnEventHandleLog
		// ���ܣ�   ʱ����־
		// ������   
		//          const CString &strTime:       ����ʱ��
		//          VirEventIrp *pVirEventIrp: 
		// ����ֵ: 
		virtual void OnEventHandleLog(const std::string &strTime, irp::CVirEventIrp *pVirEventIrp);
		//ɾ��ָ����log
		virtual void DeleteLog(_EventLog_struct *pLog);
	public:
		/*******************************************************************************/
		// �������ƣ� StartLinkLogShowInterface
		// ���ܣ� ��ʼ��������־��ʾ�ӿ�
		// ������ 
		//        IUpdateLogDataInterface *pUpdateLogInterface:      
		// ����ֵ:  
		void StartLinkLogShowInterface(IUpdateLogDataInterface *pUpdateLogInterface);
		/*******************************************************************************/
		// �������ƣ� UnLinkLogShowInterface
		// ���ܣ� �Ͽ�������־��ʾ�ӿ�
		// ������ 
		//        IUpdateLogDataInterface *pUpdateLogInterface:      
		// ����ֵ:  
		void UnLinkLogShowInterface(IUpdateLogDataInterface *pUpdateLogInterface);
	private:
		//�����־��Ϣ
		void EmptyLogs();
	};
}}
