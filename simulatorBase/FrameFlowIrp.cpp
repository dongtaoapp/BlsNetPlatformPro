#include <boost/format.hpp>
#include ".\frameflowirp.h"

namespace jysoft { namespace irp {

	CFrameFlowIrp::CFrameFlowIrp(void)
	{
		m_dwFrameId      = 0;
		m_eSceneAct      = DSS_SceneSwitch;
	}

	CFrameFlowIrp::~CFrameFlowIrp(void)
	{
	}

	bool CFrameFlowIrp::isKindOf(const std::string &strClass)
	{
		if( strClass == "CFrameFlowIrp" )
		{
			return true;
		}
		return false;
	}

	/*******************************************************************************/
	// 函数名称： DoPackageIrp
	// 功能：  打包Irp的内容
	// 参数： 
	// 返回值: 
	std::string CFrameFlowIrp::doPackageIrp()
	{
		boost::format fmt("<FrameFlowIrp><ScenarioFrameId>%d</ScenarioFrameId><EventSign>%d</EventSign><SceneAct>%d</SceneAct></FrameFlowIrp>");
		fmt % m_dwFrameId % (int)m_eEvent % (int)m_eSceneAct;
		return fmt.str();
	}

	/*******************************************************************************/
	//功能：创建情景调度Irp
	//参数：
	//      DWORD dwFrameId:
	//      _ScheduleSceneState eSceneAct:
	//      eEventSign eEvent:
	//返回值:  
	CFrameFlowIrp * CFrameFlowIrp::CreateEventIrp_SceneActFlow(unsigned short dwFrameId, _ScheduleSceneState eSceneAct, eEventSign eEvent)
	{
		CFrameFlowIrp  *pFrameFlowIrp = new CFrameFlowIrp();
		pFrameFlowIrp->m_eEvent              = eEvent;
		pFrameFlowIrp->m_eSceneAct           = eSceneAct;
		pFrameFlowIrp->m_dwFrameId           = dwFrameId;

		return pFrameFlowIrp;
	}

	/*******************************************************************************/
	//功能：创建场景框改变事件Irp
	//参数：
	//      IXMLDOMNode *pFrameNode:
	//      eEventSign eEvent:
	//返回值:  
	CFrameFlowIrp * CFrameFlowIrp::CreateEventIrp_FrameFlow(pugi::xml_node *pFrameNode, eEventSign eEvent)
	{
		return NULL;
	}

	/*******************************************************************************/
	//功能：创建情景调度Irp
	//参数：
	//      IXMLDOMNode *pSceneActNode:
	//      _ScheduleSceneState eSceneAct:
	//      eEventSign eEvent:
	//返回值:  
	CFrameFlowIrp * CFrameFlowIrp::CreateEventIrp_SceneActFlow(pugi::xml_node *pSceneActNode, _ScheduleSceneState eSceneAct, eEventSign eEvent)
	{
		return NULL;
	}

	/*******************************************************************************/
	// 函数名称： UnzipPackage
	// 功能： 解压缩打包的Irp的内容
	// 参数： 
	//        char *lpData：
	//        UINT uNumber：
	// 返回值:  
    CFrameFlowIrp * CFrameFlowIrp::UnzipPackage(char *lpData, unsigned short uNumber)
	{
		CFrameFlowIrp  *pFrameFlowIrp = NULL;
		/*CMessMemory   cMessMemory;
		if( cMessMemory.ParseContext(lpData, (DWORD)uNumber, NULL) != -1 )
		{
			if( cMessMemory.m_eStyle == CMessMemory::aComposite )
			{
				pFrameFlowIrp   = new CFrameFlowIrp();
				POSITION  pos = cMessMemory.m_LeafList.GetHeadPosition();
				while( pos )
				{
					CMessMemory  *pLeafMess = cMessMemory.m_LeafList.GetNext( pos );
					CString   strTxt((char *)pLeafMess->m_pPtr, pLeafMess->GetLeafMSize());
					if( pLeafMess->m_strCaption == _T("ScenarioFrameId") )
					{
						pFrameFlowIrp->m_dwFrameId = ::atoi( strTxt.operator LPCTSTR() );
					}
					else if( pLeafMess->m_strCaption == _T("EventSign") )
					{
						pFrameFlowIrp->m_eEvent = (eEventSign)::atoi( strTxt.operator LPCTSTR() );
					}
					else if( pLeafMess->m_strCaption == _T("SceneAct") )
					{
						pFrameFlowIrp->m_eSceneAct = (_ScheduleSceneState)::atoi( strTxt.operator LPCTSTR() );
					}
				}
			}
		}*/
		return pFrameFlowIrp;
	}

}}
