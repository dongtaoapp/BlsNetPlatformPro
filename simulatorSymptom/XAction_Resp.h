#pragma once
#include ".\xactionvirtual.h"

#include "..\Common\CommonGlobal.h"


namespace jysoft { namespace simulator {
    class SIMULATORSYMPTOMSHARED_EXPORT CXAction_Resp : public CXActionVirtual
	{
	public:
		CXAction_Resp(void);
		CXAction_Resp(eRespMode enumRespMode, long nRespRate);
		virtual ~CXAction_Resp(void);
	public:
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
		long   GetValue_AbsoluteRR(long lSrcRR);
	public:
		inline eRespMode GetRespMode() { return m_eRespMode; };
		inline long GetBreathRate() { return m_lBreathRate; };
		inline void SetRespMode(eRespMode enumRespMode) { m_eRespMode = enumRespMode; };
		inline void SetBreathRate(long lBreathRate) { m_lBreathRate = lBreathRate; };
		//百分比增减
		inline void Set_bRelatePercent( bool bPercent ) { m_bRelatePercent = bPercent; };
		inline bool Get_bRelatePercent() { return m_bRelatePercent; };
	public:
		eRespMode          m_eRespMode;    //呼吸模式
		long               m_lBreathRate;  //呼吸次数
	protected:
		bool               m_bRelatePercent;
	};
}}
