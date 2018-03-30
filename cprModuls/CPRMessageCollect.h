#pragma once
#include ".\Collates.h"
#include ".\CPRSimulateJudgeOp.h"
#include ".\CPRConfigue.h"
#include ".\CPRStatisticImplement.h"

#include "..\Common\EventHandleClockIrpOp.h"
#include "..\Common\RealTimeDataHandleIrpOp.h"

#include "..\SimulatorBase\OpLogInterface.h"
#include "..\SimulatorBase\CPRShowInterfacesAggregate.h"
#include "..\SimulatorBase\ITransportOrderIrpToSimulator.h"


namespace jysoft{  namespace cpr {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     心肺复苏信息数据集合类
	创建人：	 hjg
	创建时间：   2017/5/22
	//-----------------------------------------------------------------------------------------------------------------*/
    class CPRMODULSSHARED_EXPORT CCPRMessageCollect : public irp::CRealTimeDataHandleIrpOp
							 , public irp::CEventHandleClockIrpOp
	{
	public:
		CCPRMessageCollect(void);
		virtual ~CCPRMessageCollect(void);
	protected:
		CCPRSimulateJudgeOp*           m_pCPRJudgeOp;         //CPR规则判断类
		CCPRStatisticImplement*        m_pStatisticImpl;      //操作统计集合类
		CCPRConfigue*                  m_pCPRConfigue;        //CPR参数配置解析类
		log::COpLogInterface*          m_pEventLogInterface;  //日志事件接口
	public:
		CPressureCollate                          m_cPressureCollate;    //按压逻辑数字对照表
		CBreathCollate                            m_cBreathCollate;      //吹气逻辑数字对照表
	private:
		transLayer::ITransportOrderIrpToUp*   m_pTransportUpOrderInterface;
		CCPRRealTimeUpdateInterface*          m_pShowCPRRealTimeInteface;
		CShowCPRActUpdateInterface*           m_pShowCPRDetailActInterface;
	private:
		bool                                      m_bEnableCompleteJudge;  //辨别CPR操作完成判断的标识
		_CPRManageState                           m_eNextPhaseCPRState;    //下阶段CPR操作模式
	protected: //接口CRealTimeDataHandleIrpOp函数重载
		/*******************************************************************************/
		//功能：处理场景框转移IRP函数
		//参数：
		//      CVirtualIrp *pCurrIrp：
		//返回值:  后续不再处理（FALSE);
		virtual bool doHandleRealTimeDataIrpOp(irp::CVirtualIrp *pCurrIrp);
	protected:
		/*******************************************************************************/
		//功能：处理时钟事件IRP函数
		//参数：
		//      CVirtualIrp *pCurrIrp：
		//返回值:  后续不再处理（FALSE);
		virtual bool doHandleClockIrpOp(irp::CVirtualIrp *pCurrIrp);
	public:
		//返回CPR操作判断接口指针
		inline CCPRSimulateJudgeOp * getCPRSimulateJudgeOp() { return m_pCPRJudgeOp; };
	public:
		/*******************************************************************************/
		// 函数名称： initialCPR
		// 功能：    初始化
		// 参数：  
		// 返回值:  
		void initialCPR(CCPRConfigue *pCPRConfigue, transLayer::ITransportOrderIrpToUp *pTransUpInterface, log::COpLogInterface *pEventLogInterface = NULL);
		/*******************************************************************************/
		// 函数名称： ResetCPROperatorMessage
		// 功能：    重置CPR操作统计
		// 参数：  
		// 返回值:  
		void resetCPROperatorMessage(_CPRManageState  eCPRState);
		/*******************************************************************************/
		// 函数名称： restatisticByDefibrEventHandle
		// 功能：    除颤事件引发重置CPR操作统计
		// 参数：  
		// 返回值:  
		void restatisticByDefibrEventHandle();
		/*******************************************************************************/
		// 函数名称： StartLinkCPRShowInterfaces
		// 功能： 初始连接CPR显示的相关显示接口
		// 参数： CCPRShowInterfacesAggregate *pShowAggregate:        
		// 返回值:  
		void startLinkCPRShowInterfaces(CCPRShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// 函数名称： UnLinkCPRShowInterfaces
		// 功能： 断开CPR显示的相关显示接口
		// 参数： CCPRShowInterfacesAggregate *pShowAggregate:        
		// 返回值:
		void unLinkCPRShowInterfaces(CCPRShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// 函数名称： DoModifyCPRJudgeRange
		// 功能： 修改心肺复苏操作时，吹气与按压的范围
		// 参数：     
		// 返回值:  
		void modifyCPRJudgeRange(int nLowerDepth, int nOverDepth, int nLowerVolume, int nOverVolume);
	public:
		//设置下阶段的CPR操作模式
		void setNextPhaseCPROperatorMode(_CPRManageState  eCPRState);
		//返回心肺复苏配置类
		inline CCPRConfigue * getCPRConfiguePtr() { return m_pCPRConfigue;};
		inline CCPRStatisticImplement * getCPRStatisticImplement() { return m_pStatisticImpl; };
		//启动滴答音
		void startTickSound();
		//停止滴答音
		void stopTickSound();
	private:
		//CPR命令指令处理
		_eCPRErrorSign doCPROrderHandle(const _CPRData &cprOrder);
		//CPR操作完成处理
		void doCPRCompleteHandle();
		//CPR操作结束处理
		void doCPROperatorFinishHandle(_CPRManageState  eCPRState);
		//返回脚本当前时间
		UINT getScriptRunTime();
	};

}}
