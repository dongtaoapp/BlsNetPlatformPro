#pragma once
#include ".\symptomvirtual.h"
#include ".\XActionVirtual.h"

#include "..\SimulatorBase\ShowTempUpdateInterface.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     模拟人的体温，包括中心温度和外围温度
	创建人：	 hjg
	创建时间：   2008/10/22
	//-----------------------------------------------------------------------------------------------------------------*/
	class CSymptom_Temperature : public CSymptomVirtual
	{
	public:
		CSymptom_Temperature(void);
		virtual ~CSymptom_Temperature(void);
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
		virtual  void InitialSymptomValue( CXActionVirtual *pVirAction, short sTransTime = 0);
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
		// 功能：   断开显示连接
		// 参数：   
		// 返回值:
		virtual  void OnUnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate) ;
	public:
		void SetShowTemperatureValueInterface(base::CShowTempUpdateInterface *ptemp);
	public:
		inline float GetValue_PTemperator() { return m_fP_TempValue; };
	protected:
		float       m_fP_TempValue;   //外围温度
		base::CShowTempUpdateInterface*  m_pShowPTempValueInterface;
	};
}}