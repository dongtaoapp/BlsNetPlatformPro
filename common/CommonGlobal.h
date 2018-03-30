#pragma once
#include ".\common_global.h"

#include <vector>
#include <string>
#include <list>
#include "boost/tuple/tuple.hpp"
#include <boost/dynamic_bitset.hpp>


#define  DEFINITE          0.00001    //两小数点比较近似相等值
//====================================================================================================
//指定心律参数宏
#define  PM_ARTIFACT            0x00000001
#define  PM_EXTRASYSRATE        0x00000002
#define  PM_QRS                 0x00000004
#define  PM_BASICRHYTHM         0x00000008
#define  PM_EXTRASYS            0x00000010
#define  PM_HR                  0x00000020
#define  PM_SIZE                0x00000040
#define  PM_SPEED               0x00000080
#define  PM_EMD                 0x00000100
#define  PM_CONDUCT             0x00000200
#define  PM_HRPER               0x00000400
#define  PM_EXTEND              0x00000800
//----------------------------------------------------------------------------------------------------

//消息定义
#define WM_REVCONTROLCMD_MESS                WM_USER + 401
#define WM_PATIENTINFOSHOW_MESS             (WM_USER + 402)  //患者信息显示消息
#define WM_POPUPSETRHYTHM_MESS               WM_USER + 500
#define WM_DISCANCLOSEVIEW_MESS              WM_USER + 504   //是否能关闭窗口
#define WM_ACCEPTCOMPLETE_MESS               WM_USER + 509   //接收完数据
#define WM_DOUBLECLICKITEM_MESS             (WM_USER + 510)  //双击列表条目消息
#define WM_CONTROLSYNCSWITCH_MESS           (WM_USER + 511)  //同步切换控件消息，显示关联部件；(WPARAM=行列, LPARAM=序列)
#define WM_CLOSEPOPUPDLG_MESS               (WM_USER + 600)  //将RUN中的对话框关闭
#define WM_SIMULATELINK_OK_MESS             (WM_USER + 601)  //连接指定模拟人成功
#define WM_ACTIVEVIEW_MESS                  (WM_USER + 602)  //视图激活消息
#define WM_START_ISSUEEXAM_MESS              WM_USER + 611   //开始考试
#define WM_STOP_ISSUEEXAM_MESS               WM_USER + 612   //结束考试
#define WM_SIMULATELINK_SUCCEED_MESS        (WM_USER + 615)  //模拟人连接成功指令

//语言类型
enum  LauguageType
{
	L_chs = 0,       //中文
	L_eng,           //英文（英国/美国）
};
//----------------------------------------------------------------------------------------------------
enum Artifact
{
	AF_None = 0,
	AF_Muscular, //：肌肉颤动
	AF_Frequent  //：50/60赫兹的干扰
};
enum QRS
{//差别类型
	QRS_None = 0,
	QRS_A,
	QRS_B,
	QRS_C,
	QRS_D,
	QRS_E,
	QRS_F,
	QRS_G
};

//不同导联的标识
enum RhythmLead
{
	Lead_I = 0,
	Lead_II,
	Lead_III,
	Lead_aVR,
	Lead_aVL,
	Lead_aVF,
	Lead_V1,
	Lead_V2,
	Lead_V3,
	Lead_V4,
	Lead_V5,
	Lead_V6
};

enum BasicRhythm
{//基本心律
	BR_Sinus=0,    //窦性
	BR_ATach,
	BR_AFlutt,     //房扑
	BR_AFib,       //房颤
	BR_Junct,
	BR_Idiov,
	BR_VTach,               //室性心动过速
	BR_Torsade_DP,          //Torsade de Points
	BR_VFibr,               //V.fibr
	BR_Asystole,
	BR_AgonalRhythm,
	BR_Ventr_Standstill,
	BR_1degree_AVB,
	BR_2degree_AVB_I,
	BR_2degree_AVB_II,
	BR_3degree_AVB,
	BR_PacemakerAtr,
	BR_PacemakerAV_Seq,
	BR_PacemakerLoc,
	BR_Die,
	BR_PaceRhythm,             //起搏信号
	//-----------------hjg 2013.6.8 add  -------------------------------------------------
	BR_Sinus_Ischemia,             //伴有心肌缺血的窦性心律
	BR_Sinus_InjureIschemia,         //伴有损伤性心肌缺血的窦性心律
	BR_Sinus_InferiorAMI_ST,       //有下急性心肌梗死的窦律，ST抬高
	BR_Sinus_AnteriorAMI_ST,       //有前壁急性心肌梗死的窦律，ST抬高
	BR_Sinus_AnteriorAMI_Late,     //有前壁急性心肌梗死的窦律，后期
	BR_Sinus_LBBB,                 //伴有左束支阻滞的窦性心律
	BR_Sinus_RBBB,                 //伴有右束支阻滞的窦性心律
	BR_Sinus_LeftHypertrophy,      //左心室肥大的窦性心律
	BR_Sinus_RightHypertrophy,     //右心室肥大的窦性心律
	BR_Sinus_Hypertrophy,          //双心室肥大的窦性心律
	BR_Sinus_Hyperkalemia,         //高血钾的窦性心律
	BR_Sinus_WPW,                  //WPW预激综合
	BR_Sinus_LeftAxis_Deviation,   //心电轴左偏
	BR_Sinus_RightAxis_Deviation,  //心电轴右偏
	BR_Sinus_Prolonged_QT,         //QT间期延长
	BR_DigitalisEffect,            //洋地黄效应
	//-------------------------------------------------------------------------------------
	BR_Sinus_Doubt,                //*窦性心律不齐*
	BR_Sinus_NoPulse,              //*窦性停搏*
	BR_ParoxysmalTach,             //阵发性室上性心动过速
	BR_VFlutt,                     //室扑
	BR_PSVtach,                    //*阵发性室性心动过速；特定：室性早搏连续出现3次以上*
	BR_None
};

enum Extrasys
{//期外收缩（早搏）
	ES_None = 0,     //无
	Unifocal_PVC,    //单形性室性早搏
	PVC_RonT,        //室性早搏RonT
	Coupled_PVC,     //室性早搏显二联律
	Multifocal_PVC,  //多形性室性早搏
	PAC,             //房性早搏
	PJC              //多界性早搏
};
enum HeartSpeak
{//心跳速度
	HS_Normal,       //正常
	HS_FAST          //快
};

enum _eRefurbishDataRange
{//需要刷新的数据范围
	RD_NoChange = 0x00,//不用改变
	RD_LoadConfigFile  = 0x01,//需要重新加载配置文件
	RD_AllData  = 0x02,//需要重新加载所有数据
	RD_OpSegmentData = 0x04,//需要重新计算数据操作段
	RD_CombineSegmentData = 0x08, //需要重新计算所有组合段
	RD_MainSegmentData = 0x10 //需要生成段
};

//模拟病人类型
enum SimulatePatientType
{
	SPT_Adult   = 0,
	SPT_Enfant  = 1,
	SPT_Infant  = 2,
	SPT_PregnantWoman
};

//体征监控面板布置方式枚举
enum MonitorLayoutModule
{
	LM_5Waveform = 0,
	LM_4Waveform,
	LM_3Waveform,
	LM_BigNumeric
};

//体征监控面板布置元素的类别枚举
enum MonitorLayoutElement
{
	LME_None = 0,
	LME_ECGWaveform,
	LME_SpO2Waveform,
	LME_ABPWaveform,
	LME_RespWaveform,
	LME_EtCO2Waveform,
	LME_HR_Numeric,
	LME_SpO2_Numeric,
	LME_ABP_Numeric,
	LME_RR_Numeric,
	LME_EtCO2_Numeric,
	LME_AGT_Numeric,
	LME_CO_Numeric,
	LME_ICP_Numeric,
	LME_N2O_Numeric,
	LME_O2_Numeric,
	LME_TBlood_Numeric,
	LME_TOF_Numeric,
	LME_TPeri_Numeric,
	LME_PAP_Numeric,
	LME_CVP_Numeric,
	LME_Pulse_Numeric,
	LME_WP_Numeric,
	LME_NIBP_Numeric
};

enum _eCPRErrorSign
{//CPR错误状态标示
	CS_None = 0,
	CS_Pressure_Right,
	CS_PressureOverBig, //按压过大
	CS_PressureLack,    //按压不足
	CS_PressurePosErr,  //按压位置错误
	CS_PressureNumLack, //按压次数太少
	CS_PressureIncompleteErr,//按压次数末完全释放
	CS_PressureNumOver, //按压次数太多
	CS_Breath_Right,
	CS_BreathOverBig,   //吹气过大
	CS_BreathLack,      //吹气不足
	CS_BreathInStomach, //进胃
	CS_BreathJam,       //气道堵塞
	CS_RespTimeOver,    //通气时间过长
	CS_RespTimeLower,   //通气时间过短
	CS_BreathNumLack,   //吹气次数太少
	CS_BreathNumOver    //吹气次数太多
};

enum _CPRManageState
{//CPR操作状态
	aCPRPopularMode = 0,   //普及模式
	aCPRPractiseMode,      //实战模式
	eNoneDefine
};

//-----------------------------------------------------------------------------------------------------------------------------
enum _FlowState
{
	eFlowNone = 0,  //构建状态，构建好后自动转到暂停状态
	eFlowRun,   //运行
	eFlowPause //暂停
};

//情景/场景调度状态
enum _ScheduleSceneState
{
	DSS_SceneSwitch = 0,          //场景切换
	DSS_SceneActSchedule,         //情景调度
	DSS_SceneActLogout,           //情景退出
	DSS_Logouted                  //退出流程
};

//能否除颤
enum _DefibrEnable
{
	_defibrCan = 0,       //能除颤
	_defibrDia,           //不能除颤
	_defibrNone           //忽略
};


enum _eOpSymptomSet
{
	OS_Default = 0,
	OS_A_Airway,
	OS_A_Defi,
	OS_A_ECG,
	OS_A_BP,
	OS_A_Breath,
	OS_A_HeartSound,
	OS_A_BloodOxygen,
	OS_A_Pace,
	OS_A_Time,
	OS_A_Text,
	OS_A_Trend,
	OS_A_Pupil,
	OS_A_OtherVital,
	OS_A_LungSound,
	OS_A_Complexion
};
//-----------------------------------------------------------------------------------------------------------------------------
enum eEventSign
{//事件标志
	ES_Normal = 0x0000,           //正常状态
	ES_Pressure = 0x0001,         //胸部按压
	ES_Breathing = 0x0002,        //人工呼吸
	ES_Dunt = 0x0004,             //重击
	ES_Intubation = 0x0008,       //气管插管
	ES_LookUp = 0x0010,           //仰头
	ES_IVLine = 0x0020,           //打针
	ES_Suction = 0x0040,          //吸杂物
	ES_Oxygen = 0x0080,           //吸氧
	ES_Defib  = 0x0100,           //除颤
	ES_PulseCheck = 0x0200,       //脉搏检测
	ES_CPREvent = 0x0400,         //CPR事件
	ES_PaceEvent = 0x0800,        //起搏事件
	ES_RaiseJowl = 0x1000,        //取颌
	ES_AED = 0x2000,     
	ES_Conscious = 0x4000,              //意识判别
	ES_PipeClose = 0x8000,              //吹气时气道未开放
	ES_ClearObstruc = 0x10000,         //清除异位
	ES_InstrumentSign = 0x40000000        //设备查询指令
};

//-----------------------------------------------------------------------------------------------------------------------------
enum eRespMode
{
	RM_Normal  = 0,
	RM_Stokes,                    //成人陈施呼吸/潮式呼吸模式
	RM_Biots,                     //间停呼吸
	RM_Apneustic,                 //呼吸暂停
	RM_Apnea,                     //呼吸停止
	RM_Sign,                      //成人叹气样呼吸
	RM_IrregularGasp              //不规则呼吸
};
//IRP处理状态
enum  eIrpHandleState
{
	IH_None  = 0x00,
	IH_Execed = 0x01,
	IH_ShiftFlow = 0x02
};

//情景框事件触发条件枚举
enum  _SceneActHandleType
{
	SA_None  = 0,
	SA_Occur,                      //发生
	SA_UnoccurDurationTime,        //指定期间内没发生
	SA_StipulatedTimeRear		   //发生指定时间后
};
//-----------------------------------------------------------------------------------------------------------------------------
enum _IrpType
{//类别
	eNone      = 0,
	eParameter,            //属性
	eClock_Event,          //时钟事件
	eABC_Event,            //ABC事件
	eOxygen_Event,         //吸氧事件
	eDrug_Event,           //药物事件
	eMisce_Event,          //杂项事件
	eSimulateTrigger_Event,//模拟人触发事件
	eCPR_Stat,             //CPR操作统计事件
	eFrameModify_Event,    //场景框改变事件
	eAssist_Check,         //辅助检查
	eRealTimeData,         //实时数据
	eSimulateOrder         //模拟人通信指令
};

//-----------------------------------------------------------------------------------------------------------------------------
enum eSliderType
{
	PACE_SET = 0,
	KOROTKOFF_SET,
	LEFTEYE_SET,
	RIGHTEYE_SET
};

enum _ePressureRange
{
	PressureNone = 0,
	PressureBig ,
	PressureOK,
	PressureSmall,
	PressurePosError,
	PressureOrigin
};

enum _eResult
{
	BP_NONE = 0,	//
	BP_Big,
	BP_OK,
	BP_Small,
	BP_PosError,
	BP_Origin
};
//-----------------------------------------------------------------------------------------------------------------------------
enum _CPRRuleType
{
	eCPRStartType = 0,       //可实施AED时起始CPR
	eCPRGeneralType,     // 常规CPR
	eCPROnlyBreathType,  //单独吹气
	eCPROnlyPressureType //单独按压
};

//CPR采样数据格式
//<0>吹气量、<1>通气时间、<2>按压、<3>标识码、<4>速率>、<5>释放不足/进胃、<6>时间戳
typedef boost::tuple<unsigned char, unsigned char,unsigned char, unsigned char, unsigned char, bool, unsigned short>    _CPRData; 

namespace jysoft {
	//-----------------------------------------------------------------------------------------------------------------------------
	//I12导联心电图数据结构
    struct  AFX_EXT_CLASS I12LeadSample
	{
		float       m_fSampleI;
		float       m_fSampleII;
		float       m_fSampleIII;
		float       m_fSampleaVR;
		float       m_fSampleaVL;
		float       m_fSampleaVF;
		float       m_fSampleV1;
		float       m_fSampleV2;
		float       m_fSampleV3;
		float       m_fSampleV4;
		float       m_fSampleV5;
		float       m_fSampleV6;
	public:
		void ZeroI12LeadSample();
		//返回LA肢体导联, V(L) = V(LA)；公式： V(L) = (2*I-II)/3;
		float Get_fSampleaLA() const { return (2*m_fSampleI - m_fSampleII)/3; };
		//返回RA肢体导联，V(R) = V(RA)；公式： V(R) = -(I+II)/3;
		float Get_fSampleaRA() const { return -(m_fSampleI+m_fSampleII)/3; };
		//返回LL肢体导联，V(F) = V(LL)；公式： V(F) = (II+III)/3; //*(-I+2*II)/3;*/
		float Get_fSampleaLL() const { return (m_fSampleII+m_fSampleIII)/3; };
	public:
		// 返回特定导联的电压值
		float Get_fLeadSample( RhythmLead eRhythmLead );
	};

	//CPR规则条目细节结构
    struct  AFX_EXT_CLASS _CPRRule_DetailStruct
	{
	public:
		bool       m_bBreath;      //true：吹气 ； false：按压
		int        m_nNumber;      //次数：-1末指定
	protected:
		_CPRRule_DetailStruct *  nextDetailPtr;
	public:
		void Copy(_CPRRule_DetailStruct *pDetail);
		//设置Next指针
		inline void setNextDetailRule(_CPRRule_DetailStruct *pNextDetail) { nextDetailPtr = pNextDetail; };
		//返回Next指针
		inline _CPRRule_DetailStruct *getNextDetailRule() { return nextDetailPtr; };
	public:
		_CPRRule_DetailStruct();
		_CPRRule_DetailStruct(bool bBreath, int nNumber);
	};

	//CPR规则结构
    struct AFX_EXT_CLASS _CPRRuleStruct
	{
	public:
		_CPRRuleType      m_eRuleType;   //CPR类型
		int               m_nCycle;      //周期：-1 末指定
		_CPRRule_DetailStruct * detailRules;
	public://主要函数
		void copy(_CPRRuleStruct *pRule);
		void setEmpty();
		//五个循环CPR
		void setDefaultCPRRule(int nCycle = 5);
		//只按压
        void setOnlyPressure(long lNumber);
	    //只吹气
		void setOnlyBreath();
	public:
		void addNewDetail(_CPRRule_DetailStruct *pDetail);
	public:
		_CPRRuleStruct();
		~_CPRRuleStruct();
	};
	//------------------------------------------------------------------------------
    struct AFX_EXT_CLASS _EventLog_struct
	{
		std::string                 m_strTime;    //时间
		std::string                 m_strAct;     //动作
	protected:
		eEventSign                  m_eEventSign; //特定事件标识
	public:
		_EventLog_struct();
	public:
		inline eEventSign Get_eEventSign() { return m_eEventSign; };
		void Set_eEventSign( eEventSign eSign) { m_eEventSign = eSign; };
	};
}

