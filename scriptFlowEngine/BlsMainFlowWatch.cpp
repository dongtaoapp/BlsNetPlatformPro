#include ".\BlsMainFlowWatch.h"
#include ".\BlsSimulateCase.h"
#include ".\XScenario.h"


using namespace jysoft::simulator;
namespace jysoft { namespace flowEngine 
{
	CBlsMainFlowWatch::CBlsMainFlowWatch(CBlsSimulateCase  *pSimulateCase, transLayer::CFormatTransport* pTransport)
					: CBlsMainFlowVirtual( pSimulateCase, pTransport )
	{
	}

	CBlsMainFlowWatch::~CBlsMainFlowWatch(void)
	{
	}

	/*******************************************************************************/
	// �������ƣ� CreateScenario
	// ���ܣ� ���ݳ����ű��ļ�����ʼ��ACLS���̴�������
	// ������ 
	//       pugi::xml_node *pRootElement: 
	// ����ֵ:  
	pugi::xml_node  CBlsMainFlowWatch::CreateScenario( pugi::xml_node rootElement )
	{
		pugi::xml_node    xmlFrameNode;
		//���������߳�
		if( !CreateFlowThreads() )
		{
			return xmlFrameNode;
		}
		//������������
		pugi::xml_node scenarioNode = m_cRunFramework.parseStartScenario( &rootElement, 0);
		/*if( !scenarioNode.empty() )
		{
			//��ʼ��ִ�е�ǰ�Ľ���Actions
			ExecInitialFramework( SPT_Adult );
			//�������̲���
			transLayer::ITransportOrderIrpToUp   *pTransportUpInterface = (transLayer::ITransportOrderIrpToUp *)m_pFormatTransport;
			IGetPhysiologyActionObj  *pGetPhysiologyActionObj = (IGetPhysiologyActionObj  *)&m_cRunFramework;
			m_pAclsFlowStrategy = new CNormalAclsFlowStrategy(pTransportUpInterface, &rootElement, this, pGetPhysiologyActionObj);
			m_pAclsFlowStrategy->CreateLineLinks( &scenarioNode );

			//����ģ��������
			IModifiedSymptomsOp  *pModifiedSymptomsOp = m_pBlsSimulateCase->getModifiedSymptomsOpPtr();
			pModifiedSymptomsOp->TransmitSimulatorOrders(  );
		}*/
		return scenarioNode;
	}

	/*******************************************************************************/
	// �������ƣ� ExecInitialFramework
	// ���ܣ� ��ʼ��ִ�е�ǰ�Ľ���Actions
	// ������ 
	//   
	// ����ֵ:  
	void CBlsMainFlowWatch::ExecInitialFramework(SimulatePatientType ePatientType)
	{
		CXScenario   *pScenarioPtr = m_cRunFramework.GetScenarioPtr();
		//��ʼ��CSimulateSymptomsCollect
		std::list<CXActionVirtual *>   lstActions;
		pScenarioPtr->GetScenarioActions( &lstActions );
		ISetSimulateSymptoms  *pSetSimulateSymptomsPtr = m_pBlsSimulateCase->getSetSimulateSymptomsPtr();
		pSetSimulateSymptomsPtr->initialScenarioSet( &lstActions, ePatientType );
		//�����������,�����CXScenario�е����������б���
		m_cRunFramework.CombineCurrentActions( true );
	}
}}
