#pragma once
#include ".\symptomvirtual.h"

namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     接触患者
	创建人：	 hjg
	创建时间：   2018/2/17
	//-----------------------------------------------------------------------------------------------------------------*/
	class CSymptom_ContactPatient : public CSymptomVirtual
	{
	public:
		CSymptom_ContactPatient(void);
		virtual ~CSymptom_ContactPatient(void);
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
		// 参数：   IModifiedSymptomsOp *pInterfacePtr
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
		/*******************************************************************************/
		// 函数名称： isTransmitAEDState
		// 功能：   是否AED状态改变
		// 参数：   
		//          /*in,out*/unsigned char *sAEDState:        AED状态
		// 返回值: 
		virtual  bool isTransmitAEDState(/*in,out*/unsigned char *sAEDState);
	protected:
		bool      m_bContactPatient;
	};
}}
