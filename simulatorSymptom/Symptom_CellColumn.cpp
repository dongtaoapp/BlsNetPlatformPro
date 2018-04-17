#include ".\Symptom_CellColumn.h"
#include ".\XAction_CellColumn.h"
#include ".\IModifiedSymptomsOp.h"

#include "..\elementParse\SAction_CellColumn.h"


namespace jysoft { namespace simulator 
{
	CSymptom_CellColumn::CSymptom_CellColumn(void)
	{
		m_bNatural = true;
	}

	CSymptom_CellColumn::~CSymptom_CellColumn(void)
	{
	}

    /*******************************************************************************/
	// 函数名称： IsKindOf
	// 功能：   判断体征的类别
	// 参数：   const CString &strClassName
	// 返回值: 
	bool CSymptom_CellColumn::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_CellColumn" )
		{
			return true;
		}
		return false;
	}

	//根据标示名称判断体征参数
	bool CSymptom_CellColumn::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_CellColumn::isAction_CellColumn( strCaption );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   IModifiedSymptomsOp *pInterfacePtr
	// 返回值: 
	void CSymptom_CellColumn::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;
		//AED电量正常
		m_bNatural = true;

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
	void CSymptom_CellColumn::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_CellColumn::getAction_CellColumn_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 
		CXAction_CellColumn *pActionCellColumn = (CXAction_CellColumn *)pVirAction;
		if( m_bNatural != pActionCellColumn->getValue_isNatural() )
		{
			m_bNatural = pActionCellColumn->getValue_isNatural();

			m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
		}
	}

	/*******************************************************************************/
	// 函数名称： isTransmitAEDState
	// 功能：   是否AED状态改变
	// 参数：   
	//          /*in,out*/unsigned char *sAEDState:        AED状态
	// 返回值: 
	bool CSymptom_CellColumn::isTransmitAEDState(/*in,out*/unsigned char *sAEDState)
	{
		if( sAEDState != NULL )
		{
			*sAEDState |= (m_bNatural ? 0x00 : 0x08);
		}
		return true;
	}

}}
