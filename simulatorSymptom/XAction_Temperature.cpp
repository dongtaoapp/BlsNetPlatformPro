#include ".\xaction_temperature.h"
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

#include "..\ElementParse\SAction_Temperature.h"


namespace jysoft { namespace simulator 
{
	CXAction_Temperature::CXAction_Temperature(void)
	{
	
	}

	CXAction_Temperature::~CXAction_Temperature(void)
	{
	}

	bool CXAction_Temperature::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_Temperature")
		{
			return true;
		}
		return CXActionVitalSignVir::isKindOf(strClassName);
	}

	/*******************************************************************************/
	// 函数名称： GetActionCaption
	// 功能：   返回体征标识名
	// 参数：   
	// 返回值: 
	std::string CXAction_Temperature::getActionCaption() const
	{
		return CSAction_Temperature::getAction_Temperature_Caption();
	}

	bool CXAction_Temperature::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		return CSAction_Temperature::explainParamsFromXML(pXMLShapeNode, /*out*/&m_fP_TempValue);
	}

	/*******************************************************************************/
	// 函数名称： CombineActionParam
	// 功能：   整合体征设置参数
	// 参数：   CXActionVirtual *pDstActionVir:
	// 返回值: 
	void CXAction_Temperature::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_Temperature  *pDstAction_Temp = (CXAction_Temperature  *)pDstActionVir;
		//外围温度
		m_fP_TempValue   = pDstAction_Temp->GetValue_P_Temp();
	}

	/*******************************************************************************/
	// 函数名称： CloneAction
	// 功能：   拷贝体征参数
	// 参数：   
	// 返回值: 
	CXActionVirtual * CXAction_Temperature::CloneAction()
	{
		CXAction_Temperature *pNewTemp = new CXAction_Temperature();
		pNewTemp->SetValue_P_Temp( m_fP_TempValue );
		return pNewTemp;
	}
}}
