#pragma once
#include <string>
#include <windows.h>


namespace jysoft { namespace simulator { namespace resp {

    /*-----------------------------------------------------------------------------------------------------------------
    ��˵����     �������ڷ�Ϊ�����κͺ����Σ�����Ϊ���ݲ�������
    �����ˣ�	 hjg
    ����ʱ�䣺   2017/2/23
    //-----------------------------------------------------------------------------------------------------------------*/

    class CVirtualRespSegment
    {
        friend class CVirtualRespSegment;
    public:
        CVirtualRespSegment(void);
        virtual ~CVirtualRespSegment(void);
    protected:
        int             m_iSampleSec;      //ÿ��Ĳ�����
        float           m_fRemainVolume;   //������������λ��ml��
        float           m_fSumVolume;      //�������  ����λ��ml��
    protected:
        HANDLE          m_hHandle;
        float           *m_pPtrData;
        short           m_dwGlobalSize; //�ܷ������������
        short           m_dwSize;       //��Ч����
        bool            m_bEmpty;       //�Ƿ�Ϊ��
    public:
        inline bool  IsEmpty() { return m_bEmpty;};
        //���ز����ĵ���
        //int nTime����λ0.1΢��
        inline int   GetSampleNum(int nTime) {return int(nTime * m_iSampleSec*1e-4);}
        //���ز����ε�ʱ��
        int  GetSampleSumTime();
        //����ʱ�䷵�ز������ָ��
        float *GetSamplePtr(int  iTime);
        //���ز������ָ��
        inline float * GetSamplePtr() {return m_pPtrData;};
        //���ز�������Ŀ
        inline short GetSampleSumNumber() { return m_dwSize; };
        //���ز�����������λ��ml��
        inline float Get_RemainRespVolume() { return m_fRemainVolume; };
        //�����������  ����λ��ml��
        inline float Get_SumRespVolume() { return m_fSumVolume; };
    public:
        /*******************************************************************************/
        //���ܣ� �����ļ��ڵĺ�������
        //������ const CString &strFilePath: �����ļ�·��
        //����ֵ:
        virtual bool LoadSegmentData(const std::string &strFilePath);
        //����Ϊ��
        void ResetEmptySegment();
        //����
        void Clone(CVirtualRespSegment *pOrgRespSegment);
        /*******************************************************************************/
        // �������ƣ� ZoomSegmentDataHandle
        // ���ܣ� ���Ų������ݴ���
        // ������ int iMilliChgedTime: ѹ������ʱ��(��λ:0.1ms)
        // ����ֵ:
        //         ע�����º����Ŀ�ʼλ�ö�Ϊ��㣬��Чʱ��Ϊ���в�����
        void  ZoomSegmentDataHandle(int iMilliChgedTime) ;
    public:
        /*******************************************************************************/
        // �������ƣ� ZoomRespVolumeHandle
        // ���ܣ� ͬ��ӳ�䷽ʽ�޸Ĳ�������
        // ������ float fRemainVolume��������������λ��ml��
        //        float fSumVolume ��  �������  ����λ��ml��
        // ����ֵ:
        virtual void ZoomRespVolumeHandle(float fRemainVolume, float fSumVolume) ;
    public:
        virtual bool isKindOf(const std::string &className ) = 0;
    protected:
        /*******************************************************************************/
        // �������ƣ� GetVolumeMessageFromSegmentData
        // ���ܣ� �ɲ������ݻ�ȡ��ǰ�Ĳ��������ͳ�����
        // ������ [out]float &fRemainVolume��������������λ��ml��
        //        [out]float &fSumVolume ��  �������  ����λ��ml��
        // ����ֵ:
        virtual void GetVolumeMessageFromSegmentData(float &fRemainVolume, float &fSumVolume) = 0;
        //�������ݿռ�
        void AllocSample(unsigned long  dwGlobalSize);
    };
}}}
