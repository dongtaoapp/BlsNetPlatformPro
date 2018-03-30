#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\ibedirectelinksvir.h"
#include "..\Common\CommonGlobal.h"


namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     心脏启动信号接口
	创建人：	 hjg
	创建时间：   2008/8/22
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT IHeartStartSign :  public IBedirecteLinksVir
	{
	public:
		IHeartStartSign(void);
		virtual ~IHeartStartSign(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		//心脏开始启动一个周期的跳动的信号
		virtual void HeartStartSignHandle(BasicRhythm eRhythm, int  nCycleTime, bool bHaveHeartSign) = 0;
        virtual void WatchHeartStartSign(bool bWatching) = 0;
	public:
		/*******************************************************************************/
		// 函数名称： OnHeartStartSignHandle
		// 功能：   心脏开始启动一个周期的跳动的信号
		// 参数：
		//        BasicRhythm eRhythm:  心律名称
		//        int  nCycleTime:      心跳周期时间（单位：0.1毫秒）
		// 返回值:  
		void OnHeartStartSignHandle(BasicRhythm eRhythm, int  nCycleTime, bool bHaveHeartSign);
		/*******************************************************************************/
		// 函数名称： OnWatchHeartStartSign
		// 功能：   
		// 参数：
		//        BOOL bWatching:  
		// 返回值:  
		void OnWatchHeartStartSign(bool bWatching);
	};

}}
