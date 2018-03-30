#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\IUpdateshowVir.h"
#include "..\Common\CommonGlobal.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �¼���ʾ�ӿ�
	�����ˣ�	 las
	����ʱ�䣺   2009/6/18
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowEventSignUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowEventSignUpdateInterface(void);
		virtual ~CShowEventSignUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		// ����µı�־
		void OnAddNewEventSign(eEventSign eSign);
		// �Ƴ���־
		void OnRemoveEventSign(eEventSign eSign);
		//Ĭ������
		void OnDefaultHandle(void);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		// ��������¼�
		void OnSimulateDefibrTriggerEventUpdateShow( short sEnergy = -1 );
		// ��������¼���1:������,2:��ɶ���,3:�ҹɶ���,4:�ұ��Ŷ���,5:�ұ��㶯��,6:����Ŷ���,7:����㶯��,8:�����N����,9:���㱳����, 10:�����N����, 11:���㱳������
		void OnSimulatePulseCheckTriggerEventUpdateShow( short sPosition = 1 );
		// CPR����¼�
		void OnSimulateCPRTriggerEventUpdateShow();
		// ������¼�
		void OnSimulatePaceTriggerEventUpdateShow( short sHeartRate );
		// ���ܲ���¼�
		void OnSimulateIntubateTriggerEventUpdateShow( short sPosition );
	protected:
		// ����µı�־
		virtual void AddNewEventSign(eEventSign eSign) = 0;
		// �Ƴ���־
		virtual void RemoveEventSign(eEventSign eSign) = 0;
		//Ĭ������
		virtual void DefaultHandle(void) = 0;
		// ��������¼�
		virtual void SimulateDefibrTriggerEventUpdateShow( short sEnergy = -1 ) = 0;
		// ��������¼���1:��������
		virtual void SimulatePulseCheckTriggerEventUpdateShow( short sPosition ) = 0;
		// CPR����¼�
		virtual void SimulateCPRTriggerEventUpdateShow() = 0;
		// ������¼�
		virtual void SimulatePaceTriggerEventUpdateShow( short sHeartRate ) = 0;
		// ���ܲ���¼�
		virtual void SimulateIntubateTriggerEventUpdateShow( short sPosition ) = 0;
		//�Խ���ʾ��֪ͨ
		virtual void doLinkEventSignUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkEventSignUpdateShow() { };
	};

}}}
