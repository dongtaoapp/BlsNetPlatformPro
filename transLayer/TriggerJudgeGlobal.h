#pragma once
#include ".\LayerGlobal.h"

#include "..\common\CommonGlobal.h"
#include "..\common\LoopBuffer.h"

#include "..\simulatorBase\SimulatorOrderIrp.h"
#include "..\simulatorBase\EventIrp_SimulateTrigger.h"


namespace jysoft { namespace transLayer 
{
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     模拟人触发事件辨识接口类
	创建人：	 hjg
	创建时间：   2017/5/4
	//-----------------------------------------------------------------------------------------------------------------*/
	class ISimulateTriggerJudge
	{
	public:
		ISimulateTriggerJudge(void);
		virtual ~ISimulateTriggerJudge(void);
	public:
		/*******************************************************************************/
		// 函数名称： createEvent_SimulateTriggerIrp
		// 功能： 创建模拟人触发事件Irp
		// 参数： 
		//        _VirDataStruct *pDataStruct: 
		// 返回值:  
		virtual irp::CEventIrp_SimulateTrigger * createEvent_SimulateTriggerIrp(_VirDataStruct *pDataStruct) = 0;
		/*******************************************************************************/
		// 函数名称： judgeRealTimeDataType
		// 功能：  判断是否为CPR实时采样数据
		// 参数： 
		// 返回值: 
		virtual bool judgeRealTimeDataType(_VirDataStruct *pDataStruct, /*out*/_CPRData *lptrCPRData) = 0;
	protected:
		//查找首标志
		virtual bool searchBeginSegmentFlag();
		//查找尾标志, 并返回命令长度;-1表示没找到
		virtual int  searchEndSegmentFlag();
	public:
		//接受从串口收到的数据
		_VirDataStruct * getDataStructFromCommData(void);
		void writeCommunicateData(void *lpData, UINT uNumber);
	protected:
		utility::CLoopBuffer<unsigned char>      m_cDataTmpBuffer;
	};

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     模拟人触发事件辨识类(2.0版本的硬件设备通讯格式)
	创建人：	 hjg
	创建时间：   2011/5/5
	//-----------------------------------------------------------------------------------------------------------------*/
    class TRANSLAYERSHARED_EXPORT CBlsTriggerJudgeVersion : public ISimulateTriggerJudge
	{
	public:
		CBlsTriggerJudgeVersion();
		virtual ~CBlsTriggerJudgeVersion();
	public:
		/*******************************************************************************/
		// 函数名称： createEvent_SimulateTriggerIrp
		// 功能： 创建模拟人触发事件Irp
		// 参数： 
		//        _VirDataStruct *pDataStruct: 
		// 返回值:  
		virtual irp::CEventIrp_SimulateTrigger * createEvent_SimulateTriggerIrp(_VirDataStruct *pDataStruct);
		/*******************************************************************************/
		// 函数名称： judgeRealTimeDataType
		// 功能：  判断是否为CPR实时采样数据
		// 参数： 
		// 返回值: 
		virtual bool judgeRealTimeDataType(_VirDataStruct *pDataStruct, /*out*/_CPRData *lptrCPRData);
	};
}}
