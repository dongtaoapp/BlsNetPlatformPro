#pragma once
#include ".\ShowABPUpdateInterface.h"
#include ".\ShowSpO2UpdateInterface.h"
#include ".\ShowECGUpdateInterface.h"
#include ".\ShowEtCO2UpdateInterface.h"
#include ".\ShowRespRateUpdateInterface.h"
#include ".\IHeartStartSign.h"
#include ".\ShowGeneralNoRangeUpdateInterface.h"
#include ".\ShowTempUpdateInterface.h"
#include ".\ShowGeneralUpdateInterface.h"
#include ".\ShowNIBPUpdateInterface.h"

namespace jysoft { namespace simulator {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     模拟监控面板控件显示接口集合
	创建人：	 hjg
	创建时间：   2016/8/15
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CWatchBarsShowInterfacesAggregate
	{
	public:
		CWatchBarsShowInterfacesAggregate(void);
		virtual ~CWatchBarsShowInterfacesAggregate(void);
	protected:
		//心电图信息显示接口，包括心律名称、心率次数、心率正常范围等信息
		base::CShowECGUpdateInterface              *m_pShowHRInterface;
		//血氧信息显示接口
		base::CShowSpO2UpdateInterface             *m_pShowSpO2ValueInterface;
		//CO2浓度信息显示接口
		base::CShowEtCO2UpdateInterface            *m_pShowEtCO2ValueInterface;
		//有创血压信息显示接口
		base::CShowABPUpdateInterface              *m_pShowABPValueInterface;
		//无创血压信息显示接口
		base::CShowNIBPUpdateInterface             *m_pShowNIBPValueInterface;
		//呼吸次数信息显示接口
		base::CShowRespRateUpdateInterface         *m_pShowRRInterface;
		//外围体温（指：舌下、肛温和液下温度）
		base::CShowTempUpdateInterface             *m_pShowPTempValueInterface;
		//模拟监控面板“嘀嘀”音提示启动信号
		IHeartStartSign                     *m_pHeartStartSignInterface;
	public:
		//返回心电图信息显示接口
		inline base::CShowECGUpdateInterface * Get_ShowHRUpdateInterfacePtr() { return m_pShowHRInterface; };
		void Set_ShowHRUpdateInterfacePtr(base::CShowECGUpdateInterface *pEcgInterface, bool bRemove = false);
		//返回血氧信息显示接口
		inline base::CShowSpO2UpdateInterface * Get_ShowSpO2ValueUpdateInterfacePtr() { return m_pShowSpO2ValueInterface; };
		void Set_ShowSpO2ValueUpdateInterfacePtr(base::CShowSpO2UpdateInterface *pSpO2Interface, bool bRemove = false);
		//返回CO2浓度信息显示接口
		inline base::CShowEtCO2UpdateInterface * Get_ShowEtCO2ValueUpdateInterfacePtr() { return m_pShowEtCO2ValueInterface; };
        void Set_ShowEtCO2ValueUpdateInterfacePtr(base::CShowEtCO2UpdateInterface *pEtCO2Interface, bool bRemove = false);
		//返回有创血压信息显示接口
		inline base::CShowABPUpdateInterface * Get_ShowABPValueUpdateInterfacePtr() { return m_pShowABPValueInterface; };
		void Set_ShowABPValueUpdateInterfacePtr(base::CShowABPUpdateInterface *pABPInterface, bool bRemove = false);
		//返回无创血压消息显示接口
		inline base::CShowNIBPUpdateInterface * Get_ShowNIBPValueUpdateInterfacePtr() { return m_pShowNIBPValueInterface; };
		void Set_ShowNIBPValueUpdateInterfacePtr(base::CShowNIBPUpdateInterface *pNIBPInterface, bool bRemove = false);
		//返回呼吸次数信息显示接口
		inline base::CShowRespRateUpdateInterface * Get_ShowRespRateUpdateInterfacePtr() { return m_pShowRRInterface; };
		void Set_ShowRespRateUpdateInterfacePtr(base::CShowRespRateUpdateInterface *pRRInterface, bool bRemove = false);
		//模拟监控面板“嘀嘀”音提示启动信号
		inline IHeartStartSign * Get_HeartStartSignInterface() { return m_pHeartStartSignInterface; };
		void Set_HeartStartSignInterface(IHeartStartSign *pHeartSignInterface, bool bRemove = false);
		//体温
		inline base::CShowTempUpdateInterface * Get_ShowPTempValueInterfacePtr(){return m_pShowPTempValueInterface;};
		void Set_ShowPTempValueInterfacePtr(base::CShowTempUpdateInterface *pPTempInterface, bool bRemove = false);
	protected:
		/*******************************************************************************/
		// 函数名称： InitialWatchBarsShowInterfacesAggregate
		// 功能： 获取模拟监控面板内所有的信息显示接口
		// 参数： 
		// 返回值:  
		virtual void InitialWatchBarsShowInterfacesAggregate( ) = 0;

	};

}}
