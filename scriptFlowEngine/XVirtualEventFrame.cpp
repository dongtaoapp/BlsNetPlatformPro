#include ".\xvirtualeventframe.h"
#include ".\IGetPhysiologyActionObj.h"
#include ".\ParseShapeFactory.h"


using namespace jysoft::irp;
namespace jysoft { namespace flowEngine 
{
	CXVirtualEventFrame::CXVirtualEventFrame(IAclsFlowStrategy   *pFlowStrategy)
	{
		m_pAlcsFlowStrategy  = pFlowStrategy;
		m_eEventSign         = ES_Normal;
	}

	CXVirtualEventFrame::~CXVirtualEventFrame(void)
	{
        foreach(auto x, m_lstEvents)
		{
			delete x;
		}
	}

	bool CXVirtualEventFrame::isKindOf(const std::string &strClassName)
	{
		if(strClassName == "CXVirtualEventFrame")
		{
			return true;
		}
		return false;
	}

	eEventSign CXVirtualEventFrame::Get_eEventSign()
	{
		return m_eEventSign;
	}

	/*******************************************************************************/
	//功能：处理场景事件IRP函数
	//参数：
	//      CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
	bool CXVirtualEventFrame::doHandleCustomEventIrpOp(CVirtualIrp *pCurrIrp)
	{
		CVirEventIrp *pVirEventIrp = NULL;
		if( pCurrIrp->isKindOf("CVirEventIrp") )
		{
			pVirEventIrp = (CVirEventIrp *)pCurrIrp;
			m_eEventSign  = pVirEventIrp->Get_EventSign();
		}
		//处理事件IRP
		if( pVirEventIrp && DoHandleEventIrp(pVirEventIrp) && !m_xmlEventFrameDOMNode.empty())
		{
			return m_pAlcsFlowStrategy->OnFlowStrategy(&m_xmlEventFrameDOMNode, m_eEventSign);
		}
		return true;
	}

	/*******************************************************************************/
	//功能：处理时钟事件IRP函数
	//参数：
	//      CVirtualIrp *pCurrIrp：
	//返回值:  后续不再处理（FALSE);
	bool CXVirtualEventFrame::doHandleClockIrpOp(CVirtualIrp *pCurrIrp)
	{
		CVirEventIrp *pVirEventIrp = (CVirEventIrp *)pCurrIrp;
		//处理事件IRP
		if( DoHandleEventIrp(pVirEventIrp)  && !m_xmlEventFrameDOMNode.empty())
		{
			m_pAlcsFlowStrategy->OnFlowStrategy(&m_xmlEventFrameDOMNode, ES_Normal);
		}
		return true;
	}

	//解析事件框
	bool CXVirtualEventFrame::ParseEvents(const pugi::xml_node &eventFrameNode)
	{
        foreach(auto x, m_lstEvents)
		{
			delete x;
		}
		m_lstEvents.clear();
		m_xmlEventFrameDOMNode = eventFrameNode;
		m_eEventSign         = ES_Normal;
		//---------------------------------------------------------------------
		//解析事件参数
		for (pugi::xml_node_iterator it = m_xmlEventFrameDOMNode.begin(); it != m_xmlEventFrameDOMNode.end(); ++it)
		{
			std::string  nodeName( it->name() );
			if( nodeName == "events" )
			{
				IGetPhysiologyActionObj *pGetActionObj  = m_pAlcsFlowStrategy->GetPhysiologyActionObjInterface();
				for (pugi::xml_node_iterator eventNode = it->begin(); eventNode != it->end(); ++eventNode)
				{
					CXEventVirtual *pEventItemPtr = CParseShapeFactory::get_const_instance().ParseEventObject( &(*eventNode) );
					//添加到列表中
					if( pEventItemPtr != NULL && pEventItemPtr->Parse_EventFromXml( &(*eventNode), pGetActionObj) )
					{
						m_lstEvents.push_back( pEventItemPtr );
					}
					else
					{
						delete pEventItemPtr;
						pEventItemPtr  = NULL;
					}
				}
				break;
			}
		}
		return true;
	}
}}
