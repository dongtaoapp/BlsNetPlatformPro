#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include ".\TriggerJudgeGlobal.h"

#include "..\common\DecodeUtil.h"
#include "..\common\ParseCPRData_Singleton.h"


using namespace jysoft::irp;
using namespace jysoft::utility;
namespace jysoft { namespace transLayer 
{
	ISimulateTriggerJudge::ISimulateTriggerJudge(void)
	{
		m_cDataTmpBuffer.InitializeBuff( 1024 );
	}

	ISimulateTriggerJudge::~ISimulateTriggerJudge(void)
	{
	}

	//查找首标志
	bool ISimulateTriggerJudge::searchBeginSegmentFlag()
	{
		unsigned char lbyteData[10];
		while(m_cDataTmpBuffer.GetNoneReadedNum() >= 4)
		{
			m_cDataTmpBuffer.ReadData(lbyteData, 4, NULL);
			if(lbyteData[0] == 0xFF )
			{
				if( lbyteData[3] == 0xFC )
				{
					return true;
				}
				else if( lbyteData[1] == 0x91 )
				{
					if( m_cDataTmpBuffer.GetNoneReadedNum() > 4 )
					{
						m_cDataTmpBuffer.ReadData(lbyteData, 5, NULL);
						if( lbyteData[4] == 0xFC )
						{
							return true;
						}
					}
					else
					{
						return true;
					}
				}
				else if( lbyteData[1] == 0x00 )
				{
					if( m_cDataTmpBuffer.GetNoneReadedNum() > 5 )
					{
						m_cDataTmpBuffer.ReadData(lbyteData, 6, NULL);
						if( lbyteData[5] == 0xFC )
						{
							return true;
						}
					}
					else
					{
						return true;
					}
				}
				else if( lbyteData[1] == 0x2A || lbyteData[1] == 0x2B || lbyteData[1] == 0x4A || lbyteData[1] == 0x4B)
				{
					if( m_cDataTmpBuffer.GetNoneReadedNum() > 6 )
					{
						m_cDataTmpBuffer.ReadData(lbyteData, 7, NULL);
						if( lbyteData[6] == 0xFC )
						{
							return true;
						}
					}
					else
					{
						return true;
					}
				}
			}
			m_cDataTmpBuffer.ReadDataMovePtr(lbyteData, 1);
			m_cDataTmpBuffer.ResetBeginPosToReadBeginPos();
		}
		return false;
	}

	//查找尾标志, 并返回命令长度;-1表示没找到
	int  ISimulateTriggerJudge::searchEndSegmentFlag()
	{
		unsigned char lbyteData[10];
        short  dwActiveNum = 0;
		m_cDataTmpBuffer.ReadData(lbyteData, 4, /*out*/&dwActiveNum);
		if(lbyteData[0] == 0xFF && dwActiveNum == 4)
		{
			if( lbyteData[3] == 0xFC )
			{
				return 4;
			}
			else if( lbyteData[1] == 0x91 )
			{
				m_cDataTmpBuffer.ReadData(lbyteData, 5, /*out*/&dwActiveNum);
				if( lbyteData[4] == 0xFC && dwActiveNum == 5)
				{
					return 5;
				}
			}
			else if( lbyteData[1] == 0x00 )
			{
				m_cDataTmpBuffer.ReadData(lbyteData, 6, /*out*/&dwActiveNum);
				if( lbyteData[5] == 0xFC && dwActiveNum == 6)
				{
					return 6;
				}
			}
			else if( lbyteData[1] == 0x2A || lbyteData[1] == 0x2B || lbyteData[1] == 0x4A || lbyteData[1] == 0x4B)
			{
				m_cDataTmpBuffer.ReadData(lbyteData, 7, /*out*/&dwActiveNum);
				if( lbyteData[6] == 0xFC && dwActiveNum == 7)
				{
					return 7;
				}
			}
		}
		return -1;
	}

	//接受从串口收到的数据
	_VirDataStruct * ISimulateTriggerJudge::getDataStructFromCommData(void)
	{
		if( searchBeginSegmentFlag() )
		{
			//查找尾标志, 并返回命令长度;-1表示没找到
			int nCmdLength = searchEndSegmentFlag();
			if( nCmdLength > 0 &&  m_cDataTmpBuffer.GetNoneReadedNum() >= nCmdLength )
			{
				_DataNewAllocStruct *pDataStruct = new _DataNewAllocStruct();
				pDataStruct->m_dwSize = nCmdLength;
				pDataStruct->m_pData = new unsigned char[pDataStruct->m_dwSize];
				m_cDataTmpBuffer.ReadDataMovePtr(pDataStruct->m_pData, pDataStruct->m_dwSize);
				m_cDataTmpBuffer.ResetBeginPosToReadBeginPos();
				return pDataStruct;
			}
		}
		return NULL;
	}

	void ISimulateTriggerJudge::writeCommunicateData(void *lpData, UINT uNumber)
	{
		unsigned char *lpByte = (unsigned char *)lpData;
		m_cDataTmpBuffer.WriteData(lpByte, uNumber, NULL);
	}

	//-------------------------------------------------------------------------------------------------------------------------------
	CBlsTriggerJudgeVersion::CBlsTriggerJudgeVersion()
	{

	}

	CBlsTriggerJudgeVersion::~CBlsTriggerJudgeVersion()
	{

	}

	/*******************************************************************************/
	// 函数名称： createEvent_SimulateTriggerIrp
	// 功能： 创建模拟人触发事件Irp
	// 参数： 
	//        _VirDataStruct *pDataStruct: 
	// 返回值:  
	irp::CEventIrp_SimulateTrigger * CBlsTriggerJudgeVersion::createEvent_SimulateTriggerIrp(_VirDataStruct *pDataStruct)
	{
		CEventIrp_SimulateTrigger   *pTriggerEventIrp = NULL;
		//模拟人触发事件
		switch( pDataStruct->m_pData[1] )
		{
		case 0x04:
			{
				//仰头（0x21）、平躺（0x20）
				if( pDataStruct->m_pData[2] == 0x21 || pDataStruct->m_pData[2] == 0x20 )
				{
					pTriggerEventIrp = CEventIrp_SimulateTrigger::CreateSimulateTrigger_LookUpEventIrp( pDataStruct->m_pData[2] ? true : false );
				}
				//脉搏检查：按脉（0x11）、移开（0x10）
				if ( pDataStruct->m_pData[2] == 0x11 || pDataStruct->m_pData[2] == 0x10 )
				{
					pTriggerEventIrp = CEventIrp_SimulateTrigger::CreateSimulateTrigger_PulseCheckEventIrp(pDataStruct->m_pData[2]);
				}
				//意识判别（0x41）
				if( pDataStruct->m_pData[2] == 0x41 )
				{
					pTriggerEventIrp = CEventIrp_SimulateTrigger::CreateSimulateTrigger_ConsciousEventIrp();
				}
				//吹气时气道开放：未开放（0x61）、移除（0x60）
				if( pDataStruct->m_pData[2] == 0x61 || pDataStruct->m_pData[2] == 0x60 )
				{
					pTriggerEventIrp = CEventIrp_SimulateTrigger::CreateSimulateTrigger_PipeCloseEventIrp( (pDataStruct->m_pData[2] == 0x61) ? true : false );
				}
				//清除异物（0x51）
				if( pDataStruct->m_pData[2] == 0x51 )
				{
					pTriggerEventIrp = CEventIrp_SimulateTrigger::CreateSimulateTrigger_ClearObstructEventIrp();
				}
				break;
			}
		case 0x05:
			{
				//模拟人中电池状态
				pTriggerEventIrp = new CEventIrp_SimulateTrigger();
                pTriggerEventIrp->m_strTriggerEventName  = "Notify_ElementVolume";

				boost::format fmt("<Notify_ElementVolume>%d</Notify_ElementVolume>");
				fmt % pDataStruct->m_pData[3];
				pTriggerEventIrp->m_strTriggerXML = fmt.str();
				pTriggerEventIrp->set_eEventSign( ES_Normal );
				break;
			}
		case 0x08:
			{
				//AED操作信息
				if( pDataStruct->m_pData[2] == 0x71 )
				{
					pTriggerEventIrp = CEventIrp_SimulateTrigger::CreateSimulateTrigger_DefibrEventIrp(false);
				}
				else if( pDataStruct->m_pData[2] == 0x81 || pDataStruct->m_pData[2] == 0x80 )
				{
					pTriggerEventIrp = CEventIrp_SimulateTrigger::CreateSimulateTrigger_AEDEventIrp( (pDataStruct->m_pData[2] == 0x81) ? true : false);
				}
				else 
				{
					pTriggerEventIrp = CEventIrp_SimulateTrigger::CreateSimulateTrigger_AEDEventIrp();
				}
				break;
			}
		}
		return pTriggerEventIrp;
	}

	/*******************************************************************************/
	// 函数名称： judgeRealTimeDataType
	// 功能：  判断是否为CPR实时采样数据
	// 参数： 
	// 返回值: 
	bool CBlsTriggerJudgeVersion::judgeRealTimeDataType(_VirDataStruct *pDataStruct, /*out*/_CPRData *lptrCPRData)
	{
		unsigned char *lpData = pDataStruct->m_pData;
		if(pDataStruct && lpData[0] == 0xFF && lpData[pDataStruct->m_dwSize-1] == 0xFC)
		{
			const cpr::CParseCPRData_Singleton &cCPRParse = cpr::CParseCPRData_Singleton::get_const_instance();
			if( lpData[1] == 0x91 || lpData[1] == 0x2A || lpData[1] == 0x2B || lpData[1] == 0x4A || lpData[1] == 0x4B )
			{
				if( lptrCPRData != NULL )
				{
					switch( lpData[1] )
					{
					case 0x91:
						{
							//按压、吹气动作启停指令
							if( lpData[2] == 0x1A )
							{
								*lptrCPRData = cCPRParse.createPressurePhaseData( lpData[3] ? true : false );
							}
							else
							{
								*lptrCPRData = cCPRParse.createBreathPhaseData( lpData[3] ? true : false );
							}
							break;
						}
					case 0x2A:
						{
							//按压幅度值、释放/位置、时间戳
							unsigned char sDepth = lpData[2];
							bool bReleaseError = (lpData[3] & 0x10) ? true : false;
							unsigned char sPos = (lpData[3] & 0x0F);
							unsigned short sTimestamp = *(unsigned short *)(&lpData[4]);
							*lptrCPRData = cCPRParse.createPressureDepthData(sDepth, bReleaseError, sPos, sTimestamp);
							break;
						}
					case 0x4A:
						{
							//吹气量、进胃、时间戳
							unsigned char sVolume = (lpData[2] & 0x3F);
							bool bStomach = (lpData[3] & 0x80) ? true : false;
							unsigned short sTimestamp = *(unsigned short *)(&lpData[4]);
							*lptrCPRData = cCPRParse.createBreathVolumeData(sVolume, bStomach, sTimestamp);
							break;
						}
					case 0x2B:
						{
							//按压频率（2个字节，BCD码表示）：XXXbpm;
							unsigned char sRate = (lpData[2] & 0x0F) * 100 + ((lpData[3] & 0xF0) >> 4)*10 + (lpData[3] & 0x0F);
							unsigned short sTimestamp = *(unsigned short *)(&lpData[4]);
							*lptrCPRData = cCPRParse.createPressureRateData(sRate, sTimestamp);
							break;
						}
					case 0x4B:
						{
							//吹气频率及通气时间（BCD码表示）
							unsigned char sRate = ((lpData[2] & 0xF0) >> 4)*10 + (lpData[2] & 0x0F);
							unsigned short sRespTime = ((lpData[3] & 0xF0) >> 4)*10 + (lpData[3] & 0x0F);
							unsigned short sTimestamp = *(unsigned short *)(&lpData[4]);
							*lptrCPRData = cCPRParse.createBreathRateData(sRate, sRespTime, sTimestamp);
							break;
						}
					}
				}
				return true;
			}
			else if( lpData[1] == 0x21 || lpData[1] == 0x41)
			{
				//判断为CPR实时数据
				if( lptrCPRData != NULL )
				{
					unsigned char cDepth = (lpData[2] & 0x3F);
					bool bAscens = (lpData[2] & 0x40) ? true : false;
					*lptrCPRData = cCPRParse.createRealTimeSampleData(cDepth, lpData[1] == 0x21 ? true : false, bAscens);
				}
				return true;
			}
		}
		return false;
	}
}}
