#include ".\Symptom_FrameTime.h"
#include ".\XAction_FrameTime.h"
#include ".\IModifiedSymptomsOp.h"

#include "..\elementParse\SAction_FrameTime.h"


namespace jysoft { namespace simulator 
{
	CSymptom_FrameTime::CSymptom_FrameTime(void)
	{
		m_lFrameTime    = 0;
	}
	
	CSymptom_FrameTime::~CSymptom_FrameTime(void)
	{
	}

	/*******************************************************************************/
	// 函数名称： IsKindOf
	// 功能：   判断体征的类别
	// 参数：   const CString &strClassName
	// 返回值: 
	bool CSymptom_FrameTime::isKindOf( const std::string &strClassName )
	{
		if( strClassName == "CSymptom_FrameTime" )
		{
			return true;
		}
		return false;
	}

	//根据标示名称判断体征参数
	bool CSymptom_FrameTime::isSymptomCaption(const std::string &strCaption)
	{
		return CSAction_FrameTime::isAction_FrameTime( strCaption );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   IModifiedSymptomsOp *pInterfacePtr
	// 返回值: 
	void CSymptom_FrameTime::InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType)
	{
		m_pModifiedSymptomsOp  = pInterfacePtr;
		//设置默认值
		m_lFrameTime  = 0;

		m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
	}

	/*******************************************************************************/
	// 函数名称： InitialSymptomValue
	// 功能：   初始化体征值
	// 参数：   
	//          tag_TrendValue *pDefaultTrendValue:  相应体征修改的值返回
	//          CXActionVirtual *pVirAction:         对应体征值
	//          short sTransTime:                    转换时间（单位：秒）
	// 返回值: 
	void CSymptom_FrameTime::InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime)
	{
	#ifdef _DEBUG
		if( pVirAction == NULL || !pVirAction->isActionNameOf( CSAction_FrameTime::getAction_FrameTime_Caption() ) )
		{
			BOOST_ASSERT( 0 );
		}
	#endif 
		CXAction_FrameTime   *pAction_FrameTime = (CXAction_FrameTime *)pVirAction;
		m_lFrameTime  = pAction_FrameTime->GetValue_FrameTime();

		m_pModifiedSymptomsOp->AddNewModifiedSymptom( this );
	}

	//重置场景框时间为0
	void CSymptom_FrameTime::ResetFrameTimeToZero()
	{
		m_lFrameTime   = 0;
		//更新界面显示
		OnUpdateInterfaceShow();
	}

	//增加场景框持续时间
	void CSymptom_FrameTime::IncreaseFrameTime(long  lAddTime) 
	{ 
		m_lFrameTime += lAddTime; 
		//更新界面显示
		OnUpdateInterfaceShow();
	};
}}
