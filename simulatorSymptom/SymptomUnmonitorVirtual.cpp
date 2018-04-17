#include ".\symptomunmonitorvirtual.h"


namespace jysoft { namespace simulator 
{
	CSymptomUnmonitorVirtual::CSymptomUnmonitorVirtual(void)
	{
	}

	CSymptomUnmonitorVirtual::~CSymptomUnmonitorVirtual(void)
	{
	}

	/*******************************************************************************/
	// 函数名称： IsKindOf
	// 功能：   判断体征的类别
	// 参数：   const CString &strClassName
	// 返回值: 
	bool CSymptomUnmonitorVirtual::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptomUnmonitorVirtual" )
		{
			return true;
		}
		return false;
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   IModifiedSymptomsOp *pInterfacePtr
	//          tag_TrendValue *pDefaultTrendValue:  相应体征修改的值返回
	// 返回值: 
	void CSymptomUnmonitorVirtual::InitialSymptomValue( IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		BOOST_ASSERT( 0 );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   
	//          tag_TrendValue *pDefaultTrendValue:  相应体征修改的值返回
	//          CXActionVirtual *pVirAction:         对应体征值
	//          short sTransTime:                    转换时间（单位：秒）
	// 返回值: 
	void CSymptomUnmonitorVirtual::InitialSymptomValue( CXActionVirtual *pVirAction, short sTransTime/*=0*/)
	{
		BOOST_ASSERT( m_pModifiedSymptomsOp != NULL );
		ModifyUnmonitorSymptomValue( m_pModifiedSymptomsOp, pVirAction );
	}
}}
