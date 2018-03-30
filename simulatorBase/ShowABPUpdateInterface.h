#pragma once
#include <string>
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �д�Ѫѹ��Ϣ��ʾ�ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2016/8/5
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CShowABPUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowABPUpdateInterface(void);
		virtual ~CShowABPUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	protected:
		//��ʾ�д�Ѫѹ����ֵ
		virtual void ShowABPValue(int nShrinkValue, int nStretchValue) = 0;
		//�Խ���ʾ��֪ͨ
		virtual void doLinkABPUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkABPUpdateShow() { };
	public:
		/*******************************************************************************/
		// �������ƣ� OnShowABPValue
		// ���ܣ� ��ʾ�д�Ѫѹ����ֵ
		// ������ int nShrinkValue:              ����ѹ
		//        int nStretchValue:             ����ѹ
		// ����ֵ:  
		void OnShowABPValue(int nShrinkValue, int nStretchValue);
		void OnShowABPValue(const std::string &strABP);
	public:
		//�����д�Ѫѹ��nShrink������ѹ��nStretch������ѹ
		static bool ParseABPToShrinkAndnStretch(const std::string &strABP, int &nShrink, int &nStretch);
	};

}}}
