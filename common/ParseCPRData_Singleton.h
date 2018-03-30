#pragma once

#include ".\CommonGlobal.h"

#include <boost/logic/tribool.hpp>
#include <boost/serialization/singleton.hpp>

#define  _CPR_ORDER_L           8

using namespace boost;
//BOOST_TRIBOOL_THIRD_STATE(unknown)

namespace jysoft{  namespace cpr {
	   /*-----------------------------------------------------------------------------------------------------------------
		类说明：     CPR数据解析类（单件）
		创建人：	 hjg
		创建时间：   2017/4/9      修改时间：2018.2.27
		//****************************************************************************************************/
		//CPR指令格式说明：
	    //    CPR开始结束指令：0x7F:CPR开始, 0x70:CPR结束
	    //                     时间戳：<有效>
	    //    CPR阶段标识指令：
	    //                    0x1B:吹气开始, 0x18:吹气结束
	    //                    0x17:按压开始, 0x14:按压结束
	    //    CPR幅度指令:
	    //                    吹气幅度: 0x4X, 按压幅度:0x2X
	    //                    按压位置：0~3位分别表示左、右、上、下错误位置; 都为0表示正确；都为1表示不确定错误的位置
	    //                    时间戳： <有效>
	    //    CPR频率指令：
	    //                    吹气频率: 0xCX, 按压频率:0xAX
	    //                    时间戳： <有效>
	    //    错误标识值：
	    //                    标识值:  0x60
	    //                    时间戳： <有效?>
	    //    CPR采样数据:
	    //                    吹气数据：第3位为1，第1位代表吹气上升沿开始
	    //                    按压数据：第2位为1，第0位代表按压上升沿开始
		//-----------------------------------------------------------------------------------------------------------------*/
	class  CParseCPRData_Singleton : public serialization::singleton<CParseCPRData_Singleton>
	{
	public:
		//CPR幅度/命令指令判断
		BOOST_DLLEXPORT bool isCPROrder(const _CPRData &cprData) const;
		//CPR开始/结束指令判断
		//bStartJudge: true:开始CPR，false:结束CPR， indeterminate:CPR开始/结束指令
		BOOST_DLLEXPORT bool judgeCPRStartOrStopOrder(const _CPRData &cprData, tribool bStartJudge = indeterminate) const;
		//CPR阶段标识指令判断
		//bPhaseJudge： true:按压阶段，false:吹气阶段， indeterminate:阶段指令
		//bStartJudge： true: 开始，false:结束， indeterminate:无效
		BOOST_DLLEXPORT bool judgeCPRPhaseStartOrFinishOrder(const _CPRData &cprData, tribool bPhaseJudge, tribool bStartJudge = indeterminate) const;
		//幅度数据判断
		//bScopeJudge： true:按压幅度，false:吹气幅度， unknown:幅度指令
		BOOST_DLLEXPORT bool isCPRScopeOrder(const _CPRData &cprData, tribool bScopeJudge = indeterminate) const;
		//错误标识指令判断
		BOOST_DLLEXPORT bool isErrorSignOrder(const _CPRData &cprData) const;
		//按压幅度采样数值
		//返回值：按压深度、按压位置、释放正确
		BOOST_DLLEXPORT tuple<int, dynamic_bitset<>, bool>  getPressureScopeValue(const _CPRData &cprData) const;
		//吹气幅度采样值
		//返回值：吹气量、是否进胃
		BOOST_DLLEXPORT tuple<int, bool> getBreathScopeValue(const _CPRData &cprData) const;
		//频率数据判断
		//bScopeJudge： true:按压频率，false:吹气频率， unknown:频率指令
		BOOST_DLLEXPORT bool isRateOrder(const _CPRData &cprData, tribool bScopeJudge = indeterminate) const;
		//按压频率值
		//返回：按压频率、时间戳
		BOOST_DLLEXPORT tuple<int, unsigned short> getPressureRateValue(const _CPRData &cprData) const;
		//吹气频率值
		//返回：通气时间、频率、时间戳
		BOOST_DLLEXPORT tuple<int, short, unsigned short> getBreathRateValue(const _CPRData &cprData) const;
		//返回错误标识值
		BOOST_DLLEXPORT _eCPRErrorSign geteErrorSignValue(const _CPRData &cprData) const;
		//-------------------------------------------------------------------------------------------------------------------
		//采样数值判断
		//bRealTimeJudge： true:按压采样值，false:吹气采样值， unknown:采样数值类型
		BOOST_DLLEXPORT bool isCPRRealTimeSampleData(const _CPRData &cprData, tribool bRealTimeJudge = indeterminate) const;
		//按压采样数值
		//返回值：按压深度，是否有上升沿标识
		BOOST_DLLEXPORT tuple<int, bool> getPressureSample(const _CPRData &cprData) const;
		//返回吹气采样数值
		//返回值：吹气量，是否有上升沿标识
		BOOST_DLLEXPORT tuple<int, bool> getBreathSample(const _CPRData &cprData) const;
		//--------------------------------------------------------------------------------------------------------------------
		//构建CPR操作开始/结束标识指令
		BOOST_DLLEXPORT _CPRData createCPRPhaseData(bool bCPRStart, unsigned short sTimestamp = 0) const;
		//构建按压阶段标识指令
		BOOST_DLLEXPORT _CPRData createPressurePhaseData(bool bPhaseStart) const;
		//构建吹气阶段标识指令
		BOOST_DLLEXPORT _CPRData createBreathPhaseData(bool bPhaseStart) const;
		//构建按压幅度指令
		//sDepth： 按压深度   bReleaseError： 释放错误  sPos: 按压位置  sTimestamp: 时间戳（单位：100ms）
		BOOST_DLLEXPORT _CPRData createPressureDepthData(unsigned char sDepth, bool bReleaseError, unsigned char sPos, unsigned short sTimestamp) const;
		//构建吹气幅度指令
		//sVolume: 吹气量   bStomach：进胃  sTimestamp: 时间戳（单位：100ms）
		BOOST_DLLEXPORT _CPRData createBreathVolumeData(unsigned char sVolume, bool bStomach, unsigned short sTimestamp) const;
		//构建按压频率指令
		//sRate: 按压频率   sTimestamp: 时间戳（单位：100ms）
		BOOST_DLLEXPORT _CPRData createPressureRateData(unsigned char sRate, unsigned short sTimestamp) const;
		//构建吹气频率指令
		//sRate: 吹气频率   sRespTime： 通气时间（单位：100ms）  sTimestamp: 时间戳（单位：100ms）
		BOOST_DLLEXPORT _CPRData createBreathRateData(unsigned char sRate, unsigned char sRespTime, unsigned short sTimestamp) const;
		//构建Zero实时数据
		//cDepth: 实时幅度  bPressure: 按压/吹气  bAscens：上升沿开始
		BOOST_DLLEXPORT _CPRData createRealTimeSampleData(unsigned char cDepth, bool bPressure, bool bAscens=false) const;
		//构建错误标识指令
		BOOST_DLLEXPORT _CPRData createErrorSignData(_eCPRErrorSign eErrorSign) const;
	};
}}
