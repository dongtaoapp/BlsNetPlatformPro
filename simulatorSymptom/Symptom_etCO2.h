#pragma once
#include ".\symptomvirtual.h"

#include "..\SimulatorBase\OpEtCO2BuildInterface.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     模拟人的呼出末二氧化碳分压
	创建人：	 hjg
	创建时间：   2008/10/22
	//-----------------------------------------------------------------------------------------------------------------*/

	class CSymptom_etCO2 : public CSymptomVirtual
	{
	public:
		CSymptom_etCO2(void);
		virtual ~CSymptom_etCO2(void);
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
		virtual  void InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType);
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
		virtual  void OnUpdateInterfaceShow() { };
	public:
		//初始化呼吸末CO2模拟曲线构造器
		void InitialetCO2Build(SimulatePatientType ePatientType);
		//修改呼吸末CO2模拟曲线构造器
		void ModifyetCO2Build(bool bClearIntubate=false);
	public:
		//设置呼出末二氧化碳模拟构造器操作接口
		inline void SetEtCO2BuildInterface(base::COpEtCO2BuildInterface *pInterface) { m_pEtCO2BuildInterface = pInterface; };
		inline base::COpEtCO2BuildInterface * GetEtCO2BuildInterface() { return m_pEtCO2BuildInterface; };
		inline int  GetValue_EtCO2() { return m_nEtCO2Value; };
	protected:
		base::COpEtCO2BuildInterface   *m_pEtCO2BuildInterface; //呼出末二氧化碳模拟构造器操作接口
	protected:
		int                       m_nEtCO2Value;
	};
}}