#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��ǰ�ű�����ʱ����ʾ�ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2009/6/19
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowScenarioRunTimeUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowScenarioRunTimeUpdateInterface(void);
		virtual ~CShowScenarioRunTimeUpdateInterface(void);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		/*******************************************************************************/
		// �������ƣ� ShowScenarioRunTimeUpdate
		// ���ܣ� ��ʾ��ǰ�ű�����ʱ��
		// ������ 
        //        uScenarioTime��    �ű�����ʱ��
		// ����ֵ:  
        virtual void ShowScenarioRunTimeUpdate(unsigned long  uScenarioTime) = 0;
		//�Խ���ʾ��֪ͨ
		virtual void doLinkScenarioRunTimeUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkScenarioRunTimeUpdateShow() { };
	public:
		//��ʾ��ǰ�ű�����ʱ��
        void OnShowScenarioRunTimeUpdate(unsigned long  uScenarioTime);
	};

}}}
