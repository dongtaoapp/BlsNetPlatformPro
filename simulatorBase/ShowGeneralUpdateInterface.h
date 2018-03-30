#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"


namespace jysoft { namespace simulator { namespace base {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��Ϣ��ʾ�ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2016/8/21
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CShowGeneralUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowGeneralUpdateInterface(void);
		virtual ~CShowGeneralUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	protected:
		//��ʾ����ֵ
		virtual void ShowPhystValue(float fValue) = 0;
		//��ʾ�����ķ�Χ����
		virtual void ShowPhystRange(float fMinValue, float fMaxValue) = 0;
		//�Խ���ʾ��֪ͨ
		virtual void doLinkGeneralUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkGeneralUpdateShow() { };
	public:
		/*******************************************************************************/
		// �������ƣ� OnShowPhystValue
		// ���ܣ� ��ʾ����ֵ
		// ������ float nPhystValue:              ֵ
		// ����ֵ:  
		void OnShowPhystValue(float nPhystValue);
		/*******************************************************************************/
		// �������ƣ� OnShowPhystRange
		// ���ܣ� ��ʾ�����ķ�Χ����
		// ������ float fMinValue:              ������Сֵ
		//        float fMaxValue:              �������ֵ
		// ����ֵ:  
		void OnShowPhystRange(float fMinValue, float fMaxValue);
	};

}}}
