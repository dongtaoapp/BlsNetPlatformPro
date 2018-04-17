#include <boost/assert.hpp>
#include ".\xlinelinkscenarioobj.h"


namespace jysoft { namespace flowEngine 
{
	CXLineLinkScenarioObj::CXLineLinkScenarioObj()
	{
	}

	CXLineLinkScenarioObj::~CXLineLinkScenarioObj(void)
	{
	}

	bool  CXLineLinkScenarioObj::isKindOf(const std::string &strClassName)
	{
		if(strClassName == "CXLineLinkScenarioObj")
		{
			return true;
		}
		return CXLineLink::isKindOf(strClassName);
	}

	/*******************************************************************************
	//功能：解析连接对象
	//参数：const CString &strAimId:          连接的目标对象的ID号
	//      IXMLDOMNode *pScenarioNode:       元素scenario节点指针
	//返回值:  是否解析成功
	*********************************************************************************/
	bool CXLineLinkScenarioObj::InitialLineLink(const std::string &strAimId, pugi::xml_node *pScenarioNode, IAclsFlowStrategy  *pFlowStrategy)
	{
		//查找连接对象
		pugi::xml_node    xmlFrameNode = getFrameDOMNodePtr("frame", strAimId, pScenarioNode);
		if( xmlFrameNode.empty() )
		{
            BOOST_ASSERT(0);
			return false;
		}
		m_xmlLinkAimDOMNodePtr = xmlFrameNode;
		return true;
	}

	//返回场景转移Irp...
	irp::CFrameFlowIrp * CXLineLinkScenarioObj::GetFrameFlowIrp(eEventSign eEvent)
	{
		return irp::CFrameFlowIrp::CreateEventIrp_FrameFlow(&m_xmlLinkAimDOMNodePtr, eEvent);
	}
}}
