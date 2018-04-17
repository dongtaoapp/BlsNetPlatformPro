#pragma once
#include ".\iaclsflowstrategy.h"

#include "..\SimulatorBase\ITransportOrderIrpToSimulator.h"


namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     脚本引擎标准策略，自动选择连接的下个场景的转移策略
	创建人：	 hjg
	创建时间：   2009/3/27
	//-----------------------------------------------------------------------------------------------------------------*/

	class CNormalAclsFlowStrategy : public IAclsFlowStrategy
	{
	public:
		CNormalAclsFlowStrategy(transLayer::ITransportOrderIrpToUp *pTransportUpInterface, pugi::xml_node *pxmlRootElement, IHandleIrpsCollect *pHandleIrpsCollect, IGetPhysiologyActionObj *pGetActionObj);
		virtual ~CNormalAclsFlowStrategy(void);
	public:
		/*******************************************************************************/
		//功能：根据策略，驱动场景
		//参数：
		//      IXMLDOMNode *pFrameElement：
		//      eEventSign eEvent:
		//返回值:  后续不再处理事件（FALSE);
		virtual bool OnFlowStrategy(pugi::xml_node *pFrameElement, eEventSign eEvent=ES_Normal);
		//根据策略选择满足转移条件的下个场景
		virtual CXLineLinkScenarioObj * SelectNextScenarioFromStrategy();
	protected:
		transLayer::ITransportOrderIrpToUp*  m_pTransportUpInterface;
	};
}}
