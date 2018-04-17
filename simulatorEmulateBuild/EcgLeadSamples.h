#pragma once
#include <string>

#include "..\Common\CommonGlobal.h"

#include "..\SimulatorBase\Sample.h"


namespace jysoft { namespace simulator { namespace ecg {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     12种导联心电图单周期数据存贮类
	创建人：	 hjg
	创建时间：   2013/5/16
	//-----------------------------------------------------------------------------------------------------------------*/
	class CEcgLeadSamples
	{
	public:
		CEcgLeadSamples(void);
		virtual ~CEcgLeadSamples(void);
	public:
		/*******************************************************************************/
		// 函数名称： DirectOverlapLinkSampleData
		// 功能： 起始位置叠加操作
		// 参数：  
		//        const CEcgLeadSamples &cSrcLeadSamples:
		// 返回值: 
		void DirectOverlapLinkSampleData( CEcgLeadSamples &cSrcLeadSamples );
		/*******************************************************************************/
		// 函数名称： GetEcgLeadSample
		// 功能： 返回指定导联心电数据
		// 参数： 
		//        RhythmLead  eEcgLeadType:  
		// 返回值:  
		CSample * GetEcgLeadSample(RhythmLead  eEcgLeadType) { return &m_cLeadSample[(int)eEcgLeadType]; };
		/*******************************************************************************/
		// 函数名称： CombineArtifactData
		// 功能： 添加肌颤或50/60HZ时的数据
		// 参数： 
		//        Artifact eArtiface:  
		//        int iCycleTime:  
		//        UINT uArtifactNum:         
		// 返回值:  
		UINT  CombineArtifactData(Artifact eArtiface, int iCycleTime, UINT uArtifactNum);
		/*******************************************************************************/
		// 函数名称： CombineLeadSamples
		// 功能： 整合各导联的数据到数据交互缓冲池，用于输出
		// 参数： 
		//        int nMiliCycleTime:          周期时间(0.1ms)
		// 返回值:  
		I12LeadSample * CombineLeadSamples(int nMiliCycleTime);
		/*******************************************************************************/
		// 函数名称： ClearEcgLeadCycleData
		// 功能： 清除各导联周期时间内的心电图数据，并保留剩余数据
		// 参数： 
		//        int nMiliCycleTime:          周期时间(0.1ms)
		// 返回值:  
		void ClearEcgLeadCycleData(int nMiliCycleTime);
		/*******************************************************************************/
		// 函数名称： CutEcgLeadCycleExtendData
		// 功能： 切除超出周期部分的数据 
		// 参数： 
		//        int nMiliCycleTime:          周期时间(0.1ms)
		// 返回值:  
		bool CutEcgLeadCycleExtendData(int nMiliCycleTime);
		/*******************************************************************************/
		// 函数名称： GetBuildEcgLeadSampleNum
		// 功能： 返回构建的心电图数据数量
		// 参数： 
		//        
		// 返回值: 
		UINT GetBuildEcgLeadSampleNum();
	public:
		/*******************************************************************************/
		// 函数名称： GetSampleNum
		// 功能： 返回采样的点数
		// 参数：  
		//        int nMiliTime：     单位0.1ms
		// 返回值: 
		inline unsigned int  GetSampleNum(int nMiliTime) {return unsigned int(nMiliTime * 400*1e-4);};
		//清空各导联的心电图数据
		void EmptyEcgLeadSamples();
	protected:
		//返回三角周期的Y值
		static float* GetTriangleCycleData(int nFrequent, UINT &uCycleNum);
		//重置临时数据交互缓冲池大小
		void ResetTempBuffSize(DWORD dwSize);
	protected:
		//导联心电数据，依次为：I, II, III, aVR, aVL, aVF, V2, V3, V4, V5, V6
		CSample             m_cLeadSample[12];  
	private:
		I12LeadSample *     m_pTempBuff;          //交互缓冲池
		DWORD               m_dwTempBuffSize;
	};

}}}
