#pragma once
#include ".\cprmoduls_global.h"

#include "..\Common\CommonGlobal.h"


namespace jysoft{  namespace cpr 
{
	//数值对照表，虚类
    class CPRMODULSSHARED_EXPORT CVirCollate
	{
	public:
		CVirCollate(void);
		virtual ~CVirCollate(void);
	protected:
		int           m_nMaxValue;    //最大值
		int           m_nMinValue;    //最小值
	public:
		void changeJudgeRange(int nMaxValue, int nMinValue);
		inline int getMaxValue() { return m_nMaxValue; };
		inline int getMinValue() { return m_nMinValue; };
		//返回是否深度正确
        bool judgeIsDepthRight(const _CPRData &cprData, short vVersion = 0) const;
	public:
		//判断是否超出
        virtual bool judgeIsOver(const _CPRData &cprData, short vVersion = 0) const = 0;
		//判断是否过低
        virtual bool judgeIsLower(const _CPRData &cprData, short vVersion = 0) const = 0;
		//返回逻辑值
        virtual int  getLogicalValue(const _CPRData &cprData, short vVersion = 0) const = 0;
	};

	//--------------------------------------------------------------------------
	//按压对照表类
    class CPRMODULSSHARED_EXPORT CPressureCollate : public CVirCollate
	{
	public:
		CPressureCollate();
		virtual ~CPressureCollate();
	public:
		//判断是否超出
        virtual bool judgeIsOver(const _CPRData &cprData, short vVersion = 0) const ;
		//判断是否过低
        virtual bool judgeIsLower(const _CPRData &cprData, short vVersion = 0) const;
		//返回逻辑值
        virtual int  getLogicalValue(const _CPRData &cprData, short vVersion = 0) const;
	public:
		//判断按压位置错误
		bool  isPressurePositionError(const _CPRData &cprData) const;
		//判断按压释放不足
		bool  isIncompleteError(const _CPRData &cprData) const;
		//判断是否按压频率错误
		bool  isPressureRateError(const _CPRData &cprData) const;
	};

	//-------------------------------------------------------------------------
	//吹气对照表类
    class CPRMODULSSHARED_EXPORT CBreathCollate : public CVirCollate
	{
	public:
		CBreathCollate();
		virtual ~CBreathCollate();
	protected:
		//最小、最大通气时间(单位：100ms)
		int      lowerRespTime;
		int      overRespTime;
	public:
		//判断是否超出
        virtual bool judgeIsOver(const _CPRData &cprData, short vVersion = 0) const;
		//判断是否过低
        virtual bool judgeIsLower(const _CPRData &cprData, short vVersion = 0) const;
		//返回逻辑值
        virtual int  getLogicalValue(const _CPRData &cprData, short vVersion = 0) const;
	public:
		//判断是否进胃
		bool isToStomach( const _CPRData &cprData ) const;
		//判断通气时间是否超出
        virtual bool judgeIsRespTimeOver(const _CPRData &cprData, short vVersion = 0) const ;
		//判断通气时间是否过低
        virtual bool judgeIsRespTimeLower(const _CPRData &cprData, short vVersion = 0) const ;
	};
}}
