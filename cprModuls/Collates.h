#pragma once
#include ".\cprmoduls_global.h"

#include "..\Common\CommonGlobal.h"


namespace jysoft{  namespace cpr 
{
	//��ֵ���ձ�����
    class CPRMODULSSHARED_EXPORT CVirCollate
	{
	public:
		CVirCollate(void);
		virtual ~CVirCollate(void);
	protected:
		int           m_nMaxValue;    //���ֵ
		int           m_nMinValue;    //��Сֵ
	public:
		void changeJudgeRange(int nMaxValue, int nMinValue);
		inline int getMaxValue() { return m_nMaxValue; };
		inline int getMinValue() { return m_nMinValue; };
		//�����Ƿ������ȷ
        bool judgeIsDepthRight(const _CPRData &cprData, short vVersion = 0) const;
	public:
		//�ж��Ƿ񳬳�
        virtual bool judgeIsOver(const _CPRData &cprData, short vVersion = 0) const = 0;
		//�ж��Ƿ����
        virtual bool judgeIsLower(const _CPRData &cprData, short vVersion = 0) const = 0;
		//�����߼�ֵ
        virtual int  getLogicalValue(const _CPRData &cprData, short vVersion = 0) const = 0;
	};

	//--------------------------------------------------------------------------
	//��ѹ���ձ���
    class CPRMODULSSHARED_EXPORT CPressureCollate : public CVirCollate
	{
	public:
		CPressureCollate();
		virtual ~CPressureCollate();
	public:
		//�ж��Ƿ񳬳�
        virtual bool judgeIsOver(const _CPRData &cprData, short vVersion = 0) const ;
		//�ж��Ƿ����
        virtual bool judgeIsLower(const _CPRData &cprData, short vVersion = 0) const;
		//�����߼�ֵ
        virtual int  getLogicalValue(const _CPRData &cprData, short vVersion = 0) const;
	public:
		//�жϰ�ѹλ�ô���
		bool  isPressurePositionError(const _CPRData &cprData) const;
		//�жϰ�ѹ�ͷŲ���
		bool  isIncompleteError(const _CPRData &cprData) const;
		//�ж��Ƿ�ѹƵ�ʴ���
		bool  isPressureRateError(const _CPRData &cprData) const;
	};

	//-------------------------------------------------------------------------
	//�������ձ���
    class CPRMODULSSHARED_EXPORT CBreathCollate : public CVirCollate
	{
	public:
		CBreathCollate();
		virtual ~CBreathCollate();
	protected:
		//��С�����ͨ��ʱ��(��λ��100ms)
		int      lowerRespTime;
		int      overRespTime;
	public:
		//�ж��Ƿ񳬳�
        virtual bool judgeIsOver(const _CPRData &cprData, short vVersion = 0) const;
		//�ж��Ƿ����
        virtual bool judgeIsLower(const _CPRData &cprData, short vVersion = 0) const;
		//�����߼�ֵ
        virtual int  getLogicalValue(const _CPRData &cprData, short vVersion = 0) const;
	public:
		//�ж��Ƿ��θ
		bool isToStomach( const _CPRData &cprData ) const;
		//�ж�ͨ��ʱ���Ƿ񳬳�
        virtual bool judgeIsRespTimeOver(const _CPRData &cprData, short vVersion = 0) const ;
		//�ж�ͨ��ʱ���Ƿ����
        virtual bool judgeIsRespTimeLower(const _CPRData &cprData, short vVersion = 0) const ;
	};
}}
