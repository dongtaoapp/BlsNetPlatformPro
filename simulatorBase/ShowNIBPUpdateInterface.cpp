#include ".\shownibpupdateinterface.h"


namespace jysoft { namespace simulator { namespace base {

	CShowNIBPUpdateInterface::CShowNIBPUpdateInterface(void)
	{
	}

	CShowNIBPUpdateInterface::~CShowNIBPUpdateInterface(void)
	{
	}

	bool CShowNIBPUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowNIBPUpdateInterface" )
			return true;
		return IUpdateShowVir::isKindOf(className);
	}

	void CShowNIBPUpdateInterface::UnLinkUpdateShow()
	{
		//�Ͽ���ʾ��֪ͨ
		cutLinkNIBPUpdateShow();
	}

	void CShowNIBPUpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkNIBPUpdateShow();
	}

	/*******************************************************************************/
	// �������ƣ� OnShowNIBPValue
	// ���ܣ� ��ʾ�޴�Ѫѹ����ֵ
	// ������ int nShrinkValue:              ����ѹ
	//        int nStretchValue:             ����ѹ
	// ����ֵ:  
	void CShowNIBPUpdateInterface::OnShowNIBPValue(int nShrinkValue, int nStretchValue)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowNIBPUpdateInterface" ) )
			{
				CShowNIBPUpdateInterface *pShowNIBPInterface = (CShowNIBPUpdateInterface *)pInterface;
				pShowNIBPInterface->ShowNIBPValue( nShrinkValue,  nStretchValue);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnShowKorotkoffVolum
	// ���ܣ� ��ʾ�޴�Ѫѹ�������ֵ
	// ������ int nNIBPSoundValue:              �޴�Ѫѹ�������ֵ
	// ����ֵ:  
	void CShowNIBPUpdateInterface::OnShowKorotkoffVolume(int nNIBPSoundValue)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowNIBPUpdateInterface" ) )
			{
				CShowNIBPUpdateInterface *pShowNIBPInterface = (CShowNIBPUpdateInterface *)pInterface;
				pShowNIBPInterface->ShowNIBPSoundValue( nNIBPSoundValue );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
