#pragma once
#include <pugixml.hpp>
#include <boost/assert.hpp>
#include ".\XVirtualComponent.h"
#include ".\simulatorsymptom_global.h"

#include "..\Common\CommonGlobal.h"

namespace jysoft { namespace simulator {

    class SIMULATORSYMPTOMSHARED_EXPORT CXActionVirtual : public CXVirtualComponent
	{
	public:
		CXActionVirtual(void);
		virtual ~CXActionVirtual(void);
	public:
		virtual bool isKindOf(const std::string &strClassName);
	public:
		/*******************************************************************************/
		// 函数名称： GetActionCaption
		// 功能：   返回体征标识名
		// 参数：   
		// 返回值: 
		virtual std::string getActionCaption() const = 0;
		/*******************************************************************************/
		// 函数名称： Parse_ActionFromXml
		// 功能：   解析体征参数内容
		// 参数：   IXMLDOMNode *pXMLShapeNode:
		// 返回值: 
		virtual bool Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode) = 0;
		/*******************************************************************************/
		// 函数名称： CombineActionParam
		// 功能：   整合体征设置参数
		// 参数：   CXActionVirtual *pDstActionVir:
		// 返回值: 
		virtual void CombineActionParam(CXActionVirtual *pDstActionVir) = 0;
		/*******************************************************************************/
		// 函数名称： CloneAction
		// 功能：   拷贝体征参数
		// 参数：   
		// 返回值: 
		virtual CXActionVirtual * CloneAction() = 0;
	public:
		bool isActionNameOf(const std::string &strCaption);
	};
}}
