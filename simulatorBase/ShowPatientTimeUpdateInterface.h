#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��ǰ�ű����еĲ���ʱ����ʾ�ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2016/6/19
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowPatientTimeUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowPatientTimeUpdateInterface(void);
		virtual ~CShowPatientTimeUpdateInterface(void);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		/*******************************************************************************/
		// �������ƣ� ShowPatientTimeUpdate
		// ���ܣ� ��ʾ��ǰ���˵�ʱ��
		// ������ 
		//        long  lPatientTime��    ����ʱ��
		// ����ֵ:  
		virtual void ShowPatientTimeUpdate(long  lPatientTime) = 0;
		//�Խ���ʾ��֪ͨ
		virtual void doLinkPatientTimeUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkPatientTimeUpdateShow() { };
	public:
		//��ʾ��ǰ���˵�ʱ��
		void OnShowPatientTimeUpdate(long  lPatientTime);
		//�����ǰ���˵�ʱ��
		virtual void OnClearShowPateintTimeUpdate() = 0;
	};

}}}
