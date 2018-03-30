#pragma once
#include ".\simulatorbase_global.h"

#include "..\common\iupdateshowvir.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �ĵ�ͼ��Ϣ��ʾ�ӿڣ������������ơ����ʴ���������������Χ����Ϣ
	�����ˣ�	 hjg
	����ʱ�䣺   2016/8/5
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CShowECGUpdateInterface : public IUpdateShowVir
	{
	public:
		CShowECGUpdateInterface(void);
		virtual ~CShowECGUpdateInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		//��ʾ�ĵ�ͼ����
        virtual void ShowECGName(const std::string & strRhythm, const std::string &strExtrasyst, int nHR, bool bEMD) = 0;
		// ���ܣ� ��������޸��ĵ�ͼ����
        virtual void ShowECGNameInDefib(const std::string &strRhythm, const std::string &strExtrasyst, int nHR, bool bEMD, int nMillDelayTime) = 0;
		//��ʾ��ȷ���ʵķ�Χ
		virtual void ShowECGRateRange(int nMinRate, int nMaxRate) = 0;
		//��ʾ��ǰ������ֵ
		virtual void ShowECGRate(int nHR) = 0;
		//��������޸ĵ�ǰ������ֵ
		virtual void ShowECGRateInDefib(int nHR, int nMillDelayTime) = 0;
		//-------------------------------------------------------------------------------
		//�Խ���ʾ��֪ͨ
		virtual void doLinkECGUpdateShow() { };
		//�Ͽ���ʾ��֪ͨ
		virtual void cutLinkECGUpdateShow() { };
	public:
		virtual void UnLinkUpdateShow();
		virtual void LinkUpdateShow();
	public:
		/*******************************************************************************/
		// �������ƣ� OnShowECGName
		// ���ܣ� ��ʾ�ĵ�ͼ����
		// ������ 
		//        CString strRhythm:          ������������
		//        CString strExtrasyst:       �粫    
		//        CString  strHR:             ����
		//        BOOL bEMD: 
		//ע��  ����������Ϊ�������ƣ���ʾʱ��ת��Ϊ��ʾ����
		// ����ֵ:  
        void OnShowECGName(const std::string &strRhythm, const std::string &strExtrasyst, int nHR, bool bEMD);
		/*******************************************************************************/
		// �������ƣ� OnShowECGNameInDefib
		// ���ܣ� ��������޸��ĵ�ͼ����
		// ������ 
		//        CString strRhythm:          ������������
		//        CString strExtrasyst:       �粫    
		//        CString  strHR:             ����
		//        BOOL bEMD: 
		//ע��  ����������Ϊ�������ƣ���ʾʱ��ת��Ϊ��ʾ����
		// ����ֵ:  
        void OnShowECGNameInDefib(const std::string &strRhythm, const std::string &strExtrasyst, int nHR, bool bEMD, int nMillDelayTime);
		/*******************************************************************************/
		// �������ƣ� OnShowECGRateRange
		// ���ܣ� ��ʾ��ȷ���ʵķ�Χ
		// ������ int nMinRate:               ������С���ʣ���λ����/���ӣ�
		//        int nMaxRate:               ����������ʣ���λ����/���ӣ�  
		// ����ֵ:  
		void OnShowECGRateRange(int nMinRate, int nMaxRate);
		/*******************************************************************************/
		// �������ƣ� OnShowECGRate
		// ���ܣ� ��ʾ��ǰ������ֵ
		// ������ int nHR:                    ����ֵ����λ����/���ӣ�
		// ����ֵ:  
		void OnShowECGRate(int nHR);
		/*******************************************************************************/
		// �������ƣ� OnShowECGRate
		// ���ܣ� ��������޸ĵ�ǰ������ֵ
		// ������ int nHR:                    ����ֵ����λ����/���ӣ�
		// ����ֵ: 
		void OnShowECGRateInDefib(int nHR, int nMillDelayTime);
	};

}}}
