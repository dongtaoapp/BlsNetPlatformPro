#pragma once
#include ".\simulatorbase_global.h"
#include <pugixml.hpp>

#include "..\Common\VirtualIrp.h"
#include "..\Common\CommonGlobal.h"


/////////////////////////////////////modified hjg/////////////////////////////////////////////////////
namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     场景框改变事件Irp
	创建人：	 hjg
	创建时间：   2009/4/8
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CFrameFlowIrp : public CVirtualIrp
	{
	public:
		CFrameFlowIrp(void);
		virtual ~CFrameFlowIrp(void);
	public:
		virtual _IrpType Get_eIrpType() { return eFrameModify_Event; };
		virtual bool isKindOf(const std::string &strClass);
		/*******************************************************************************/
		// 函数名称： DoPackageIrp
		// 功能：  打包Irp的内容
		// 参数： 
		// 返回值: 
		virtual std::string doPackageIrp();
		/*******************************************************************************/
		// 函数名称： UnzipPackage
		// 功能： 解压缩打包的Irp的内容
		// 参数： 
		//        char *lpData：
		//        UINT uNumber：
		// 返回值:  
        static CFrameFlowIrp * UnzipPackage(char *lpData, unsigned short uNumber);
	public:
		eEventSign                   m_eEvent;
		unsigned short               m_dwFrameId;
		_ScheduleSceneState          m_eSceneAct;             //情景/场景演化动作类别
	public:
		/*******************************************************************************/
		//功能：创建场景框改变事件Irp
		//参数：
		//      IXMLDOMNode *pFrameNode:
		//      eEventSign eEvent:
		//返回值:  
		static CFrameFlowIrp *CreateEventIrp_FrameFlow(pugi::xml_node *pFrameNode, eEventSign eEvent);
		/*******************************************************************************/
		//功能：创建情景调度Irp
		//参数：
		//      IXMLDOMNode *pSceneActNode:
		//      _ScheduleSceneState eSceneAct:
		//      eEventSign eEvent:
		//返回值:  
		static CFrameFlowIrp *CreateEventIrp_SceneActFlow(pugi::xml_node *pSceneActNode, _ScheduleSceneState eSceneAct, eEventSign eEvent);
		/*******************************************************************************/
		//功能：创建情景调度Irp
		//参数：
		//      DWORD dwFrameId:
		//      _ScheduleSceneState eSceneAct:
		//      eEventSign eEvent:
		//返回值:  
		static CFrameFlowIrp *CreateEventIrp_SceneActFlow(unsigned short dwFrameId, _ScheduleSceneState eSceneAct, eEventSign eEvent);
	};

}}
