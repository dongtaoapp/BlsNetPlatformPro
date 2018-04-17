#include ".\Symptom_Defibri.h"
#include ".\XAction_Defibri.h"
#include ".\IModifiedSymptomsOp.h"

#include "..\elementParse\SAction_Defibrillate.h"

namespace jysoft { namespace simulator 
{
	CSymptom_Defibri::CSymptom_Defibri(void)
	{
		m_bEnableDefibri = true;
		m_bClearCount = false;
	}

	CSymptom_Defibri::~CSymptom_Defibri(void)
	{
	}

	/*******************************************************************************/
	// 函数名称： IsKindOf
	// 功能：   判断体征的类别
	// 参数：   const CString &strClassName
	// 返回值: 
	bool CSymptom_Defibri::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_Defibri" )
		{
			return true;
		}
		return false;
	}

	//根据标示名称判断体征参数
	bool CSymptom_Defibri::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_Defibrillate::isAction_Defibri( strCaption );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   IModifiedSymptomsOp *pInterfacePtr
	// 返回值: 
	void CSymptom_Defibri::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;
		//设置能除颤
		m_bEnableDefibri = true;
		m_bClearCount = false;

		pInterfacePtr->AddNewModifiedSymptom( this );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   
	//          tag_TrendValue *pDefaultTrendValue:  相应体征修改的值返回
	//          CXActionVirtual *pVirAction:         对应体征值
	//          short sTransTime:                    转换时间（单位：秒）
	// 返回值: 
	void CSymptom_Defibri::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_Defibrillate::getAction_Defibri_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 
		CXAction_Defibri *pActionDefibr = (CXAction_Defibri *)pVirAction;
		//是否能除颤
		m_bEnableDefibri = pActionDefibr->getValue_EnableDefibri();
		//去除除颤次数
		m_bClearCount = pActionDefibr->getValue_ClearCount();

		m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
	}

	/*******************************************************************************/
	// 函数名称： isTransmitAEDState
	// 功能：   是否AED状态改变
	// 参数：   
	//          /*in,out*/unsigned char *sAEDState:        AED状态
	// 返回值: 
	bool CSymptom_Defibri::isTransmitAEDState(/*in,out*/unsigned char *sAEDState)
	{
		if( sAEDState != NULL )
		{
			*sAEDState |= (m_bEnableDefibri ? 0x01 : 0x00);
		}
		return true;
	}
}}
