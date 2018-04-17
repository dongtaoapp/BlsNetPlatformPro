#pragma once
#include ".\vircardiogramparam.h"

#include "..\Common\CommonGlobal.h"


namespace jysoft { namespace simulator { 

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     I2导联心电图参数集合操作接口类
	创建人：	 hjg
	创建时间：   2013/5/13
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT ICardiogramLeads
	{
	public:
		ICardiogramLeads(void);
		virtual ~ICardiogramLeads(void);
	public:
		/*******************************************************************************/
		// 函数名称： IsCanExpressCardiogramParam
		// 功能： 根据传入的心电图描述，是否能用此对象得到画此心电图所需要的参数。
		// 参数：  
		// 返回值: 
        virtual bool IsCanExpressCardiogramParam(BasicRhythm eRhythm, int uHR) = 0;
		/*******************************************************************************/
		// 函数名称： LoadCardiogramLeadsParam
		// 功能： 加载心电图各导联的参数值
		// 参数： 
		//         
		// 返回值:
        virtual bool LoadCardiogramLeadsParam( BasicRhythm eRhythm, int uHR, short sConduct = 0, short sExtendParam = 0 ) = 0;
		/*******************************************************************************/
		// 函数名称： ReLoadCardiogramParam
		// 功能： 
		// 参数：  
		// 返回值: 
		virtual void ReLoadCardiogramParam() = 0;
		/*******************************************************************************/
		// 函数名称： SeteRefurbishDataRange
		// 功能： 设定刷新数据的程度
		// 参数：  
		// 返回值: 
		virtual void SeteRefurbishDataRange(_eRefurbishDataRange eRange) = 0;
		/*******************************************************************************/
		// 函数名称： GeteRefurbishDataRange
		// 功能： 返回构建数据的程度最深的枚举值
		// 参数：  
		// 返回值:   RD_LoadConfigFile最深，RD_NoChange最浅 
		virtual _eRefurbishDataRange GeteRefurbishDataRange() = 0;
	public:
		/*******************************************************************************/
		// 函数名称： GetEcgLeadParam
		// 功能： 返回指定导联心电图的参数构建类
		// 参数： 
		//        RhythmLead  eEcgLeadType:  
		// 返回值:  
		virtual CVirCardiogramParam * GetEcgLeadParam(RhythmLead  eEcgLeadType);
		//产生心电时，血氧的启动时间
		virtual bool GetSpO2BeginTimeToCardiogram(/*out*/long &lBeginTime, /*out*/long &lCycleTime);
		//产生早博时，血氧的启动时间
		virtual bool GetSpO2BeginTimeToExtrasyst(/*out*/long &lBeginTime, /*out*/long &lPreSpO2BeginTime, /*out*/long &lCycleTime);
		/*******************************************************************************/
		// 函数名称： ResetSyncFlag
		// 功能： 重置同步标识符，用于下周期导联构建的协调
		// 参数：  
		// 返回值: 
		virtual void ResetSyncFlag()  { };
		//是否初始构建时发送两次心电图数据
		virtual bool IsInitialSendDoubleSampleData() { return false; };
		//是否有缺省的早播
		virtual bool IsHaveDefalutExtrasyst() {return true;};
		virtual void LoadExtrasystParamPre(Extrasys eExtrasyst) { };
		virtual void LoadExtrasystParam(Extrasys eExtrasyst) { };
	public:
		//返回周期时间（单位：0.1毫秒）
		virtual int GetCycleTime();
		//返回当前的心率
		int Get_iRhythmHR();
		//返回当前的心律
		inline BasicRhythm Get_eCurrentRhythm() { return m_eBasicRhythm; };
	protected:
		CVirCardiogramParam *           m_pEcgLeadParam[9];
		BasicRhythm                     m_eBasicRhythm;
	protected:
		IStorage *                      m_pI12LeadsStorage;
	};

}}
