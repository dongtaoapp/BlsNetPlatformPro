#pragma once
#include ".\simulatorbase_global.h"
#include ".\ShowEventSignUpdateInterface.h"

#include "..\Common\VirtualIrp.h"

namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �¼�Irp����
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/8
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CVirEventIrp : public CVirtualIrp
	{
	public:
		CVirEventIrp(void);
		virtual ~CVirEventIrp(void);
	public:
		virtual _IrpType Get_eIrpType() = 0;
	public:
		virtual bool isKindOf(const std::string &strClass);
		//�����¼���־
		virtual eEventSign Get_EventSign() { return ES_Normal; };
		/*******************************************************************************/
		// �������ƣ� doPackageIrp
		// ���ܣ�  ���Irp������
		// ������ 
		// ����ֵ: 
		virtual std::string doPackageIrp() = 0;
		/*******************************************************************************/
		// �������ƣ� UpdateEventSignShow
		// ���ܣ�  ��ʾ�¼�����
		// ������ 
		// ����ֵ: 
		virtual void UpdateEventSignShow(simulator::base::CShowEventSignUpdateInterface  *pInterface ) { };
		/*******************************************************************************/
		// �������ƣ� getIrpLogMessage
		// ���ܣ�  ����Irp��������־��Ϣ
		// ������ 
		//        /*out*/_EventLog_struct *pLogStruct: 
		// ����ֵ: 
		virtual bool getIrpLogMessage(/*out*/_EventLog_struct *pLogStruct) { return false; };
	};

}}
