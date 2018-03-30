#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\IUpdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �޴�Ѫѹ��Ϣ��ʾ�ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2016/5/4
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowNIBPUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowNIBPUpdateInterface(void);
		virtual ~CShowNIBPUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		//��ʾ�޴�Ѫѹ����ֵ
		virtual void ShowNIBPValue(int nShrinkValue, int nStretchValue) = 0;
		virtual void ShowNIBPSoundValue(int nNIBPSoundValue) = 0;
		//-----------------------------------------------------------------------------------
		//�Խ���ʾ��֪ͨ
		virtual void doLinkNIBPUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkNIBPUpdateShow() { };
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		/*******************************************************************************/
		// �������ƣ� OnShowNIBPValue
		// ���ܣ� ��ʾ�޴�Ѫѹ����ֵ
		// ������ int nShrinkValue:              ����ѹ
		//        int nStretchValue:             ����ѹ
		// ����ֵ:  
		void OnShowNIBPValue(int nShrinkValue, int nStretchValue);
		/*******************************************************************************/
		// �������ƣ� OnShowKorotkoffVolum
		// ���ܣ� ��ʾ�޴�Ѫѹ�������ֵ
		// ������ int nNIBPSoundValue:              �޴�Ѫѹ�������ֵ
		// ����ֵ:  
		void OnShowKorotkoffVolume(int nNIBPSoundValue);
	};

}}}
