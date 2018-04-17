#include <boost/assert.hpp>
#include ".\xlinelinkeventobj.h"
#include ".\XSingleEventFrame.h"
#include ".\XCombineEventsFrame.h"
#include ".\XSelEventsFrame.h"


using namespace jysoft::irp;
namespace jysoft { namespace flowEngine 
{
	CXLineLinkEventObj::CXLineLinkEventObj()
	{
		m_pEventFrame = NULL;
	}

	CXLineLinkEventObj::~CXLineLinkEventObj(void)
	{
		if( m_pEventFrame )
		{
			delete m_pEventFrame;
		}
	}

	bool CXLineLinkEventObj::isKindOf(const std::string &strClassName)
	{
		if(strClassName == "CXLineLinkEventObj")
		{
			return TRUE;
		}
		return CXLineLink::isKindOf(strClassName);
	}

	/*******************************************************************************
	//功能：解析连接对象
	//参数：const std::string &strAimId:          连接的目标对象的ID号
	//      IXMLDOMNode *pScenarioNode:       元素scenario节点指针
	//返回值:  是否解析成功
	*********************************************************************************/
	bool CXLineLinkEventObj::InitialLineLink(const std::string &strAimId, pugi::xml_node *pScenarioNode, IAclsFlowStrategy  *pFlowStrategy)
	{
		//查找连接对象
        pugi::xml_node    xmlEventFrameNode = getFrameDOMNodePtr("event-Frame", strAimId, pScenarioNode);
		if( xmlEventFrameNode.empty() )
		{
            BOOST_ASSERT(0);
			return false;
		}
		//获取事件框类型
		std::string  attrType = xmlEventFrameNode.attribute("type").as_string();
		if( attrType == "Single" )
		{
			m_pEventFrame = new CXSingleEventFrame( pFlowStrategy );
		}
		else if( attrType == "Combine" )
		{
			m_pEventFrame = new CXCombineEventsFrame( pFlowStrategy );
		}
		else if( attrType == "Select" )
		{
			m_pEventFrame = new CXSelEventsFrame( pFlowStrategy );
		}
		else
		{
            BOOST_ASSERT(0);
			return false;
		}
		//解析事件框
		bool bSec = m_pEventFrame->ParseEvents(xmlEventFrameNode);
		if( !bSec )
		{
            BOOST_ASSERT(0);
			delete m_pEventFrame;
			return false;
		}
		m_xmlLinkAimDOMNodePtr = xmlEventFrameNode;
		return true;
	}


	//添加连接对象到队列中，以便可以处理Irp
	void CXLineLinkEventObj::AddLinkObjToHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect)
	{
		//事件Irp处理接口
		CEventHandleCustomIrpOp *pHandleEventIrpOp = dynamic_cast<CEventHandleCustomIrpOp *>(m_pEventFrame);
		pHandleIrpsCollect->addNewHandleEventIrpObj( pHandleEventIrpOp );
		//时钟Irp处理接口
		CEventHandleClockIrpOp *pHandleClockIrpOp  = dynamic_cast<CEventHandleClockIrpOp *>(m_pEventFrame);
		pHandleIrpsCollect->addNewHandleIrpObj(pHandleClockIrpOp, eClock_Event);
	}

	//移除连接对象
	void CXLineLinkEventObj::RemoveLinkObjFromHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect)
	{
		//事件Irp处理接口
		CEventHandleCustomIrpOp *pHandleEventIrpOp = dynamic_cast<CEventHandleCustomIrpOp *>(m_pEventFrame);
		pHandleIrpsCollect->removeHandleEventIrpObj(pHandleEventIrpOp);
		//时钟Irp处理接口
		CEventHandleClockIrpOp *pHandleClockIrpOp  = dynamic_cast<CEventHandleClockIrpOp *>(m_pEventFrame);
		pHandleIrpsCollect->removeHandleIrpObj(pHandleClockIrpOp, eClock_Event);
	}
}}
