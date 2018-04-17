#pragma once
#include "xactionvirtual.h"


namespace jysoft { namespace simulator {
    class SIMULATORSYMPTOMSHARED_EXPORT CXAction_Pupil : public CXActionVirtual
	{
	public:
		CXAction_Pupil(void);
		virtual ~CXAction_Pupil(void);
	public://基类函数重载
		virtual bool isKindOf(const std::string &strClassName);
		/*******************************************************************************/
		// 函数名称： GetActionCaption
		// 功能：   返回体征标识名
		// 参数：   
		// 返回值: 
		virtual std::string getActionCaption() const;
		/*******************************************************************************/
		// 函数名称： Parse_ActionFromXml
		// 功能：   解析体征参数内容
		// 参数：   IXMLDOMNode *pXMLShapeNode:
		// 返回值: 
		virtual bool Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode);
		/*******************************************************************************/
		// 函数名称： CombineActionParam
		// 功能：   整合体征设置参数
		// 参数：   CXActionVirtual *pDstActionVir:
		// 返回值: 
		virtual void CombineActionParam(CXActionVirtual *pDstActionVir);
		/*******************************************************************************/
		// 函数名称： CloneAction
		// 功能：   拷贝体征参数
		// 参数：   
		// 返回值: 
		virtual CXActionVirtual * CloneAction();
	public:
		inline bool getPupilState() { return m_bNatural; };
		inline void setPupilState(bool bNatural) { m_bNatural = bNatural; };
	protected:
		bool        m_bNatural;
	};
}}
