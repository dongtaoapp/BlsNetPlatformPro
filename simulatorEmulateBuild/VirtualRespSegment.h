#pragma once
#include <string>
#include <windows.h>


namespace jysoft { namespace simulator { namespace resp {

    /*-----------------------------------------------------------------------------------------------------------------
    类说明：     呼吸周期分为吸气段和呼出段；此类为数据操作基类
    创建人：	 hjg
    创建时间：   2017/2/23
    //-----------------------------------------------------------------------------------------------------------------*/

    class CVirtualRespSegment
    {
        friend class CVirtualRespSegment;
    public:
        CVirtualRespSegment(void);
        virtual ~CVirtualRespSegment(void);
    protected:
        int             m_iSampleSec;      //每秒的采样率
        float           m_fRemainVolume;   //残留气量（单位：ml）
        float           m_fSumVolume;      //最大气量  （单位：ml）
    protected:
        HANDLE          m_hHandle;
        float           *m_pPtrData;
        short           m_dwGlobalSize; //总分配的数据总数
        short           m_dwSize;       //有效数据
        bool            m_bEmpty;       //是否为空
    public:
        inline bool  IsEmpty() { return m_bEmpty;};
        //返回采样的点数
        //int nTime：单位0.1微秒
        inline int   GetSampleNum(int nTime) {return int(nTime * m_iSampleSec*1e-4);}
        //返回采样段的时间
        int  GetSampleSumTime();
        //根据时间返回采样点的指针
        float *GetSamplePtr(int  iTime);
        //返回采样点的指针
        inline float * GetSamplePtr() {return m_pPtrData;};
        //返回采样点数目
        inline short GetSampleSumNumber() { return m_dwSize; };
        //返回残留气量（单位：ml）
        inline float Get_RemainRespVolume() { return m_fRemainVolume; };
        //返回最大气量  （单位：ml）
        inline float Get_SumRespVolume() { return m_fSumVolume; };
    public:
        /*******************************************************************************/
        //功能： 加载文件内的呼吸数据
        //参数： const CString &strFilePath: 数据文件路径
        //返回值:
        virtual bool LoadSegmentData(const std::string &strFilePath);
        //设置为空
        void ResetEmptySegment();
        //拷贝
        void Clone(CVirtualRespSegment *pOrgRespSegment);
        /*******************************************************************************/
        // 函数名称： ZoomSegmentDataHandle
        // 功能： 缩放采样数据处理
        // 参数： int iMilliChgedTime: 压缩到的时间(单位:0.1ms)
        // 返回值:
        //         注：以下函数的开始位置都为起点，有效时间为所有采样点
        void  ZoomSegmentDataHandle(int iMilliChgedTime) ;
    public:
        /*******************************************************************************/
        // 函数名称： ZoomRespVolumeHandle
        // 功能： 同过映射方式修改采样数据
        // 参数： float fRemainVolume：残留气量（单位：ml）
        //        float fSumVolume ：  最大气量  （单位：ml）
        // 返回值:
        virtual void ZoomRespVolumeHandle(float fRemainVolume, float fSumVolume) ;
    public:
        virtual bool isKindOf(const std::string &className ) = 0;
    protected:
        /*******************************************************************************/
        // 函数名称： GetVolumeMessageFromSegmentData
        // 功能： 由采样数据获取当前的残留气量和潮气量
        // 参数： [out]float &fRemainVolume：残留气量（单位：ml）
        //        [out]float &fSumVolume ：  最大气量  （单位：ml）
        // 返回值:
        virtual void GetVolumeMessageFromSegmentData(float &fRemainVolume, float &fSumVolume) = 0;
        //分配数据空间
        void AllocSample(unsigned long  dwGlobalSize);
    };
}}}
