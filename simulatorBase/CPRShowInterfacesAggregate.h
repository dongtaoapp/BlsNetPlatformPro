#pragma once
#include ".\simulatorbase_global.h"

#include ".\ShowCPRActUpdateInterface.h"
#include ".\ShowCPRStatisticUpdateInterface.h"
#include ".\CPRRealTimeUpdateInterface.h"

namespace jysoft{  namespace cpr {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：    心肺复苏显示接口集合类
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CCPRShowInterfacesAggregate
	{
	public:
		CCPRShowInterfacesAggregate(void);
		virtual ~CCPRShowInterfacesAggregate(void);
	protected:
		CShowCPRActUpdateInterface    *m_pShowCPRDetailActInterface;
		CShowCPRStatisticUpdateInterface    *m_pShowCPRStatisticInterface;
		CCPRRealTimeUpdateInterface     *m_pShowCPRRealTimeInteface;
	public:
		//返回CPR操作详解动作显示接口
		inline CShowCPRActUpdateInterface *Get_ShowCPRDetailActUpdateInterface() { return m_pShowCPRDetailActInterface; };
		//返回CPR统计显示接口
		inline CShowCPRStatisticUpdateInterface *Get_ShowCPRStatisticUpdateInterface() { return m_pShowCPRStatisticInterface; };
		//返回CPR实施波形显示接口
		inline CCPRRealTimeUpdateInterface *Get_ShowCPRRealTimeUpdateInterface() { return m_pShowCPRRealTimeInteface; };
		//-----------------------------------------------------------------------------------------------------------------------
		//设置CPR操作详解动作显示接口
		void Set_ShowCPRDetailActUpdateInterface(CShowCPRActUpdateInterface *pInterface);
		//设置CPR统计显示接口
		void Set_ShowCPRStatisticUpdateInterface(CShowCPRStatisticUpdateInterface *pInterface);
		//设置CPR实施波形显示接口
		void Set_ShowCPRRealTimeUpdateInterface(CCPRRealTimeUpdateInterface *pInterface);
	public:
		//移除CPR操作详解动作显示接口
		void Remove_ShowCPRDetailActUpdateInterface(CShowCPRActUpdateInterface *pRmvInterface);
	};
}}
