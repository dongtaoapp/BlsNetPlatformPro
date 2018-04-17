#include ".\symptom_etco2.h"
#include ".\IModifiedSymptomsOp.h"
#include ".\XAction_etCO2.h"

#include "..\ElementParse\SAction_etCO2.h"


namespace jysoft { namespace simulator 
{
	CSymptom_etCO2::CSymptom_etCO2(void)
	{
		m_pEtCO2BuildInterface = NULL;
	}

	CSymptom_etCO2::~CSymptom_etCO2(void)
	{
	}

	/*******************************************************************************/
	// 函数名称： IsKindOf
	// 功能：   判断体征的类别
	// 参数：   const CString &strClassName
	// 返回值: 
	bool CSymptom_etCO2::isKindOf( const std::string &strClassName )
	{	
		if( strClassName == "CSymptom_etCO2" )
		{
			return true;
		}
		return false;
	}

	//根据标示名称判断体征参数
	bool  CSymptom_etCO2::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_etCO2::isAction_etCO2( strCaption );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   IModifiedSymptomsOp *pInterfacePtr
	// 返回值: 
	void CSymptom_etCO2::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;
		//设置默认etCO2值
		m_nEtCO2Value   = 34;
		
		pInterfacePtr->AddNewModifiedSymptom( this );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   
	//          CXActionVirtual *pVirAction:         对应体征值
	//          short sTransTime:                    转换时间（单位：秒）
	// 返回值: 
	void CSymptom_etCO2::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime/*=0*/)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_etCO2::getAction_etCO2_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 
		CXAction_etCO2 *pAction_etCO2 = (CXAction_etCO2 *)pVirAction;
		
		if( sTransTime == 0 && m_nEtCO2Value != pAction_etCO2->GetValue_AbsoluteEtCO2( m_nEtCO2Value ) )
		{
			m_nEtCO2Value = pAction_etCO2->GetValue_AbsoluteEtCO2( m_nEtCO2Value );

			m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
		}
	}

	//初始化呼吸末CO2模拟曲线构造器
	void CSymptom_etCO2::InitialetCO2Build(SimulatePatientType ePatientType)
	{
		if( m_pEtCO2BuildInterface != NULL )
		{
			m_pEtCO2BuildInterface->InitializeBuild( m_nEtCO2Value );
		}
	}

	//修改呼吸末CO2模拟曲线构造器
	void CSymptom_etCO2::ModifyetCO2Build(bool bClearIntubate /*=false*/)
	{
		if( m_pEtCO2BuildInterface != NULL )
		{
			if( bClearIntubate  )
			{
				m_pEtCO2BuildInterface->OnIntubateEventOp( false );
			}
			//修改分压值
			m_pEtCO2BuildInterface->OnModifyCO2PercentValue( m_nEtCO2Value );
		}
	}
}}
