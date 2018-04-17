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
	//���ܣ��������Ӷ���
	//������const CString &strAimId:          ���ӵ�Ŀ������ID��
	//      IXMLDOMNode *pScenarioNode:       Ԫ��scenario�ڵ�ָ��
	//����ֵ:  �Ƿ�����ɹ�
	*********************************************************************************/
	bool CXLineLinkScenarioObj::InitialLineLink(const std::string &strAimId, pugi::xml_node *pScenarioNode, IAclsFlowStrategy  *pFlowStrategy)
	{
		//�������Ӷ���
		pugi::xml_node    xmlFrameNode = getFrameDOMNodePtr("frame", strAimId, pScenarioNode);
		if( xmlFrameNode.empty() )
		{
            BOOST_ASSERT(0);
			return false;
		}
		m_xmlLinkAimDOMNodePtr = xmlFrameNode;
		return true;
	}

	//���س���ת��Irp...
	irp::CFrameFlowIrp * CXLineLinkScenarioObj::GetFrameFlowIrp(eEventSign eEvent)
	{
		return irp::CFrameFlowIrp::CreateEventIrp_FrameFlow(&m_xmlLinkAimDOMNodePtr, eEvent);
	}
}}
