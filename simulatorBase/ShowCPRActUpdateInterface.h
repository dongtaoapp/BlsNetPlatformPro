#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"

namespace jysoft{  namespace cpr {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     CPR����ϸ�ڶ�����ʾ�ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/25
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowCPRActUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowCPRActUpdateInterface(void);
		virtual ~CShowCPRActUpdateInterface(void);
	public://�ӿں�������
		virtual bool isKindOf(const std::string &className);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	protected:
		//�Խ���ʾ��֪ͨ
		virtual void doLinkCPRDetailActUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkCPRDetailActUpdateShow() { };
		virtual void RaiseJowAct(bool bLookUp) = 0;
		//�˹�������ʼ\����(TRUE:��ʼ��FALSE:����)
		virtual void BreathStateAct(bool bState) = 0;
		//��ѹ��ʼ\����(TRUE:��ʼ��FALSE:����)
		virtual void PressureStateAct(bool bState) = 0;
		//������ѭ����CPR
		virtual void FiveCycleCompleteAct() = 0;
		//����CPR����
		virtual void FinishCPROperator(bool bSecceed) = 0;
	public:
		//��ͷ��ƽ��
		void OnRaiseJowAct(bool bLookUp);
		//�˹�������ʼ\����(TRUE:��ʼ��FALSE:����)
		void OnBreathStateAct(bool bState);
		//��ѹ��ʼ\����(TRUE:��ʼ��FALSE:����)
		void OnPressureStateAct(bool bState);
		//������ѭ����CPR
		virtual void OnFiveCycleCompleteAct();
		//����CPR����
		void OnFinishCPROperator(bool bSecceed);
	};
}}
