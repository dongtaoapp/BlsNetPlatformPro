#pragma once
#include ".\simulatoremulatebuild_global.h"

#include "..\Common\EmulateTimer.h"
#include "..\common\criticalmutex.h"

#include "..\SimulatorBase\IPaneMoveControlInterface.h"

namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     呼吸实时数据分发类
	创建人：	 hjg
	创建时间：   2008/7/16
	//-----------------------------------------------------------------------------------------------------------------*/

	class IGetRespSimulateData;
	class IDistributeRespSimulateData;
    class SIMULATOREMULATEBUILDSHARED_EXPORT CRespSimulateCanvas
	{
	public:
		CRespSimulateCanvas();
		~CRespSimulateCanvas(void);
	protected:
		IGetRespSimulateData           *m_pGetSimulateData;
		IDistributeRespSimulateData    *m_pDistributeData;
		utility::IPaneMoveControlInterface      *m_pPaneMoveControl;
	private:
		float                       m_fTempSumLungBuffer[100]; //临时数据读取缓冲
		float                       m_fTempLeftLungBuffer[100];
		int                         m_iMilliTime;      //单位：0.1ms
		utility::CCriticalMutex     m_cMutex;
		bool                        m_bStartDistribute;       //是否开始派发
		//-------------------------------------------------------------------------------------------------
		utility::CEmulateTimer*     t;
	public:
		//停止计数处理
		void StopTimerHandle();
	public:
		void InitialRespSimulate(IGetRespSimulateData *pSimulateData, utility::IPaneMoveControlInterface *pMoveControlInterface, int iMilliTime = 800);
		//释放钩子
		void FreeHook();
		// 开始分发呼吸实时数据
		void StartDistributeSimulateData();
		//分发采样数据
		void OnDistributeSimulateDataHandle();
		//停止分发呼吸实时数据
		void StopDistributeSimulateData();
	public:
		//开始监视呼吸波形
		void OnStartWatchResp(IDistributeRespSimulateData *pDistributeData);
		//断开与呼吸的监控
		void OnCutWatchResp(IDistributeRespSimulateData *pCutDistributeData);
	};
}}
