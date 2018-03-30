#pragma once
#include ".\cprmoduls_global.h"
#include <boost/date_time/posix_time/posix_time.hpp>

#include "..\Common\CommonGlobal.h"


using namespace boost::posix_time; 
//-----------------------------------------------------------------------------------------------------------------------
struct CPRMODULSSHARED_EXPORT _StatDataSeg
{//����ͳ�ƶνṹ
public:
	time_duration     segBeginTime; //��ʼʱ��
	time_duration     segPeriod;    //ʱ������
	short             average;      //����ֵ(ע������ƽ��ָ��Ҫ��sunNum)
	short            sumNum;    //�ܵĴ���
	short            rightNum;  //��ȷ����
	short            sumErrorNum; //�ܴ������(����CPR����ļ���)
	//������ȷ����ѹ: 5~6cm; ����: 500 ~1000ml��
	short            overNum;   //����
	short            lackNum;   //����
	//CPR����30:2, �����������ٵ�����
	short            lackSumNum; //��ѹ/������������
	short            overSumNum; //��ѹ/������������
	//--------------------------------------------------------------------------------
	bool              bValidate;  //ͳ���Ƿ���Ч
public:
	_StatDataSeg()
	{
		::memset(this, 0, sizeof(_StatDataSeg));
	};
public:
	void clone(const _StatDataSeg &sourceSeg);
	//����ƽ��ֵ��ƽ����ȡ�ƽ����������
	short getAverageValue() const { return sumNum == 0 ? 0 : short(average/ sumNum); };
	//���ط�����ȷ����
	short getRightDepthNum() { return sumNum - overNum - lackNum; };
	//����ƽ��Ƶ��
	short getAverageRate() const;
	//�ܵĴ���
	short getSumCount() const { return sumNum; };
    //��������
	short getSumErrorsNum()const { return sumErrorNum; };
protected:
	//����
	void resetBase();
};

//��ѹ�׶�ͳ�ƽ��
struct CPRMODULSSHARED_EXPORT _StatPressueSeg : public _StatDataSeg
{
public:
	short                   incompleteNum;    //��ѹʱ����ȫ�ͷ�
	short                   posErrorNum;      //��ѹλ���ܴ���
	short                   posErr_low;       //��ѹλ��̫��
	short                   posErr_high;      //��ѹλ��̫��
	short                   posErr_right;     //��ѹλ��̫��
	short                   posErr_left;      //��ѹλ��̫��
	//��ȷƵ�ʷ�Χ(100~120/����)�ڵĸ���
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
	//����
	void reset();
};

//�����׶�ͳ�ƽ��
struct CPRMODULSSHARED_EXPORT _StatBreathSeg : public _StatDataSeg
{
public:
	short                    ventiOverTimeNum;   //ͨ��ʱ�����
	short                    ventiLowerTimeNum;  //ͨ��ʱ�����
	short                    stomachNum; //��θ
	short                    pipeCloseNum;//�����ر�
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
	//����
	void reset();
};

namespace jysoft{  namespace cpr {  namespace cprShow
{
    struct CPRMODULSSHARED_EXPORT _CPRErrorSign
	{//CPR��������״̬��ʾ
	public:
		float           m_fDevicePos;
		unsigned short  m_dwTimePos;
		_eCPRErrorSign  m_eErrorSign;
	public:
		_CPRErrorSign(unsigned short dwTimePos, float fDevicePos, _eCPRErrorSign eErrorSign);

	};
}}}
