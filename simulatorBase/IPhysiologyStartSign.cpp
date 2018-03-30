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
	//功能：血氧采样数据加载
	//参数：int nDifferMilliTime:          时间（0.1豪秒）
	//      int nQtoSMilliTime:            Q波到S波的时间（0.1豪秒）
	//      int nStoTMilliTime:            S波到T波的时间（0.1豪秒）
	//      int nCycleTime:                周期时间（0.1豪秒）
	//返回值:  
	*********************************************************************************/
	void IPhysiologyStartSign::OnStartPhysiologySimpleLoad(int nDifferMilliTime, int nQtoSMilliTime, int nStoTMilliTime, int nCycleTime)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface )
		{
			if( pInterface->isKindOf("IPhysiologyStartSign") )
			{
				IPhysiologyStartSign *pStartSign = (IPhysiologyStartSign *)pInterface;
				//血氧采样数据加载
				pStartSign->StartPhysiologySimpleLoad(nDifferMilliTime, nQtoSMilliTime, nStoTMilliTime, nCycleTime);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}
