#include ".\ParseCPRData_Singleton.h"

#include <boost/utility/binary.hpp>


namespace jysoft{  namespace cpr 
{
	//CPR幅度/命令指令判断
	bool CParseCPRData_Singleton::isCPROrder(const _CPRData &cprData) const
	{
		dynamic_bitset<>  db(_CPR_ORDER_L, BOOST_BINARY(01110000));
		dynamic_bitset<>  cprOder(_CPR_ORDER_L, cprData.get<3>());
		db &= cprOder;
		return db.any();
	}

	//CPR开始/结束指令判断
	//bStartJudge: true:开始CPR，false:结束CPR， indeterminate:CPR开始/结束指令
	bool CParseCPRData_Singleton::judgeCPRStartOrStopOrder(const _CPRData &cprData, tribool bStartJudge/*=unknown*/) const
	{
		dynamic_bitset<>  db(_CPR_ORDER_L, cprData.get<3>());
		if( indeterminate(bStartJudge) )
		{
			db &= dynamic_bitset<>(_CPR_ORDER_L, BOOST_BINARY(1110000));
			return (db.to_ulong() == 0x70) ? true : false;
		}
		else if( bStartJudge )
		{
			return (db.to_ulong() == 0x7F) ? true : false;
		}
		else
		{
			return (db.to_ulong() == 0x70) ? true : false;
		}
		return false;
	}

	//CPR阶段标识指令判断
	//bPhaseJudge： true:按压阶段，false:吹气阶段， indeterminate:阶段指令
	//bStartJudge： true: 开始，false:结束， indeterminate:无效
	bool CParseCPRData_Singleton::judgeCPRPhaseStartOrFinishOrder(const _CPRData &cprData, tribool bPhaseJudge, tribool bStartJudge/*=unknown*/) const
	{
		dynamic_bitset<>  db(_CPR_ORDER_L, cprData.get<3>());
		if( indeterminate(bPhaseJudge) )
		{
			db &= dynamic_bitset<>(_CPR_ORDER_L, BOOST_BINARY(1110000));
			return (db.to_ulong() == 0x10) ? true : false;
		}
		else if( indeterminate(bStartJudge) )
		{
			if( bPhaseJudge )
			{
				//按压开始或结束判断
				db &= dynamic_bitset<>(_CPR_ORDER_L, BOOST_BINARY(1110100));
				return (db.to_ulong() == 0x14) ? true : false;
			}
			else
			{
				//吹气开始或结束判断
				db &= dynamic_bitset<>(_CPR_ORDER_L, BOOST_BINARY(1111000));
				return (db.to_ulong() == 0x18) ? true : false;
			}
		}
		else if( bPhaseJudge )
		{
			//按压开始/结束判断
			db &= dynamic_bitset<>(_CPR_ORDER_L, 0x7F);
			if( bStartJudge )
			{
				return (db.to_ulong() == 0x17) ? true : false;
			}
			else 
			{
				return (db.to_ulong() == 0x14) ? true : false;
			}
		}
		else
		{
			//吹气开始/结束判断
			db &= dynamic_bitset<>(_CPR_ORDER_L, 0x7F);
			if( bStartJudge )
			{
				return (db.to_ulong() == 0x1B) ? true : false;
			}
			else 
			{
				return (db.to_ulong() == 0x18) ? true : false;
			}
		}
		return false;
	}

	//幅度数据判断
	//bScopeJudge： true:按压幅度，false:吹气幅度， unknown:幅度指令
	bool CParseCPRData_Singleton::isCPRScopeOrder(const _CPRData &cprData, tribool bScopeJudge/*=unknown*/) const
	{
		dynamic_bitset<>  db(_CPR_ORDER_L, cprData.get<3>());
		db &= dynamic_bitset<>(_CPR_ORDER_L, 0xF0);
		if( indeterminate(bScopeJudge) )
		{
			if( db.to_ulong() == 0x40 || db.to_ulong() == 0x20 )
			{
				return true;
			}
			return false;
		}
		else if( bScopeJudge )
		{
			//按压幅度
			return ( db.to_ulong() == 0x20 ) ? true : false;
		}
		else
		{
			//吹气幅度
			return ( db.to_ulong() == 0x40 ) ? true : false;
		}
		return false;
	}

	//错误标识指令判断
	bool CParseCPRData_Singleton::isErrorSignOrder(const _CPRData &cprData) const
	{
		dynamic_bitset<>  db(_CPR_ORDER_L, cprData.get<3>());
		db &= dynamic_bitset<>(_CPR_ORDER_L, BOOST_BINARY(11110000));
		return ( db.to_ulong() == 0x60 ) ? true : false;
	}

	//按压幅度采样数值
	//返回值：按压深度、按压位置、释放正确
	tuple<int, dynamic_bitset<>, bool>  CParseCPRData_Singleton::getPressureScopeValue(const _CPRData &cprData) const
	{
		int   pressureDepth = 0;
		bool  bReleaseRight = true;
		dynamic_bitset<>  pressurePos(_CPR_ORDER_L, 0);
		//按压深度
		pressureDepth = cprData.get<2>();
		//按压位置
		int pos = cprData.get<3>();
		pressurePos = dynamic_bitset<>(_CPR_ORDER_L, cprData.get<3>()) & dynamic_bitset<>(_CPR_ORDER_L, BOOST_BINARY(1111));
		//释放正确
		bReleaseRight = !cprData.get<5>();
		return make_tuple(pressureDepth, pressurePos, bReleaseRight);
	}

	//吹气幅度采样值
	//返回值：吹气量、是否进胃
	tuple<int, bool> CParseCPRData_Singleton::getBreathScopeValue(const _CPRData &cprData) const
	{
		int  breathVolume = 0;
		bool bStomach = false;
		//吹气幅度采样值
		breathVolume = cprData.get<0>();
		//是否进胃
		bStomach = cprData.get<5>();
		return make_tuple(breathVolume, bStomach);
	}

	//返回错误标识值
	_eCPRErrorSign CParseCPRData_Singleton::geteErrorSignValue(const _CPRData &cprData) const
	{
		dynamic_bitset<> order(_CPR_ORDER_L, cprData.get<3>());
		order &= dynamic_bitset<>(_CPR_ORDER_L, BOOST_BINARY(01111));
		return (_eCPRErrorSign)order.to_ulong();
	}

	//频率数据判断
	//bScopeJudge： true:按压频率，false:吹气频率， unknown:频率指令
	bool CParseCPRData_Singleton::isRateOrder(const _CPRData &cprData, tribool bScopeJudge/*=unknown*/) const
	{
		dynamic_bitset<>  db(_CPR_ORDER_L, cprData.get<3>());
		db &= dynamic_bitset<>(_CPR_ORDER_L, 0xF0);
		if( indeterminate(bScopeJudge) )
		{
			if( db.to_ulong() == 0xC0 || db.to_ulong() == 0xA0 )
			{
				return true;
			}
			return false;
		}
		else if( bScopeJudge )
		{
			//按压幅度
			return ( db.to_ulong() == 0xA0 ) ? true : false;
		}
		else
		{
			//吹气幅度
			return ( db.to_ulong() == 0xC0 ) ? true : false;
		}
		return false;
	}

	//按压频率值
	//返回：按压频率、时间戳
	tuple<int, unsigned short> CParseCPRData_Singleton::getPressureRateValue(const _CPRData &cprData) const
	{
		int  nRate = 0;
		unsigned short  sTime = 0;
		//按压频率
		nRate = cprData.get<4>();
		//时间戳
		sTime = cprData.get<6>();
		return make_tuple(nRate, sTime);
	}

	//吹气频率值
	//返回：通气时间、频率、时间戳
	tuple<int, short, unsigned short> CParseCPRData_Singleton::getBreathRateValue(const _CPRData &cprData) const
	{
		int  nRate = 0;
		short  sBreathTime = 0;
		unsigned short  sTime = 0;
		//吹气频率
		nRate = cprData.get<4>();
		//通气时间
		sBreathTime = (short)cprData.get<1>();
		//时间戳
		sTime = cprData.get<6>();
		return make_tuple(nRate, sBreathTime, sTime);
	}
	//-------------------------------------------------------------------------------------------------------------------
	//采样数值判断
	//bRealTimeJudge： true:按压采样值，false:吹气采样值， unknown:采样数值类型
	bool CParseCPRData_Singleton::isCPRRealTimeSampleData(const _CPRData &cprData, tribool bRealTimeJudge/*=unknown*/) const
	{
		dynamic_bitset<> db(_CPR_ORDER_L, cprData.get<3>());
		if( indeterminate(bRealTimeJudge) )
		{
			db &= dynamic_bitset<>(_CPR_ORDER_L, 0x70);
			return db.none();
		}
		else if( bRealTimeJudge )
		{
			//按压采样值
			db &= dynamic_bitset<>(_CPR_ORDER_L, 0x74);
			return (db.to_ulong() == 0x04) ? true : false;
		}
		else 
		{
			//吹气采样值
			db &= dynamic_bitset<>(_CPR_ORDER_L, 0x78);
			return (db.to_ulong() == 0x08) ? true : false;
		}
		return false;
	}

	//按压采样数值
	//返回值：按压深度，是否有上升沿标识
	tuple<int, bool> CParseCPRData_Singleton::getPressureSample(const _CPRData &cprData) const
	{
		int  nPressureDepth = 0;
		bool bUpSign = false;
		//按压深度
		nPressureDepth = cprData.get<2>();
		//判断是否上升沿标识
		dynamic_bitset<>  db(_CPR_ORDER_L, cprData.get<3>());
		if(db[0] && db[1])
		{
			bUpSign = true;
		}
		return make_tuple(nPressureDepth, bUpSign);
	}

	//返回吹气采样数值
	//返回值：吹气量，是否有上升沿标识
	tuple<int, bool> CParseCPRData_Singleton::getBreathSample(const _CPRData &cprData) const
	{
		int  nBreathVolume = 0;
		bool bUpSign = false;
		//吹气量
		nBreathVolume = cprData.get<0>() + cprData.get<1>();
		//判断是否上升沿标识
		dynamic_bitset<>  db(_CPR_ORDER_L, cprData.get<3>());
		if(db[0] && db[1])
		{
			bUpSign = true;
		}
		return make_tuple(nBreathVolume, bUpSign);
	}

	//构建CPR操作开始/结束标识指令
	_CPRData CParseCPRData_Singleton::createCPRPhaseData(bool bCPRStart, unsigned short sTimestamp/*=0*/) const
	{
		unsigned char  cprOrder = bCPRStart ? 0x7F : 0x70;
		return make_tuple(0, 0, 0, cprOrder, 0, false, sTimestamp);
	}

	//构建按压阶段标识指令
	_CPRData CParseCPRData_Singleton::createPressurePhaseData(bool bPhaseStart) const
	{
		unsigned char  cprOrder = bPhaseStart ? 0x17 : 0x14;
		return make_tuple(0, 0, 0, cprOrder, 0, false, 0);
	}

	//构建吹气阶段标识指令
	_CPRData CParseCPRData_Singleton::createBreathPhaseData(bool bPhaseStart) const
	{
		unsigned char  cprOrder = bPhaseStart ? 0x1B : 0x18;
		return make_tuple(0, 0, 0, cprOrder, 0, false, 0);
	}

	//构建按压幅度指令
	//sDepth： 按压深度   bReleaseError： 是否正确  sPos: 按压位置  sTimestamp: 时间戳（单位：100ms）
	_CPRData CParseCPRData_Singleton::createPressureDepthData(unsigned char sDepth, bool bReleaseError, unsigned char sPos, unsigned short sTimestamp) const
	{
		unsigned char  cprOrder = 0x20 + sPos;
		return make_tuple(0, 0, sDepth, cprOrder, 0, bReleaseError, sTimestamp);
	}

	//构建吹气幅度指令
	//sVolume: 吹气量   bStomach：进胃  sTimestamp: 时间戳（单位：100ms）
	_CPRData CParseCPRData_Singleton::createBreathVolumeData(unsigned char sVolume, bool bStomach, unsigned short sTimestamp) const
	{
		return make_tuple(sVolume, 0, 0, 0x40, 0, bStomach, sTimestamp);
	}

	//构建按压频率指令
	//sRate: 按压频率   sTimestamp: 时间戳（单位：100ms）
	_CPRData CParseCPRData_Singleton::createPressureRateData(unsigned char sRate, unsigned short sTimestamp) const
	{
		return make_tuple(0, 0, 0, 0xA0, sRate, false, sTimestamp);
	}

	//构建吹气频率指令
	//sRate: 吹气频率   sRespTime： 通气时间（单位：100ms）  sTimestamp: 时间戳（单位：100ms）
	_CPRData CParseCPRData_Singleton::createBreathRateData(unsigned char sRate, unsigned char sRespTime, unsigned short sTimestamp) const
	{
		return make_tuple(0, sRespTime, 0, 0xC0, sRate, false, sTimestamp);
	}

	//构建Zero实时数据
	//cDepth: 实时幅度  bPressure: 按压/吹气  bAscens：上升沿开始
	_CPRData CParseCPRData_Singleton::createRealTimeSampleData(unsigned char cDepth, bool bPressure, bool bAscens/*=false*/) const
	{
		if( bPressure )
		{
			return make_tuple(0, 0, cDepth, bAscens ? 0x05 : 0x04, 0, false, 0);
		}
		return make_tuple(cDepth, 0, 0, bAscens ? 0x0A : 0x08, 0, false, 0);
	}

	//构建错误标识指令
	_CPRData CParseCPRData_Singleton::createErrorSignData(_eCPRErrorSign eErrorSign) const
	{
		return make_tuple(0, 0, 0, 0x60+eErrorSign, 0, false, 0);
	}
}}
