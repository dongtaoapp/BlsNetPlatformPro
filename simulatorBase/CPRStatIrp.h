#pragma once
#include ".\simulatorbase_global.h"
#include ".\VirEventIrp.h"


namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     CPR操作状态事件Irp
	创建人：	 hjg
	创建时间：   2017/2/8
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CCPRStatIrp : public CVirEventIrp
	{
	public:
		CCPRStatIrp(void);
		virtual ~CCPRStatIrp(void);
	public:
		virtual _IrpType Get_eIrpType() { return eCPR_Stat; };
		virtual bool isKindOf(const std::string &strClass);
		//返回事件标志
		virtual eEventSign Get_EventSign() { return ES_CPREvent; };
		/*******************************************************************************/
		// 函数名称： doPackageIrp
		// 功能：  打包Irp的内容
		// 参数： 
		// 返回值: 
		virtual std::string doPackageIrp();
		/*******************************************************************************/
		// 函数名称： UpdateEventSignShow
		// 功能：  显示事件动作
		// 参数： 
		// 返回值: 
		virtual void UpdateEventSignShow(simulator::base::CShowEventSignUpdateInterface  *pInterface );
	public:
		/*******************************************************************************/
		// 函数名称： CreateEvent_CPRIrp
		// 功能： 创建CPR事件Irp类
		// 参数： 
		//       _CPRManageState eCPRMode: CPR模式
		//       int nStat:               状态
		// 返回值:  
		static CCPRStatIrp * CreateEvent_CPRIrp(_CPRManageState eCPRMode, int nStat);
		/*******************************************************************************/
		// 函数名称： UnzipPackage
		// 功能： 解压缩打包的Irp的内容
		// 参数： 
		//        char *lpData：
		//        UINT uNumber：
		// 返回值:  
        static CCPRStatIrp * UnzipPackage(char *lpData, unsigned short uNumber);
	public:
		inline void Set_eCPRMode(_CPRManageState  eState) { m_eCPRMode = eState; };
		inline void Set_OperatorStat(int nStat) { m_nStat = nStat; };
		inline _CPRManageState Get_eCPRMode() { return m_eCPRMode; };
		inline int GetValue_Stat() { return m_nStat; };
	protected:
		_CPRManageState    m_eCPRMode;        //CPR操作模式
		//------------------------------------------------------------------------
		//0:    CPR操作结束
		//1:    CPR操作开始
		//2:    在标准模式及实战模式下，完成5个循环的CPR操作
		int                m_nStat;          
	};

}}
