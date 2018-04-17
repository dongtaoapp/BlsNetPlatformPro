#pragma once
#include "symptomvirtual.h"

#include "..\SimulatorBase\ShowPaceUpdateInterface.h"

namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     起搏设置
	创建人：	 hjg
	创建时间：   2009/4/1
	//-----------------------------------------------------------------------------------------------------------------*/
	class CSymptom_Pace : public CSymptomVirtual
	{
	public:
		CSymptom_Pace(void);
		virtual ~CSymptom_Pace(void);
	public: 
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
		// 参数：   
		//          IModifiedSymptomsOp *pInterfacePtr
		//          tag_TrendValue *pDefaultTrendValue:  相应体征修改的值返回
		// 返回值: 
		virtual  void InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType);
		/*******************************************************************************/
		// 函数名称： InitialSymptomValue
		// 功能：   初始化体征值
		// 参数：   
		//          tag_TrendValue *pDefaultTrendValue:  相应体征修改的值返回
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
	protected:
		bool                         m_bEnablePace;  //是否能起搏
		short                        m_sData;        //起搏电流（mA）
	protected:
		base::CShowPaceUpdateInterface    *m_pShowPaceInterface;
	};
}}