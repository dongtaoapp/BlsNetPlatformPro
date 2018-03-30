#include ".\Collates.h"

#include "..\Common\ParseCPRData_Singleton.h"


namespace jysoft{  namespace cpr 
{
	CVirCollate::CVirCollate(void)
	{
		m_nMaxValue = m_nMinValue = 0;
	}

	CVirCollate::~CVirCollate(void)
	{
	}

	void CVirCollate::changeJudgeRange(int nMaxValue, int nMinValue)
	{
		m_nMaxValue = nMaxValue;
		m_nMinValue = nMinValue;
	}


	//返回是否深度正确
    bool CVirCollate::judgeIsDepthRight(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		if( judgeIsOver(cprData, vVersion) || judgeIsLower(cprData, vVersion) )
		{
			return false;
		}
		return true;
	}
	//----------------------------------------------------------------------------------------------
	//按压对照表类
	CPressureCollate::CPressureCollate()
	{
		m_nMaxValue = 60; //单位:mm
		m_nMinValue = 50; //单位:mm
	}

	CPressureCollate::~CPressureCollate()
	{

	}

	//判断是否超出
    bool CPressureCollate::judgeIsOver(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		if( getLogicalValue(cprData, vVersion) > m_nMaxValue )
		{
			return true;
		}
		return false;
	}

	//判断是否过低
    bool CPressureCollate::judgeIsLower(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		if( getLogicalValue(cprData, vVersion) < m_nMinValue )
		{
			return true;
		}
		return false;
	}

	//返回逻辑值
    int  CPressureCollate::getLogicalValue(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		int     nPressureDepth, cData;
		tie(cData, tuples::ignore) = CParseCPRData_Singleton::get_const_instance().getPressureSample(cprData);
		float   k[4];
		k[0] = 30.0/35.0f;             //注： 0~30mm
		k[1] = (50-30.0f)/(68-35.0f);  //注：30~50mm
		k[2] = (58-50.0f)/(90-68.0f); //注：50~58mm
		k[3] = k[2]*3/4;
		//不同的区间用不同的斜率
		if( cData <= 35 )
		{
			nPressureDepth = k[0] * cData;
		}
		else if( cData > 35 && cData < 68 )
		{
			nPressureDepth = k[1] * (cData - 35) + 30;
		}
		else if( cData >= 68 && cData < 90 )
		{
			nPressureDepth = k[2] *(cData - 68) + 50;
		}
		else
		{
			nPressureDepth = k[3] * (cData - 90) + 58;
		}
		return nPressureDepth * 1.08;
	}

	//判断按压位置错误
	bool  CPressureCollate::isPressurePositionError(const _CPRData &cprData) const
	{
		dynamic_bitset<>  pos(_CPR_ORDER_L, 0x00);
		tie(tuples::ignore, pos, tuples::ignore) = CParseCPRData_Singleton::get_const_instance().getPressureScopeValue(cprData);
		return pos.none() ? false : true;
	}

	//判断按压释放不足
	bool  CPressureCollate::isIncompleteError(const _CPRData &cprData) const
	{
		bool completeRight = true;
		tie(tuples::ignore, tuples::ignore, completeRight) = CParseCPRData_Singleton::get_const_instance().getPressureScopeValue(cprData);
		return completeRight ? false : true;
	}

	//判断是否按压频率错误(频率范围：100 ~ 120)
	bool  CPressureCollate::isPressureRateError(const _CPRData &cprData) const
	{
		int  rate = 0;
		tie(rate, tuples::ignore) = CParseCPRData_Singleton::get_const_instance().getPressureRateValue(cprData);
		if( rate == 0 || (rate >= 100 && rate <= 120) )
		{
			return true;
		}
		return false;
	}
	//----------------------------------------------------------------------------------------------
	//吹气对照表类
	CBreathCollate::CBreathCollate()
	{
		m_nMaxValue = 1000; //单位:ml
		m_nMinValue = 500;  //单位:ml
		//通气时间范围(单位：100ms)
		lowerRespTime = 5;
		overRespTime  = 60;
	}

	CBreathCollate::~CBreathCollate()
	{

	}

	//判断是否超出
    bool CBreathCollate::judgeIsOver(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		if( getLogicalValue( cprData, vVersion ) > m_nMaxValue )
		{
			return true;
		}
		return false;
	}

	//判断是否过低
    bool CBreathCollate::judgeIsLower(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		if( getLogicalValue( cprData, vVersion ) < m_nMinValue )
		{
			return true;
		}
		return false;
	}

	//返回逻辑值
    int  CBreathCollate::getLogicalValue(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		int   nBreathVolume, cData;
		tie(cData, tuples::ignore) = CParseCPRData_Singleton::get_const_instance().getBreathSample(cprData);
		if( cData <= 12 )
			nBreathVolume = cData * 150 / 12;
		else if( cData <= 18 )
			nBreathVolume = (cData-12)*(500-150)/(18-12) + 150;
		else if( cData <= 35 )
			nBreathVolume = (cData-18)*(1000-500)/(35-18) + 500;
		else
			nBreathVolume = cData * 1500 / 35;
		return nBreathVolume;
	}

	//判断是否进胃
	bool CBreathCollate::isToStomach( const _CPRData &cprData ) const
	{
		bool  bToStomach = false;
		tie(tuples::ignore, bToStomach) = CParseCPRData_Singleton::get_const_instance().getBreathScopeValue(cprData);
		return bToStomach;
	}

	//判断通气时间是否超出
    bool CBreathCollate::judgeIsRespTimeOver(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		int   sRespTime = 0;
		tie(sRespTime, tuples::ignore, tuples::ignore)  = CParseCPRData_Singleton::get_const_instance().getBreathRateValue(cprData);
		if( sRespTime > overRespTime )
		{
			return true;
		}
		return false;
	}

	//判断通气时间是否过低
    bool CBreathCollate::judgeIsRespTimeLower(const _CPRData &cprData, short vVersion/*=0*/) const
	{
		int   sRespTime = 0;
		tie(sRespTime, tuples::ignore, tuples::ignore) = CParseCPRData_Singleton::get_const_instance().getBreathRateValue(cprData);
		if( sRespTime < lowerRespTime )
		{
			return true;
		}
		return false;
	}

}}
