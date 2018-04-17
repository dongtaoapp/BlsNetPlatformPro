#pragma once

#include "..\simulatorbase\icardiogramleads.h"


namespace jysoft { namespace simulator { namespace ecg {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     "二度Ⅰ型房室传导阻滞"心电图不同导联参数集合类
	创建人：	 hjg
	创建时间：   2013/5/13
	//-----------------------------------------------------------------------------------------------------------------*/

	class CCardiogram2degree_AVBI : public ICardiogramLeads
	{
	public:
		CCardiogram2degree_AVBI( IStorage *pRootStorage );
		virtual ~CCardiogram2degree_AVBI(void);
	public:  //接口ICardiogramLeads函数重载
		/*******************************************************************************/
		// 函数名称： LoadCardiogramLeadsParam
		// 功能： 加载心电图各导联的参数值
		// 参数： 
		//         
		// 返回值:
        virtual bool LoadCardiogramLeadsParam( BasicRhythm eRhythm, int uHR, short sConduct, short sExtendParam );
		/*******************************************************************************/
		// 函数名称： ReLoadCardiogramParam
		// 功能： 
		// 参数：  
		// 返回值: 
		virtual void ReLoadCardiogramParam();
		/*******************************************************************************/
		// 函数名称： IsCanExpressCardiogramParam
		// 功能： 根据传入的心电图描述，是否能用此对象得到画此心电图所需要的参数。
		// 参数：  
		// 返回值: 
        virtual bool IsCanExpressCardiogramParam(BasicRhythm eRhythm, int uHR);
		/*******************************************************************************/
		// 函数名称： SeteRefurbishDataRange
		// 功能： 设定构建数据的程度
		// 参数：  
		// 返回值: 
		virtual void SeteRefurbishDataRange(_eRefurbishDataRange eRange);
		// 返回构建数据的程度最深的枚举值（RD_LoadConfigFile最深，RD_NoChange最浅）
		virtual _eRefurbishDataRange GeteRefurbishDataRange();
	public:
		/*******************************************************************************/
		// 函数名称： ResetSyncFlag
		// 功能： 重置同步标识符，用于下周期导联构建的协调
		// 参数：  
		// 返回值: 
		virtual void ResetSyncFlag();
		//是否初始构建时发送两次心电图数据
		virtual bool IsInitialSendDoubleSampleData() { return true; };
	public:
		//是否有缺省的早播
		virtual bool IsHaveDefalutExtrasyst() {return true;};
		virtual void LoadExtrasystParamPre(Extrasys eExtrasyst);
		virtual void LoadExtrasystParam(Extrasys eExtrasyst) ;
	public:
        static bool IsCanParamExpress(BasicRhythm eRhythm, int uHR);
	};

}}}
