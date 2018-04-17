#pragma once
#include ".\xeventvirtual.h"


namespace jysoft { namespace flowEngine 
{
	class CXEvent_CPR : public CXEventVirtual
	{
	public:
		CXEvent_CPR(void);
		virtual ~CXEvent_CPR(void);
	public:
		virtual bool isKindOf(const std::string &strClassName);
	public:
		/*******************************************************************************/
		// 函数名称： GetEventCaption
		// 功能：   返回体征标识名
		// 参数：   
		// 返回值: 
		virtual std::string getEventCaption();
		/*******************************************************************************/
		// 函数名称： Parse_EventFromXml
		// 功能：   解析体征参数内容
		// 参数：   IXMLDOMNode *pXMLShapeNode:
		// 返回值: 
		virtual bool Parse_EventFromXml(pugi::xml_node *pXMLShapeNode, IGetPhysiologyActionObj *pGetActionObj);
		/*******************************************************************************/
		// 功能：   是否触发设定的事件
		// 参数：   
		// 返回值: 满足(TRUE)；不满足(FALSE)
		virtual bool IsSatisfactionEvent();
		/*******************************************************************************/
		// 功能：   清除事件触发相关的信息
		// 参数：   
		// 返回值: 
		virtual void ClearSatisfactionInfo();
		/*******************************************************************************/
		// 功能：   事件处理
		// 参数：   
		// 返回值: 
		virtual void DoHandleEventIrp(irp::CVirEventIrp  *pEventIrp);
	private:
		//增加累积时间
		void AddCaculateTime(short sSecond);
		//设置是否能进行累积时间计数
		void SetEnableCaculateTime(bool bEnable, bool bClearCalcTime);
	protected:
		short                  m_sAccumulateTime;       //CPR操作累计时间
		short                  m_sAccumulateNum;        //CPR检查累计次数
		//-------------------------------------------------------------------
		//0：   心肺复苏操作开始；满足条件：累积次数
		//1：   心肺复苏操作结束；满足条件：累积次数
		//2：   心肺复苏操作模式
		//3：   标准心肺复苏操作模式；满足条件：成功累积次数
		short                  m_sOpMode;               // 当前操作的状态
	private:
		short                  m_sImplementNum;         //实施事件的累积次数
		cpr::CCPRMessageCollect    *m_pCPMessageCollect;     
		//--------------------------------------------------------------------
		bool                   m_bEnableCaculateTime;   //是否能进行时间计数
		short                  m_sCaculateTimeValue;    //时间计数值
	};
}}
