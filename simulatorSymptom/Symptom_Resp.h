#pragma once
#include <list>
#include ".\SymptomVirtual.h"
#include ".\XActionVirtual.h"

#include "..\Common\CommonGlobal.h"

#include "..\SimulatorBase\OpRespBuildInterface.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     模拟人的当前呼吸
	创建人：	 hjg
	创建时间：   2017/2/17
	//-----------------------------------------------------------------------------------------------------------------*/
	class  CSymptom_Resp : public CSymptomVirtual
	{
	public:
		CSymptom_Resp(void);
		virtual ~CSymptom_Resp(void);
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
		/*******************************************************************************/
		// 函数名称： OnUpdateInterfaceShow
		// 功能：   更新界面显示
		// 参数：   
		// 返回值: 
		virtual  void OnUpdateInterfaceShow();
		/*******************************************************************************/
		// 函数名称： OnLinkSimulatorBarUpdateInterfaceShow
		// 功能：   断开模拟人面板显示连接
		// 参数：   
		// 返回值:
		virtual  void OnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate );
		/*******************************************************************************/
		// 函数名称： OnUnLinkSimulatorBarUpdateInterfaceShow
		// 功能：   断开模拟人面板显示连接
		// 参数：   
		// 返回值:
		virtual  void OnUnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate );
	public:
		//初始化呼吸模拟曲线构造器
		void InitialRespBuild(SimulatePatientType ePatientType);
		//修改呼吸模拟曲线构造器
		void ModifyRespBuild();
	public:
		inline eRespMode GetRespMode() { return m_eRespMode; };
		inline int GetValue_RespRate() { return m_nRespRate; };
		//设置呼吸模拟构造器操作接口
		inline void SetRespBuildInterface(base::COpRespBuildInterface *pInterface) { m_pRespBuildInterface = pInterface; };
		inline base::COpRespBuildInterface * GetRespBuildInterface() { return m_pRespBuildInterface; };
	protected:
		base::COpRespBuildInterface           *m_pRespBuildInterface;   //呼吸模拟构造器操作接口
		//呼吸模式显示接口
		base::CShowRespRateUpdateInterface    *m_pShowRespInterface;
	protected:
		eRespMode                        m_eRespMode;             //呼吸模式
		int                              m_nRespRate;             //呼吸次数
	};
}}