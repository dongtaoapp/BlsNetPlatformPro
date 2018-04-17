#include ".\BlsMainFlowVirtual.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/lexical_cast.hpp>
#include ".\XSceneActFrame.h"
#include ".\blsmainflowvirtual.h"
#include ".\BlsSimulateCase.h"

#include "..\Common\DecodeUtil.h"

#include "..\elementParse\SEvent_Intubate.h"

#include "..\SimulatorBase\SimulatorOrderIrp.h"
#include "..\SimulatorBase\EventIrp_ClockTime.h"
#include "..\SimulatorBase\CPRStatIrp.h"

#include "..\SimulatorSymptom\Symptom_FrameTime.h"

#include "crtdbg.h"
inline void enableMemLeakCheck()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

using namespace jysoft::irp;
using namespace jysoft::simulator;
using namespace jysoft::simulator::base;
namespace jysoft { namespace flowEngine 
{
	//ʱ���̺߳���
	void  CBlsMainFlowVirtual::_ThrdTimeFunc()
	{
		enableMemLeakCheck();
		//ʱ�Ӽ�һ��
		CEventIrp_ClockTime  *pClockIrp = CEventIrp_ClockTime::CreateEvent_ClockIrp();
		if( m_pFormatTransport != NULL )
		{
			m_pFormatTransport->DecreaseFilterTransUpIrpTime( 1 );
		}
		boost::mutex::scoped_lock lock(muPackage);
		AddNeedHandleIrp( pClockIrp );
	}

	//���¶˽�����Ϣ��
	void CBlsMainFlowVirtual::_ThrdReceiveIrpFunc()
	{
		try
		{
			while(1)
			{
				{
					boost::mutex::scoped_lock lock(muPackage);
					cond_IrpRecv.wait(lock, boost::bind(&CBlsMainFlowVirtual::isTransInUpIrps, this));
					//��ȡ�µĴ����
					CVirtualIrp *pVirIrp = m_pFormatTransport->TransportIrpInUplst();
					AddNeedHandleIrp( pVirIrp );
				}
				boost::this_thread::interruption_point();
			}
		}
		catch (boost::thread_interrupted &)
		{
			//std::cout << "interrupt irp handle" << std::endl;
		}
	}
	//��Ϣ�������߳�
	void CBlsMainFlowVirtual::_ThrdHandleIrpFunc()
	{
		try
		{
			while(1)
			{
				CVirtualIrp *pCurrIrp = NULL;
				{
					boost::mutex::scoped_lock lock(muPackage);
					cond_IrpHandle.wait(lock, boost::bind(&CBlsMainFlowVirtual::isCanPackageHandle, this));
					//�Ƚ��ȳ�������հ�, ��ȡ��һ����
					if( m_IrpList.size() > 0 )
					{
						pCurrIrp = *m_IrpList.begin();
						m_IrpList.pop_front();
					}
				}
				boost::this_thread::interruption_point();
				if( pCurrIrp != NULL )
				{
					OnHandleIrp( pCurrIrp );
					delete pCurrIrp;
				}
				boost::this_thread::interruption_point();
			}
		}
		catch (boost::thread_interrupted &)
		{
			;
		}
	}

	CBlsMainFlowVirtual::CBlsMainFlowVirtual(CBlsSimulateCase  *pSimulateCase, transLayer::CFormatTransport* pTransport)
	{
		m_pBlsSimulateCase   = pSimulateCase;
		//����SimulateSymptomsCollectָ��
		CSimulateSymptomsCollect  *pCollect = pSimulateCase->getSimulateSymptomsCollectPtr();
		m_cRunFramework.setSimulateSymptomsCollectPtr( pCollect );
		m_cRunFramework.Set_CPRMessageCollectPtr( pSimulateCase->getCPRMessageCollect() );
		secondEumlate = NULL;
		m_pAclsFlowStrategy       = NULL;
		m_pShowEventSignInterface = NULL;
		m_eState   = eFlowNone;
		//---------------------------------------------------------------------------------------
		m_pFormatTransport = pTransport;
		m_pFormatTransport->SetReceivePackageIrpHandlePtr( &cond_IrpRecv );
	}

	CBlsMainFlowVirtual::~CBlsMainFlowVirtual(void)
	{
		if( secondEumlate != NULL )
		{
			delete secondEumlate;
		}
		secondEumlate = NULL;
		tg.interrupt_all();
		tg.join_all();
		//------------------------------------------------------------
		if( m_pAclsFlowStrategy != NULL )
		{
			delete m_pAclsFlowStrategy;
		}
		m_pAclsFlowStrategy = NULL;
	}

	//�Ƿ��ܴ���Irp
	bool CBlsMainFlowVirtual::isCanPackageHandle()
	{
		if( m_eState == eFlowRun )
		{
			//boost::mutex::scoped_lock lockIrp(muPackage);
			if( m_IrpList.begin() == m_IrpList.end() || m_IrpList.size() == 0 )
			{
				return false;
			}
			return true;
		}
		return false;
	}

	//�Ƿ���ͨ�Ų��ϴ���Irp��
	bool CBlsMainFlowVirtual::isTransInUpIrps()
	{
		if( m_pFormatTransport != NULL )
		{
			return m_pFormatTransport->isTransUpIrps();
		}
		return false;
	}

	//���������߳�
	bool CBlsMainFlowVirtual::CreateFlowThreads()
	{
		BOOST_ASSERT(secondEumlate == NULL);

        foreach(auto x, m_IrpList)
		{
			delete x;
		}
		m_IrpList.clear();
		//��ȱʣ���ý���
		m_eState = eFlowPause;
		//=======�����߳�==============
		tg.create_thread( boost::bind(&CBlsMainFlowVirtual::_ThrdHandleIrpFunc, this) );
		tg.create_thread( boost::bind(&CBlsMainFlowVirtual::_ThrdReceiveIrpFunc, this) );
		//���������Ĵ���
		m_pFormatTransport->StartTransportData();
		return true;
	}

	/*******************************************************************************/
	// �������ƣ� ResetScenario
	// ���ܣ� ����ACLS���̴�������
	// ������ 
	// ����ֵ:  
	pugi::xml_node CBlsMainFlowVirtual::ResetScenario()
	{
		//�����ǰ��ִ��λ�ÿ�
		m_cRunFramework.ClearRunFramework();
		pugi::xml_node xmlElement = m_pBlsSimulateCase->getScriptXMLElement();
		//������������
		pugi::xml_node scenarioNode = m_cRunFramework.parseStartScenario( &xmlElement, 0);
		if( !scenarioNode.empty() )
		{
			//---------------------------------------------------------------------------------------
			//��ʼ��ִ�е�ǰ�Ľ���Actions
			ExecInitialFramework( SPT_Adult );
			//���ó��������ʱ��
			CSymptom_FrameTime *pScenarioFrameTime = m_cRunFramework.getFrameTimeSymptomPtr();
			pScenarioFrameTime->ResetFrameTimeToZero();
			//�������̲���
			m_pAclsFlowStrategy->CreateLineLinks( &scenarioNode );

			//����ģ��������
			IModifiedSymptomsOp  *pModifiedSymptomsOp = m_pBlsSimulateCase->getModifiedSymptomsOpPtr();
			pModifiedSymptomsOp->TransmitSimulatorOrders(  );
		}
		return scenarioNode;
	}

	/*******************************************************************************/
	// �������ƣ� DoFlowNextScenario
	// ���ܣ� ִ���¸�������
	// ������ 
	//       DWORD  dwFrameID:      ������ı�ʶֵ
	// ����ֵ:  
	pugi::xml_node CBlsMainFlowVirtual::DoFlowNextScenario(unsigned short  dwFrameID, eEventSign eEvent/*=ES_Normal*/)
	{
		std::string  strFrameID = boost::lexical_cast<std::string>(dwFrameID);
		//1.1�����¸�����
		pugi::xml_node xmlElement = m_pBlsSimulateCase->getScriptXMLElement();
        pugi::xml_node scenarioNode = m_cRunFramework.parseNextScenario(&xmlElement, strFrameID, "ScenarioFrame");
		if( !scenarioNode.empty() )
		{
			//ִ�е�ǰ�Ľ���Actions
			ExecNextFramework( eEvent );
			//���ó��������ʱ��
			CSymptom_FrameTime *pScenarioFrameTime = m_cRunFramework.getFrameTimeSymptomPtr();
			pScenarioFrameTime->ResetFrameTimeToZero();

			m_pAclsFlowStrategy->CreateLineLinks( &scenarioNode );

			//����ģ��������
			IModifiedSymptomsOp  *pModifiedSymptomsOp = m_pBlsSimulateCase->getModifiedSymptomsOpPtr();
			pModifiedSymptomsOp->TransmitSimulatorOrders( );
			pModifiedSymptomsOp->ModifiedSymptomsUpdateShow( false );
		}
		return scenarioNode;
	}

	/*******************************************************************************/
	// �������ƣ� DoFlowNextScenario
	// ���ܣ� ִ���¸�������
	// ������ 
	//       IXMLDOMNode *pScenarioNode:      �������Node
	//       eEventSign eEvent:     
	// ����ֵ:  
	pugi::xml_node  CBlsMainFlowVirtual::DoFlowNextScenario(pugi::xml_node  *pScenarioNode, eEventSign eEvent /*= ES_Normal*/)
	{
		pugi::xml_node scenarioNode = m_cRunFramework.parseNextScenario( pScenarioNode );
		if( !scenarioNode.empty() )
		{
			//ִ�е�ǰ�Ľ���Actions
			ExecNextFramework( eEvent );
			//���ó��������ʱ��
			CSymptom_FrameTime *pScenarioFrameTime = m_cRunFramework.getFrameTimeSymptomPtr();
			pScenarioFrameTime->ResetFrameTimeToZero();

			m_pAclsFlowStrategy->CreateLineLinks( pScenarioNode );

			//����ģ��������
			IModifiedSymptomsOp  *pModifiedSymptomsOp = m_pBlsSimulateCase->getModifiedSymptomsOpPtr();
			/*pModifiedSymptomsOp->TransmitSimulatorOrders( );*/
			pModifiedSymptomsOp->ModifiedSymptomsUpdateShow( false );
		}
		return scenarioNode;
	}

	/*******************************************************************************/
	// �������ƣ� DoFlowSceneActRun
	// ���ܣ� ִ���龰���
	// ������ 
	//       DWORD dwSceneActFrameID:      �龰��ı�ʶֵ
	//       BOOL bLogoutFlow:             �Ƿ��˳�������
	//       eEventSign eEvent:     
	// ����ֵ:  
	CXSceneActFrame * CBlsMainFlowVirtual::DoFlowSceneActRun(unsigned short dwSceneActFrameID, bool bLogoutFlow, eEventSign eEvent/*=ES_Normal*/)
	{
		CXSceneActFrame *pDstSceneActFrame = NULL;
		CSceneActsCollect *pSceneActsCollect = m_pBlsSimulateCase->getSceneActsCollectPtr();
		if( pSceneActsCollect != NULL )
		{
			pDstSceneActFrame = pSceneActsCollect->SearchSceneActFramePtr( dwSceneActFrameID );
		}
		if( pDstSceneActFrame != NULL )
		{
			CXScenario   *pScenarioPtr = m_cRunFramework.GetScenarioPtr();
			pScenarioPtr->EmptyActions();
			//�����޸ĵ�������
			pScenarioPtr->CopyActions( pDstSceneActFrame );
			//ִ�е�ǰ��Actions
			ExecNextFramework( eEvent );

			if( bLogoutFlow )
			{
				//�˳�������
				m_pAclsFlowStrategy->DeleteAllLineLinks();
			}

			//����ģ��������
			IModifiedSymptomsOp  *pModifiedSymptomsOp = m_pBlsSimulateCase->getModifiedSymptomsOpPtr();
			/*pModifiedSymptomsOp->TransmitSimulatorOrders( );*/
			pModifiedSymptomsOp->ModifiedSymptomsUpdateShow( false );
		}
		return pDstSceneActFrame;
	}

	//ִ�е�ǰ�Ľ���Actions
	void CBlsMainFlowVirtual::ExecNextFramework(eEventSign eEvent /*= ES_Normal*/)
	{
		CXScenario   *pScenarioPtr = m_cRunFramework.GetScenarioPtr();
		//�޸�CSimulateSymptomsCollect
		std::list<CXActionVirtual *>   lstActions;
		pScenarioPtr->GetScenarioActions( &lstActions );
		ISetSimulateSymptoms  *pSetSimulateSymptomsPtr = m_pBlsSimulateCase->getSetSimulateSymptomsPtr();
		pSetSimulateSymptomsPtr->modifyScenarioSet(&lstActions, eEvent, false);
		//�����������,�����CXScenario�е����������б���
		m_cRunFramework.CombineCurrentActions( true );
	}

	// ����Ҫ�����IRP����������л�������Ӧ�Ĵ���
	bool CBlsMainFlowVirtual::AddNeedHandleIrp(CVirtualIrp * pVirIrp)
	{
		//�ж����Ƿ���Ҫ������Ӧ�Ĵ���
		if(m_eState == eFlowRun)
		{
			m_IrpList.push_back(pVirIrp);
			cond_IrpHandle.notify_one();
		}
		else
			delete pVirIrp;
		return false;//������
	}

	//������Ϣ��
	void CBlsMainFlowVirtual::OnHandleIrp(CVirtualIrp *pVirIrp)
	{
		m_cHandleActionIrpMutex.Lock();
		if( pVirIrp != NULL )
		{
			IHandleIrpsCollect::OnHandleIrp( pVirIrp );
			//��¼�¼���־
			if( pVirIrp->isKindOf( "CVirEventIrp" ) && !pVirIrp->isKindOf( "CEventIrp_ClockTime" ) )
			{
				CVirEventIrp  *pVirEventIrp = (CVirEventIrp *)pVirIrp;
				//����CPR�¼��Ĳ���ģʽΪ��ǰģʽ��ע��Ӱ��CPR��־�ı�����
				FilterCPREventIrp(pVirEventIrp, m_pBlsSimulateCase);
				//��¼�¼���־
				std::string  strCurrentRunTime = m_pBlsSimulateCase->CurrentTimeFormat();
				log::COpLogInterface  *pLogInterface = m_pBlsSimulateCase->getOpLogMessagePtr();
				pLogInterface->OnEventHandleLog(strCurrentRunTime, pVirEventIrp);
				//��ʾ�¼�����Ч��
				DoUpdateEventSignShow(pVirEventIrp, m_pShowEventSignInterface, m_pBlsSimulateCase);
			}
		}
		m_cHandleActionIrpMutex.Unlock();
	}

	// ��ʼ���г���
	void CBlsMainFlowVirtual::StartCurrScenario( )
	{
		m_eState = eFlowRun;
		if( secondEumlate != NULL )
		{
			delete secondEumlate;
			secondEumlate = NULL;
		}
		secondEumlate = new utility::CEmulateTimer(1000, boost::bind(&CBlsMainFlowVirtual::_ThrdTimeFunc, this));
		secondEumlate->startTimer();
		
		if( m_pFormatTransport != NULL )
		{
			CSimulatorOrderIrp *pOrderIrp = CSimulatorOrderIrp::createSimulatorOrderIrp(0x20, 0x20);;
			m_pFormatTransport->OnTransportDownOrderToSimulater( pOrderIrp );
		}
		cond_IrpHandle.notify_one();
	}

	// ��ͣĿǰ���еĳ���
	void CBlsMainFlowVirtual::PauseCurrScenario( bool bClearSimulator )
	{
		m_eState = eFlowPause;
		if( secondEumlate != NULL )
		{
			secondEumlate->killTimer();
		}
		//����ϵͳ����ָ��
		if( bClearSimulator && m_pFormatTransport != NULL )
		{
			CSimulatorOrderIrp *pOrderIrp = CSimulatorOrderIrp::createSimulatorOrderIrp(0x50, 0x50);;
			m_pFormatTransport->OnTransportDownOrderToSimulater( pOrderIrp );
		}
	}

	/*******************************************************************************/
	// �������ƣ� ExecuteAction
	// ���ܣ� ִ������������
	// ������ 
	//       IXMLDOMElement *pRootElement: 
	// ����ֵ:  
	void CBlsMainFlowVirtual::ExecuteActions(std::list<CXActionVirtual *> *plstVirActions, short sTransferTime/*=0*/)
	{
		m_cHandleActionIrpMutex.Lock();
		ISetSimulateSymptoms  *pSetSimulateSymptomsPtr = m_pBlsSimulateCase->getSetSimulateSymptomsPtr();
		pSetSimulateSymptomsPtr->modifyScenarioSet(plstVirActions, ES_Normal, false, sTransferTime);
		//�����������
		m_cRunFramework.CombineCurrentActions( plstVirActions );

		m_cHandleActionIrpMutex.Unlock();
	}

	/*******************************************************************************/
	// �������ƣ� StartLinkEventSignShowInterfaces
	// ���ܣ� ��ʼ�������¼���ʾ�ӿ�
	// ������ 
	//        CModularBarsShowInterfacesAggregate *pShowAggregate:      
	// ����ֵ:  
	void CBlsMainFlowVirtual::StartLinkEventSignShowInterfaces(CShowEventSignUpdateInterface *pShowInterface)
	{
		if( m_pShowEventSignInterface == NULL )
		{
			m_pShowEventSignInterface  = pShowInterface;
		}
		else if( pShowInterface != NULL )
		{
			m_pShowEventSignInterface->SetNextInterfacePtr( pShowInterface );
		}
		if( pShowInterface != NULL )
		{
			pShowInterface->LinkUpdateShow();
		}
	}

	/*******************************************************************************/
	// �������ƣ� UnLinkModularBarShowInterfaces
	// ���ܣ� �Ͽ������¼���ʾ�ӿ�
	// ������ 
	//        CModularBarsShowInterfacesAggregate *pShowAggregate:      
	// ����ֵ:  
	void CBlsMainFlowVirtual::UnLinkEventSignShowInterfaces(CShowEventSignUpdateInterface *pShowInterface)
	{
		if( pShowInterface != NULL )
		{
			m_pShowEventSignInterface = (CShowEventSignUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowEventSignInterface, pShowInterface);
			pShowInterface->UnLinkUpdateShow();
		}
	}

	/*******************************************************************************/
	// �������ƣ� DoManualDispatchEventFlow
	// ���ܣ� �ֶ���ת�¼���
	// ������      
	// ����ֵ: 
	void CBlsMainFlowVirtual::DoManualDispatchEventFlow(pugi::xml_node *pEventXMLNode)
	{
		m_pAclsFlowStrategy->OnFlowStrategy(pEventXMLNode);
	}

	//����CPR�¼��Ĳ���ģʽΪ��ǰģʽ
	void CBlsMainFlowVirtual::FilterCPREventIrp(CVirEventIrp *pVirEventIrp, CBlsSimulateCase *pBlsCase)
	{
        if( pVirEventIrp->isKindOf( "CCPRStatIrp" ) && pBlsCase )
		{
			irp::CCPRStatIrp  *pCPREventIrp = (irp::CCPRStatIrp *)pVirEventIrp;
			cpr::CCPRSimulateJudgeOp *pCPRJudgeOp = pBlsCase->getCPRMessageCollect()->getCPRSimulateJudgeOp();
			if( pCPRJudgeOp != NULL && pCPREventIrp->Get_eCPRMode() == eNoneDefine )
			{
				_CPRManageState  eCPRSate = pCPRJudgeOp->get_eCPRState();
				pCPREventIrp->Set_eCPRMode( eCPRSate );
			}
		}
	}

	/*******************************************************************************/
	// �������ƣ� DoUpdateEventSignShow
	// ���ܣ� ��ʾ�¼�����Ч��
	// ������  
	//         CVirEventIrp *pVirEventIrp: 
	//         CShowEventSignUpdateInterface  *pShowEventSignInterface:
	// ����ֵ:  
	void CBlsMainFlowVirtual::DoUpdateEventSignShow(CVirEventIrp *pVirEventIrp, CShowEventSignUpdateInterface  *pShowEventSignInterface, CBlsSimulateCase *pBlsCase)
	{
		CSimulateBuildAggregate *pBuildAggregate = pBlsCase->getSimulateBuildAggregatePtr();
		//ģ��������¼�������������,��,���ܲ��,CPR�ȣ���ʾ
		if( pVirEventIrp->isKindOf( "CEventIrp_SimulateTrigger" ) )
		{
			CEventIrp_SimulateTrigger *pSimulateEventIrp = (CEventIrp_SimulateTrigger *)pVirEventIrp;
			if( pSimulateEventIrp->getName_TriggerEvent() == CSEvent_Intubate::getEvent_Intubate_Caption() )
			{
				//�����Ϣ
				short   sAct, sPosition;
				pSimulateEventIrp->explainSimulateTrigger_IntubateEventIrp(/*out*/sPosition, /*out*/sAct);
				bool   bIntubate = false;
				if( sAct == 0x11 && sPosition == 0x02 )
				{
					bIntubate = true;
				}
				pBuildAggregate->Set_EtCO2WatchLinkState( bIntubate );
			}
		}
	}

}}
