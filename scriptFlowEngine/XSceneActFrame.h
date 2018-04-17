#pragma once
#include <pugixml.hpp>
#include ".\xscenario.h"
#include ".\XEventVirtual.h"
#include ".\ISceneActRunOp.h"

#include "..\common\CommonGlobal.h"

namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     情景框解析类
	创建人：	 hjg
	创建时间：   2017/2/16
	//-----------------------------------------------------------------------------------------------------------------*/
	class CXSceneActFrame : public CXScenario
						  , public ISceneActRunOp
	{
	public:
		CXSceneActFrame(unsigned short dwFrameID);
		virtual ~CXSceneActFrame(void);
	protected:
		CXEventVirtual *               m_pActEvent;       //标题框事件
		_SceneActHandleType            m_eActHandleType;  //事件触发条件枚举
		short                          m_sDurationTime;   //触发时间参数
		bool                           m_bExitFlow;       //是否退出流程
	protected:
		unsigned short                    m_dwFrameID;
	public: //基函数重载
		virtual bool isKindOf(const std::string &strClassName);
		//返回当前场景设置的体征列表
		virtual void GetScenarioActions(std::list<simulator::CXActionVirtual *>* plstActions);
	public: //接口ISceneActRunOp函数重载
		/*******************************************************************************/
		//功能：处理事件IRP函数虚函数
		//参数：
		//      CVirEventIrp *pCurrEventIrp：
		//      /*out*/_ScheduleSceneState &eSceneState:    
		//返回值:  触发事件是否满足(TURE:满足；FALSE:不满足)
		virtual bool DoHandleEventIrp(irp::CVirEventIrp *pCurrEventIrp, /*out*/_ScheduleSceneState &eSceneState);
		/*******************************************************************************/
		//功能：处理时钟事件IRP函数
		//参数：
		//      CEventIrp_ClockTime *pCurrClockTimeIrp：
		//返回值:  后续不再处理（FALSE);
		virtual bool DoHandleClockIrpOp(irp::CEventIrp_ClockTime *pCurrClockTimeIrp, /*out*/_ScheduleSceneState &eSceneState);
		/*******************************************************************************/
		//功能：激活情景框的处理状态
		//参数：   
		//      BOOL bReactive:     是否重新激活
		//返回值: 
		virtual void DoStateActiveSceneFrame(bool bReactive);
		//返回情景框的ID值
		virtual unsigned short Get_SceneActFrameId() { return m_dwFrameID; };
	public:
		//解析情景框的所有体征及相关信息
		void ParseSceneActFrame(pugi::xml_node *pScenarioNode, IGetPhysiologyActionObj *pGetActionObj);
	protected:
		//解析场景框的所有体征（不生成CXAction_FrameTime项）hjg 2014.2.28 add
		virtual void ParseActions(pugi::xml_node *pScenarioNode);
		void LoadActEventFromXML(pugi::xml_node *pXMLActChild, IGetPhysiologyActionObj *pGetActionObj);
	};
}}
