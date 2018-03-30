#include ".\ipanemovecontrolinterface.h"

namespace jysoft{  namespace utility {

	IPaneMoveControlInterface::IPaneMoveControlInterface(void)
	{
	}

	IPaneMoveControlInterface::~IPaneMoveControlInterface(void)
	{
	}

	bool IPaneMoveControlInterface::isKindOf(const std::string &className)
	{
		if( className == "IPaneMoveControlInterface" )
		{
			return true;
		}
		return false;
	}

	//�ƶ��컬������
	void IPaneMoveControlInterface::OnPaneMoveOp()
	{
		IBedirecteLinksVir  *pInterface = GetHeaderInterfacePtr();
		while( pInterface )
		{
			if( pInterface->isKindOf("IPaneMoveControlInterface") )
			{
				IPaneMoveControlInterface *pPaneMoveInterface = (IPaneMoveControlInterface *)pInterface;
				pPaneMoveInterface->PaneMoveOp();
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	// ��ʼ���ĵ�ͼ
	void IPaneMoveControlInterface::OnStart(bool bClear)
	{
		IBedirecteLinksVir  *pInterface = GetHeaderInterfacePtr();
		while( pInterface )
		{
			if( pInterface->isKindOf("IPaneMoveControlInterface") )
			{
				IPaneMoveControlInterface *pPaneMoveInterface = (IPaneMoveControlInterface *)pInterface;
				pPaneMoveInterface->Start(bClear);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}
