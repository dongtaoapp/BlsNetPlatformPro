#include ".\iheartstartsign.h"

namespace jysoft { namespace simulator {

	IHeartStartSign::IHeartStartSign(void)
	{
	}

	IHeartStartSign::~IHeartStartSign(void)
	{
	}

	bool IHeartStartSign::isKindOf(const std::string &className)
	{
		if( className == "IHeartStartSign" ) 
		{
			return true;
		}
		return false;
	}

	/*******************************************************************************/
	// 函数名称： OnHeartStartSignHandle
	// 功能：   心脏开始启动一个周期的跳动的信号
	// 参数：
	//        BasicRhythm eRhythm:  心律名称
	//        int  nCycleTime:      心跳周期时间（单位：0.1毫秒）
	// 返回值:  
	void IHeartStartSign::OnHeartStartSignHandle(BasicRhythm eRhythm, int  nCycleTime, bool bHaveHeartSign)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface )
		{
			IHeartStartSign *pHeartStartSign = (IHeartStartSign *)pInterface;
			pHeartStartSign->HeartStartSignHandle(eRhythm, nCycleTime, bHaveHeartSign);
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// 函数名称： OnWatchHeartStartSign
	// 功能：   
	// 参数：
	//        BOOL bWatching:  
	// 返回值:  
	void IHeartStartSign::OnWatchHeartStartSign(bool bWatching)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface )
		{
			IHeartStartSign *pHeartStartSign = (IHeartStartSign *)pInterface;
			pHeartStartSign->WatchHeartStartSign( bWatching );
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}
