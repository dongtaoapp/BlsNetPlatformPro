#include <boost/format.hpp>
#include ".\cprstatirp.h"

using namespace jysoft::simulator::base;

namespace jysoft { namespace irp {

	CCPRStatIrp::CCPRStatIrp(void)
	{
	}

	CCPRStatIrp::~CCPRStatIrp(void)
	{
	}

	bool CCPRStatIrp::isKindOf(const std::string &strClass)
	{
		if( strClass == "CCPRStatIrp" )
		{
			return true;
		}
		return CVirEventIrp::isKindOf( strClass );
	}

	/*******************************************************************************/
	// 函数名称： doPackageIrp
	// 功能：  打包Irp的内容
	// 参数： 
	// 返回值: 
	std::string CCPRStatIrp::doPackageIrp()
	{
		boost::format fmt("<CPRStatIrp><Mode>%d</Mode><State>%d</State></CPRStatIrp>");
		fmt % (int)m_eCPRMode % m_nStat;
		return fmt.str();
	}

	/*******************************************************************************/
	// 函数名称： CreateEvent_CPRIrp
	// 功能： 创建CPR事件Irp类
	// 参数： 
	//       _CPRManageState eCPRMode: CPR模式
	//       int nStat:               状态
	// 返回值:  
	CCPRStatIrp * CCPRStatIrp::CreateEvent_CPRIrp(_CPRManageState eCPRMode, int nStat)
	{
		CCPRStatIrp  *pCPRStatIrp = new CCPRStatIrp();
		//设置CPR模式
		pCPRStatIrp->Set_eCPRMode( eCPRMode );
		//设置此模式下的事件
		pCPRStatIrp->Set_OperatorStat( nStat );
		return pCPRStatIrp;
	}

	/*******************************************************************************/
	// 函数名称： UnzipPackage
	// 功能： 解压缩打包的Irp的内容
	// 参数： 
	//        char *lpData：
	//        UINT uNumber：
	// 返回值:  
    CCPRStatIrp * CCPRStatIrp::UnzipPackage(char *lpData, unsigned short uNumber)
	{
		CCPRStatIrp  *pCPRStateIrp = NULL;
		/*CMessMemory   cMessMemory;
		if( cMessMemory.ParseContext(lpData, (DWORD)uNumber, NULL) != -1 )
		{
			if( cMessMemory.m_eStyle == CMessMemory::aComposite )
			{
				pCPRStateIrp   = new CCPRStatIrp();
				POSITION  pos = cMessMemory.m_LeafList.GetHeadPosition();
				while( pos )
				{
					CMessMemory  *pLeafMess = cMessMemory.m_LeafList.GetNext( pos );
					CString   strTxt((char *)pLeafMess->m_pPtr, pLeafMess->GetLeafMSize());
					if( pLeafMess->m_strCaption == _T("Mode") )
					{
						pCPRStateIrp->m_eCPRMode = (_CPRManageState)::atoi( strTxt.operator LPCTSTR() );
					}
					else if( pLeafMess->m_strCaption == _T("EventSign") )
					{
						pCPRStateIrp->m_nStat = ::atoi( strTxt.operator LPCTSTR() );
					}
				}
			}
		}*/
		return pCPRStateIrp;
	}

	/*******************************************************************************/
	// 函数名称： UpdateEventSignShow
	// 功能：  显示事件动作
	// 参数： 
	// 返回值: 
	void CCPRStatIrp::UpdateEventSignShow(CShowEventSignUpdateInterface  *pInterface )
	{
		//------------------------------------------------------------------------
		//0:    CPR操作结束
		//1:    CPR操作开始
		//2:    在标准模式及实战模式下，完成5个循环的CPR操作
		if( m_nStat == 1 )
		{
			pInterface->OnAddNewEventSign( ES_CPREvent );
		}
		else if( m_nStat == 0 )
		{
			pInterface->OnRemoveEventSign( ES_CPREvent );
		}
	}

}}
