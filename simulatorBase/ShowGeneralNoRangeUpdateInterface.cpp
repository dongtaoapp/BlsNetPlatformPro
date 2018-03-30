#include ".\showgeneralnorangeupdateinterface.h"

namespace jysoft { namespace simulator { namespace base {

	CShowGeneralNoRangeUpdateInterface::CShowGeneralNoRangeUpdateInterface(void)
	{
	}

	CShowGeneralNoRangeUpdateInterface::~CShowGeneralNoRangeUpdateInterface(void)
	{
	}

	bool CShowGeneralNoRangeUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowGeneralNoRangeUpdateInterface" )
		{
			return true;
		}
		return IUpdateShowVir::isKindOf( className );
	}

	void CShowGeneralNoRangeUpdateInterface::UnLinkUpdateShow()
	{
		//�Ͽ���ʾ��֪ͨ
		cutLinkGeneralNoRangeUpdateShow();
	}

	void CShowGeneralNoRangeUpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkGeneralNoRangeUpdateShow();
	}

	/*******************************************************************************/
	// �������ƣ� OnShowPhystValue
	// ���ܣ� ��ʾ����ֵ
	// ������ float fPhystValue:              ֵ
	// ����ֵ:  
	void CShowGeneralNoRangeUpdateInterface::OnShowPhystValue(float fPhystValue)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowGeneralNoRangeUpdateInterface" ) )
			{
				CShowGeneralNoRangeUpdateInterface *pShowInterface = (CShowGeneralNoRangeUpdateInterface *)pInterface;
				pShowInterface->ShowPhystValue( fPhystValue );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}}
