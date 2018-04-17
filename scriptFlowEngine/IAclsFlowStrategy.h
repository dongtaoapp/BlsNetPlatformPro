#pragma once
#include <list>
#include <pugixml.hpp>
#include ".\xvirtuallink.h"
#include ".\IHandleIrpsCollect.h"
#include ".\IGetPhysiologyActionObj.h"


namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     脚本引擎策略接口类
	创建人：	 hjg
	创建时间：   2009/3/27
	//-----------------------------------------------------------------------------------------------------------------*/
	class CXLineLink;
	class CXLineLinkScenarioObj;
    class SCRIPTFLOWENGINESHARED_EXPORT IAclsFlowStrategy
	{
	public:
		IAclsFlowStrategy(pugi::xml_node *pxmlRootElement, IHandleIrpsCollect *pHandleIrpsCollect, IGetPhysiologyActionObj *pGetActionObj);
		virtual ~IAclsFlowStrategy(void);
	protected:
		pugi::xml_node                            m_xmlRootElement;
		IHandleIrpsCollect*                       m_pHandleIrpsCollect;
		IGetPhysiologyActionObj*                  m_pGetPhysiologyActionObj;
		std::list<CXVirtualLink *>                m_lstLineLinks;
	private:
		std::list<CXVirtualLink *>                m_lstDeletedLineLinks; //删除的连接
	protected:
		//返回脚本内容节点
		pugi::xml_node getScenarioXMLDOMNodePtr();
		//生成无条件连接对象
		CXLineLink * CreateLineLink(pugi::xml_node *pLinkNodePtr);
		//清空被删除的连接
		void EmptyDeletedLineLinks();
	public:
		IHandleIrpsCollect * GetHandleIrpsCollectPtr() { return m_pHandleIrpsCollect; };
		inline IGetPhysiologyActionObj * GetPhysiologyActionObjInterface() { return m_pGetPhysiologyActionObj; };
		//生成所有的连接对象
		void CreateLineLinks(pugi::xml_node *pFrameElement);
		//删除所有生成的连接对象，并转移到临时列表中
		void DeleteAllLineLinks();
	public:
		/*******************************************************************************/
		//功能：根据策略，驱动场景
		//参数：
		//      IXMLDOMNode *pFrameElement：
		//      eEventSign eEvent:
		//返回值:  后续不再处理事件（FALSE);
		virtual bool OnFlowStrategy(pugi::xml_node *pFrameElement, eEventSign eEvent=ES_Normal) = 0;
		//根据策略选择满足转移条件的下个场景
		virtual CXLineLinkScenarioObj * SelectNextScenarioFromStrategy() = 0;
	};
}}
