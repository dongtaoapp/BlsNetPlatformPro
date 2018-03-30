#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\IUpdateshowVir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��ǰ�ű����еĳ�������ʱ����ʾ�ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2009/6/19
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CShowFrameTimeUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowFrameTimeUpdateInterface(void);
		virtual ~CShowFrameTimeUpdateInterface(void);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		/*******************************************************************************/
		// �������ƣ� ShowFrameTimeUpdate
		// ���ܣ� ��ʾ��ǰ���г�����ʱ��
		// ������ 
		//        long  lFrameTime��    ��������ʱ��
		// ����ֵ:  
		virtual void ShowFrameTimeUpdate(long  lFrameTime) = 0;
		//�Խ���ʾ��֪ͨ
		virtual void doLinkFrameTimeUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkFrameTimeUpdateShow() { };
	public:
		//��ʾ��ǰ���г�����ʱ��
		void OnShowFrameTimeUpdate(long  lFrameTime);
	};
}}}
