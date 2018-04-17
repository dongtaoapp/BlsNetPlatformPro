#pragma once
#include "symptomvirtual.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     可不被监控参数的生理体征基类
	创建人：	 hjg
	创建时间：   2009/3/31
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORSYMPTOMSHARED_EXPORT CSymptomUnmonitorVirtual : public CSymptomVirtual
	{
	public:
		CSymptomUnmonitorVirtual(void);
		virtual ~CSymptomUnmonitorVirtual(void);
	public:
		//根据标示名称判断体征参数
		virtual  bool isSymptomCaption(const std::string &strCaption) = 0;
		//修改对应体征的参数
		virtual  void ModifyUnmonitorSymptomValue(IModifiedSymptomsOp *pInterfacePtr, CXActionVirtual *pVirAction) = 0;
	public: 
		/*******************************************************************************/
		// 函数名称： IsKindOf
		// 功能：   判断体征的类别
		// 参数：   const CString &strClassName
		// 返回值: 
		virtual  bool isKindOf( const std::string &strClassName );
		/*******************************************************************************/
		// 函数名称： InitialSymptomValue
		// 功能：   初始化体征值
		// 参数：   IModifiedSymptomsOp *pInterfacePtr
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
		virtual  void InitialSymptomValue( CXActionVirtual *pVirAction, short sTransTime = 0) ;
		// 函数名称： OnUpdateInterfaceShow
		// 功能：   更新界面显示
		// 参数：   
		// 返回值: 
		virtual  void OnUpdateInterfaceShow() = 0; 
		/*******************************************************************************/
		// 函数名称： OnLinkWatchBarUpdateInterfaceShow
		// 功能：   连接模拟监控显示连接
		// 参数：   
		// 返回值:
		virtual  void OnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate) = 0;
		// 函数名称： OnUnLinkWatchBarUpdateInterfaceShow
		// 功能：   断开显示连接
		// 参数：   
		// 返回值:
		virtual  void OnUnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate) = 0;
	};
}}
