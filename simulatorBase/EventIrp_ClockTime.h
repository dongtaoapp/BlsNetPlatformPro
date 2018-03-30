#pragma once
#include ".\simulatorbase_global.h"
#include ".\VirEventIrp.h"

namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ʱ���¼�Irp
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/8
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CEventIrp_ClockTime : public CVirEventIrp
	{
	public:
		CEventIrp_ClockTime(void);
		virtual ~CEventIrp_ClockTime(void);
	public:
		virtual _IrpType Get_eIrpType() { return eClock_Event; };
		virtual bool isKindOf(const std::string &strClass);
	public:
		inline short  GetValue_ClockEvent() { return m_sClockNum; };
		inline void   SetValue_ClockEvent(short sValue) { m_sClockNum = sValue; };
	protected:
		short        m_sClockNum;    //ʱ����ֵ
	public:
		/*******************************************************************************/
		// �������ƣ� doPackageIrp
		// ���ܣ�  ���Irp������
		// ������ 
		// ����ֵ: 
		virtual std::string doPackageIrp() { return ""; };
	public:
		/*******************************************************************************/
		// �������ƣ� CreateEvent_ClockIrp
		// ���ܣ� ����ʱ���¼�Irp��
		// ������ short sSecond:       
		// ����ֵ:  
		static CEventIrp_ClockTime * CreateEvent_ClockIrp(short sSecond = 1);
	};

}}
