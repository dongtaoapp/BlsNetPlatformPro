#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\IBedirecteLinksVir.h"

namespace jysoft { namespace simulator {

	//启动信号接口类
    class SIMULATORBASESHARED_EXPORT IPhysiologyStartSign : public IBedirecteLinksVir
	{
	public:
		IPhysiologyStartSign(void);
		virtual ~IPhysiologyStartSign(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		/*******************************************************************************
		//功能：血氧采样数据加载
		//参数：int nDifferMilliTime:          时间（0.1豪秒）
		//      int nQtoSMilliTime:            Q波到S波的时间（0.1豪秒）
		//      int nStoTMilliTime:            S波到T波的时间（0.1豪秒）
		//      int nCycleTime:                周期时间（0.1豪秒）
		//返回值:  
		*********************************************************************************/
		void OnStartPhysiologySimpleLoad(int nDifferMilliTime, int nQtoSMilliTime, int nStoTMilliTime, int nCycleTime);
	protected:
		//血氧采样数据加载
		virtual void StartPhysiologySimpleLoad(int nDifferMilliTime, int nQtoSMilliTime, int nStoTMilliTime, int nCycleTime) = 0;
	};
}}
