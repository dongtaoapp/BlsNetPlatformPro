#include ".\XEvent_Time.h"

#include "..\ElementParse\SEvent_Time.h"

#include "..\simulatorBase\EventIrp_ClockTime.h"


namespace jysoft { namespace flowEngine 
{
	CXEvent_Time::CXEvent_Time(void)
	{
		m_sImplementNum           = 0;
		m_pGetActionObjInterface  = NULL;
	}

	CXEvent_Time::~CXEvent_Time(void)
	{
	}

	bool CXEvent_Time::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXEvent_Time" )
		{
			return true;
		}
		return CXEventVirtual::isKindOf( strClassName );
	}

	/*******************************************************************************/
	// 函数名称： GetEventCaption
	// 功能：   返回体征标识名
	// 参数：   
	// 返回值: 
	std::string CXEvent_Time::getEventCaption()
	{
		return CSEvent_Time::getEvent_Time_Caption();
	}

	/*******************************************************************************/
	// 函数名称： Parse_EventFromXml
	// 功能：   解析体征参数内容
	// 参数：   IXMLDOMNode *pXMLShapeNode:
	// 返回值: 
	bool CXEvent_Time::Parse_EventFromXml(pugi::xml_node *pXMLShapeNode, IGetPhysiologyActionObj *pGetActionObj)
	{
		bool  bSec = CSEvent_Time::explainParamsFromXML(pXMLShapeNode, &m_bTimeType, &m_sTimeValue);
		m_sImplementNum = 0;
		m_pGetActionObjInterface  = pGetActionObj;
		return bSec ;
	}

	/*******************************************************************************/
	// 功能：   是否触发设定的事件
	// 参数：   
	// 返回值: 满足(TRUE)；不满足(FALSE)
	bool CXEvent_Time::IsSatisfactionEvent()
	{
		if( m_sImplementNum > 0 )
		{
			return true;
		}
		return false;
	}

	/*******************************************************************************/
	// 功能：   清除事件触发相关的记录信息
	// 参数：   
	// 返回值: 
	void CXEvent_Time::ClearSatisfactionInfo()
	{
		m_sImplementNum = 0;
	}

	/*******************************************************************************/
	// 功能：   事件处理
	// 参数：   
	// 返回值: 
	void CXEvent_Time::DoHandleEventIrp(irp::CVirEventIrp  *pEventIrp)
	{
		if( pEventIrp->isKindOf( "CEventIrp_ClockTime" ) && !IsSatisfactionEvent())
		{
			irp::CEventIrp_ClockTime *pClockTimeIrp = (irp::CEventIrp_ClockTime *)pEventIrp;
			if( m_bTimeType == true )
			{
				//框架时间判断
				simulator::CSymptom_FrameTime  *pFrameTime = m_pGetActionObjInterface->getFrameTimeSymptomPtr();
				if( pFrameTime != NULL && pFrameTime->GetValue_FrameTime() > m_sTimeValue )
				{
					m_sImplementNum += 1;
				}
			}
		}
	}
}}
