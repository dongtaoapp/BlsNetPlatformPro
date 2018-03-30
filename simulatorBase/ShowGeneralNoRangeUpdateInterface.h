#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

    class SIMULATORBASESHARED_EXPORT CShowGeneralNoRangeUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowGeneralNoRangeUpdateInterface(void);
		virtual ~CShowGeneralNoRangeUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	protected:
		//��ʾ����ֵ
		virtual void ShowPhystValue(float fPhystValue) = 0;
		//�Խ���ʾ��֪ͨ
		virtual void doLinkGeneralNoRangeUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkGeneralNoRangeUpdateShow() { };
	public:
		/*******************************************************************************/
		// �������ƣ� OnShowPhystValue
		// ���ܣ� ��ʾ����ֵ
		// ������ float fPhystValue:              ֵ
		// ����ֵ:  
		void OnShowPhystValue(float fPhystValue);
	};

}}}
