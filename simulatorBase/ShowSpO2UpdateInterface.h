#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     Ѫ����Ϣ��ʾ�ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2008/8/5
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowSpO2UpdateInterface : public IUpdateShowVir
	{
	public:
		CShowSpO2UpdateInterface(void);
		virtual ~CShowSpO2UpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		//��ʾѪ������ֵ
		virtual void ShowSpO2Value(int nSpO2Value) = 0;
		//��ʾѪ�������ķ�Χ����
		virtual void ShowSpO2Range(int nMinValue, int nMaxValue) = 0;
		//�Խ���ʾ��֪ͨ
		virtual void doLinkSpO2UpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkSpO2UpdateShow() { };
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		/*******************************************************************************/
		// �������ƣ� OnShowSpO2Value
		// ���ܣ� ��ʾѪ������ֵ
		// ������ int nSpO2Value:              Ѫ��ֵ����λ���ٷֱȣ� 
		// ����ֵ:  
		void OnShowSpO2Value(int nSpO2Value);
		/*******************************************************************************/
		// �������ƣ� OnShowSpO2Range
		// ���ܣ� ��ʾѪ�������ķ�Χ����
		// ������ int nMinValue:              ������СѪ��ֵ����λ���ٷֱȣ� 
		//        int nMaxValue:              �������Ѫ��ֵ����λ���ٷֱȣ� 
		// ����ֵ:  
		void OnShowSpO2Range(int nMinValue, int nMaxValue);
	};
}}}
