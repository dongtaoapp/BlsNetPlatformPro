#pragma once
#include ".\cprmoduls_global.h"
#include <boost/date_time/posix_time/posix_time.hpp>

#include "..\Common\CommonGlobal.h"


using namespace boost::posix_time; 
//-----------------------------------------------------------------------------------------------------------------------
struct CPRMODULSSHARED_EXPORT _StatDataSeg
{//操作统计段结构
public:
	time_duration     segBeginTime; //开始时间
	time_duration     segPeriod;    //时间区间
	short             average;      //总数值(注：计算平均指数要除sunNum)
	short            sumNum;    //总的次数
	short            rightNum;  //正确次数
	short            sumErrorNum; //总错误次数(包括CPR规则的计数)
	//幅度正确（按压: 5~6cm; 吹气: 500 ~1000ml）
	short            overNum;   //过大
	short            lackNum;   //不足
	//CPR规则：30:2, 次数过多或过少的总数
	short            lackSumNum; //按压/吹气次数过少
	short            overSumNum; //按压/吹气次数过多
	//--------------------------------------------------------------------------------
	bool              bValidate;  //统计是否有效
public:
	_StatDataSeg()
	{
		::memset(this, 0, sizeof(_StatDataSeg));
	};
public:
	void clone(const _StatDataSeg &sourceSeg);
	//返回平均值（平均深度、平均吹气量）
	short getAverageValue() const { return sumNum == 0 ? 0 : short(average/ sumNum); };
	//返回幅度正确次数
	short getRightDepthNum() { return sumNum - overNum - lackNum; };
	//返回平均频率
	short getAverageRate() const;
	//总的次数
	short getSumCount() const { return sumNum; };
    //错误总数
	short getSumErrorsNum()const { return sumErrorNum; };
protected:
	//重置
	void resetBase();
};

//按压阶段统计结果
struct CPRMODULSSHARED_EXPORT _StatPressueSeg : public _StatDataSeg
{
public:
	short                   incompleteNum;    //按压时非完全释放
	short                   posErrorNum;      //按压位置总错误
	short                   posErr_low;       //按压位置太低
	short                   posErr_high;      //按压位置太高
	short                   posErr_right;     //按压位置太右
	short                   posErr_left;      //按压位置太左
	//正确频率范围(100~120/分钟)内的个数
	short                   rateRightSum;     
public:
	_StatPressueSeg() : _StatDataSeg()
	{
		incompleteNum = 0;
		posErrorNum = posErr_low = posErr_high = posErr_right = posErr_left = 0;
		rateRightSum = 0;
	};
public:
	void operator = (const _StatPressueSeg &pressureSeg);
	//重置
	void reset();
};

//吹气阶段统计结果
struct CPRMODULSSHARED_EXPORT _StatBreathSeg : public _StatDataSeg
{
public:
	short                    ventiOverTimeNum;   //通气时间过长
	short                    ventiLowerTimeNum;  //通气时间过短
	short                    stomachNum; //进胃
	short                    pipeCloseNum;//气道关闭
public:
	_StatBreathSeg() : _StatDataSeg()
	{
		ventiOverTimeNum = 0;
		ventiLowerTimeNum = 0;
		stomachNum = 0;
		pipeCloseNum = 0;
	};
public:
	void operator = (const _StatBreathSeg &breathSeg);
	//重置
	void reset();
};

namespace jysoft{  namespace cpr {  namespace cprShow
{
    struct CPRMODULSSHARED_EXPORT _CPRErrorSign
	{//CPR操作错误状态标示
	public:
		float           m_fDevicePos;
		unsigned short  m_dwTimePos;
		_eCPRErrorSign  m_eErrorSign;
	public:
		_CPRErrorSign(unsigned short dwTimePos, float fDevicePos, _eCPRErrorSign eErrorSign);

	};
}}}
