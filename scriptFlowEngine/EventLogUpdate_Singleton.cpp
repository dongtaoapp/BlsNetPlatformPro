#include <boost/format.hpp>
#include ".\EventLogUpdate_Singleton.h"

#include "..\Common\CommonGlobal.h"


namespace jysoft{  namespace log 
{
	//�¼���־��ʽ��
	//strTime:  ����ʱ��
	//pVirEventIrp: Ŀ���¼�������
	_EventLog_struct * CEventLogUpdate_Singleton::getIrpLogMessage(const std::string &strTime, irp::CVirEventIrp *pVirEventIrp) const
	{
		_EventLog_struct  *pLogStruct = NULL;
		if( pVirEventIrp != NULL )
		{
			pLogStruct = new _EventLog_struct();
			pLogStruct->m_strTime = strTime;
			//ģ�����¼�
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
				pLogStruct->m_strAct = "��ʶ�б�";
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
						pLogStruct->m_strAct = "�������";
					}
				}
				break;
			}
		case ES_ClearObstruc:
			{
				bRecordLog = true; 
				pLogStruct->m_strAct = "�������";
				break;
			}
		case ES_Defib:
			{
				bool    bSyncDefibr  = false;
				short   sDefibrCount, sDefibrEnergy = 0;
				//��¼��������־��Ϣ
				if( pTriggerEventIrp->explainSimulateTrigger_DefibrEventIrp(/*out*/sDefibrCount, /*out*/sDefibrEnergy, /*out*/bSyncDefibr) )
				{
					if( sDefibrEnergy == 0 )
					{
                        strAct1 = "ͬ������";
                        strAct2 = "����";
						pLogStruct->m_strAct = bSyncDefibr ? strAct1 : strAct2;
					}
					else
					{
                        strAct1 = "ͬ������";
                        strAct2 = "����";
						boost::format  fmt("%s�� %dJ");
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
				//��¼�����Ϣ
				if( pTriggerEventIrp->explainSimulateTrigger_IntubateEventIrp( /*out*/sPosition, /*out*/sAct ) )
				{
					switch( sPosition )
					{
					case 0x00: //ʳ��
						{
                            strAct1 = "��ܽ���ʳ��";
                            strAct2 = "�Ƴ�����ʳ�ܵĲ��";
							pLogStruct->m_strAct = sAct == 0x11 ? strAct1 : strAct2;
							break;
						}
					case 0x02: //����
						{
                            strAct1 = "��ܽ�������";
                            strAct2 = "�Ƴ��������ܵĲ��";
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
