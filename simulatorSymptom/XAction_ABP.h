#pragma once
#include ".\XActionVirtual.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     有创血压
	创建人：	 hjg
	创建时间：   2017/2/1
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORSYMPTOMSHARED_EXPORT CXAction_ABP : public CXActionVirtual
	{
	public:
		CXAction_ABP(void);
		virtual ~CXAction_ABP(void);
	public://基类内容重载
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
		long   GetValue_AbsoluteShrink( long lSrcShrink );
		long   GetValue_AbsoluteStretch( long lSrcStretch );
	public:
		//返回收缩压值
		inline long Get_ShrinkValue_ABP() { return m_nShrinkValue_ABP; };
		//返回舒张压值
		inline long Get_StretchValue_ABP() { return m_nStretchValue_ABP; };
		//设置收缩压值
		inline void Set_ShrinkValue_ABP(long lValue) { m_nShrinkValue_ABP = lValue; };
		//设置舒张压值
		inline void Set_StretchValue_ABP(long lValue) { m_nStretchValue_ABP = lValue; };
	public:
		long        m_nShrinkValue_ABP;        //有创收缩压
		long        m_nStretchValue_ABP;       //有创舒张压
	public:
		int         m_nKorotkOffVolume;        //KorotkOff音量值
        unsigned long       m_dwField;                 //0x01: 收缩压；0x02：KorotkOff音量值
	};
}}
