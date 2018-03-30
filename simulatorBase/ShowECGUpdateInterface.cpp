#include ".\showecgupdateinterface.h"

namespace jysoft { namespace simulator { namespace base {

	CShowECGUpdateInterface::CShowECGUpdateInterface(void)
	{
	}

	CShowECGUpdateInterface::~CShowECGUpdateInterface(void)
	{
	}

	bool CShowECGUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowECGUpdateInterface" )
			return true;
		return IUpdateShowVir::isKindOf(className);
	}

	void CShowECGUpdateInterface::UnLinkUpdateShow()
	{
		//�Ͽ���ʾ��֪ͨ
		cutLinkECGUpdateShow();
	}

	void CShowECGUpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkECGUpdateShow();
	}

	/*******************************************************************************/
	// �������ƣ� OnShowECGName
	// ���ܣ� ��ʾ�ĵ�ͼ����
	// ������ CString  strQRS:            QRS����
	//        CString strRhythm:          ������������
	//        CString strExtrasyst:       �粫    
	//        int nHR:             ����
	//        BOOL bEMD: 
	//ע��  ����������Ϊ�������ƣ���ʾʱ��ת��Ϊ��ʾ����
	// ����ֵ:  
    void CShowECGUpdateInterface::OnShowECGName(const std::string &strRhythm, const std::string &strExtrasyst, int nHR, bool bEMD)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowECGUpdateInterface" ) )
			{
				CShowECGUpdateInterface *pShowECGInterface = (CShowECGUpdateInterface *)pInterface;
				pShowECGInterface->ShowECGName(strRhythm, strExtrasyst, nHR, bEMD);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnShowECGRateRange
	// ���ܣ� ��ʾ��ȷ���ʵķ�Χ
	// ������ int nMinRate:               ��С���ʣ���λ����/���ӣ�
	//        int nMaxRate:               ������ʣ���λ����/���ӣ�  
	// ����ֵ:  
	void CShowECGUpdateInterface::OnShowECGRateRange(int nMinRate, int nMaxRate)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowECGUpdateInterface" ) )
			{
				CShowECGUpdateInterface *pShowECGInterface = (CShowECGUpdateInterface *)pInterface;
				pShowECGInterface->ShowECGRateRange(nMinRate, nMaxRate);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnShowECGRate
	// ���ܣ� ��ʾ��ǰ������ֵ
	// ������ int nHR:                    ����ֵ����λ����/���ӣ�
	// ����ֵ:  
	void CShowECGUpdateInterface::OnShowECGRate(int nHR)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowECGUpdateInterface" ) )
			{
				CShowECGUpdateInterface *pShowECGInterface = (CShowECGUpdateInterface *)pInterface;
				pShowECGInterface->ShowECGRate(nHR);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnShowECGNameInDefib
	// ���ܣ� ��������޸��ĵ�ͼ����
	// ������ CString  strQRS:            QRS����
	//        CString strRhythm:          ������������
	//        CString strExtrasyst:       �粫    
	//        int nHR:             ����
	//        BOOL bEMD: 
	//ע��  ����������Ϊ�������ƣ���ʾʱ��ת��Ϊ��ʾ����
	// ����ֵ:  
    void CShowECGUpdateInterface::OnShowECGNameInDefib(const std::string &strRhythm, const std::string &strExtrasyst, int nHR, bool bEMD, int nMillDelayTime)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowECGUpdateInterface" ) )
			{
				CShowECGUpdateInterface *pShowECGInterface = (CShowECGUpdateInterface *)pInterface;
				pShowECGInterface->ShowECGNameInDefib(strRhythm, strExtrasyst, nHR, bEMD, nMillDelayTime);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnShowECGRate
	// ���ܣ� ��������޸ĵ�ǰ������ֵ
	// ������ int nHR:                    ����ֵ����λ����/���ӣ�
	// ����ֵ: 
	void CShowECGUpdateInterface::OnShowECGRateInDefib(int nHR, int nMillDelayTime)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowECGUpdateInterface" ) )
			{
				CShowECGUpdateInterface *pShowECGInterface = (CShowECGUpdateInterface *)pInterface;
				pShowECGInterface->ShowECGRateInDefib(nHR, nMillDelayTime);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
