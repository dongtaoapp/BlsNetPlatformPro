#include <sstream>
#include <boost/assert.hpp>
#include <boost/format.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include ".\eventirp_simulatetrigger.h"

#include "..\elementParse\SEvent_AED.h"
#include "..\ElementParse\SEvent_Defibr.h"
#include "..\ElementParse\SEvent_Intubate.h"
#include "..\ElementParse\SEvent_Pace.h"
#include "..\ElementParse\SEvent_Pulse.h"

using namespace boost::property_tree;
using namespace jysoft::simulator::base;

namespace jysoft { namespace irp {

	CEventIrp_SimulateTrigger::CEventIrp_SimulateTrigger(void)
	{
		m_bAddLog     = true;
		m_eEventSign  = ES_Normal;
		m_sExtendData[0] = m_sExtendData[1] = 0;
	}

	CEventIrp_SimulateTrigger::~CEventIrp_SimulateTrigger(void)
	{
	}

	bool CEventIrp_SimulateTrigger::isKindOf(const std::string &className)
	{
		if( className == "CEventIrp_SimulateTrigger" )
		{
			return true;
		}
		return CVirEventIrp::isKindOf( className );
	}

	//�����¼���־
	eEventSign CEventIrp_SimulateTrigger::Get_EventSign()
	{
		return m_eEventSign;
	}

	//������ͷ\ƽ�ɴ����¼�Irp
	CEventIrp_SimulateTrigger * CEventIrp_SimulateTrigger::CreateSimulateTrigger_LookUpEventIrp(bool bHeadLookUp)
	{
		CEventIrp_SimulateTrigger  *pSimulatorEventIrp = new CEventIrp_SimulateTrigger();
		pSimulatorEventIrp->m_strTriggerEventName = "Event_LookUp";
		if( bHeadLookUp )
		{
			pSimulatorEventIrp->m_strTriggerXML = "<Event_LookUp>head LookUp</Event_LookUp>";
		}
		else
		{
			pSimulatorEventIrp->m_strTriggerXML = "<Event_LookUp>head Lie</Event_LookUp>";
		}
		pSimulatorEventIrp->set_eEventSign( ES_LookUp );
		pSimulatorEventIrp->m_sExtendData[0] = bHeadLookUp ? 1 : 0;
		return pSimulatorEventIrp;
	}

	//�����ٶ�\�ٶ��ƽ�¼�
	CEventIrp_SimulateTrigger * CEventIrp_SimulateTrigger::CreateSimulateTrigger_RaiseJowlEventIrp(bool bRaiseJowl)
	{
		CEventIrp_SimulateTrigger  *pSimulatorEventIrp = new CEventIrp_SimulateTrigger();
		pSimulatorEventIrp->m_strTriggerEventName = "Event_RaiseJowl";
		if( bRaiseJowl )
		{
			pSimulatorEventIrp->m_strTriggerXML = "<Event_RaiseJowl>Jowl LookUp</Event_RaiseJowl>";
		}
		else
		{
			pSimulatorEventIrp->m_strTriggerXML = "<Event_RaiseJowl>Jowl Lie</Event_RaiseJowl>";
		}
		pSimulatorEventIrp->set_eEventSign( ES_RaiseJowl );

		pSimulatorEventIrp->m_sExtendData[0] = bRaiseJowl ? 1 : 0;
		return pSimulatorEventIrp;
	}

	/*******************************************************************************/
	// �������ƣ� CreateSimulateTrigger_PipeCloseEventIrp
	// ���ܣ� ��������ʱ����δ�����¼�Irp
	// ������      
	// ����ֵ:  
	CEventIrp_SimulateTrigger * CEventIrp_SimulateTrigger::CreateSimulateTrigger_PipeCloseEventIrp(bool bPipeClose)
	{
		CEventIrp_SimulateTrigger  *pSimulatorEventIrp = new CEventIrp_SimulateTrigger();
		pSimulatorEventIrp->m_strTriggerEventName = "Event_PipeClose";
		if( bPipeClose )
		{
			pSimulatorEventIrp->m_strTriggerXML = "<Event_PipeClose state=\"respStart\" />";
		}
		else
		{
			pSimulatorEventIrp->m_strTriggerXML = "<Event_PipeClose state=\"respEnd\" />";
		}
		pSimulatorEventIrp->set_eEventSign( ES_PipeClose );

		pSimulatorEventIrp->m_sExtendData[0] = bPipeClose ? 1 : 0;
		return pSimulatorEventIrp;
	}

	/*******************************************************************************/
	// �������ƣ� CreateSimulateTrigger_ClearObstructEventIrp
	// ���ܣ� ������������¼�
	// ������      
	// ����ֵ:  
	CEventIrp_SimulateTrigger * CEventIrp_SimulateTrigger::CreateSimulateTrigger_ClearObstructEventIrp()
	{
		CEventIrp_SimulateTrigger  *pTriggerEventIrp = new CEventIrp_SimulateTrigger();
        pTriggerEventIrp->m_strTriggerEventName  = "Event_ClearObstruc";
        pTriggerEventIrp->m_strTriggerXML = "<Event_ClearObstruc />";
		pTriggerEventIrp->set_eEventSign( ES_ClearObstruc );
		return pTriggerEventIrp;
	}

	/*******************************************************************************/
	// �������ƣ� CreateSimulateTrigger_ConsciousEventIrp
	// ���ܣ� ������ʶ�б��¼�
	// ������      
	// ����ֵ:  
	CEventIrp_SimulateTrigger * CEventIrp_SimulateTrigger::CreateSimulateTrigger_ConsciousEventIrp()
	{
		CEventIrp_SimulateTrigger  *pTriggerEventIrp = new CEventIrp_SimulateTrigger();
        pTriggerEventIrp->m_strTriggerEventName  = "Event_Conscious";
        pTriggerEventIrp->m_strTriggerXML = "<Event_Conscious></Event_Conscious>";
		pTriggerEventIrp->set_eEventSign( ES_Conscious );
		return pTriggerEventIrp;
	}

	/*******************************************************************************/
	// �������ƣ� CreateSimulateTrigger_AEDEventIrp
	// ���ܣ� ����AED�¼�
	// ������    
	//          bStartupAED:     ture:��ʼ  false: ����  unknow: ����
	// ����ֵ:  
	CEventIrp_SimulateTrigger * CEventIrp_SimulateTrigger::CreateSimulateTrigger_AEDEventIrp(boost::tribool bStartupAED/*=indeterminate*/)
	{
		CEventIrp_SimulateTrigger  *pTriggerEventIrp = new CEventIrp_SimulateTrigger();
        pTriggerEventIrp->m_strTriggerEventName  = "Event_AED";
		pTriggerEventIrp->m_strTriggerXML = CSEvent_AED::saveParams( bStartupAED );
		pTriggerEventIrp->set_eEventSign( ES_AED );
		return pTriggerEventIrp;
	}

	/*******************************************************************************/
	// �������ƣ� CreateSimulateTrigger_DefibrEventIrp
	// ���ܣ� ���������¼�
	// ������    
	//           BOOL bSyncDefibr:      �Ƿ�ͬ������
	//           short sEnergy:         ����������0:��ʾδָ��
	// ����ֵ:  
	CEventIrp_SimulateTrigger * CEventIrp_SimulateTrigger::CreateSimulateTrigger_DefibrEventIrp(bool bSyncDefibr, short sEnergy/*=0*/)
	{
		CEventIrp_SimulateTrigger  *pSimulatorEventIrp = new CEventIrp_SimulateTrigger();
		//�¼���ʶ����
		pSimulatorEventIrp->m_strTriggerEventName = CSEvent_Defibr::getEvent_Defibr_Caption();
	
		pSimulatorEventIrp->m_strTriggerXML = CSEvent_Defibr::saveParams(1, sEnergy, bSyncDefibr);
		pSimulatorEventIrp->set_eEventSign( ES_Defib );

		pSimulatorEventIrp->m_sExtendData[0] = bSyncDefibr ? 1 : 0;
		pSimulatorEventIrp->m_sExtendData[1] = sEnergy;
		return pSimulatorEventIrp;
	}

	/*******************************************************************************/
	// �������ƣ� CreateSimulateTrigger_PulseCheckEventIrp
	// ���ܣ� ������������¼�
	// ������     
	//        short sPosition:       ��λ��������(1),��ɶ���(2),�ҹɶ���(3),�ұ��Ŷ���(4),�ұ��㶯��(5),����Ŷ���(6),����㶯��(7),�����N����(8),���㱳����(9),�����N����(10),���㱳����(11)��
	//        short sAct:                ������0x11�����ƿ���0x10��
	// ����ֵ:  
	CEventIrp_SimulateTrigger * CEventIrp_SimulateTrigger::CreateSimulateTrigger_PulseCheckEventIrp(short sAct, short sPosition/*=1*/)
	{
        BOOST_ASSERT( sPosition != 0 );
		CEventIrp_SimulateTrigger *pSimulatorEventIrp = new CEventIrp_SimulateTrigger();
		//�¼���ʶ����
		pSimulatorEventIrp->m_strTriggerEventName = CSEvent_Pulse::getEvent_Pulse_Caption();

		pSimulatorEventIrp->m_strTriggerXML = CSEvent_Pulse::saveParams( 1, sAct );
		pSimulatorEventIrp->set_eEventSign( ES_PulseCheck );

		pSimulatorEventIrp->m_sExtendData[0] = sPosition;
		pSimulatorEventIrp->m_sExtendData[1] = sAct;
		return pSimulatorEventIrp;
	}

	/*******************************************************************************/
	// �������ƣ� CreateSimulateTrigger_IntubateEventIrp
	// ���ܣ� ��������¼�
	// ������      
	// ����ֵ:  
	CEventIrp_SimulateTrigger * CEventIrp_SimulateTrigger::CreateSimulateTrigger_IntubateEventIrp(short sPosition, short sAct)
	{
		CEventIrp_SimulateTrigger *pSimulatorEventIrp = new CEventIrp_SimulateTrigger();
		//�¼���ʶ����
		pSimulatorEventIrp->m_strTriggerEventName = CSEvent_Intubate::getEvent_Intubate_Caption();

		pSimulatorEventIrp->m_strTriggerXML = CSEvent_Intubate::saveParams(sPosition, sAct);
		pSimulatorEventIrp->set_eEventSign( ES_Intubation );

		pSimulatorEventIrp->m_sExtendData[0]  = sPosition;
		pSimulatorEventIrp->m_sExtendData[1]  = sAct;
		return pSimulatorEventIrp;
	}

	/*******************************************************************************/
	// �������ƣ� CreateSimulateTrigger_PaceEventIrp
	// ���ܣ� �������¼�
	// ������   
	//         sPaceSign:    �𲫶�Ӧ�¼�
	// ����ֵ: 
	//ע��    ���¼���ʶֵ�����𲫿�ʼ(0x11)���𲫲�׽��ʼ(0x12)���𲫶����޸�����(0x13)���𲫶�����(0x02)���𲫽���(0x01)��
	CEventIrp_SimulateTrigger * CEventIrp_SimulateTrigger::CreateSimulateTrigger_PaceEventIrp(short sPaceSign, short sHeartRate /*= 0*/)
	{
		CEventIrp_SimulateTrigger *pSimulatorEventIrp = new CEventIrp_SimulateTrigger();
		//�¼���ʶ����
		pSimulatorEventIrp->m_strTriggerEventName = CSEvent_Pace::getEvent_Pace_Caption();

		pSimulatorEventIrp->m_strTriggerXML = CSEvent_Pace::saveParams( sPaceSign, sHeartRate );
		pSimulatorEventIrp->set_eEventSign( ES_PaceEvent );

		pSimulatorEventIrp->m_sExtendData[0]  = sPaceSign;
		pSimulatorEventIrp->m_sExtendData[1]  = sHeartRate;
		return pSimulatorEventIrp;
	}

	//������ͷ���ٶ��¼�
	bool CEventIrp_SimulateTrigger::explainSimulateTrigger_LookUpEventIrp(bool &bLookUp)
	{
		if( m_eEventSign == ES_LookUp || m_eEventSign == ES_RaiseJowl )
		{
			bLookUp = m_sExtendData[0] ? true : false;
		}
		return true;
	}

	//���������¼�
	bool  CEventIrp_SimulateTrigger::explainSimulateTrigger_DefibrEventIrp( /*out*/short &sDefibrCount, /*out*/short &sDefibrEnergy, /*out*/bool &bSyncDefibr )
	{
		if( m_eEventSign == ES_Defib )
		{
			sDefibrCount    = 1;
			bSyncDefibr     = m_sExtendData[0] ? true : false;
			sDefibrEnergy   = m_sExtendData[1];
			if( m_sExtendData[0] == 0 && sDefibrEnergy == 0 )
			{
				CSEvent_Defibr::explainSimulateTriggerDefibrEvent( m_strTriggerXML, /*out*/&sDefibrCount, /*out*/&sDefibrEnergy, /*out*/&bSyncDefibr);
			}
			return true;
		}
		return false;
	}

	//��������¼�
	bool  CEventIrp_SimulateTrigger::explainSimulateTrigger_IntubateEventIrp( /*out*/short &sPosition, /*out*/short &sAct)
	{
		if( m_eEventSign == ES_Intubation )
		{
			sPosition   = m_sExtendData[0];
			sAct        = m_sExtendData[1];
			if( !(sPosition == 0 && sAct == 0 ) || CSEvent_Intubate::explainSimulateTriggerIntubateEvent(m_strTriggerXML, /*out*/&sPosition, /*out*/&sAct) )
			{
				return true;
			}
		}
		return false;
	}

	//�������¼�
	bool  CEventIrp_SimulateTrigger::explainSimulateTrigger_PaceEventIrp( /*out*/short &sPaceSign, /*out*/short &sHeartRate )
	{
		if( m_eEventSign == ES_PaceEvent )
		{
			sPaceSign   = m_sExtendData[0];
			sHeartRate  = m_sExtendData[1];
			if( !(sPaceSign == 0 && sHeartRate == 0 ) || CSEvent_Pace::explainSimulateTriggerPaceEvent(m_strTriggerXML, /*out*/&sPaceSign, /*out*/&sHeartRate) )
			{
				return true;
			}
		}
		return false;
	}

	//�����������ָ��
	bool  CEventIrp_SimulateTrigger::explainSimulateTrigger_PulseCheckIrp(/*out*/short &sPulsePort, /*out*/short &sAct)
	{
		if( m_eEventSign == ES_PulseCheck )
		{
			sPulsePort   = m_sExtendData[0];
			sAct         = m_sExtendData[1];
			if( sPulsePort != 0 || CSEvent_Pulse::explainSimulateTriggerPulseEvent(m_strTriggerXML, /*out*/&sPulsePort, /*out*/&sAct) )
			{
				return true;
			}
		}
		return false;
	}

	/*******************************************************************************/
	// �������ƣ� UpdateEventSignShow
	// ���ܣ�  ��ʾ�¼�����
	// ������ 
	// ����ֵ: 
	void CEventIrp_SimulateTrigger::UpdateEventSignShow(CShowEventSignUpdateInterface  *pInterface )
	{
		if( pInterface != NULL )
		{
			switch( m_eEventSign )
			{
			case ES_LookUp:
				{
                    if( GetEventSign( m_strTriggerXML ) == "head LookUp" )
					{
						pInterface->OnAddNewEventSign( ES_LookUp );
					}
					else
					{
						pInterface->OnRemoveEventSign( ES_LookUp );
					}
					break;
				}
			case ES_RaiseJowl:
				{
                    if( GetEventSign( m_strTriggerXML ) == "Jowl LookUp" )
					{
						pInterface->OnAddNewEventSign( ES_RaiseJowl );
					}
					else
					{
						pInterface->OnRemoveEventSign( ES_RaiseJowl );
					}
					break;
				}
			case ES_Defib:
				{
					pInterface->OnSimulateDefibrTriggerEventUpdateShow();
					break;
				}
			case ES_PulseCheck:
				{
					short  sAct, sPosition;
					if( explainSimulateTrigger_PulseCheckIrp(/*out*/sPosition, /*out*/sAct) )
					{
						if( sAct == 0x01 )
						{
							pInterface->OnSimulatePulseCheckTriggerEventUpdateShow( sPosition );
						}
						else
						{
							pInterface->OnRemoveEventSign( ES_PulseCheck );
						}
					}
					break;
				}
			case ES_Intubation:
				{
					short   sAct, sPosition;
					if( explainSimulateTrigger_IntubateEventIrp(/*out*/sPosition, /*out*/sAct) )
					{
						if( sAct == 0x11 )
						{
							pInterface->OnSimulateIntubateTriggerEventUpdateShow( sPosition );
						}
						else if( sAct == 0x10 )
						{
							pInterface->OnRemoveEventSign( ES_Intubation );
						}
					}
					break;
				}
			case ES_Dunt:
				{
					//�ػ�
					pInterface->OnAddNewEventSign( ES_Dunt );
					break;
				}
			case ES_PaceEvent:
				{
					//����־��Ϣ��¼
					short  sPaceSign, sHeartRate = 0;
					explainSimulateTrigger_PaceEventIrp(/*out*/sPaceSign, /*out*/sHeartRate);
					//���¼���ʶֵ�����𲫿�ʼ(0x11)���𲫲�׽��ʼ(0x12)���𲫶����޸�����(0x13)���𲫶�����(0x02)���𲫽���(0x01)��
					if( sPaceSign == 0x12 )
					{
						pInterface->OnSimulatePaceTriggerEventUpdateShow( sHeartRate );
					}
					else if( sPaceSign == 0x02 || sPaceSign == 0x01)
					{
						pInterface->OnRemoveEventSign( ES_PaceEvent );
					}
					break;
				}
			}
		}
	}

	std::string  CEventIrp_SimulateTrigger::GetEventSign(const std::string &strTriggerXML)
	{
        /*utility::CMessMemory   cMess;
		cMess.ParseContext( (char *)strTriggerXML.c_str(), strTriggerXML.length(), NULL );
        return std::string((char *)cMess.m_pPtr, cMess.GetLeafMSize() );*/
        return "";
	}

	/*******************************************************************************/
	// �������ƣ� doPackageIrp
	// ���ܣ�  ���Irp������
	// ������ 
	// ����ֵ: 
	std::string  CEventIrp_SimulateTrigger::doPackageIrp()
	{
		boost::format fmt("<SimulateTriggerIrp><EventSign>%d</EventSign><TriggerName>%s</TriggerName><ExpressXML>%s</ExpressXML><AddLog>%s</AddLog></SimulateTriggerIrp>");
        fmt % (int)m_eEventSign % m_strTriggerEventName % CEventIrp_SimulateTrigger::encodeTriggerXMLExpress(m_strTriggerXML) % (m_bAddLog ? "true" : "false");
		return    fmt.str();
	}

	/*******************************************************************************/
	// �������ƣ� UnzipPackage
	// ���ܣ� ��ѹ�������Irp������
	// ������ 
	//        char *lpData��
	//        UINT uNumber��
	// ����ֵ:  
    CEventIrp_SimulateTrigger * CEventIrp_SimulateTrigger::UnzipPackage(char *lpData, unsigned short uNumber)
	{
		CEventIrp_SimulateTrigger  *pSimulateTriggerIrp = NULL;
		/*CMessMemory   cMessMemory;
		if( cMessMemory.ParseContext(lpData, (DWORD)uNumber, NULL) != -1 )
		{
			if( cMessMemory.m_eStyle == CMessMemory::aComposite )
			{
				pSimulateTriggerIrp   = new CEventIrp_SimulateTrigger();
				POSITION  pos = cMessMemory.m_LeafList.GetHeadPosition();
				while( pos )
				{
					CMessMemory  *pLeafMess = cMessMemory.m_LeafList.GetNext( pos );
					CString   strTxt((char *)pLeafMess->m_pPtr, pLeafMess->GetLeafMSize());
					if( pLeafMess->m_strCaption == _T("TriggerName") )
					{
						pSimulateTriggerIrp->m_strTriggerEventName = strTxt;
					}
					else if( pLeafMess->m_strCaption == _T("ExpressXML") )
					{
						pSimulateTriggerIrp->m_strTriggerXML = CEventIrp_SimulateTrigger::DecodeTriggerXMLExpress( strTxt );
					}
					else if( pLeafMess->m_strCaption == _T("AddLog") )
					{
						if( strTxt == _T("true") )
							pSimulateTriggerIrp->m_bAddLog = TRUE;
						else
							pSimulateTriggerIrp->m_bAddLog = FALSE;
					}
					else if( pLeafMess->m_strCaption == _T("EventSign") )
					{
						pSimulateTriggerIrp->Set_eEventSign( (eEventSign)::atoi(strTxt.operator LPCTSTR() ) );
					}
				}
			}
		}*/
		return pSimulateTriggerIrp;
	}

	//����ģ���˴����¼��������
	std::string CEventIrp_SimulateTrigger::encodeTriggerXMLExpress(const std::string &strTriggerXML)
	{
		long  dwSize   = strTriggerXML.length();
		char * pTmpBuff = new char[ dwSize + 1 ];
		::memcpy(pTmpBuff, strTriggerXML.c_str(), dwSize);
		for(long dwStep = 0; dwStep < dwSize; dwStep++)
		{
			pTmpBuff[dwStep] ^= 0xD2;
            unsigned char tempByte = (pTmpBuff[dwStep]&0x3)<<6;
			pTmpBuff[dwStep] = (pTmpBuff[dwStep]>>2)&0x3F;
			pTmpBuff[dwStep] |= tempByte;
			pTmpBuff[dwStep] ^= 0xA6;
		}
		pTmpBuff[dwSize] = '\0';
		std::string   strRtnEncodeTxt(pTmpBuff, dwSize);
		delete [] pTmpBuff;
		return strRtnEncodeTxt;
	}

	//����ģ���˴����¼��������
	std::string CEventIrp_SimulateTrigger::decodeTriggerXMLExpress(const std::string &strEncode)
	{
		long  dwSize   = strEncode.length();
		char * pTmpBuff = new char[ dwSize + 1 ];
		::memcpy(pTmpBuff, strEncode.c_str(), dwSize);
		for(long dwStep = 0; dwStep < dwSize; dwStep++)
		{
			pTmpBuff[dwStep] ^= 0xA6;
			char tempByte = ((pTmpBuff[dwStep]&0xC0)>>6)&0x3;
			pTmpBuff[dwStep] <<= 2;
			pTmpBuff[dwStep] |= tempByte;
			pTmpBuff[dwStep] ^= 0xD2;
		}
		pTmpBuff[dwSize] = '\0';
		std::string   strRtnDecodeTxt(pTmpBuff, dwSize);
		delete [] pTmpBuff;
		return strRtnDecodeTxt;
	}

}}
