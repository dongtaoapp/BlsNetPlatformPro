#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\IUpdateshowVir.h"

namespace jysoft { namespace simulator { namespace base {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��ѵ�ű�������ʾ�ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2009/6/19
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowScriptTrainNameUpdateInterface  : public IUpdateShowVir
	{
	public:
		CShowScriptTrainNameUpdateInterface(void);
		virtual ~CShowScriptTrainNameUpdateInterface(void);
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		/*******************************************************************************/
		// �������ƣ� ShowScriptTrainNameUpdate
		// ���ܣ� ��ʾ��ѵ�ű�����
		// ������ 
		//        const CString &strScriptName��    �ű�����
		// ����ֵ:  
		virtual void ShowScriptTrainNameUpdate(const std::string &strScriptName) = 0;
		//�Խ���ʾ��֪ͨ
		virtual void doLinkScriptNameUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkScriptNameUpdateShow() { };
	public:
		//��ʾ��ѵ�ű�����
		void OnShowScriptTrainNameUpdate(const std::string &strScriptName);
	};

}}}
