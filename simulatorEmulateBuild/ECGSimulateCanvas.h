#pragma once
#include ".\simulatoremulatebuild_global.h"

#include "..\Common\EmulateTimer.h"
#include "..\common\criticalmutex.h"
#include "..\Common\CommonGlobal.h"
#include "..\Common\LineBuffer.h"

#include "..\SimulatorBase\IGetPhysioloySimulateData.h"
#include "..\SimulatorBase\IDistributeSimulateData.h"
#include "..\SimulatorBase\IPaneMoveControlInterface.h"


namespace jysoft { namespace simulator { namespace ecg {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     心电图实时数据分发类
	创建人：	 hjg
	创建时间：   2008/8/19
	//-----------------------------------------------------------------------------------------------------------------*/

    class  SIMULATOREMULATEBUILDSHARED_EXPORT CECGSimulateCanvas
	{
	public:
		CECGSimulateCanvas(void);
		virtual ~CECGSimulateCanvas(void);
	protected:
		I12LeadSample                      m_fTempBuffer[100];      //临时数据读取缓冲
		IGetEcgSimulateData *              m_pGetECGSimulateData;   //心电图数据获取接口
		IDistributeEcgLeadsSimulateData *  m_pDistributeECGData;    //心电图数据派发接口
		utility::IPaneMoveControlInterface *m_pPaneMoveControl;
		//------------------------------------------------------------------------------------------
		utility::CLineBuffer<float>  m_cPressureDisturbDatas; //按压时干扰心电图的数据
	private:
		int                            m_iMilliTime;      //单位：0.1ms
		utility::CCriticalMutex        m_cMutex;
		bool                           m_bStartDistribute;       //是否开始派发
		bool                           m_bPressureAct;          //按压开始\结束(TRUE:开始；FALSE:结束)
		//-------------------------------------------------------------------------------------------------
		utility::CEmulateTimer*        t;
	public:
		//停止计数处理
		void StopTimerHandle();
	public:
		void InitialEcgSimulate(IGetEcgSimulateData *pGetEcgSimulateData, utility::IPaneMoveControlInterface *pMoveControlInterface, const std::string &resPath, int iMilliTime = 400);
		//释放钩子
		void FreeHook();
		// 开始分发心电图实时数据
		void StartDistributeSimulateData();
		//分发采样数据
		void OnDistributeSimulateDataHandle();
		//停止分发心电图实时数据
		void StopDistributeSimulateData();
		//设置按压开始\结束状态(TRUE:开始；FALSE:结束)
		void SetPressureActState(bool bState);
	public:
		//开始监视心电图波形
		void OnStartWatchEcg(IDistributeEcgLeadsSimulateData *pDistributeECGData);
		//断开与心电图的监控
		void OnCutWatchEcg(IDistributeEcgLeadsSimulateData *pCutDistributeECGData);
	private:
		//初始化加载按压时干扰心电图的数据
		void InitialLoadPressureDisturbDatas( const std::string &strDisturbDataFile );
		//叠加按压时干扰心电图的数据
		void OverlapPressureDisturbData(I12LeadSample *pEcgLeadSamples, short  dwNumber);
	};

}}}
