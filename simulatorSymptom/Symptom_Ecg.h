#pragma once
#include <list>
#include <string>
#include ".\SymptomVirtual.h"
#include ".\XActionVirtual.h"

#include "..\Common\CommonGlobal.h"

#include "..\SimulatorBase\OpECGBuildInterface.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     模拟人的当前心律
	创建人：	 hjg
	创建时间：   2008/10/17
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORSYMPTOMSHARED_EXPORT CSymptom_Ecg :  public CSymptomVirtual
	{
	public:
		CSymptom_Ecg(void);
		virtual ~CSymptom_Ecg(void);
	public: //基类函数重载
		/*******************************************************************************/
		// 函数名称： IsKindOf
		// 功能：   判断体征的类别
		// 参数：   const CString &strClassName
		// 返回值: 
		virtual  bool isKindOf( const std::string &strClassName );
		//根据标示名称判断体征参数
		virtual  bool isSymptomCaption(const std::string &strCaption);
		/*******************************************************************************/
		// 函数名称： InitialSymptomValue
		// 功能：   初始化体征值
		// 参数：   IModifiedSymptomsOp *pInterfacePtr
		//          tag_TrendValue *pDefaultTrendValue:  相应体征修改的值返回
		// 返回值: 
		virtual  void InitialSymptomValue( IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType);
		/*******************************************************************************/
		// 函数名称： InitialSymptomValue
		// 功能：   初始化心电图
		// 参数：   /*out*/tag_TrendValue *pTrendValue: 
		//          CXActionVirtual *pEcgAction:
		//          short sTransTime:                    转换时间（单位：秒）
		// 返回值: 
		void InitialSymptomValue( CXActionVirtual *pVirAction, short sTransTime = 0);
		/*******************************************************************************/
		// 函数名称： isTransmitAEDState
		// 功能：   是否AED状态改变
		// 参数：   
		//          /*in,out*/unsigned char *sAEDState:        AED状态
		// 返回值: 
		virtual  bool isTransmitAEDState(/*in,out*/unsigned char *sAEDState);
		// 函数名称： OnUpdateInterfaceShow
		// 功能：   更新界面显示
		// 参数：   
		// 返回值: 
		virtual  void OnUpdateInterfaceShow();
		/*******************************************************************************/
		// 函数名称： OnLinkSimulatorBarUpdateInterfaceShow
		// 功能：   断开模拟人面板显示连接
		// 参数：   
		// 返回值:
		virtual  void OnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate );
		/*******************************************************************************/
		// 函数名称： OnUnLinkSimulatorBarUpdateInterfaceShow
		// 功能：   断开模拟人面板显示连接
		// 参数：   
		// 返回值:
		virtual  void OnUnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate );
	public:
		//初始化心电图模拟曲线构造器
		void InitialEcgBuild(SimulatePatientType ePatientType);
		//修改心电图模拟曲线构造器
		void ModifyEcgBuild(eEventSign eEventValue);
		//直接修改心电图模拟曲线构造器
		void DirectEcgBuild();
		//设置心电图模拟器操作接口
		inline void SetECGBuildInterface(base::COpECGBuildInterface *pInterface) { m_pECGBuildInterface = pInterface; };
		inline base::COpECGBuildInterface * GetECGBuildInterface() { return m_pECGBuildInterface; };
		//返回心率
		inline int  GetValue_HR() { return m_iHR; };
	public:
		//开始起搏夺获
		void StartPaceCapture();
		//修改起搏夺获后的心率
		void ModifyPaceCaptureHR(int nCaptureHR);
		//结束起搏夺获
		void StopPaceCapture();
	public:
		std::string getBasicRmShowText();
	protected:
		QRS                    m_eQRS;           //差别类型   PM_QRS = 0x00000004
		BasicRhythm            m_eBasicRm;       //基本心律   PM_BASICRHYTHM = 0x00000008
		Extrasys               m_eExtrasys;      //期外收缩（早搏） PM_EXTRASYS = 0x00000010
		int                    m_iHR;            //心跳次数   PM_HR = 0x00000020
		BOOL                   m_bEMD;           //           PM_EMD   = 0x00000100
		short                  m_sConduct;       //传导       PM_CONDUCT = 0x00000200
		short                  m_sExtendParam;   //扩展参数   PM_EXTEND  = 0x00000800
		Artifact               m_eArtifact;      //           PM_ARTIFACT = 0x00000001
		int                    m_iExtrasysRate;  //早搏的比率 PM_EXTRASYSRATE = 0x00000002
		int                    m_nPaceCaptureHR; //起搏夺获后，心率值
	private:
        unsigned long                  m_dwFields;  //用项位指名那些参数被修改，需要更新对应的界面
		SimulatePatientType    m_ePatientType;
		base::COpECGBuildInterface  *m_pECGBuildInterface; //心电图模拟器操作接口
		//-------------------------------------------------------------------------------------------
		base::CShowECGUpdateInterface *m_pEcgShowInterface;//心电图显示接口类
	};
}}
