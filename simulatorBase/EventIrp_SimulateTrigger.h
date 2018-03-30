#pragma once
#include ".\simulatorbase_global.h"
#include ".\VirEventIrp.h"
#include <boost/logic/tribool.hpp>


using namespace boost;
namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     模拟人触发事件Irp
	创建人：	 hjg
	创建时间：   2017/2/8
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CEventIrp_SimulateTrigger : public CVirEventIrp
	{
	public:
		CEventIrp_SimulateTrigger(void);
		virtual ~CEventIrp_SimulateTrigger(void);
	public:
		virtual _IrpType Get_eIrpType() { return eSimulateTrigger_Event; };
		virtual bool isKindOf(const std::string &className);
		//返回事件标志
		virtual eEventSign Get_EventSign();
		//返回模拟人触发事件名称
		inline std::string  getName_TriggerEvent() { return m_strTriggerEventName; };
		//设置是否能添加到日志信息
		inline void setEnableAdditionLog(bool bEnable) { m_bAddLog = bEnable; };
		inline void set_eEventSign(eEventSign  eTriggerEventSign) { m_eEventSign = eTriggerEventSign; };
		/*******************************************************************************/
		// 函数名称： UpdateEventSignShow
		// 功能：  显示事件动作
		// 参数： 
		// 返回值: 
		virtual void UpdateEventSignShow(simulator::base::CShowEventSignUpdateInterface  *pInterface );
		/*******************************************************************************/
		// 函数名称： doPackageIrp
		// 功能：  打包Irp的内容
		// 参数： 
		// 返回值: 
		virtual std::string doPackageIrp();
	public:
		//解析仰头、举额事件
		bool explainSimulateTrigger_LookUpEventIrp(bool &bLookUp);
		//解析除颤事件
		bool  explainSimulateTrigger_DefibrEventIrp( /*out*/short &sDefibrCount, /*out*/short &sDefibrEnergy, /*out*/bool &bSyncDefibr );
		//解析插管事件
		bool  explainSimulateTrigger_IntubateEventIrp( /*out*/short &sPosition, /*out*/short &sAct);
		//解析起搏事件
		bool  explainSimulateTrigger_PaceEventIrp( /*out*/short &sPaceSign, /*out*/short &sHeartRate );
		//解析脉搏检查指令
		bool  explainSimulateTrigger_PulseCheckIrp(/*out*/short &sPulsePort, /*out*/short &sAct);
	private:
		eEventSign              m_eEventSign;
		//---------------------------------------------------------------------------------------------------------------------------
		short                   m_sExtendData[2];
	public:
		/*******************************************************************************/
		// 函数名称： CreateSimulateTrigger_LookUpEventIrp
		// 功能： 创建仰头\平躺触发事件Irp
		// 参数：      
		// 返回值:  
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_LookUpEventIrp(bool bHeadLookUp);
		/*******************************************************************************/
		// 函数名称： CreateSimulateTrigger_RaiseJowlEventIrp
		// 功能： 创建举额\举额放平事件
		// 参数：      
		// 返回值:  
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_RaiseJowlEventIrp(bool bRaiseJowl);
		/*******************************************************************************/
		// 函数名称： CreateSimulateTrigger_PipeCloseEventIrp
		// 功能： 创建吹气时气道未开放事件Irp
		// 参数：      
		// 返回值:  
		static CEventIrp_SimulateTrigger *CreateSimulateTrigger_PipeCloseEventIrp(bool bPipeClose);
		/*******************************************************************************/
		// 函数名称： CreateSimulateTrigger_ClearObstructEventIrp
		// 功能： 创建清除异物事件
		// 参数：      
		// 返回值:  
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_ClearObstructEventIrp();
		/*******************************************************************************/
		// 函数名称： CreateSimulateTrigger_ConsciousEventIrp
		// 功能： 创建意识判别事件
		// 参数：      
		// 返回值:  
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_ConsciousEventIrp();
		/*******************************************************************************/
		// 函数名称： CreateSimulateTrigger_DefibrEventIrp
		// 功能： 创建除颤事件
		// 参数：    
		//           bool bSyncDefibr:      是否同步除颤
		//           short sEnergy:         除颤能量；0:表示未指定
		// 返回值:  
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_DefibrEventIrp(bool bSyncDefibr, short sEnergy = 0);
		/*******************************************************************************/
		// 函数名称： CreateSimulateTrigger_AEDEventIrp
		// 功能： 创建AED事件
		// 参数：    
		//          bStartupAED:     ture:开始  false: 结束  unknow: 到达
		// 返回值:  
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_AEDEventIrp(boost::tribool bStartupAED = indeterminate);
		/*******************************************************************************/
		// 函数名称： CreateSimulateTrigger_PulseCheckEventIrp
		// 功能： 创建脉搏检查事件
		// 参数：     
		//        short sPosition:      部位（颈动脉(1),左股动脉(2),右股动脉(3),右臂肱动脉(4),右臂桡动脉(5),左臂肱动脉(6),左臂桡动脉(7),右腿腘动脉(8),右足背动脉(9),左腿腘动脉(10),左足背动脉(11)）
		//        short sAct:           按脉（0x11）、移开（0x10）
		// 返回值:  
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_PulseCheckEventIrp(short sAct, short sPosition=1);
		/*******************************************************************************/
		// 函数名称： CreateSimulateTrigger_IntubateEventIrp
		// 功能： 创建插管事件
		// 参数：      
		//         short sPosition:   气管0x02，支气管0x01，食道0x00
		//         short sAct:        插入0x11，拔出0x10
		// 返回值:  
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_IntubateEventIrp(short sPosition, short sAct);
		/*******************************************************************************/
		// 函数名称： CreateSimulateTrigger_PaceEventIrp
		// 功能： 创建起搏事件
		// 参数：   
		//         sPaceSign:    起搏对应事件
		// 返回值: 
		//注：    起搏事件标识值：【起搏开始(0x11)；起搏捕捉开始(0x12)；起搏夺获后修改心率(0x13)；起搏夺获结束(0x02)；起搏结束(0x01)】
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_PaceEventIrp(short sPaceSign, short sHeartRate = 0);
		/*******************************************************************************/
		// 函数名称： UnzipPackage
		// 功能： 解压缩打包的Irp的内容
		// 参数： 
		//        char *lpData：
		//        UINT uNumber：
		// 返回值:  
        static CEventIrp_SimulateTrigger * UnzipPackage(char *lpData, unsigned short uNumber);
		//编码模拟人触发事件具体表述
		static std::string encodeTriggerXMLExpress(const std::string &strTriggerXML);
		//解码模拟人触发事件具体表述
		static std::string decodeTriggerXMLExpress(const std::string &strEncode);
	private:
		std::string  GetEventSign(const std::string &strTriggerXML);
	public:
		std::string       m_strTriggerEventName;    //模拟人触发事件名称
		std::string       m_strTriggerXML;          //模拟人触发事件具体表述
		bool              m_bAddLog;
	};

}}
