#include ".\showresprateupdateinterface.h"

namespace jysoft { namespace simulator { namespace base {

	CShowRespRateUpdateInterface::CShowRespRateUpdateInterface(void)
	{
	}

	CShowRespRateUpdateInterface::~CShowRespRateUpdateInterface(void)
	{
	}

	bool CShowRespRateUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowRespRateUpdateInterface" )
			return true;
		return IUpdateShowVir::isKindOf(className);
	}

	void CShowRespRateUpdateInterface::UnLinkUpdateShow()
	{
		//�Ͽ���ʾ��֪ͨ
		cutLinkRespRateUpdateShow();
	}

	void CShowRespRateUpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkRespRateUpdateShow();
	}

	/*******************************************************************************/
	// �������ƣ� OnShowRespRate
	// ���ܣ� ��ʾ��������
	// ������ int nRate:              ������������λ����/���ӣ�
	// ����ֵ:  
	void CShowRespRateUpdateInterface::OnShowRespRate(eRespMode  enumMode, int nRate)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowRespRateUpdateInterface" ) )
			{
				CShowRespRateUpdateInterface *pShowRespInterface = (CShowRespRateUpdateInterface *)pInterface;
				pShowRespInterface->ShowRespRate( enumMode, nRate );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnShowRespRateRange
	// ���ܣ� ��ʾѪ�������ķ�Χ����
	// ������ int nMinRate:              ������С������������λ����/���ӣ� 
	//        int nMaxRate:              ������������������λ����/���ӣ� 
	// ����ֵ:  
	void CShowRespRateUpdateInterface::OnShowRespRateRange(int nMinRate, int nMaxRate)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowRespRateUpdateInterface" ) )
			{
				CShowRespRateUpdateInterface *pShowRespInterface = (CShowRespRateUpdateInterface *)pInterface;
				pShowRespInterface->ShowRespRateRange(nMinRate, nMaxRate);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
