#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"


namespace jysoft { namespace simulator { namespace base {

    class SIMULATORBASESHARED_EXPORT CShowPaceUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowPaceUpdateInterface(void);
		virtual ~CShowPaceUpdateInterface(void);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		//��ʾ������
        virtual void ShowPaceset(bool bEnablePace, short sElectric) = 0;
		//�Խ���ʾ��֪ͨ
		virtual void doLinkPacesetUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkPacesetUpdateShow() { };
	public:
		/*******************************************************************************/
		// �������ƣ� OnShowPaceset
		// ���ܣ�   �����𲫵�����
		// ������   
        //          bool bEnablePace:  �Ƿ�����
		//          short sElectric:   ������
		// ����ֵ:
        void OnShowPaceset(bool bEnablePace, short sElectric);
	};

}}}
