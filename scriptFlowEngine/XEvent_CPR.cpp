#include ".\XEvent_CPR.h"

#include "..\ElementParse\SEvent_CPR.h"

#include "..\SimulatorBase\EventIrp_ClockTime.h"
#include "..\SimulatorBase\CPRStatIrp.h"


namespace jysoft { namespace flowEngine 
{
	CXEvent_CPR::CXEvent_CPR(void)
	{
		m_sImplementNum        = 0;
		m_sAccumulateTime      = 0;
		m_pCPMessageCollect    = NULL;
	}

	CXEvent_CPR::~CXEvent_CPR(void)
	{
		m_pCPMessageCollect    = NULL;
	}

	bool CXEvent_CPR::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXEvent_CPR" )
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
	std::string CXEvent_CPR::getEventCaption()
	{
		return CSEvent_CPR::getEvent_CPR_Caption();
	}
	/*******************************************************************************/
	// 函数名称： Parse_EventFromXml
	// 功能：   解析体征参数内容
	// 参数：   IXMLDOMNode *pXMLShapeNode:
	// 返回值: 
	bool CXEvent_CPR::Parse_EventFromXml(pugi::xml_node *pXMLShapeNode, IGetPhysiologyActionObj *pGetActionObj)
	{
		m_sImplementNum  = 0;
		SetEnableCaculateTime( false, true);
		bool bSec = CSEvent_CPR::explainParamsFromXML(pXMLShapeNode, &m_sOpMode, &m_sAccumulateTime, &m_sAccumulateNum);
		//获取CPR信息集合指针
		m_pCPMessageCollect   = pGetActionObj->Get_CPRMessageCollectPtr();
		return bSec ;
	}

	/*******************************************************************************/
	// 功能：   是否触发设定的事件
	// 参数：   
	// 返回值: 满足(TRUE)；不满足(FALSE)
	bool CXEvent_CPR::IsSatisfactionEvent()
	{
		if( m_sAccumulateNum <= m_sImplementNum )
		{
			return true;
		}
		return false;
	}

	/*******************************************************************************/
	// 功能：   清除事件触发相关的信息
	// 参数：   
	// 返回值: 
	void CXEvent_CPR::ClearSatisfactionInfo()
	{
		m_sImplementNum = 0;
		SetEnableCaculateTime( false, true );
	}

	/*******************************************************************************/
	// 功能：   事件处理
	// 参数：   
	// 返回值: 
	void CXEvent_CPR::DoHandleEventIrp(irp::CVirEventIrp  *pEventIrp)
	{
		if( pEventIrp->isKindOf( "CEventIrp_ClockTime" ) )
		{
			irp::CEventIrp_ClockTime *pClockTimeIrp = (irp::CEventIrp_ClockTime *)pEventIrp;
			//增加累积时间
			AddCaculateTime( pClockTimeIrp->GetValue_ClockEvent() );
		}
		else if( pEventIrp->isKindOf( "CCPRStatIrp" ) )
		{
			irp::CCPRStatIrp *pCPRStatIrp = (irp::CCPRStatIrp *)pEventIrp;
			_CPRManageState  eCPRMode = pCPRStatIrp->Get_eCPRMode();
			//CPR事件
			int     nStat  = pCPRStatIrp->GetValue_Stat();
			if( (m_sOpMode == 1 && nStat == 1) || (m_sOpMode == 0 && nStat == 0) )
			{
				m_sImplementNum += 1;
			}
			else if( m_sOpMode == 2 && nStat == 1)
			{
				m_sImplementNum += 1;
			}
			else if( m_sOpMode == 3 && (eCPRMode != eNoneDefine) && nStat == 2 )
			{
				m_sImplementNum += 1;
			}
		}
	}

	//增加累积时间
	void CXEvent_CPR::AddCaculateTime(short sSecond)
	{
		if( m_bEnableCaculateTime )
		{
			m_sCaculateTimeValue += sSecond;
		}
	}

	//设置是否能进行累积时间计数
	void CXEvent_CPR::SetEnableCaculateTime(bool bEnable, bool bClearCalcTime)
	{
		m_bEnableCaculateTime  = bEnable;
		if( bClearCalcTime )
		{
			m_sCaculateTimeValue   = 0;
		}
	}
	
}}
