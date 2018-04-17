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
	//���ܣ��������Ӷ���
	//������const std::string &strAimId:          ���ӵ�Ŀ������ID��
	//      IXMLDOMNode *pScenarioNode:       Ԫ��scenario�ڵ�ָ��
	//����ֵ:  �Ƿ�����ɹ�
	*********************************************************************************/
	bool CXLineLinkEventObj::InitialLineLink(const std::string &strAimId, pugi::xml_node *pScenarioNode, IAclsFlowStrategy  *pFlowStrategy)
	{
		//�������Ӷ���
        pugi::xml_node    xmlEventFrameNode = getFrameDOMNodePtr("event-Frame", strAimId, pScenarioNode);
		if( xmlEventFrameNode.empty() )
		{
            BOOST_ASSERT(0);
			return false;
		}
		//��ȡ�¼�������
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
		//�����¼���
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


	//������Ӷ��󵽶����У��Ա���Դ���Irp
	void CXLineLinkEventObj::AddLinkObjToHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect)
	{
		//�¼�Irp����ӿ�
		CEventHandleCustomIrpOp *pHandleEventIrpOp = dynamic_cast<CEventHandleCustomIrpOp *>(m_pEventFrame);
		pHandleIrpsCollect->addNewHandleEventIrpObj( pHandleEventIrpOp );
		//ʱ��Irp����ӿ�
		CEventHandleClockIrpOp *pHandleClockIrpOp  = dynamic_cast<CEventHandleClockIrpOp *>(m_pEventFrame);
		pHandleIrpsCollect->addNewHandleIrpObj(pHandleClockIrpOp, eClock_Event);
	}

	//�Ƴ����Ӷ���
	void CXLineLinkEventObj::RemoveLinkObjFromHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect)
	{
		//�¼�Irp����ӿ�
		CEventHandleCustomIrpOp *pHandleEventIrpOp = dynamic_cast<CEventHandleCustomIrpOp *>(m_pEventFrame);
		pHandleIrpsCollect->removeHandleEventIrpObj(pHandleEventIrpOp);
		//ʱ��Irp����ӿ�
		CEventHandleClockIrpOp *pHandleClockIrpOp  = dynamic_cast<CEventHandleClockIrpOp *>(m_pEventFrame);
		pHandleIrpsCollect->removeHandleIrpObj(pHandleClockIrpOp, eClock_Event);
	}
}}
