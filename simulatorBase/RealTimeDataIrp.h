#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\CommonGlobal.h"
#include "..\Common\VirtualIrp.h"


namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     实时数据Irp
	创建人：	 hjg
	创建时间：   2017/2/8
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CRealTimeDataIrp : public CVirtualIrp
	{
	public:
		CRealTimeDataIrp(void);
		virtual ~CRealTimeDataIrp(void);
	public:
		virtual _IrpType Get_eIrpType() { return eRealTimeData; };
		virtual bool isKindOf(const std::string &strClass);
		/*******************************************************************************/
		// 函数名称： doPackageIrp
		// 功能：  打包Irp的内容
		// 参数： 
		// 返回值: 
		virtual std::string doPackageIrp();
	public:
		/*******************************************************************************/
		// 函数名称： CreateRealTimeData_CPRIrp
		// 功能： 创建CPR实时数据Irp类
		// 参数： 
		//        const _CPRData *ptrCPRDatas：
		//        int nLength：
		// 返回值:  
		static CRealTimeDataIrp * CreateRealTimeData_CPRIrp(const _CPRData *ptrCPRDatas, int nLength);
		/*******************************************************************************/
		// 函数名称： UnzipPackage
		// 功能： 解压缩打包的Irp的内容
		// 参数： 
		//        const char *lpstrPackage：
		//        UINT uNumber：
		// 返回值:  
        static CRealTimeDataIrp * UnzipPackage(const char *lpstrPackage, short uNumber);
	public:
		//设置CPR实时采样数据
		void SetCPR_RealTimeData(/*in*/const _CPRData *ptrCPRDatas, int nLength);
		//获取CPR实时采样数据
		int GetCPR_RealTimeData(/*out*/_CPRData *ptrCPRDatas);
	public:
		_CPRData*       m_ptrCPRDatas;
		int             m_nLength;
	};

}}
