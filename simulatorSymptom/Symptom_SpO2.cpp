#include <algorithm>
#include <boost/foreach.hpp>
#include ".\symptom_spo2.h"
#include ".\IModifiedSymptomsOp.h"
#include ".\XAction_Osat.h"

#include "..\elementParse\SAction_Osat.h"


using namespace jysoft::simulator::base;
namespace jysoft { namespace simulator 
{
	CSymptom_SpO2::CSymptom_SpO2(void)
	{
		m_pSpO2BuildInterface  = NULL;
	}

	CSymptom_SpO2::~CSymptom_SpO2(void)
	{
	}

	/*******************************************************************************/
	// 函数名称： IsKindOf
	// 功能：   判断体征的类别
	// 参数：   const CString &strClassName
	// 返回值: 
	bool CSymptom_SpO2::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_SpO2" )
		{
			return true;
		}
		return false;
	}

	//根据标示名称判断体征参数
	bool CSymptom_SpO2::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_Osat::isAction_Osat( strCaption );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   IModifiedSymptomsOp *pInterfacePtr
	// 返回值: 
	void CSymptom_SpO2::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;

		m_nSpO2Value  = 98;

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
	void CSymptom_SpO2::InitialSymptomValue( CXActionVirtual *pVirAction, short sTransTime/*=0*/)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_Osat::getAction_Osat_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 	
		int   nSrcSpO2Value  = m_nSpO2Value;
		CXAction_Osat  *pAction_BloodOxygen = (CXAction_Osat *)pVirAction;
		if( sTransTime == 0 && pAction_BloodOxygen->GetValue_AbsoluteSpO2( nSrcSpO2Value ) != m_nSpO2Value )
		{
			m_nSpO2Value = pAction_BloodOxygen->GetValue_AbsoluteSpO2( nSrcSpO2Value );

			m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
		}
	}

	//初始化血氧模拟曲线构造器
	void CSymptom_SpO2::InitialSpO2Build(SimulatePatientType ePatientType)
	{
		if( m_pSpO2BuildInterface != NULL )
		{
			m_pSpO2BuildInterface->OnModifySpO2ValuePrecent( m_nSpO2Value );
		}
	}

	//修改血氧模拟曲线构造器
	void CSymptom_SpO2::ModifySpO2Build()
	{
		if( m_pSpO2BuildInterface != NULL )
		{
			m_pSpO2BuildInterface->OnModifySpO2ValuePrecent( m_nSpO2Value );
		}
	}
}}
