#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ����CO2Ũ����Ϣ��ʾ�ӿ�
	�����ˣ�	 hjg
	����ʱ�䣺   2008/8/6
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowEtCO2UpdateInterface : public IUpdateShowVir
	{
	public:
		CShowEtCO2UpdateInterface(void);
		virtual ~CShowEtCO2UpdateInterface(void);
	public:
		bool isKindOf(const std::string &className);
	protected:
		//��ʾ����CO2Ũ��
		virtual void ShowEtCO2Value(int nCO2Value) = 0;
		//��ʾ����CO2Ũ�������ķ�Χ����
		virtual void ShowEtCO2Range(int nMinCO2Value, int nMaxCO2Value) = 0;
		//�Խ���ʾ��֪ͨ
		virtual void doLinkEtCO2UpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkEtCO2UpdateShow() { };
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		/*******************************************************************************/
		// �������ƣ� OnShowEtCO2Value
		// ���ܣ� ��ʾ����CO2Ũ��
		// ������ int nCO2Value:                CO2Ũ�ȣ���λ���ٷְ٣�
		// ����ֵ:  
		void OnShowEtCO2Value(int nCO2Value);
		/*******************************************************************************/
		// �������ƣ� OnShowEtCO2Range
		// ���ܣ� ��ʾ����CO2Ũ�������ķ�Χ����
		// ������ int nMinCO2Value:              ������СCO2Ũ�ȣ���λ���ٷְ٣� 
		//        int nMaxCO2Value:              �������CO2Ũ�ȣ���λ���ٷְ٣� 
		// ����ֵ:  
		void OnShowEtCO2Range(int nMinCO2Value, int nMaxCO2Value);
	};

}}}
