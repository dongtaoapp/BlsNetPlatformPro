#pragma once
#include <pugixml.hpp>
#include ".\BLSConfigue.h"
#include ".\BlsLogs.h"
#include ".\SceneActsCollect.h"
#include ".\IHandleIrpsCollect.h"
#include ".\IGetPhysiologyActionObj.h"

#include "..\Common\PatientTypeFactory.h"
#include "..\Common\EventHandleClockIrpOp.h"
#include "..\Common\EventHandleFrameFlowIrpOp.h"
#include "..\Common\VirTcpTransferOpGather.h"
#include "..\Common\CommonGlobal.h"


#include "..\SimulatorBase\WatchBarsShowInterfacesAggregate.h"
#include "..\SimulatorBase\IUpdateLogDataInterface.h"
#include "..\simulatorBase\ShowFrameNameUpdateInterface.h"
#include "..\simulatorBase\ShowScenarioRunTimeUpdateInterface.h"

#include "..\SimulatorSymptom\XActionVirtual.h"
#include "..\SimulatorSymptom\IModifiedSymptomsOp.h"
#include "..\SimulatorSymptom\SimulateSymptomsCollect.h"

#include "..\SimulatorEmulateBuild\SimulateBuildAggregate.h"

#include "..\physiologyWatchBar\IWatchBarsHandle.h"

#include "..\cprModuls\CPRMessageCollect.h"
#include "..\cprModuls\CPRConfigue.h"
#include "..\cprModuls\Collates.h"

#include "..\transLayer\FormatTransport.h"


using namespace jysoft::simulator;
namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ����ѵ�������а���������ģ�������������ơ�����ģ��������־��CPR�������ݵ���Ϣ
	�����ˣ�	 hjg
	����ʱ�䣺   20017/3/5
	//-----------------------------------------------------------------------------------------------------------------*/
    class SCRIPTFLOWENGINESHARED_EXPORT CBlsSimulateCase  : public irp::CEventHandleClockIrpOp
							,public irp::CEventHandleFrameFlowIrpOp
	{
		friend class CBlsMainFlowVirtual;
	public:
		CBlsSimulateCase(CSceneActsCollect *pSceneActsCollect = NULL);
		virtual ~CBlsSimulateCase(void);
	protected:
		pugi::xml_document           m_xmlScriptDoc;
		//-----------------------------------------------------------------------------------------------
		CPatientTypeFactory          m_cPatientTypeFactory;
		CBlsMainFlowVirtual *        m_pBlsFlowEnginer;        //BLS��������
		CSimulateSymptomsCollect     m_cSymotomsCollect;        //ģ�������������������Ϲ����࣬������ǰģ���״̬
		CSimulateBuildAggregate      m_cBuildAggregate;         //����ģ����������
		cpr::CCPRMessageCollect      m_cCPRMessageCollect;      //�ķθ�����Ϣ������
		log::CBlsLogs                m_cBlsLogs;
		CSceneActsCollect *			 m_pSceneActsCollect;
	protected://�Ͳ����ݴ�����
		transLayer::CFormatTransport *m_pFormatTransport;
		CBLSConfigue                 m_cBlsConfigue;
		cpr::CCPRConfigue            m_cCPRConfigue;
	private:
        unsigned long                m_uLogTime;                 //��־ʱ��
		unsigned short               m_dwCurrentFrameId;         //��ǰ�ű���ʶ��
	private:
		//ͨ����Դ·����ע����������Ӹ������ļ��Ķ�λ hjg 2012.8 add��
		std::string                  m_strCommonResourcePath; 
	protected:  //��ʾ�ӿ�ָ��;
		base::CShowScenarioRunTimeUpdateInterface*   m_pShowScenarioRunTimeInterface; //�ű�����ʱ��
		base::CShowFrameNameUpdateInterface*         m_pShowFrameNameInterface;       //��ǰ�ű�����
	public: //�ӿ�CEventHandleClockIrpOp��������
		/*******************************************************************************/
		//���ܣ�����ʱ���¼�IRP����
		//������
		//      CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool doHandleClockIrpOp(irp::CVirtualIrp *pCurrIrp);
	public: //�ӿ�CEventHandleFrameFlowIrpOp��������
		/*******************************************************************************/
		//���ܣ���������ת��IRP����
		//������
		//      CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool doHandleFrameFlowIrpOp(irp::CVirtualIrp *pCurrIrp);
	public:
		/*******************************************************************************/
		// �������ƣ� isValidateRightScenario
		// ���ܣ� �������صĽű��ļ����ж��ļ���ʽ���汾
		// ������ 
		// ����ֵ:  CString *pstrError��������Ϣ��ʾ
		bool isValidateRightScenario(const std::string &strFilePath, /*out*/std::string *pstrError);
		//�رո�����ʵʱ���ι���
		void closePhysBuilds();
		/*******************************************************************************/
		// �������ƣ� initialAclsScenario
		// ���ܣ� ���ݳ����ű��ļ�����ʼ��ACLS����ѵ�������а���
		// ������ 
		// ����ֵ:  
		bool initialAclsScenario(const std::string &resourcePath, const std::string &commonPath, bool bAsyncWatch=false);
	public:
		/*******************************************************************************/
		// �������ƣ� setCPRParameters
		// ���ܣ� ����CPR����ʱ����ѹ�������ķ�Χ
		// ������ 
		//          long  nLowerDepth��
		//          long  nOverDepth��
		//          long nLowerVolume��
		//          long  nOverVolume��
		// ����ֵ: 
		void setCPRParameters(long  nLowerDepth, long  nOverDepth, long nLowerVolume, long  nOverVolume);
		/*******************************************************************************/
		// �������ƣ� getCPRParameters
		// ���ܣ� ��ȡCPR����ʱ����ѹ�������ķ�Χ
		// ������ 
		void getCPRParameters(long  *nLowerDepth, long  *nOverDepth, long  *nLowerVolume, long  *nOverVolume);
		/*******************************************************************************/
		// �������ƣ� setMonitorSignLinkHandle
		// ���ܣ�  ģ�������źŴ���
		// ������ 
		//         BOOL bEcgLink��
		//         BOOL bSpO2Link��
		// ����ֵ: 
		void setMonitorSignLinkHandle( bool bEcgLink, bool bSpO2Link);
	public://����ؼ���ʾ����
		/*******************************************************************************/
		// �������ƣ� StartLinkCPROperatorShowInterfaces
		// ���ܣ� ��ʼ����CPR�ؼ��������ʾ�ӿ�
		// ������ 
		//        CCPRShowInterfacesAggregate *pShowAggregate:      
		// ����ֵ:  
		void StartLinkCPROperatorShowInterfaces(cpr::CCPRShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// �������ƣ� UnLinkCPROperatorShowInterfaces
		// ���ܣ� �Ͽ�CPR�ؼ��������ʾ�ӿ�
		// ������ 
		//        CCPRShowInterfacesAggregate *pShowAggregate:      
		// ����ֵ:  
		void UnLinkCPROperatorShowInterfaces(cpr::CCPRShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// �������ƣ� StartLinkWatchBarsShowInterfaces
		// ���ܣ� ��ʼ����ģ�������������ʾ�ӿ�
		// ������ 
		//        CWatchBarsShowInterfacesAggregate *pShowAggregate:      
		//        IWatchBarsHandle *pWatchBarsHandle:
		// ����ֵ:  
		void StartLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate, controls::IWatchBarsHandle *pWatchBarsHandle);
		/*******************************************************************************/
		// �������ƣ� UnLinkWatchBarsShowInterfaces
		// ���ܣ� �Ͽ�ģ�������������ʾ�ӿ�
		// ������ 
		//        CWatchBarsShowInterfacesAggregate *pShowAggregate:      
		//        IWatchBarsHandle *pWatchBarsHandle:     
		// ����ֵ:
		void UnLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate, controls::IWatchBarsHandle *pWatchBarsHandle);
		/*******************************************************************************/
		// �������ƣ� StartLinkLogShowInterface
		// ���ܣ� ��ʼ��������־��ʾ�ӿ�
		// ������ 
		//        IUpdateLogDataInterface *pUpdateLogInterface:      
		// ����ֵ:  
		void StartLinkLogShowInterface(log::IUpdateLogDataInterface *pUpdateLogInterface);
		/*******************************************************************************/
		// �������ƣ� UnLinkLogShowInterface
		// ���ܣ� �Ͽ�������־��ʾ�ӿ�
		// ������ 
		//        IUpdateLogDataInterface *pUpdateLogInterface:      
		// ����ֵ:  
		void UnLinkLogShowInterface(log::IUpdateLogDataInterface *pUpdateLogInterface);
		/*******************************************************************************/
		// �������ƣ� StopDistributeSimulateData
		// ���ܣ� ֹͣ�ַ�ʵʱ��������
		// ������ 
		// ����ֵ:  
		void StopDistributeSimulateData();
	public:
		inline pugi::xml_node getScriptXMLElement() { return m_xmlScriptDoc.document_element(); };
		//���������޸Ĳ����ӿ���
		inline ISetSimulateSymptoms * getSetSimulateSymptomsPtr() { return ( ISetSimulateSymptoms *)&m_cSymotomsCollect; };
		inline IModifiedSymptomsOp  * getModifiedSymptomsOpPtr()  { return ( IModifiedSymptomsOp * )&m_cSymotomsCollect; };
		CSimulateBuildAggregate * getSimulateBuildAggregatePtr() { return &m_cBuildAggregate; };
		//��������ָ��
		CBlsMainFlowVirtual * getBlsMainFlowPtr();
		inline CSimulateSymptomsCollect * getSimulateSymptomsCollectPtr() { return &m_cSymotomsCollect; };
		inline transLayer::CFormatTransport * getTransportLayerPtr() { return m_pFormatTransport; };
		//�����ķθ�����Ϣ������
		inline cpr::CCPRMessageCollect * getCPRMessageCollect() { return &m_cCPRMessageCollect; };
		//����Irp�����Ͻӿ�
		inline IHandleIrpsCollect * getHandleIrpsCollectPtr() { return (IHandleIrpsCollect *)m_pBlsFlowEnginer; };
		//���ص�ǰ��Ӧ���õ�Action
		IGetPhysiologyActionObj * getPhysiologyActionInterfacePtr();
		//�龰�򼯺���
		inline CSceneActsCollect * getSceneActsCollectPtr() { return m_pSceneActsCollect; };
		//������־�ӿ�ָ��
		inline log::COpLogInterface * getOpLogMessagePtr() { return  &m_cBlsLogs; };
	public:
		//�õ���������ʱ��
        unsigned long  GetAclsSimulateCaseRunTime() { return m_uLogTime; };
		// ��Ŀǰ�����ڸ�ʽ��
		std::string CurrentTimeFormat(void);
		// �趨�ű�����
		void SetScriptName(const std::string &strScripName);
		// ��ʼ�ű�������
		void OnStartScenario();
		// �ָ��ű�������
		void OnResumeScenario(bool bLogTimeToZero = true);
		// ��ͣ�ű�������
		void OnPauseScenario( bool bClearSimulator = false);
		//���ص�ǰ���еĽű�
		void OnResetScenario();
		//�жϽű��Ƿ���ͣ״̬
		bool IsPauseScenarioRun();
	public:
		//���ش������ձ���
		cpr::CBreathCollate * getBreathCollatePtr();
		//���ذ�ѹ���ձ���
		cpr::CPressureCollate * getPressureCollatePtr();
	protected:
		//����ģ�������������ơ�����ģ��������־��CPR�������ݵȵ�Ԫ�Ĺ�ϵ
		void SetUnitsRelate();
		//�����ű�������Ϣ
		virtual void parseACLSScriptConfigue( const std::string &strCommonResourcePath);
		//��ʼ��CPR��Ϣ�ռ���
		virtual void InitialCPR( const std::string &strCPRConfigueFile, const std::string &strCommonResourcePath );
	};
}}
