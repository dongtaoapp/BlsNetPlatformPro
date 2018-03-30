#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"


namespace jysoft { namespace simulator { namespace base {

    class SIMULATORBASESHARED_EXPORT CShowTempUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowTempUpdateInterface(void);
		virtual ~CShowTempUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	protected:
		//��ʾ����ֵ
		virtual void ShowTempValue(float fValue) = 0;
		//��ʾ�����ķ�Χ����
		virtual void ShowTempRange(float fMinValue, float fMaxValue) = 0;
		//�Խ���ʾ��֪ͨ
		virtual void doLinkTempUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkTempUpdateShow() { };
	public:
		/*******************************************************************************/
		// �������ƣ� OnShowTempValue
		// ���ܣ� ��ʾ����ֵ
		// ������ int nSpO2Value:              ֵ
		// ����ֵ:  
		void OnShowTempValue(float fValue);
		/*******************************************************************************/
		// �������ƣ� OnShowTempRange
		// ���ܣ� ��ʾ�����ķ�Χ����
		// ������ float fMinValue:              ������Сֵ
		//        float fMaxValue:              �������ֵ
		// ����ֵ:  
		void OnShowTempRange(float fMinValue, float fMaxValue);
	};

}}}
