#pragma once
#include <boost/thread.hpp>
#include ".\simulatoremulatebuild_global.h"
#include ".\EcgLeadSamples.h"
#include ".\EcgCycleLeadsBuild.h"
#include ".\ExtrasystSignBuildInterface.h"
#include ".\SpO2SignBuildInterface.h"

#include "..\Common\VirBuffer.h"
#include "..\Common\LoopBuffer.h"
#include "..\Common\ECGParams.h"

#include "..\SimulatorBase\IPhysiologyStartSign.h"
#include "..\SimulatorBase\IGetPhysioloySimulateData.h"
#include "..\SimulatorBase\VirCardiogramParaFactory.h"
#include "..\SimulatorBase\ITransportOrderIrpToSimulator.h"
#include "..\SimulatorBase\OpECGBuildInterface.h"
#include "..\SimulatorBase\SimulatorOrderIrp.h"
#include "..\SimulatorBase\IHeartStartSign.h"
#include "..\SimulatorBase\ICardiogramLeads.h"


namespace jysoft { namespace simulator { namespace ecg {

    class SIMULATOREMULATEBUILDSHARED_EXPORT CCardiogramBuild : public IGetEcgSimulateData
										 , public base::COpECGBuildInterface
	{
	protected:
		enum _NEXTCYCLESTATE
		{//下一周期的状态
			NC_Rhythm = 0,  //下一周期为原来的状态
			NC_Change      //下一周期改为其他状态
		};
	public:
		CCardiogramBuild( );
		~CCardiogramBuild(void);
	protected: //COpECGBuildInterface基类函数重载
		/*******************************************************************************/
		// 函数名称： DirectModifyECGHandle
		// 功能： 直接修改心电图
		// 参数： CECGParams *pECGParams
		//注： 对心电图Build初始化构造时也用此函数
		// 返回值:  
		virtual void DirectModifyECGHandle(const CECGParams &cECGParams);
		/*******************************************************************************/
		// 函数名称： ModifyECGInDefibrEventHandle
		// 功能： 因为除颤而修改波形
		// 参数： CECGParams *pECGParams
		// 返回值:  
		virtual void ModifyECGInDefibrEventHandle(const CECGParams *pECGParams);
		/*******************************************************************************/
		// 函数名称： ModifyECGHandle
		// 功能： 修改心电图
		// 参数： CECGParams *pECGParams:       
		// 返回值:  
		virtual void ModifyECGHandle(const CECGParams &cECGParams);
	public:
		/*******************************************************************************/
		// 函数名称： getIGetEcgLeadSimulateDataPtr
		// 功能： 返回IGetEcgSimulateData接口指针
		// 参数： 
		// 返回值: 
		virtual simulator::IGetEcgSimulateData * getIGetEcgLeadSimulateDataPtr() { return dynamic_cast<simulator::IGetEcgSimulateData *>(this); };
		/*******************************************************************************/
		// 函数名称： OnInitializeBuild
		// 功能： 初始化心电图构造器
		// 参数： CECGParams *pECGParams:       
		// 返回值:  
		virtual bool OnInitializeBuild(const CECGParams &cECGParams);
	public: //接口IGetEcgSimulateData函数重载
		/*******************************************************************************/
		//功能：获取滑块区域内的各导联曲线数据
		//参数：int iMilliTime:             时间（0.1豪秒）
		//      I12LeadSample *pcBuffer:    返回的各导联曲线数据
		//返回值:  曲线数据的长度
		virtual unsigned long GetI12LeadEcgSimulateData(int iMilliTime, /*out*/I12LeadSample *pcBuffer = NULL);
	public:
		/*******************************************************************************/
		// 函数名称： SetEcgBuildRelateInterfacesPtr
		// 功能： 设置心电图构造相关指针
		// 参数： 
		//        ITransportOrderIrpToSimulator *pPtrTransportLayer:
		//        IPhysiologyStartSign *pSpO2SignPtr:  
		//        SimulatePatientType ePateintType:    模拟人类别
		// 返回值: 
		void SetEcgBuildRelateInterfacesPtr(IPhysiologyStartSign *pSpO2SignPtr, const std::string &resPath, transLayer::ITransportOrderIrpToSimulator *pPtrTransportLayer, SimulatePatientType ePateintType);
		// 初试化心电图构造器
		bool InitializeBuild(const CECGParams &cECGParams);
		//插入心脏启动信号接口
		void InsertHeartStartSignPtr(IHeartStartSign  *pInterface);
		void RemoveHeartStartSignPtr(IHeartStartSign  *pInterface);
		//设置是否忽略心电链接检查
		void Set_IsClearEcgWatchLink(bool bClear);
		//设置心电链接检查状态
		void Set_EcgWatchLinkState(bool bLinking);
		//关闭心电图构造器
		void CloseCardiogramBuild();
		//创建下个周期的数据
		void BuildNextCycleCardiogram();
		bool CreateCardiogram(const CECGParams *ptrParam, /*out*/CEcgLeadSamples *pDestLeadsSample);
		bool CreateExtrasyst(Extrasys eExtrasyst, /*out*/CEcgLeadSamples *pDestLeadsSample);
		//获取心电图的数据缓冲区的数据
		template<class T> void GetBufferData(utility::CVirBuffer<T> *pcBuffer, short dwReadNum)
		{
			boost::mutex::scoped_lock  lock(muEcgData);
			m_DataBuffer.ReadDataToBuffer(pcBuffer,dwReadNum);
		};
	public:
		// 返回数据刷新的速度，即滑块移动的速度（单位：毫米/秒）
		int GetMoveSpeed(void);
		//返回是否已初始化
		inline bool IsInitialCardiogramBuild() { return m_bInitialed;};
		//根据心电链接状态，返回是否显示心电数据
		bool IsShowEcgByLinkState();
		//返回当前周期时间(单位：0.1毫秒)
		inline int Get_nCycleTime() { return m_iCycleTime; };
	protected:
		/*******************************************************************************
		//功能：组合下周期的数据
		//返回值:  数据的长度
		*********************************************************************************/
		short CombinNextCycleCurveData(bool changeInDefibr = false);
		//添加肌颤或50/60HZ时的数据
		void  CombineArtifactData(Artifact eArtiface, float *fptrBegin, float *fptrEnd);
		//判断及启动血氧的信号; int iMilliTime:   时间（0.1豪秒）
		void  JudgeSpO2Sign(ICardiogramLeads  *pVirEcgLeads, int  iMilliTime);
	public:
		//返回除颤引起的电流饱和时间
		int   GetDefibrillateActDelayTime();
protected:
		//返回三角周期的Y值
		static float* GetTriangleCycleData(int nFrequent, unsigned int &uCycleNum);
		//实施了一次除颤
		void DefibrillateAct();
		//由于除颤而引起的心电图参数修改
		void DirectModifyCardiogramInDefibrState(const CECGParams * ptrParam);
		//直接修改心电图参数 2006/11/2 hjg 添加
		void DirectModifyCardiogram(const CECGParams * ptrParam);
		//更新心率
		void UpdateShowHR(ICardiogramLeads  *pVirEcgLeads);
		//心脏跳动信号发送
		void SendHeartStartSign(bool   bHaveHeartSign);
	private:
		bool CreateCardiogram(ICardiogramLeads *pVirEcgLeads, /*out*/CEcgLeadSamples *pDestLeadsSample);
	private:
		bool                                     m_bInitialed;        //是否已经初始化产生器
		CSpO2SignBuildInterface                  m_cSpO2SignBuildInterface;
		IPhysiologyStartSign *                   m_pPhysiologyStartSignPtr;
		bool                                     m_bClearWatchLink;    //是否忽略心电链接检查
		bool                                     m_bLinkWatchEcg;
	protected:
		CExtrasystSignBuildInterface             m_cExtrasystSignInterface;
		IHeartStartSign *                        m_pHeartStartSignAgg;
	protected:
		transLayer::ITransportOrderIrpToSimulator *m_pPtrTransportLayer;
		CVirCardiogramParaFactory *                m_pParamFactory;
		CEcgCycleLeadsBuild                        m_cCycleLeadsBuild;
		_NEXTCYCLESTATE                            m_eNextCycleState;
		CECGParams                                 m_cParams;
		CEcgLeadSamples                            m_cLeadsSampleBuff[2];
		bool                                       m_bCardiogramModifyed[2];
		int                                        m_iCycleTime; //周期时间 
		//事件句柄
		utility::CLoopBuffer<I12LeadSample>      m_DataBuffer;        //心电图的数据缓冲区
		boost::mutex                             muEcgData;
		boost::mutex                             muHeartStartSign;
		boost::mutex                             muSwapMutex;
		boost::mutex                             muCardiogramParamMutex;
		boost::mutex                             muDirectEcgModifyMutex;
		//-----------------------------------------------------------------------------------------
		unsigned short                           m_uArtifactNum;       //肌颤时的取数量
	};
}}}
