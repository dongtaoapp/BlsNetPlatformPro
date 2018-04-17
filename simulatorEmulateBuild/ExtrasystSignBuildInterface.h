#pragma once
#include ".\simulatoremulatebuild_global.h"

#include  "..\common\criticalmutex.h"

namespace jysoft { namespace simulator { namespace ecg {

	//早搏信号生成类
    class SIMULATOREMULATEBUILDSHARED_EXPORT CExtrasystSignBuildInterface
	{
	public:
		CExtrasystSignBuildInterface(void);
		virtual ~CExtrasystSignBuildInterface(void);
	private:
		int         m_nSigns[60];
		long        m_nCurrentTime;      //当前时间，单位：0.1毫秒
		int         m_nExtrasystRate;
	private:
		utility::CCriticalMutex      m_cMutex;
	protected:
		void RandonExtrasystSignBuildTime(int nExtrasystRate);
	public:
		//修改早搏产生的数率
		void  ModifyExtrasystRate(int  nExtrasystRate);
		//返回是否要产生早搏（单位：0.1毫秒）
		bool  AddMilliterTime( int iMilliTime );
	};
}}}
