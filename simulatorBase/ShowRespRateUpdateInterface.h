#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\CommonGlobal.h"
#include "..\common\iupdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ����������Ϣ��ʾ�ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2008/8/5
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowRespRateUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowRespRateUpdateInterface(void);
		virtual ~CShowRespRateUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		//��ʾ��������
		virtual void ShowRespRate(eRespMode  enumMode, int nRate) = 0;
		//��ʾ�������������ķ�Χ����
		virtual void ShowRespRateRange(int nMinRate, int nMaxRate) = 0;
		//�Խ���ʾ��֪ͨ
		virtual void doLinkRespRateUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkRespRateUpdateShow() { };
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		/*******************************************************************************/
		// �������ƣ� OnShowRespRate
		// ���ܣ� ��ʾ��������
		// ������ int nRate:                ������������λ����/���ӣ�
		// ����ֵ:  
		void OnShowRespRate(eRespMode  enumMode, int nRate);
		/*******************************************************************************/
		// �������ƣ� OnShowRespRateRange
		// ���ܣ� ��ʾ�������������ķ�Χ����
		// ������ int nMinRate:              ������С������������λ����/���ӣ� 
		//        int nMaxRate:              ������������������λ����/���ӣ� 
		// ����ֵ:  
		void OnShowRespRateRange(int nMinRate, int nMaxRate);
	};

}}}
