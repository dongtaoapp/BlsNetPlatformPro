#pragma once
#include <list>
#include ".\XSceneActFrame.h"
#include ".\scriptflowengine_global.h"

#include "..\common\CommonGlobal.h"
#include "..\common\EventHandleClockIrpOp.h"
#include "..\common\EventHandleCustomIrpOp.h"

#include "..\SimulatorBase\ITransportOrderIrpToSimulator.h"

namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     情景框集合类
	创建人：	 hjg
	创建时间：   2017/2/16
	//-----------------------------------------------------------------------------------------------------------------*/
    class SCRIPTFLOWENGINESHARED_EXPORT CSceneActsCollect : public irp::CEventHandleCustomIrpOp
											,public irp::CEventHandleClockIrpOp
	{
	public:
		CSceneActsCollect();
		virtual ~CSceneActsCollect(void);
	protected:
		std::list<CXSceneActFrame *>       m_lstSceneActFrames;
		//激活的情景框列表
		std::list<ISceneActRunOp *>        m_lstActiveSceneActs;
	private:
		transLayer::ITransportOrderIrpToUp *m_pTransOrderIrpToUp;
	public: //函数重载
		/*******************************************************************************/
		//功能：处理场景事件IRP函数
		//参数：
		//      CVirtualIrp *pCurrIrp：
		//返回值:  后续不再处理（FALSE);
		virtual bool doHandleCustomEventIrpOp(irp::CVirtualIrp *pCurrIrp);
		/*******************************************************************************/
		//功能：处理时钟事件IRP函数
		//参数：
		//      CVirtualIrp *pCurrIrp：
		//返回值:  后续不再处理（FALSE);
		virtual bool doHandleClockIrpOp(irp::CVirtualIrp *pCurrIrp);
	public:
		/*******************************************************************************/
		//功能：加载默认的情景框
		//参数：
		//      const CString &strUnzipCataloguePath：解压包目标路径
		//返回值:  
		void LoadDefaultSceneActsFile(const std::string &strUnzipCataloguePath);
		/*******************************************************************************/
		//功能：加载脚本内定义的情景框
		//参数：
		//      pRootElement：
		//      pTransOrderIrpToUp:
		//返回值:
		void InitialScriptSceneActs(pugi::xml_node rootElement, IGetPhysiologyActionObj *pGetActionObj, transLayer::ITransportOrderIrpToUp *pTransOrderIrpToUp);
		/*******************************************************************************/
		//功能：激活全局情景框
		//参数：
		//返回值: 
		void ActiveSceneActsRun();
		/*******************************************************************************/
		//功能：清除所有情景框
		//参数：
		//返回值: 
		void ClearSceneActs();
	public:
		CXSceneActFrame * SearchSceneActFramePtr(unsigned short dwSignID);
	};
}}
