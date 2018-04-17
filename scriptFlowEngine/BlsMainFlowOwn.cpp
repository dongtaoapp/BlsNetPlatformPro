#include ".\BlsMainFlowOwn.h"
#include ".\BlsSimulateCase.h"
#include ".\NormalAclsFlowStrategy.h"
#include ".\XScenario.h"


namespace jysoft { namespace flowEngine 
{
	CBlsMainFlowOwn::CBlsMainFlowOwn(CBlsSimulateCase  *pSimulateCase, transLayer::CFormatTransport* pTransport)
					: CBlsMainFlowVirtual( pSimulateCase, pTransport )
	{
	}

	CBlsMainFlowOwn::~CBlsMainFlowOwn(void)
	{
	}

	/*******************************************************************************/
	// 函数名称： CreateScenario
	// 功能： 根据场景脚本文件，初始化ACLS流程处理中心
	// 参数： 
	//       pugi::xml_node *pRootElement: 
	// 返回值:  
	pugi::xml_node  CBlsMainFlowOwn::CreateScenario( pugi::xml_node rootElement )
	{
		pugi::xml_node    xmlFrameNode;
		//创建流程线程
		if( !CreateFlowThreads() )
		{
			return xmlFrameNode;
		}
		//解析启动场景
		pugi::xml_node scenarioNode = m_cRunFramework.parseStartScenario( &rootElement, 0);
		if( !scenarioNode.empty() )
		{
			//初始化执行当前的解析Actions
			ExecInitialFramework( SPT_Adult );
			//设置流程策略
			transLayer::ITransportOrderIrpToUp   *pTransportUpInterface = (transLayer::ITransportOrderIrpToUp *)m_pFormatTransport;
			IGetPhysiologyActionObj  *pGetPhysiologyActionObj = (IGetPhysiologyActionObj  *)&m_cRunFramework;
			m_pAclsFlowStrategy = new CNormalAclsFlowStrategy(pTransportUpInterface, &rootElement, this, pGetPhysiologyActionObj);
			m_pAclsFlowStrategy->CreateLineLinks( &scenarioNode );

			//控制模拟人体征
			IModifiedSymptomsOp  *pModifiedSymptomsOp = m_pBlsSimulateCase->getModifiedSymptomsOpPtr();
			pModifiedSymptomsOp->TransmitSimulatorOrders(  );
		}
		return scenarioNode;
	}

	/*******************************************************************************/
	// 函数名称： ExecInitialFramework
	// 功能： 初始化执行当前的解析Actions
	// 参数： 
	//   
	// 返回值:  
	void CBlsMainFlowOwn::ExecInitialFramework(SimulatePatientType ePatientType)
	{
		CXScenario   *pScenarioPtr = m_cRunFramework.GetScenarioPtr();
		//初始化CSimulateSymptomsCollect
		std::list<CXActionVirtual *>   lstActions;
		pScenarioPtr->GetScenarioActions( &lstActions );
		ISetSimulateSymptoms  *pSetSimulateSymptomsPtr = m_pBlsSimulateCase->getSetSimulateSymptomsPtr();
		pSetSimulateSymptomsPtr->initialScenarioSet( &lstActions, ePatientType );
		//组合生理体征,并清空CXScenario中的生理体征列表项
		m_cRunFramework.CombineCurrentActions( true );
	}

}}
