#pragma once
#include "..\common\criticalmutex.h"

#include "..\SimulatorBase\IPaneMoveControlInterface.h"


namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     受控实时数据分发类
	创建人：	 hjg
	创建时间：   2008/8/19
	//-----------------------------------------------------------------------------------------------------------------*/

	class IGetPhysioloySimulateData;
	class IDistributeSimulateData;
	class CGeneralSimulateControledCanvas : public utility::IPaneMoveControlInterface
	{
	public:
		CGeneralSimulateControledCanvas(void);
		virtual ~CGeneralSimulateControledCanvas(void);
	protected:
		float                          m_fTempBuffer[100];    //临时数据读取缓冲
		IGetPhysioloySimulateData      *m_pGetSimulateData;   //心电图数据获取接口
		IDistributeSimulateData        *m_pDistributeData;    //心电图数据派发接口
	private:
		utility::CCriticalMutex        m_cMutex;
		int                            m_iMilliTime;      //单位：0.1ms
		BOOL                           m_bStartDistribute;
	public:
		void InitialSimulate(IGetPhysioloySimulateData *pGetSimulateData, int iMilliTime = 400);
	protected:
		//移动快滑动操作
		virtual void PaneMoveOp();
		// 开始绘心电图
		virtual void Start(bool bClear);
	public:
		//开始监视时实波形
		void OnStartWatchPhyst(IDistributeSimulateData *pDistributeData);
		//断开与时实的监控
		void OnCutWatchPhyst(IDistributeSimulateData *pCutDistributeData);
	};
}}