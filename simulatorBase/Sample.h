#pragma once
#include <string>
#include <atlconv.h>
#include <objbase.h>
#include <windows.h>
#include ".\simulatorbase_global.h"

/////////////////////////////////////modified hjg/////////////////////////////////////////////////////
namespace jysoft { namespace simulator {

    class SIMULATORBASESHARED_EXPORT CSample
	{
		enum _Heap_Alloc_Type
		{
			Customized,            //此类专用内存分配句柄，由此类收回
			ExternalDeliver        //外部传递来的内存分配句柄，由外部对象收回
		};
	private:
		unsigned long              m_dwID;//标志号
	public:
		int                m_iSampleSec; //每秒的采样率
		int                m_iSampleVolt;//每伏特的采样率
	private:
		HANDLE             m_hHandle;
		_Heap_Alloc_Type   m_eAllocType;
		unsigned long              m_dwGlobalSize; //总分配的数据总数
	public:
		float *            m_pPtrData;
		unsigned long              m_dwSize;       //有效数据
	public:
		CSample(void);
		CSample( HANDLE hAllocHeap, int nAllocSize );
		CSample(unsigned long dwID);
		CSample( HANDLE hAllocHeap, unsigned long dwID, int nAllocSize);
		virtual ~CSample(void);
	public://主要函数
		inline bool  IsEmpty() const { return m_dwGlobalSize == 0 || m_pPtrData == NULL || m_dwSize == 0;};
		inline unsigned long GetSampleID() { return m_dwID;};
		//加载文件中的采样数据
        bool CSample::LoadSampleDataFromTxt(const std::string &strPathFile);
		bool LoadSampleDataFromStream(LPSTREAM lpFileSteam);
		void ChangeSampleData(float *fSrcBegin,const int nCount,int nBeginTime);
		//拷贝
		void Clone(CSample *pOrgSample);
		void Clone(CSample *pSrcSample,float *fpBegin,float *fpEnd);
		void ResetSample(void);
		//分配数据空间
		void AllocSample(unsigned long  dwGlobalSize);
		//返回采样段的时间
		int  GetSampleSumTime();
		//根据时间返回采样点的指针
		float *GetSamplePtr(int  iTime);
		//根据X轴的长度，返回此长度所代表的时间
		int GetSampleTime(float fX);
		//根据指针，返回此位置所代表的时间
		int GetValidTime(float *pfPos,int nBeginTime);
		//根据时间，返回长度
		float GetLength(int nTime);
		//返回采样的点数 
		//int nTime：单位0.1微秒
		inline int   GetSampleNum(int nTime) {return int(nTime * m_iSampleSec*1e-4);};
		//根据Y轴的数值，返回表示的电压(单位：毫伏)
		float GetMilliVolt(float fH);
		//根据电压(单位：毫伏)，返回Y轴的数值
		float GetYFromMilliVolt(float fMillVolt);
		void  AddSampleData(int nDstBeginTime, int nTime, float fValue);
		void  AddSampleData(int nDstBeginTime, int nTime, float fBeginValue, float fEndValue);
		void  AddSampleData(int nDstBeginTime, CSample *pSrcSample,float *fpBegin,float *fpEnd);
		void  OverlapSampleData(int nDstBeginTime,int nLogicTime,CSample *pSrcSample,float *fpBegin,float *fpEnd);
		void  HoriIntervalLinkSampleData(int nExtendTime, float fValue, bool bHorDirect=true);
		//水平延长到指定时间长度
		//int nTime：单位0.1微秒
		void  HoriExtendSampleData(int nTime);
		//将电压值转换成对应的BYTE值
        static int  ModifyVoltToLogicValue(const float *pBeginPtr, long uSrcSize,/*out*/unsigned char *pDstPtr, int iRate = 1);
		//调整采样曲线
		void  AdjustSampleData(float fData);
		//将采样数据转换为8bit采样的数据
		void  ChangeSampleDataTo8Big();
		//除噪
		void  RidSampleYawp(int nBeginTime, int nValidTime);
		//*******************************************************************************************************
		//*********注：以下函数的开始位置都为起点，有效时间为所有采样点******************************************/
		//缩放采样数据处理
		void  ZoomSampleDataHandle(int iChgedTime);
		//切割采样数据处理
		void  CutSampleDataHandle(int iPosTime, bool bRmvPostion);
		//void  AddDirectSampleData(CSample *pSrcSample);
		//添加pSrcSample中的数据
		void  DirectLinkSampleData(CSample *pSrcSample);
		//水平间隔连接操作
		void  HoriIntervalLinkSampleData(CSample *pSrcSample,int nIntervalTime, float fValue);
		//直线间隔连接操作
		void  LineIntervalLinkSampleData(CSample *pSrcSample,int nIntervalTime);
		//区域叠加操作
		void  OverlapLinkSampleData(CSample *pSrcSample,int nOverlapTime);
		//起始位置叠加操作
		void  DirectOverlapLinkSampleData(const CSample *pSrcSample);
		//起始位置覆盖操作
		void  DirectCoverLinkeSampleData(const CSample *pSrcSample);
	};

}}
