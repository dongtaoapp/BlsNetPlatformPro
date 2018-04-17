#pragma once
#include <list>
#include <Windows.h>
#include <pugixml.hpp>
#include <boost/thread.hpp>
#include ".\XRunFramework.h"
#include ".\XSceneActFrame.h"
#include ".\IAclsFlowStrategy.h"
#include ".\IHandleIrpsCollect.h"

#include "..\common\VirtualIrp.h"
#include "..\common\EmulateTimer.h"
#include "..\common\criticalmutex.h"

#include "..\transLayer\FormatTransport.h"

#include "..\simulatorBase\VirEventIrp.h"
#include "..\simulatorBase\ITransportOrderIrpToSimulator.h"
#include "..\simulatorBase\ShowEventSignUpdateInterface.h"


namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �ű����̴������
	�����ˣ�	 hjg
	����ʱ�䣺   2017/3/1
	//-----------------------------------------------------------------------------------------------------------------*/
	class CBlsSimulateCase;
	class CBlsMainFlowVirtual : public IHandleIrpsCollect
	{
	public:
		CBlsMainFlowVirtual(CBlsSimulateCase  *pSimulateCase, transLayer::CFormatTransport* pTransport);
		virtual ~CBlsMainFlowVirtual(void);
	public:
		// ��ʼ���г���
		void StartCurrScenario();
		// ��ͣĿǰ���еĳ���
		void PauseCurrScenario( bool bClearSimulator );
	protected://����
		std::list<irp::CVirtualIrp *>  m_IrpList;
		//------------------------------------------------------------------------
		//boost::mutex     muIrpHandle;
		boost::mutex     muPackage;
		boost::condition_variable_any    cond_IrpHandle;
		boost::condition_variable_any    cond_IrpRecv;
		utility::CEmulateTimer*          secondEumlate;
		boost::thread_group   tg;
	protected:
		CXRunFramework                  m_cRunFramework;
		IAclsFlowStrategy *             m_pAclsFlowStrategy;   //�ű����泡��ת�Ʋ���
		CBlsSimulateCase *              m_pBlsSimulateCase;    //BLS����ѵ�������а���
		simulator::base::CShowEventSignUpdateInterface * m_pShowEventSignInterface;
	protected:
		utility::CCriticalMutex          m_cHandleActionIrpMutex;
	public://�Ͳ����ݴ�����
		transLayer::CFormatTransport*   m_pFormatTransport;
	private://����
		_FlowState            m_eState;       //״̬
	public:
		// ����Ҫ�����IRP����������л�������Ӧ�Ĵ���
		bool AddNeedHandleIrp(irp::CVirtualIrp * pVirIrp);
		//������Ϣ��
		virtual void OnHandleIrp(irp::CVirtualIrp *pVirIrp);
	public:
		/*******************************************************************************/
		// �������ƣ� ResetScenario
		// ���ܣ� ����ACLS���̴�������
		// ������ 
		// ����ֵ:  
		virtual pugi::xml_node ResetScenario();
		/*******************************************************************************/
		// �������ƣ� DoFlowNextScenario
		// ���ܣ� ִ���¸�������
		// ������ 
		//       DWORD  dwFrameID:      ������ı�ʶֵ
		//       eEventSign eEvent:     
		// ����ֵ:  
		pugi::xml_node DoFlowNextScenario(unsigned short  dwFrameID, eEventSign eEvent = ES_Normal);
		/*******************************************************************************/
		// �������ƣ� DoFlowNextScenario
		// ���ܣ� ִ���¸�������
		// ������ 
		//       IXMLDOMNode *pScenarioNode:      �������Node
		//       eEventSign eEvent:     
		// ����ֵ:  
		pugi::xml_node DoFlowNextScenario(pugi::xml_node *pScenarioNode, eEventSign eEvent = ES_Normal);
		/*******************************************************************************/
		// �������ƣ� DoFlowSceneActRun
		// ���ܣ� ִ���龰���
		// ������ 
		//       DWORD dwSceneActFrameID:      �龰��ı�ʶֵ
		//       BOOL bLogoutFlow:             �Ƿ��˳�������
		//       eEventSign eEvent:     
		// ����ֵ:  
		CXSceneActFrame * DoFlowSceneActRun(unsigned short dwSceneActFrameID, bool bLogoutFlow, eEventSign eEvent = ES_Normal);
		//����ģ����ͨ�Žӿ�
		transLayer::ITransportOrderIrpToSimulator * GetTransportOrderIrpToSimulatorInterface() { return (transLayer::ITransportOrderIrpToSimulator *)m_pFormatTransport; };
		//���ص�ǰ��Ӧ���õ�Action
		inline IGetPhysiologyActionObj * Get_PhysiologyActionPtr() { return (IGetPhysiologyActionObj *)&m_cRunFramework; };
		inline IAclsFlowStrategy * Get_IAclsFlowStrategyPtr() { return m_pAclsFlowStrategy; };
		//���������״̬
		inline _FlowState Get_eFlowState() { return m_eState; };
	public:
		/*******************************************************************************/
		// �������ƣ� CreateScenario
		// ���ܣ� ���ݳ����ű��ļ�����ʼ��ACLS���̴�������
		// ������ 
		//       rootElement: 
		// ����ֵ:  
		virtual pugi::xml_node  CreateScenario( pugi::xml_node rootElement ) = 0;
	public:
		/*******************************************************************************/
		// �������ƣ� StartLinkEventSignShowInterfaces
		// ���ܣ� ��ʼ�������¼���ʾ�ӿ�
		// ������ 
		//        CModularBarsShowInterfacesAggregate *pShowAggregate:      
		// ����ֵ:  
		void StartLinkEventSignShowInterfaces(simulator::base::CShowEventSignUpdateInterface *pShowInterface);
		/*******************************************************************************/
		// �������ƣ� DoManualDispatchEventFlow
		// ���ܣ� �ֶ���ת�¼���
		// ������      
		// ����ֵ: 
		void DoManualDispatchEventFlow(pugi::xml_node *pEventXMLNode);
		/*******************************************************************************/
		// �������ƣ� UnLinkModularBarShowInterfaces
		// ���ܣ� �Ͽ������¼���ʾ�ӿ�
		// ������ 
		//        CModularBarsShowInterfacesAggregate *pShowAggregate:      
		// ����ֵ:  
		void UnLinkEventSignShowInterfaces(simulator::base::CShowEventSignUpdateInterface *pShowInterface);
	public:
		/*******************************************************************************/
		// �������ƣ� ExecInitialFramework
		// ���ܣ� ��ʼ��ִ�е�ǰ�Ľ���Actions
		// ������ 
		//   
		// ����ֵ:  
		virtual void ExecInitialFramework(SimulatePatientType ePatientType) = 0;
		/*******************************************************************************/
		// �������ƣ� DoUpdateEventSignShow
		// ���ܣ� ��ʾ�¼�����Ч��
		// ������  
		//         CVirEventIrp *pVirEventIrp: 
		//         CShowEventSignUpdateInterface  *pShowEventSignInterface:
		// ����ֵ:  
		virtual void DoUpdateEventSignShow(irp::CVirEventIrp *pVirEventIrp, simulator::base::CShowEventSignUpdateInterface  *pShowEventSignInterface, CBlsSimulateCase *pBlsCase);
		//ִ�е�ǰ�Ľ���Actions
		void ExecNextFramework(eEventSign eEvent = ES_Normal);
		//���������߳�
		bool CreateFlowThreads();
		//����CPR�¼��Ĳ���ģʽΪ��ǰģʽ
		void FilterCPREventIrp(irp::CVirEventIrp *pVirEventIrp, CBlsSimulateCase *pBlsCase);
	public:
		/*******************************************************************************/
		// �������ƣ� ExecuteAction
		// ���ܣ� ִ������������
		// ������ 
		//       IXMLDOMElement *pRootElement: 
		// ����ֵ:  
		void ExecuteActions(std::list<simulator::CXActionVirtual *> *plstVirActions, short sTransferTime = 0);
	protected:
		//ʱ���̺߳���
		void  _ThrdTimeFunc();
		//���¶˽�����Ϣ���̺߳���
		void _ThrdReceiveIrpFunc();
		//��Ϣ�������̺߳���
		void _ThrdHandleIrpFunc();
		//�Ƿ��ܴ���Irp
		bool isCanPackageHandle();
		//�Ƿ���ͨ�Ų��ϴ���Irp��
		bool isTransInUpIrps();
	};
}}
