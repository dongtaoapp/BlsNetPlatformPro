#include <boost/lexical_cast.hpp>

#include ".\showabpupdateinterface.h"

namespace jysoft { namespace simulator { namespace base {

	CShowABPUpdateInterface::CShowABPUpdateInterface(void)
	{
	}

	CShowABPUpdateInterface::~CShowABPUpdateInterface(void)
	{
	}

	bool CShowABPUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowABPUpdateInterface" )
			return true;
		return IUpdateShowVir::isKindOf(className);
	}

	void CShowABPUpdateInterface::UnLinkUpdateShow()
	{
		//�Ͽ���ʾ��֪ͨ
		cutLinkABPUpdateShow();
	}

	void CShowABPUpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkABPUpdateShow();
	}

	//�����д�Ѫѹ��nShrink������ѹ��nStretch������ѹ
	bool CShowABPUpdateInterface::ParseABPToShrinkAndnStretch(const std::string &strABP, int &nShrink, int &nStretch)
	{
		std::string::size_type nPos = strABP.find('/');
		if(nPos != -1)
		{
			//����ѹ
			std::string nValue = strABP.substr(0, nPos);
			nShrink = boost::lexical_cast<int>(nValue);
			//����ѹ
			nValue = strABP.substr(nPos+1);
			nStretch = boost::lexical_cast<int>(nValue);
			return true;
		}
		return false;
	}

	/*******************************************************************************/
	// �������ƣ� OnShowABPValue
	// ���ܣ� ��ʾ�д�Ѫѹ����ֵ
	// ������ int nShrinkValue:              ����ѹ
	//        int nStretchValue:             ����ѹ
	// ����ֵ:  
	void CShowABPUpdateInterface::OnShowABPValue(int nShrinkValue, int nStretchValue)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf("CShowABPUpdateInterface") )
			{
				CShowABPUpdateInterface *pShowABPInterface = (CShowABPUpdateInterface *)pInterface;
				pShowABPInterface->ShowABPValue( nShrinkValue,  nStretchValue);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	void CShowABPUpdateInterface::OnShowABPValue(const std::string &strABP)
	{
		int nShrink, nStretch;
		if( CShowABPUpdateInterface::ParseABPToShrinkAndnStretch(strABP, /*out*/nShrink, /*out*/nStretch) )
		{
			OnShowABPValue(nShrink, nStretch);
		}
	}

}}}
