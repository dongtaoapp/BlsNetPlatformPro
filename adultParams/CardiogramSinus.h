#pragma once

#include "..\SimulatorBase\ICardiogramLeads.h"


namespace jysoft { namespace simulator { namespace ecg {

    /*-----------------------------------------------------------------------------------------------------------------
    ��˵����     Sinus�ĵ�ͼ��ͬ��������������
    �����ˣ�	 hjg
    ����ʱ�䣺   2013/5/13
    //-----------------------------------------------------------------------------------------------------------------*/
class CCardiogramSinus  : public ICardiogramLeads
    {
    public:
        CCardiogramSinus( IStorage *pRootStorage );
        virtual ~CCardiogramSinus(void);
    public:  //�ӿ�ICardiogramLeads��������
        /*******************************************************************************/
        // �������ƣ� LoadCardiogramLeadsParam
        // ���ܣ� �����ĵ�ͼ�������Ĳ���ֵ
        // ������
        //
        // ����ֵ:
        virtual bool LoadCardiogramLeadsParam( BasicRhythm eRhythm, int uHR, short sConduct = 0, short sExtendParam = 0 );
        /*******************************************************************************/
        // �������ƣ� ReLoadCardiogramParam
        // ���ܣ�
        // ������
        // ����ֵ:
        virtual void ReLoadCardiogramParam();
        /*******************************************************************************/
        // �������ƣ� IsCanExpressCardiogramParam
        // ���ܣ� ���ݴ�����ĵ�ͼ�������Ƿ����ô˶���õ������ĵ�ͼ����Ҫ�Ĳ�����
        // ������
        // ����ֵ:
        virtual bool IsCanExpressCardiogramParam(BasicRhythm eRhythm, int uHR);
        /*******************************************************************************/
        // �������ƣ� SeteRefurbishDataRange
        // ���ܣ� �趨�������ݵĳ̶�
        // ������
        // ����ֵ:
        virtual void SeteRefurbishDataRange(_eRefurbishDataRange eRange);
        // ���ع������ݵĳ̶������ö��ֵ��RD_LoadConfigFile���RD_NoChange��ǳ��
        virtual _eRefurbishDataRange GeteRefurbishDataRange();
    public:
        //�Ƿ���ȱʡ���粥
        virtual bool IsHaveDefalutExtrasyst() {return true;};
        virtual void LoadExtrasystParamPre(Extrasys eExtrasyst);
        virtual void LoadExtrasystParam(Extrasys eExtrasyst) ;
    public:
        static bool IsCanParamExpress(BasicRhythm eRhythm, int uHR);
    };

}}}
