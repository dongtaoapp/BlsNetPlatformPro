#include ".\Symptom_Electrode.h"
#include ".\XAction_Electrode.h"
#include ".\IModifiedSymptomsOp.h"

#include "..\elementParse\SAction_Electrode.h"


namespace jysoft { namespace simulator 
{

	CSymptom_Electrode::CSymptom_Electrode(void)
	{
		m_bPosRight = true;
	}

	CSymptom_Electrode::~CSymptom_Electrode(void)
	{
	}

	/*******************************************************************************/
	// 函数名称： IsKindOf
	// 功能：   判断体征的类别
	// 参数：   const CString &strClassName
	// 返回值: 
	bool CSymptom_Electrode::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_Electrode" )
		{
			return true;
		}
		return false;
	}

	//根据标示名称判断体征参数
	bool CSymptom_Electrode::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_Electrode::isAction_Electrode( strCaption );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   IModifiedSymptomsOp *pInterfacePtr
	// 返回值: 
	void CSymptom_Electrode::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;
		//电极片贴正常
		m_bPosRight = true;

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
	void CSymptom_Electrode::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_Electrode::getAction_Electrode_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 
		CXAction_Electrode *pActionElec = (CXAction_Electrode *)pVirAction;
		m_bPosRight = pActionElec->m_bPosRight;

		m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
	}

	/*******************************************************************************/
	// 函数名称： isTransmitAEDState
	// 功能：   是否AED状态改变
	// 参数：   
	//          /*in,out*/unsigned char *sAEDState:        AED状态
	// 返回值: 
	bool CSymptom_Electrode::isTransmitAEDState(/*in,out*/unsigned char *sAEDState)
	{
		if( sAEDState != NULL )
		{
			*sAEDState |= (m_bPosRight ? 0x00 : 0x02);
		}
		return true;
	}
}}
