#pragma once
#include ".\XActionVitalSignVir.h"


namespace jysoft { namespace simulator {
    class SIMULATORSYMPTOMSHARED_EXPORT CXAction_etCO2 : public CXActionVitalSignVir
	{
	public:
		CXAction_etCO2(void);
		virtual ~CXAction_etCO2(void);
	public: //基类函数重载
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
		long  GetValue_AbsoluteEtCO2( long lSrcValue );
	public:
		inline long GetValue_etCO2() { return m_lEtCO2Value; };
		inline void SetValue_etCO2(long lValue) { m_lEtCO2Value = lValue; };
	public:
		long           m_lEtCO2Value;
	};
}}
