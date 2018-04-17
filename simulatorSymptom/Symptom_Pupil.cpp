#include ".\symptom_pupil.h"
#include ".\IModifiedSymptomsOp.h"
#include ".\XAction_Pupil.h"

#include "..\Common\DecodeUtil.h"

#include "..\ElementParse\SAction_Pupil.h"


using namespace jysoft::simulator::base;
namespace jysoft { namespace simulator 
{
	CSymptom_Pupil::CSymptom_Pupil(void)
	{
		m_bNatural = false;
	}

	CSymptom_Pupil::~CSymptom_Pupil(void)
	{
	}

	/*******************************************************************************/
	// 函数名称： IsKindOf
	// 功能：   判断体征的类别
	// 参数：   const CString &strClassName
	// 返回值: 
	bool CSymptom_Pupil::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_Pupil" )
		{
			return true;
		}
		return false;
	}

	//根据标示名称判断体征参数
	bool CSymptom_Pupil::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_Pupil::isAction_Pupil( strCaption );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   IModifiedSymptomsOp *pInterfacePtr
	// 返回值: 
	void CSymptom_Pupil::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;
		m_bNatural = false;

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
	void CSymptom_Pupil::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime/*=0*/)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_Pupil::getAction_Pupil_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 	
		CXAction_Pupil *pAction_Pupil = (CXAction_Pupil *)pVirAction;
		if( m_bNatural != pAction_Pupil->getPupilState() )
		{
			m_bNatural = pAction_Pupil->getPupilState();

			m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
		}
	}
}}
