#include <algorithm>
#include <fstream>
#include <boost/assert.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include ".\BlsSimulateCase.h"
#include ".\BlsMainFlowVirtual.h"
#include ".\BlsMainFlowOwn.h"
#include ".\BlsMainFlowWatch.h"
#include ".\ParseShapeFactory.h"

#include "..\simulatorBase\EventIrp_ClockTime.h"
#include "..\simulatorBase\FrameFlowIrp.h"


#include "..\common\CommonGlobal.h"
#include "..\common\EventHandleCPRStatIrpOp.h"


using namespace jysoft::irp;
using namespace jysoft::network;
using namespace jysoft::utility;
using namespace jysoft::transLayer;
namespace jysoft { namespace flowEngine 
{
	CBlsSimulateCase::CBlsSimulateCase(CSceneActsCollect *pSceneActsCollect/*=NULL*/)
	{
		m_pBlsFlowEnginer = NULL;
		m_pFormatTransport   = NULL;;
		//------------------------------------------------------------------------
		m_pShowScenarioRunTimeInterface  = NULL;
		m_pShowFrameNameInterface        = NULL;

		m_uLogTime           = 0;
		m_dwCurrentFrameId   = 0;
		m_pSceneActsCollect  = pSceneActsCollect;
		//Ĭ��ΪV1.0�汾ͨ��Э��
		m_pFormatTransport   = new CFormatTransport( 10 );
	}

	CBlsSimulateCase::~CBlsSimulateCase(void)
	{
		m_cBuildAggregate.ClosePhysBuilds();
		if( m_pBlsFlowEnginer != NULL )
		{
			delete m_pBlsFlowEnginer;
		}
		//-----------------------------------------------
		delete m_pFormatTransport;
	}

	/*******************************************************************************/
	// �������ƣ� isValidateRightScenario
	// ���ܣ� �������صĽű��ļ����ж��ļ���ʽ���汾
	// ������ 
	// ����ֵ:  string *pstrError��������Ϣ��ʾ
	bool CBlsSimulateCase::isValidateRightScenario(const std::string &strFilePath, /*out*/std::string *pstrError)
	{
		std::ifstream stream( strFilePath.c_str() );
		pugi::xml_parse_result result = m_xmlScriptDoc.load(stream);
		//��֤�ű��ļ�...
		if( result == true)
		{
			;
		}
		return true;
	}

	/*******************************************************************************/
	// �������ƣ� initialAclsScenario
	// ���ܣ� ���ݳ����ű��ļ�����ʼ��ACLS����ѵ�������а���
	// ������ 
	// ����ֵ:  
	bool CBlsSimulateCase::initialAclsScenario(const std::string &resourcePath, const std::string &commonPath, bool bAsyncWatch/*=false*/)
	{
		bool                 bInitialSec  = false;
		//�����ű�������Ϣ
		parseACLSScriptConfigue( commonPath );
		//��ʼ��CPR��Ϣ�ռ���
		boost::format fmt("%s\\configure\\scriptCPRRule.config");
		fmt % commonPath;
		InitialCPR( fmt.str(), commonPath );
		//����ģ�������������ơ�����ģ��������־��CPR�������ݵȵ�Ԫ
		if( !bAsyncWatch )
		{
			m_pBlsFlowEnginer  = new CBlsMainFlowOwn( this, m_pFormatTransport );
		}
		else
		{
			m_pBlsFlowEnginer  = new CBlsMainFlowWatch( this, m_pFormatTransport );
		}
		
		//����������������໥Լ����ϵ
		m_cSymotomsCollect.LoadSymptomsRelateRestrict();
		//���ø���Ԫ�໥�Ĺ�ϵ
		SetUnitsRelate();
		//��ʼ��������������ص�ָ���趨
		m_cBuildAggregate.InitialPhysBuildsRelationAndResources(resourcePath);
		//����BLS���̴�������
		pugi::xml_node xmlScenarioNode = m_pBlsFlowEnginer->CreateScenario( getScriptXMLElement() );
		if( !xmlScenarioNode.empty() )
		{
			m_cSymotomsCollect.initialSimulateSymptomsBuild( SPT_Adult );
			//����ģ����
			m_cBuildAggregate.StartSimulateBuild();
			bInitialSec  = true;
		}
		//���ؽű����龰��
		if( m_pSceneActsCollect != NULL )
		{
			IGetPhysiologyActionObj *pIGetActionObj = getPhysiologyActionInterfacePtr();
			m_pSceneActsCollect->InitialScriptSceneActs( getScriptXMLElement(), pIGetActionObj, m_pFormatTransport);
			//����ȫ���龰��
			m_pSceneActsCollect->ActiveSceneActsRun();
		}
		//������޸������ı�ʶ
		IModifiedSymptomsOp  *pModifiedSymptomsOp = getModifiedSymptomsOpPtr();
		pModifiedSymptomsOp->emptyModifiedSymptomsFlag( );
		m_uLogTime  = 0;
		//ͨ����Դ·��
		m_strCommonResourcePath = commonPath;
		return bInitialSec;
	}

	//�����ű�������Ϣ
	void CBlsSimulateCase::parseACLSScriptConfigue( const std::string &strCommonResourcePath)
	{
		boost::format fmtCommon("%s\\configure\\blsConfig.ini");
		fmtCommon % strCommonResourcePath;
		m_cBlsConfigue.parseBLSConfigue(fmtCommon.str());
	}

	//��ʼ��CPR��Ϣ�ռ���
	void CBlsSimulateCase::InitialCPR( const std::string &strCPRConfigueFile, const std::string &strCommonResourcePath )
	{
		//����CPR������Ϣ
		m_cCPRConfigue.loadCPRConfigue( strCPRConfigueFile );
		//��ʼ��CCPRMessageCollect
		transLayer::ITransportOrderIrpToUp  *pTransUpOrderInterface = (transLayer::ITransportOrderIrpToUp *)m_pFormatTransport;
		m_cCPRMessageCollect.initialCPR( &m_cCPRConfigue, pTransUpOrderInterface, &m_cBlsLogs);
	}

	//����ģ�������������ơ�����ģ��������־��CPR�������ݵȵ�Ԫ�Ĺ�ϵ
	void CBlsSimulateCase::SetUnitsRelate()
	{
		//����������������ģ����������Ĺ�ϵ
		COpPhysBuildInterfacesAggregate *pPhysBuildInterfacesAggregate = (COpPhysBuildInterfacesAggregate *)&m_cBuildAggregate;
		m_cSymotomsCollect.LinkSimulateBuildInterfaces( pPhysBuildInterfacesAggregate );
		//����ͨ�Žӿ�ָ��
		ITransportOrderIrpToSimulator *pTransportInterface = m_pBlsFlowEnginer->GetTransportOrderIrpToSimulatorInterface();
		m_cSymotomsCollect.set_TransportOrderIrpToSimulatorInterface(  pTransportInterface );
		//�����������ô���ӿ�
		CEventHandleClockIrpOp *pAclsCaseHandleClockIrpOp = (CEventHandleClockIrpOp *)this;
		m_pBlsFlowEnginer->addNewHandleIrpObj(pAclsCaseHandleClockIrpOp, eClock_Event);
		CEventHandleFrameFlowIrpOp *pAclsCaseFrameFlowHandleIrpOp = (CEventHandleFrameFlowIrpOp *)this;
		m_pBlsFlowEnginer->addNewHandleIrpObj(pAclsCaseFrameFlowHandleIrpOp, eFrameModify_Event);
		//����CPRʵʱ���ô���ӿ�
		CRealTimeDataHandleIrpOp *pRealTimeInterface = (CRealTimeDataHandleIrpOp *)&m_cCPRMessageCollect;
		m_pBlsFlowEnginer->addNewHandleIrpObj(pRealTimeInterface, eRealTimeData);
		CEventHandleClockIrpOp *pCPRClockIrpOp = (CEventHandleClockIrpOp *)&m_cCPRMessageCollect;
		m_pBlsFlowEnginer->addNewHandleIrpObj(pCPRClockIrpOp, eClock_Event);
		pRealTimeInterface = (CRealTimeDataHandleIrpOp *)&m_cSymotomsCollect;
		m_pBlsFlowEnginer->addNewHandleIrpObj(pRealTimeInterface, eRealTimeData);
		//CPR״̬�¼���hjg �����2010.11.30
		CEventHandleCPRStatIrpOp  *pCPRStatIrpOp = (CEventHandleCPRStatIrpOp *)&m_cSymotomsCollect;
		m_pBlsFlowEnginer->addNewHandleIrpObj(pCPRStatIrpOp, eCPR_Stat);
		//���������������Ϲ������Irp����
		CEventHandleClockIrpOp *pSymptomsHandleClockIrpOp = (CEventHandleClockIrpOp *)&m_cSymotomsCollect;
		m_pBlsFlowEnginer->addNewHandleIrpObj(pSymptomsHandleClockIrpOp, eClock_Event);
		CEventHandleCustomIrpOp *pCustomEventIrpOp = (CEventHandleCustomIrpOp *)&m_cSymotomsCollect;
		m_pBlsFlowEnginer->addNewHandleEventIrpObj( pCustomEventIrpOp );

		//�����龰�򼯺Ϲ������Irp����  hjg 2013.12.6
		if( m_pSceneActsCollect != NULL )
		{
			CEventHandleClockIrpOp *pSceneActHandleClockIrpOp = m_pSceneActsCollect;
			m_pBlsFlowEnginer->addNewHandleIrpObj( pSceneActHandleClockIrpOp, eClock_Event, true );
			CEventHandleCustomIrpOp *pCustomSceneActEventIrpOp = m_pSceneActsCollect;
			m_pBlsFlowEnginer->addNewHandleEventIrpObj( pCustomSceneActEventIrpOp, true );
		}
	}

	/*******************************************************************************/
	// �������ƣ� StartLinkWatchBarsShowInterfaces
	// ���ܣ� ��ʼ����ģ�������������ʾ�ӿ�
	// ������ 
	//        CWatchBarsShowInterfacesAggregate *pShowAggregate:      
	//        IWatchBarsHandle *pWatchBarsHandle:
	// ����ֵ:  
	void CBlsSimulateCase::StartLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate, controls::IWatchBarsHandle *pWatchBarsHandle)
	{
		//���ģ��������ֵ
		m_cSymotomsCollect.StartLinkWatchBarsShowInterfaces( pShowAggregate );
		//���ģ��������
		COpPhysBuildInterfacesAggregate  *pOpPhysBuilds = (COpPhysBuildInterfacesAggregate *)&m_cBuildAggregate;
		pWatchBarsHandle->OnDefineWatchedSimulateTypeHandle(SPT_Adult, pOpPhysBuilds);
		pWatchBarsHandle->OnStartWatchPhysBuilds( pOpPhysBuilds );
	}

	/*******************************************************************************/
	// �������ƣ� UnLinkWatchBarsShowInterfaces
	// ���ܣ� �Ͽ�ģ�������������ʾ�ӿ�
	// ������ 
	//        CWatchBarsShowInterfacesAggregate *pShowAggregate:      
	//        IWatchBarsHandle *pWatchBarsHandle:     
	// ����ֵ:
	void CBlsSimulateCase::UnLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate, controls::IWatchBarsHandle *pWatchBarsHandle)
	{
		//�Ͽ�ģ��������ֵ
		m_cSymotomsCollect.UnLinkWatchBarsShowInterfaces( pShowAggregate );
		//�Ͽ�ģ��������
		COpPhysBuildInterfacesAggregate  *pOpPhysBuilds = (COpPhysBuildInterfacesAggregate *)&m_cBuildAggregate;
		pWatchBarsHandle->OnCutWatchPhysBuilds( pOpPhysBuilds );
	}

	/*******************************************************************************/
	// �������ƣ� StartLinkLogShowInterface
	// ���ܣ� ��ʼ��������־��ʾ�ӿ�
	// ������ 
	//        IUpdateLogDataInterface *pUpdateLogInterface:      
	// ����ֵ:  
	void CBlsSimulateCase::StartLinkLogShowInterface(log::IUpdateLogDataInterface *pUpdateLogInterface)
	{

	}

	/*******************************************************************************/
	// �������ƣ� UnLinkLogShowInterface
	// ���ܣ� �Ͽ�������־��ʾ�ӿ�
	// ������ 
	//        IUpdateLogDataInterface *pUpdateLogInterface:      
	// ����ֵ:  
	void CBlsSimulateCase::UnLinkLogShowInterface(log::IUpdateLogDataInterface *pUpdateLogInterface)
	{

	}

	/*******************************************************************************/
	// �������ƣ� StopDistributeSimulateData
	// ���ܣ� ֹͣ�ַ�ʵʱ��������
	// ������ 
	// ����ֵ:  
	void CBlsSimulateCase::StopDistributeSimulateData()
	{
		m_cBuildAggregate.StopSimulateBuilds();
	}

	//��������ָ��
	CBlsMainFlowVirtual * CBlsSimulateCase::getBlsMainFlowPtr()
	{
		return m_pBlsFlowEnginer;
	}

	//���ص�ǰ��Ӧ���õ�Action
	IGetPhysiologyActionObj * CBlsSimulateCase::getPhysiologyActionInterfacePtr()
	{
		if( m_pBlsFlowEnginer != NULL )
		{
			return m_pBlsFlowEnginer->Get_PhysiologyActionPtr();
		}
		return NULL;
	}

	//�رո�����ʵʱ���ι���
	void CBlsSimulateCase::closePhysBuilds()
	{
		//ֹͣ�ַ�ʵʱ��������
		StopDistributeSimulateData();
		m_cBuildAggregate.ClosePhysBuilds();
	}

	//���ش������ձ���
	cpr::CBreathCollate * CBlsSimulateCase::getBreathCollatePtr()
	{
		return &m_cCPRMessageCollect.m_cBreathCollate;
	}

	//���ذ�ѹ���ձ���
	cpr::CPressureCollate * CBlsSimulateCase::getPressureCollatePtr()
	{
		return &m_cCPRMessageCollect.m_cPressureCollate;
	}

	/*******************************************************************************/
	// �������ƣ� StartLinkCPROperatorShowInterfaces
	// ���ܣ� ��ʼ����CPR�ؼ��������ʾ�ӿ�
	// ������ 
	//        CCPRShowInterfacesAggregate *pShowAggregate:      
	// ����ֵ:  
	void CBlsSimulateCase::StartLinkCPROperatorShowInterfaces(cpr::CCPRShowInterfacesAggregate *pShowAggregate)
	{
		//����ĵ�ͼ�Ͱ�ѹ�¼���֪ͨ hjg 2016.9.8 add
		cpr::CShowCPRActUpdateInterface *pShowCPRDetailAct = dynamic_cast<cpr::CShowCPRActUpdateInterface *>(&m_cBuildAggregate);
		cpr::CShowCPRActUpdateInterface *pShowCPRDetailAct2 = dynamic_cast<cpr::CShowCPRActUpdateInterface *>(&m_cSymotomsCollect);
		pShowAggregate->Set_ShowCPRDetailActUpdateInterface(pShowCPRDetailAct);
		pShowAggregate->Set_ShowCPRDetailActUpdateInterface(pShowCPRDetailAct2);
		//��ʼ����CPR�ؼ��������ʾ�ӿ�
		m_cCPRMessageCollect.startLinkCPRShowInterfaces( pShowAggregate );
	}

	/*******************************************************************************/
	// �������ƣ� UnLinkCPROperatorShowInterfaces
	// ���ܣ� �Ͽ�CPR�ؼ��������ʾ�ӿ�
	// ������ 
	//        CCPRShowInterfacesAggregate *pShowAggregate:      
	// ����ֵ:  
	void CBlsSimulateCase::UnLinkCPROperatorShowInterfaces(cpr::CCPRShowInterfacesAggregate *pShowAggregate)
	{
		m_cCPRMessageCollect.unLinkCPRShowInterfaces( pShowAggregate );
		//�Ƴ��ĵ�ͼ�Ͱ�ѹ�¼���֪ͨ hjg 2016.9.8 add
		cpr::CShowCPRActUpdateInterface *pShowCPRDetailAct = dynamic_cast<cpr::CShowCPRActUpdateInterface *>(&m_cBuildAggregate);
		pShowAggregate->Remove_ShowCPRDetailActUpdateInterface( pShowCPRDetailAct );
		cpr::CShowCPRActUpdateInterface *pShowCPRDetailAct2 = dynamic_cast<cpr::CShowCPRActUpdateInterface *>(&m_cSymotomsCollect);
		pShowAggregate->Remove_ShowCPRDetailActUpdateInterface( pShowCPRDetailAct2 );
	}

	/*******************************************************************************/
	//���ܣ�����ʱ���¼�IRP����
	//������
	//      CVirtualIrp *pCurrIrp��
	//����ֵ:  �������ٴ���FALSE);
	bool CBlsSimulateCase::doHandleClockIrpOp(CVirtualIrp *pCurrIrp)
	{
#ifdef  _DEBUG
        if( !pCurrIrp->isKindOf( "CEventIrp_ClockTime" ) )
		{
            BOOST_ASSERT( 0 );
		}
#endif
		CEventIrp_ClockTime  *pEventClockTime = (CEventIrp_ClockTime *)pCurrIrp;
		m_uLogTime += pEventClockTime->GetValue_ClockEvent();
		//���³�������ʱ����ʾ
		if( m_pShowScenarioRunTimeInterface != NULL )
		{
			m_pShowScenarioRunTimeInterface->OnShowScenarioRunTimeUpdate( m_uLogTime );
		}
		m_cBlsLogs.SetScriptRunTime( m_uLogTime );
		return true;
	}

	/*******************************************************************************/
	//���ܣ���������ת��IRP����
	//������
	//      CVirtualIrp *pCurrIrp��
	//����ֵ:  �������ٴ���FALSE);
	bool CBlsSimulateCase::doHandleFrameFlowIrpOp(CVirtualIrp *pCurrIrp)
	{	
#ifdef  _DEBUG
		if( !pCurrIrp->isKindOf( "CFrameFlowIrp" ) )
		{
            BOOST_ASSERT( 0 );
		}
#endif
		/*CFrameFlowIrp  *pFrameFlowEvent = (CFrameFlowIrp *)pCurrIrp;
		IXMLDOMNode *pDestScenarioNode = NULL;
		switch( pFrameFlowEvent->m_eSceneAct )
		{
		case DSS_SceneSwitch:
			{
				if( pFrameFlowEvent->m_pScenarioNode != NULL )
				{
					pDestScenarioNode = m_pAclsFlowEnginer->DoFlowNextScenario(pFrameFlowEvent->m_pScenarioNode, pFrameFlowEvent->m_eEvent);
				}
				else
				{
					pDestScenarioNode = m_pAclsFlowEnginer->DoFlowNextScenario(pFrameFlowEvent->m_dwFrameId, pFrameFlowEvent->m_eEvent);
				}
				//��־��Ϣ
				std::string  strScriptTime = CurrentTimeFormat();
				m_pLogMessages->OnRunScenarioLog(strScriptTime, pDestScenarioNode);
				//��ǰ�������Ƶ���ʾ
				if( m_pShowFrameNameInterface != NULL )
				{
					m_pShowFrameNameInterface->OnShowFrameNameUpdate( pFrameFlowEvent->m_dwFrameId );
				}
				break;
			}
		case DSS_SceneActSchedule:
		case DSS_Logouted:
			{
				BOOL  bLogoutFlow = pFrameFlowEvent->m_eSceneAct == DSS_Logouted ? TRUE : FALSE;
				//�龰���Ȼ��˳�����
				CXSceneActFrame *pDestSceneActFrame = m_pAclsFlowEnginer->DoFlowSceneActRun(pFrameFlowEvent->m_dwFrameId, bLogoutFlow, pFrameFlowEvent->m_eEvent);
				std::string    strFrameId = boost::lexical_cast<std::string>(pFrameFlowEvent->m_dwFrameId);
				IXMLDOMElement *pRootElement = NULL;
				Get_XMLDOMDocumentPtr()->get_documentElement( &pRootElement );
				pDestScenarioNode = CXRunFramework::SearchFrameXMLDOMNodePtr( pRootElement, strFrameId, _T("SceneActFrame") );
				if( pDestSceneActFrame != NULL && pDestScenarioNode )
				{
					//��־��Ϣ
					std::string  strScriptTime = CurrentTimeFormat();
					m_pLogMessages->OnRunScenarioLog(strScriptTime, pDestScenarioNode);
				}
				pRootElement->Release();
				break;
			}
		}*/
		return true;
	}

	// ��Ŀǰ�����ڸ�ʽ��
	std::string  CBlsSimulateCase::CurrentTimeFormat(void)
	{
		boost::format fmt("%d:%02d:%02d");
		fmt % (m_uLogTime/3600) % ((m_uLogTime%3600)/60) % (m_uLogTime%60);
		return fmt.str();
	}

	// ��ʼ�ű�������
	void CBlsSimulateCase::OnStartScenario()
	{
		if( IsPauseScenarioRun() && m_pBlsFlowEnginer )
		{
			//�����ű����������
			m_pBlsFlowEnginer->StartCurrScenario( );
		}
	}

	// �ָ��ű�������
	void CBlsSimulateCase::OnResumeScenario(bool bLogTimeToZero/*=true*/)
	{
		// ��ͣ�ű�������
		if( bLogTimeToZero == true )
		{
			m_uLogTime  = 0;
			if( m_pShowScenarioRunTimeInterface != NULL )
			{
				m_pShowScenarioRunTimeInterface->OnShowScenarioRunTimeUpdate( m_uLogTime );
			}
		}
		//�����ű����������
		m_pBlsFlowEnginer->StartCurrScenario( );
	}

	// ��ͣ�ű�������
	void CBlsSimulateCase::OnPauseScenario(bool bClearSimulator/*=false*/)
	{
		if( !IsPauseScenarioRun() && m_pBlsFlowEnginer )
		{
			//��ͣ�ű����������
			m_pBlsFlowEnginer->PauseCurrScenario( bClearSimulator );
		}
	}

	//���ص�ǰ���еĽű�
	void CBlsSimulateCase::OnResetScenario()
	{
		m_pBlsFlowEnginer->PauseCurrScenario( true );
		// ��ͣ�ű�������
		m_uLogTime  = 0;
		if( m_pShowScenarioRunTimeInterface != NULL )
		{
			m_pShowScenarioRunTimeInterface->OnShowScenarioRunTimeUpdate( m_uLogTime );
		}
		//����CPR..
		m_cCPRMessageCollect.resetCPROperatorMessage( eNoneDefine );
		//����������е����ƣ����ָ���ʼ״̬
		m_cSymotomsCollect.emptyModifiedSymptomsFlag();
		//���ýű����������
		m_pBlsFlowEnginer->ResetScenario( );
		//���ô��䴦��
		m_pFormatTransport->ResetTransportHandle();
		//������־
		m_cBlsLogs.OnResetScenarioLog();
	
		//����ģ����
		m_cSymotomsCollect.DirectModifySymptomsBuild( true );
		//�����龰������ hjg 2013.12.6 add
		if( m_pSceneActsCollect != NULL )
		{
			m_pSceneActsCollect->ActiveSceneActsRun();
		}
		//������޸������ı�ʶ
		IModifiedSymptomsOp  *pModifiedSymptomsOp = getModifiedSymptomsOpPtr();
		pModifiedSymptomsOp->ModifiedSymptomsUpdateShow( true );
		//��ǰ���������ʾ
		if( m_pShowFrameNameInterface != NULL )
		{
			m_pShowFrameNameInterface->OnShowFrameNameUpdate( m_dwCurrentFrameId );
		}
	}

	//�жϽű��Ƿ���ͣ״̬
	bool CBlsSimulateCase::IsPauseScenarioRun()
	{
		if( m_pBlsFlowEnginer != NULL )
		{
			_FlowState  eState = m_pBlsFlowEnginer->Get_eFlowState();
			if( eState == eFlowRun )
			{
				return false;
			}
		}
		return true;
	}

	/*******************************************************************************/
	// �������ƣ� setCPRParameters
	// ���ܣ� ����CPR����ʱ����ѹ�������ķ�Χ
	// ������ 
	//          long  nLowerDepth��
	//          long  nOverDepth��
	//          long nLowerVolume��
	//          long  nOverVolume��
	// ����ֵ: 
	void CBlsSimulateCase::setCPRParameters(long  nLowerDepth, long  nOverDepth, long nLowerVolume, long  nOverVolume)
	{
		m_cCPRConfigue.set_LowerPressureDepth( nLowerDepth );
		m_cCPRConfigue.setOverPressureDepth( nOverDepth );
		m_cCPRConfigue.setLowerBreathVolume( nLowerVolume );
		m_cCPRConfigue.setOverBreathVolume( nOverVolume );

		m_cCPRMessageCollect.modifyCPRJudgeRange((int)nLowerDepth, (int)nOverDepth, (int)nLowerVolume, (int)nOverVolume);
	}

	/*******************************************************************************/
	// �������ƣ� getCPRParameters
	// ���ܣ� ��ȡCPR����ʱ����ѹ�������ķ�Χ
	// ������ 
	void CBlsSimulateCase::getCPRParameters(long  *nLowerDepth, long  *nOverDepth, long  *nLowerVolume, long  *nOverVolume)
	{
		//��ѹ��Сֵ
		*nLowerDepth   = m_cCPRConfigue.getLowerPressureDepth();
		//��ѹ���ֵ
		*nOverDepth    = m_cCPRConfigue.getOverPressureDepth();
		//��������Сֵ
		*nLowerVolume  = m_cCPRConfigue.getLowerBreathVolume();
		//���������ֵ
		*nOverVolume   = m_cCPRConfigue.getOverBreathVolume();
	}

}}
