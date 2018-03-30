#include ".\CPRCommonGlobal.h"


//--------------------------------------------------------------------------------------------------------------
//_StatDataSeg
void _StatDataSeg::clone(const _StatDataSeg &sourceSeg)
{
	segBeginTime = sourceSeg.segBeginTime;
	segPeriod = sourceSeg.segPeriod;
	average = sourceSeg.average;
	sumNum = sourceSeg.sumNum;
	sumErrorNum = sourceSeg.sumErrorNum;
	rightNum = sourceSeg.rightNum;
	overNum = sourceSeg.overNum;
	lackNum = sourceSeg.lackNum;
	lackSumNum = sourceSeg.lackSumNum;
	overSumNum = sourceSeg.overSumNum;
	bValidate = sourceSeg.bValidate;
}

//重置
void _StatDataSeg::resetBase()
{
	::memset(this, 0, sizeof(_StatDataSeg));
}

void _StatPressueSeg::operator= (const _StatPressueSeg &pressureSeg)
{
	incompleteNum = pressureSeg.incompleteNum;
	posErrorNum = pressureSeg.posErrorNum;
	posErr_low = pressureSeg.posErr_low;
	posErr_high = pressureSeg.posErr_high;
	posErr_right = pressureSeg.posErr_right;
	posErr_left = pressureSeg.posErr_left;
	rateRightSum = pressureSeg.rateRightSum;
	clone(pressureSeg);
}

//返回平均频率
short _StatDataSeg::getAverageRate() const
{
	short  uRate = 0;
	int nSec = segPeriod.total_seconds();
	if( sumNum > 0 && nSec > 0 )
	{
		uRate = (short)(sumNum / (nSec / 60.0f));
	}
	return uRate;
}

//重置
void _StatPressueSeg::reset()
{
	overNum = lackNum = incompleteNum = 0;
	posErrorNum = posErr_low = posErr_high = posErr_right = posErr_left = 0;
	rateRightSum = 0;
	resetBase();
}

void _StatBreathSeg::operator= (const _StatBreathSeg &breathSeg)
{
	ventiOverTimeNum = breathSeg.ventiOverTimeNum;
	ventiLowerTimeNum = breathSeg.ventiLowerTimeNum;	
	stomachNum = breathSeg.stomachNum;
	pipeCloseNum = breathSeg.pipeCloseNum;
	clone(breathSeg);
}

//重置
void _StatBreathSeg::reset()
{
	overNum = lackNum = stomachNum = 0;
	pipeCloseNum = 0;
	ventiOverTimeNum = 0;
	ventiLowerTimeNum = 0;
	resetBase();
}

//----------------------------------------------------------------------------------------------------------------
namespace jysoft{  namespace cpr {  namespace cprShow
{
	//struct _CPRErrorSign
	_CPRErrorSign::_CPRErrorSign(unsigned short dwTimePos, float fDevicePos, _eCPRErrorSign eErrorSign) 
	{ 
		
	}
}}}
