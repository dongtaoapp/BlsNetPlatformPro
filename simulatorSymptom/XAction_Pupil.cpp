#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include ".\xaction_pupil.h"

#include "..\elementParse\SAction_Pupil.h"


namespace jysoft { namespace simulator 
{
	CXAction_Pupil::CXAction_Pupil(void)
	{
		m_bNatural = true;
	}

	CXAction_Pupil::~CXAction_Pupil(void)
	{
	}

	bool CXAction_Pupil::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_Pupil")
		{
			return true;
		}
		return CXActionVirtual::isKindOf(strClassName);
	}

	/*******************************************************************************/
	// 函数名称： GetActionCaption
	// 功能：   返回体征标识名
	// 参数：   
	// 返回值: 
	std::string CXAction_Pupil::getActionCaption() const
	{
		return CSAction_Pupil::getAction_Pupil_Caption();
	}

	bool CXAction_Pupil::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		return CSAction_Pupil::explainParamsFromXML(pXMLShapeNode, &m_bNatural);
	}

	/*******************************************************************************/
	// 函数名称： CombineActionParam
	// 功能：   整合体征设置参数
	// 参数：   CXActionVirtual *pDstActionVir:
	// 返回值: 
	void CXAction_Pupil::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_Pupil  *pDstAction_Pupil = (CXAction_Pupil  *)pDstActionVir;
		//瞳孔大小
		m_bNatural  = pDstAction_Pupil->getPupilState();
	}

	/*******************************************************************************/
	// 函数名称： CloneAction
	// 功能：   拷贝体征参数
	// 参数：   
	// 返回值: 
	CXActionVirtual * CXAction_Pupil::CloneAction()
	{
		CXAction_Pupil  *pNewAction = new CXAction_Pupil();
		pNewAction->setPupilState( m_bNatural );
		return pNewAction;
	}
}}

