#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\IUpdateshowVir.h"

namespace jysoft { namespace simulator { namespace base {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��ǰ�ű����еĳ���������ʾ�ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2016/6/19
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowFrameNameUpdateInterface  : public IUpdateShowVir
	{
	public:
		CShowFrameNameUpdateInterface(void);
		virtual ~CShowFrameNameUpdateInterface(void);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		/*******************************************************************************/
		// �������ƣ� ShowFrameNameUpdate
		// ���ܣ� ��ʾ��ǰ���г���������
		// ������ unsigned long dwFrameId: ������ʶ��
		// ����ֵ:  
		virtual void ShowFrameNameUpdate(unsigned long dwFrameId) = 0;
		//�Խ���ʾ��֪ͨ
		virtual void doLinkFrameNameUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkFrameNameUpdateShow() { };
	public:
		//��ʾ��ǰ���г���������
		void OnShowFrameNameUpdate(unsigned long dwFrameId);
	};

}}}
