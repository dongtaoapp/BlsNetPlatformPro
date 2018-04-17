#include <boost/format.hpp>
#include ".\EventLogUpdate_Singleton.h"

#include "..\Common\CommonGlobal.h"


namespace jysoft{  namespace log 
{
	//事件日志格式化
	//strTime:  操作时间
	//pVirEventIrp: 目标事件包基类
	_EventLog_struct * CEventLogUpdate_Singleton::getIrpLogMessage(const std::string &strTime, irp::CVirEventIrp *pVirEventIrp) const
	{
		_EventLog_struct  *pLogStruct = NULL;
		if( pVirEventIrp != NULL )
		{
			pLogStruct = new _EventLog_struct();
			pLogStruct->m_strTime = strTime;
			//模拟人事件
			if( pVirEventIrp->isKindOf("CEventIrp_SimulateTrigger") )
			{
				irp::CEventIrp_SimulateTrigger *pTriggerEventIrp = (irp::CEventIrp_SimulateTrigger *)pVirEventIrp;
				if( !getSimulateTriggerIrpLog(pLogStruct, pTriggerEventIrp) )
				{
					delete pLogStruct;
					pLogStruct = NULL;
				}
			}
			else if( !pVirEventIrp->getIrpLogMessage( pLogStruct ) )
			{
				delete pLogStruct;
				pLogStruct = NULL;
			}
		}
		return pLogStruct;
	}

	bool CEventLogUpdate_Singleton::getSimulateTriggerIrpLog(_EventLog_struct *pLogStruct, irp::CEventIrp_SimulateTrigger* pTriggerEventIrp) const
	{
		bool     bRecordLog = false;
		std::string   strAct1, strAct2;
		switch( pTriggerEventIrp->Get_EventSign() )
		{
		case ES_Conscious:
			{
				pLogStruct->m_strAct = "意识判别";
				bRecordLog  = true;
				break;
			}
		case ES_PulseCheck:
			{
				short  sPulsePort, sAct;
				if( pTriggerEventIrp->explainSimulateTrigger_PulseCheckIrp(/*out*/sPulsePort, /*out*/sAct) && sAct == 1 )
				{
					if( sPulsePort == 0x01 )
					{
						bRecordLog = true; 
						pLogStruct->m_strAct = "脉搏检查";
					}
				}
				break;
			}
		case ES_ClearObstruc:
			{
				bRecordLog = true; 
				pLogStruct->m_strAct = "清除异物";
				break;
			}
		case ES_Defib:
			{
				bool    bSyncDefibr  = false;
				short   sDefibrCount, sDefibrEnergy = 0;
				//记录除颤的日志信息
				if( pTriggerEventIrp->explainSimulateTrigger_DefibrEventIrp(/*out*/sDefibrCount, /*out*/sDefibrEnergy, /*out*/bSyncDefibr) )
				{
					if( sDefibrEnergy == 0 )
					{
                        strAct1 = "同步除颤";
                        strAct2 = "除颤";
						pLogStruct->m_strAct = bSyncDefibr ? strAct1 : strAct2;
					}
					else
					{
                        strAct1 = "同步除颤";
                        strAct2 = "除颤";
						boost::format  fmt("%s， %dJ");
						fmt % (bSyncDefibr ? strAct1 : strAct2) % sDefibrEnergy;
						pLogStruct->m_strAct = fmt.str();
					}
					bRecordLog  = true;
				}
				break;
			}
		case ES_Intubation:
			{
				short   sAct, sPosition;
				//记录插管信息
				if( pTriggerEventIrp->explainSimulateTrigger_IntubateEventIrp( /*out*/sPosition, /*out*/sAct ) )
				{
					switch( sPosition )
					{
					case 0x00: //食管
						{
                            strAct1 = "插管进入食管";
                            strAct2 = "移除进入食管的插管";
							pLogStruct->m_strAct = sAct == 0x11 ? strAct1 : strAct2;
							break;
						}
					case 0x02: //气管
						{
                            strAct1 = "插管进入气管";
                            strAct2 = "移除进入气管的插管";
							pLogStruct->m_strAct = sAct == 0x11 ? strAct1 : strAct2;
							break;
						}
					}
					bRecordLog  = true;
				}
				break;
			}
		}
		return bRecordLog;
	}
}}
