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
	类说明：     场景训练的运行案例，包括模拟人体征、趋势、体征模拟器、日志及CPR操作数据等信息
	创建人：	 hjg
	创建时间：   20017/3/5
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
		CBlsMainFlowVirtual *        m_pBlsFlowEnginer;        //BLS流程引擎
		CSimulateSymptomsCollect     m_cSymotomsCollect;        //模拟人生理体征参数集合管理类，存贮当前模拟的状态
		CSimulateBuildAggregate      m_cBuildAggregate;         //体征模拟器集合类
		cpr::CCPRMessageCollect      m_cCPRMessageCollect;      //心肺复苏信息集合类
		log::CBlsLogs                m_cBlsLogs;
		CSceneActsCollect *			 m_pSceneActsCollect;
	protected://低层数据传输类
		transLayer::CFormatTransport *m_pFormatTransport;
		CBLSConfigue                 m_cBlsConfigue;
		cpr::CCPRConfigue            m_cCPRConfigue;
	private:
        unsigned long                m_uLogTime;                 //日志时间
		unsigned short               m_dwCurrentFrameId;         //当前脚本标识号
	private:
		//通用资源路径【注：用于自添加辅助项文件的定位 hjg 2012.8 add】
		std::string                  m_strCommonResourcePath; 
	protected:  //显示接口指针;
		base::CShowScenarioRunTimeUpdateInterface*   m_pShowScenarioRunTimeInterface; //脚本运行时间
		base::CShowFrameNameUpdateInterface*         m_pShowFrameNameInterface;       //当前脚本名称
	public: //接口CEventHandleClockIrpOp函数重载
		/*******************************************************************************/
		//功能：处理时钟事件IRP函数
		//参数：
		//      CVirtualIrp *pCurrIrp：
		//返回值:  后续不再处理（FALSE);
		virtual bool doHandleClockIrpOp(irp::CVirtualIrp *pCurrIrp);
	public: //接口CEventHandleFrameFlowIrpOp函数重载
		/*******************************************************************************/
		//功能：处理场景框转移IRP函数
		//参数：
		//      CVirtualIrp *pCurrIrp：
		//返回值:  后续不再处理（FALSE);
		virtual bool doHandleFrameFlowIrpOp(irp::CVirtualIrp *pCurrIrp);
	public:
		/*******************************************************************************/
		// 函数名称： isValidateRightScenario
		// 功能： 解析加载的脚本文件，判断文件格式及版本
		// 参数： 
		// 返回值:  CString *pstrError：错误信息提示
		bool isValidateRightScenario(const std::string &strFilePath, /*out*/std::string *pstrError);
		//关闭各体征实时波形构建
		void closePhysBuilds();
		/*******************************************************************************/
		// 函数名称： initialAclsScenario
		// 功能： 根据场景脚本文件，初始化ACLS场景训练的运行案例
		// 参数： 
		// 返回值:  
		bool initialAclsScenario(const std::string &resourcePath, const std::string &commonPath, bool bAsyncWatch=false);
	public:
		/*******************************************************************************/
		// 函数名称： setCPRParameters
		// 功能： 设置CPR操作时，按压及吹气的范围
		// 参数： 
		//          long  nLowerDepth：
		//          long  nOverDepth：
		//          long nLowerVolume：
		//          long  nOverVolume：
		// 返回值: 
		void setCPRParameters(long  nLowerDepth, long  nOverDepth, long nLowerVolume, long  nOverVolume);
		/*******************************************************************************/
		// 函数名称： getCPRParameters
		// 功能： 获取CPR操作时，按压及吹气的范围
		// 参数： 
		void getCPRParameters(long  *nLowerDepth, long  *nOverDepth, long  *nLowerVolume, long  *nOverVolume);
		/*******************************************************************************/
		// 函数名称： setMonitorSignLinkHandle
		// 功能：  模拟监控器信号处理
		// 参数： 
		//         BOOL bEcgLink：
		//         BOOL bSpO2Link：
		// 返回值: 
		void setMonitorSignLinkHandle( bool bEcgLink, bool bSpO2Link);
	public://界面控件显示连接
		/*******************************************************************************/
		// 函数名称： StartLinkCPROperatorShowInterfaces
		// 功能： 初始连接CPR控件的相关显示接口
		// 参数： 
		//        CCPRShowInterfacesAggregate *pShowAggregate:      
		// 返回值:  
		void StartLinkCPROperatorShowInterfaces(cpr::CCPRShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// 函数名称： UnLinkCPROperatorShowInterfaces
		// 功能： 断开CPR控件的相关显示接口
		// 参数： 
		//        CCPRShowInterfacesAggregate *pShowAggregate:      
		// 返回值:  
		void UnLinkCPROperatorShowInterfaces(cpr::CCPRShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// 函数名称： StartLinkWatchBarsShowInterfaces
		// 功能： 初始连接模拟监控面板的相关显示接口
		// 参数： 
		//        CWatchBarsShowInterfacesAggregate *pShowAggregate:      
		//        IWatchBarsHandle *pWatchBarsHandle:
		// 返回值:  
		void StartLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate, controls::IWatchBarsHandle *pWatchBarsHandle);
		/*******************************************************************************/
		// 函数名称： UnLinkWatchBarsShowInterfaces
		// 功能： 断开模拟监控面板的相关显示接口
		// 参数： 
		//        CWatchBarsShowInterfacesAggregate *pShowAggregate:      
		//        IWatchBarsHandle *pWatchBarsHandle:     
		// 返回值:
		void UnLinkWatchBarsShowInterfaces(CWatchBarsShowInterfacesAggregate *pShowAggregate, controls::IWatchBarsHandle *pWatchBarsHandle);
		/*******************************************************************************/
		// 函数名称： StartLinkLogShowInterface
		// 功能： 初始化连接日志显示接口
		// 参数： 
		//        IUpdateLogDataInterface *pUpdateLogInterface:      
		// 返回值:  
		void StartLinkLogShowInterface(log::IUpdateLogDataInterface *pUpdateLogInterface);
		/*******************************************************************************/
		// 函数名称： UnLinkLogShowInterface
		// 功能： 断开连接日志显示接口
		// 参数： 
		//        IUpdateLogDataInterface *pUpdateLogInterface:      
		// 返回值:  
		void UnLinkLogShowInterface(log::IUpdateLogDataInterface *pUpdateLogInterface);
		/*******************************************************************************/
		// 函数名称： StopDistributeSimulateData
		// 功能： 停止分发实时构造数据
		// 参数： 
		// 返回值:  
		void StopDistributeSimulateData();
	public:
		inline pugi::xml_node getScriptXMLElement() { return m_xmlScriptDoc.document_element(); };
		//生理体征修改操作接口类
		inline ISetSimulateSymptoms * getSetSimulateSymptomsPtr() { return ( ISetSimulateSymptoms *)&m_cSymotomsCollect; };
		inline IModifiedSymptomsOp  * getModifiedSymptomsOpPtr()  { return ( IModifiedSymptomsOp * )&m_cSymotomsCollect; };
		CSimulateBuildAggregate * getSimulateBuildAggregatePtr() { return &m_cBuildAggregate; };
		//返回引擎指针
		CBlsMainFlowVirtual * getBlsMainFlowPtr();
		inline CSimulateSymptomsCollect * getSimulateSymptomsCollectPtr() { return &m_cSymotomsCollect; };
		inline transLayer::CFormatTransport * getTransportLayerPtr() { return m_pFormatTransport; };
		//返回心肺复苏信息集合类
		inline cpr::CCPRMessageCollect * getCPRMessageCollect() { return &m_cCPRMessageCollect; };
		//返回Irp处理集合接口
		inline IHandleIrpsCollect * getHandleIrpsCollectPtr() { return (IHandleIrpsCollect *)m_pBlsFlowEnginer; };
		//返回当前对应设置的Action
		IGetPhysiologyActionObj * getPhysiologyActionInterfacePtr();
		//情景框集合类
		inline CSceneActsCollect * getSceneActsCollectPtr() { return m_pSceneActsCollect; };
		//返回日志接口指针
		inline log::COpLogInterface * getOpLogMessagePtr() { return  &m_cBlsLogs; };
	public:
		//得到场景运行时间
        unsigned long  GetAclsSimulateCaseRunTime() { return m_uLogTime; };
		// 将目前的日期格式化
		std::string CurrentTimeFormat(void);
		// 设定脚本名称
		void SetScriptName(const std::string &strScripName);
		// 开始脚本的运行
		void OnStartScenario();
		// 恢复脚本的运行
		void OnResumeScenario(bool bLogTimeToZero = true);
		// 暂停脚本的运行
		void OnPauseScenario( bool bClearSimulator = false);
		//重载当前运行的脚本
		void OnResetScenario();
		//判断脚本是否暂停状态
		bool IsPauseScenarioRun();
	public:
		//返回吹气对照表类
		cpr::CBreathCollate * getBreathCollatePtr();
		//返回按压对照表类
		cpr::CPressureCollate * getPressureCollatePtr();
	protected:
		//设置模拟人体征、趋势、体征模拟器、日志及CPR操作数据等单元的关系
		void SetUnitsRelate();
		//解析脚本配置信息
		virtual void parseACLSScriptConfigue( const std::string &strCommonResourcePath);
		//初始化CPR信息收集类
		virtual void InitialCPR( const std::string &strCPRConfigueFile, const std::string &strCommonResourcePath );
	};
}}
