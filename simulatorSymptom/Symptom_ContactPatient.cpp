#include ".\Symptom_ContactPatient.h"

#include "..\elementParse\SAction_ContactPatient.h"


namespace jysoft { namespace simulator 
{
	CSymptom_ContactPatient::CSymptom_ContactPatient(void)
	{
		m_bContactPatient = false;
	}

	CSymptom_ContactPatient::~CSymptom_ContactPatient(void)
	{
	}

	/*******************************************************************************/
	// 函数名称： IsKindOf
	// 功能：   判断体征的类别
	// 参数：   const CString &strClassName
	// 返回值: 
	bool CSymptom_ContactPatient::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_ContactPatient" )
		{
			return true;
		}
		return false;
	}

	//根据标示名称判断体征参数
	bool CSymptom_ContactPatient::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_ContactPatient::isAction_ContactPatient( strCaption );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   IModifiedSymptomsOp *pInterfacePtr
	// 返回值: 
	void CSymptom_ContactPatient::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   
	//          tag_TrendValue *pDefaultTrendValue:  相应体征修改的值返回
	//          CXActionVirtual *pVirAction:         对应体征值
	//          short sTransTime:                    转换时间（单位：秒）
	// 返回值: 
	void CSymptom_ContactPatient::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime)
	{
	}

	/*******************************************************************************/
	// 函数名称： isTransmitAEDState
	// 功能：   是否AED状态改变
	// 参数：   
	//          /*in,out*/unsigned char *sAEDState:        AED状态
	// 返回值: 
	bool CSymptom_ContactPatient::isTransmitAEDState(/*in,out*/unsigned char *sAEDState)
	{
		if( sAEDState != NULL )
		{
			*sAEDState |= (m_bContactPatient ? 0x04 : 0x00);
		}
		return true;
	}
}}
