#pragma once
#include ".\symptomvirtual.h"
#include ".\XActionVirtual.h"

#include "..\common\EmulateTimer.h"

#include "..\SimulatorBase\OpABPBuildInterface.h"
#include "..\SimulatorBase\ShowNIBPUpdateInterface.h"
#include "..\SimulatorBase\SimulatorOrderIrp.h"
#include "..\SimulatorBase\SymptomsShowInterfacesAggregate.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     模拟人的有创血压， 无创血压为1分钟内的有创血压值
	创建人：	 hjg
	创建时间：   2017/2/22
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORSYMPTOMSHARED_EXPORT CSymptom_ABP : public CSymptomVirtual
	{
	public:
		CSymptom_ABP(void);
		virtual ~CSymptom_ABP(void);
	public: //基类函数重载
		/*******************************************************************************/
		// 函数名称： IsKindOf
		// 功能：   判断体征的类别
		// 参数：   const CString &strClassName
		// 返回值: 
		virtual  bool isKindOf( const std::string &strClassName );
		//根据标示名称判断体征参数
		virtual  bool isSymptomCaption(const std::string &strCaption);
		/*******************************************************************************/
		// 函数名称： InitialSymptomValue
		// 功能：   初始化体征值
		// 参数：   IModifiedSymptomsOp *pInterfacePtr
		// 返回值: 
		virtual  void InitialSymptomValue( IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType);
		/*******************************************************************************/
		// 函数名称： InitialSymptomValue
		// 功能：   初始化体征值
		// 参数：   
		//          CXActionVirtual *pVirAction:         对应体征值
		//          short sTransTime:                    转换时间（单位：秒）
		// 返回值: 
		virtual  void InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime = 0);
		// 函数名称： OnUpdateInterfaceShow
		// 功能：   更新界面显示
		// 参数：   
		// 返回值: 
		virtual  void OnUpdateInterfaceShow();
		/*******************************************************************************/
		// 函数名称： OnLinkWatchBarUpdateInterfaceShow
		// 功能：   连接模拟监控显示连接
		// 参数：   
		// 返回值:
		virtual  void OnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// 函数名称： OnUnLinkWatchBarUpdateInterfaceShow
		// 功能：   断开模拟监控显示连接
		// 参数：   
		// 返回值:
		virtual  void OnUnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// 函数名称： OnLinkSimulatorBarUpdateInterfaceShow
		// 功能：   连接模拟人面板显示连接
		// 参数：   
		// 返回值:
		virtual  void OnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate );
		/*******************************************************************************/
		// 函数名称： OnUnLinkSimulatorBarUpdateInterfaceShow
		// 功能：   断开模拟人面板显示连接
		// 参数：   
		// 返回值:
		virtual  void OnUnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate );
		/*******************************************************************************/
		// 函数名称： ResetFlag
		// 功能：   重置修改的标识
		// 参数：   
		// 返回值:
		virtual  void ResetFlag() { m_bModifyNIBPValue = false; };
	public:
		//初始化血压模拟曲线构造器
		void InitialABPBuild(SimulatePatientType ePatientType);
		//修改血压模拟曲线构造器
		void ModifyABPBuild();
		//根据ABP的数值，获取NIBP(1分钟)
		void   Set_NIBPCurrentValue();
	public:
		//设置有创血压模拟构造器操作接口
		inline void SetABPBuildInterface(base::COpABPBuildInterface *pInterface) { m_pABPBuildInterface = pInterface; };
		inline int  GetValue_SBP() { return m_nShrinkValue_ABP; };
		inline int  GetValue_DBP() { return m_nStretchValue_ABP; };
	public:
		void SetShowNIBPInterface(base::CShowNIBPUpdateInterface *pShowInterface);
		//设置传送NIBP指令
		void SetEnableTranslateNIBPOrder();
	protected:
		int                       m_nShrinkValue_ABP;        //有创收缩压
		int                       m_nStretchValue_ABP;       //有创舒张压
		//----------------------------------------------------------------------------------------------------------
		int                       m_nShrinkValue_NIBP;       //无创收缩压
		int                       m_nStretchValue_NIBP;      //无创舒张压
	protected:
		base::COpABPBuildInterface     *m_pABPBuildInterface;      //有创血压模拟构造器操作接口
		base::CShowNIBPUpdateInterface *m_pShowNIBPInterface;      //无创血压显示接口
	private:
		utility::CEmulateTimer    m_cNIBPTimer;
		bool                      m_bModifyNIBPValue;        //是否修改了NIBP的值
	};
}}
