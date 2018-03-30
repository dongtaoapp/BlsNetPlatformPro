#include ".\iphysiologystartsign.h"

namespace jysoft { namespace simulator {

	IPhysiologyStartSign::IPhysiologyStartSign(void)
	{
	
	}

	IPhysiologyStartSign::~IPhysiologyStartSign(void)
	{
	}

	bool IPhysiologyStartSign::isKindOf(const std::string &className)
	{
		if( className == "IPhysiologyStartSign" )
		{
			return true;
		}
		return false;
	}

	/*******************************************************************************
	//���ܣ�Ѫ���������ݼ���
	//������int nDifferMilliTime:          ʱ�䣨0.1���룩
	//      int nQtoSMilliTime:            Q����S����ʱ�䣨0.1���룩
	//      int nStoTMilliTime:            S����T����ʱ�䣨0.1���룩
	//      int nCycleTime:                ����ʱ�䣨0.1���룩
	//����ֵ:  
	*********************************************************************************/
	void IPhysiologyStartSign::OnStartPhysiologySimpleLoad(int nDifferMilliTime, int nQtoSMilliTime, int nStoTMilliTime, int nCycleTime)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface )
		{
			if( pInterface->isKindOf("IPhysiologyStartSign") )
			{
				IPhysiologyStartSign *pStartSign = (IPhysiologyStartSign *)pInterface;
				//Ѫ���������ݼ���
				pStartSign->StartPhysiologySimpleLoad(nDifferMilliTime, nQtoSMilliTime, nStoTMilliTime, nCycleTime);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}
