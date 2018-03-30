#pragma once
#include ".\simulatorbase_global.h"
#include <string>

namespace jysoft { namespace pnp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     即插即用设备接口类
	创建人：	 hjg
	创建时间：   2009/4/30
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT IPnPFacility
	{
	public:
		IPnPFacility(short sPnpID, short sPort);
		virtual ~IPnPFacility(void);
	protected:
		IPnPFacility            *m_pNextInterface;    //下个接口
		IPnPFacility            *m_pPreInterface;     //上个接口
	protected:
		short                    m_sPnpID;     //设备号
		short                    m_sPnPAddress;
	public:
		//设置下个即插即用设备接口类
		void SetNextInterfacePtr(IPnPFacility *pNextInterface);
		//设置上个接口
		inline void SetPreviouInterfacePtr(IPnPFacility *pPreInterface) { m_pPreInterface = pPreInterface;};
		//返回下个接口
		inline IPnPFacility * GetNextInterfacePtr() { return m_pNextInterface;};
		//返回上个接口
		inline IPnPFacility * GetPreviouInterfacePtr() { return m_pPreInterface;};
		//返回设备连接的地址号
		inline short Get_PnPId() { return m_sPnpID; };
	public:
		//返回接口联表的头
		IPnPFacility * GetHeaderInterfacePtr();
		//移除制定的接口
		static IPnPFacility * RemoveInterfacePtr(IPnPFacility *pOrgInterfacePtr, IPnPFacility *pRmvInterface);
	public:
		/*******************************************************************************/
		// 函数名称： OnModifyTransmitAddress
		// 功能：   修改通讯指令的转发地址
		// 参数：   
		//      /*out*/BYTE &byteAddress: 
		// 返回值: 
		virtual  void OnModifyTransmitAddress(/*out*/short &sAddress, const std::string &symptomCaption) ;
	public:
		/*******************************************************************************/
		// 函数名称： isModifyTransmitAddress
		// 功能：   判断是否修改通讯指令的转发地址
		// 参数：   
		//      const std::string &symptomCaption: 
		// 返回值: 
		virtual bool isModifyTransmitAddress( const std::string &symptomCaption ) = 0;
	};

}}
