#pragma once
#include ".\XActionVitalSignVir.h"


namespace jysoft { namespace simulator {
    class SIMULATORSYMPTOMSHARED_EXPORT CXAction_Osat : public CXActionVitalSignVir
	{
	public:
		CXAction_Osat(void);
		virtual ~CXAction_Osat(void);
	protected:
		long							m_lBloodOxygenValue;
	protected:
		bool                            m_bRelatePercent;
	public: //基类函数重栽
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
		long  GetValue_AbsoluteSpO2(long  lSrcValue);
	public:
		inline long GetBloodOxygenValue() { return m_lBloodOxygenValue; };
		inline void SetValue_BloodOxygen(long lValue) { m_lBloodOxygenValue = lValue; };
		//百分比增减
		inline void Set_bRelatePercent( bool bPercent ) { m_bRelatePercent = bPercent; };
		inline bool Get_bRelatePercent() { return m_bRelatePercent; };
	};
}}
