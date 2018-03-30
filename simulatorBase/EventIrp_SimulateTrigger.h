#pragma once
#include ".\simulatorbase_global.h"
#include ".\VirEventIrp.h"
#include <boost/logic/tribool.hpp>


using namespace boost;
namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ģ���˴����¼�Irp
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/8
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CEventIrp_SimulateTrigger : public CVirEventIrp
	{
	public:
		CEventIrp_SimulateTrigger(void);
		virtual ~CEventIrp_SimulateTrigger(void);
	public:
		virtual _IrpType Get_eIrpType() { return eSimulateTrigger_Event; };
		virtual bool isKindOf(const std::string &className);
		//�����¼���־
		virtual eEventSign Get_EventSign();
		//����ģ���˴����¼�����
		inline std::string  getName_TriggerEvent() { return m_strTriggerEventName; };
		//�����Ƿ�����ӵ���־��Ϣ
		inline void setEnableAdditionLog(bool bEnable) { m_bAddLog = bEnable; };
		inline void set_eEventSign(eEventSign  eTriggerEventSign) { m_eEventSign = eTriggerEventSign; };
		/*******************************************************************************/
		// �������ƣ� UpdateEventSignShow
		// ���ܣ�  ��ʾ�¼�����
		// ������ 
		// ����ֵ: 
		virtual void UpdateEventSignShow(simulator::base::CShowEventSignUpdateInterface  *pInterface );
		/*******************************************************************************/
		// �������ƣ� doPackageIrp
		// ���ܣ�  ���Irp������
		// ������ 
		// ����ֵ: 
		virtual std::string doPackageIrp();
	public:
		//������ͷ���ٶ��¼�
		bool explainSimulateTrigger_LookUpEventIrp(bool &bLookUp);
		//���������¼�
		bool  explainSimulateTrigger_DefibrEventIrp( /*out*/short &sDefibrCount, /*out*/short &sDefibrEnergy, /*out*/bool &bSyncDefibr );
		//��������¼�
		bool  explainSimulateTrigger_IntubateEventIrp( /*out*/short &sPosition, /*out*/short &sAct);
		//�������¼�
		bool  explainSimulateTrigger_PaceEventIrp( /*out*/short &sPaceSign, /*out*/short &sHeartRate );
		//�����������ָ��
		bool  explainSimulateTrigger_PulseCheckIrp(/*out*/short &sPulsePort, /*out*/short &sAct);
	private:
		eEventSign              m_eEventSign;
		//---------------------------------------------------------------------------------------------------------------------------
		short                   m_sExtendData[2];
	public:
		/*******************************************************************************/
		// �������ƣ� CreateSimulateTrigger_LookUpEventIrp
		// ���ܣ� ������ͷ\ƽ�ɴ����¼�Irp
		// ������      
		// ����ֵ:  
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_LookUpEventIrp(bool bHeadLookUp);
		/*******************************************************************************/
		// �������ƣ� CreateSimulateTrigger_RaiseJowlEventIrp
		// ���ܣ� �����ٶ�\�ٶ��ƽ�¼�
		// ������      
		// ����ֵ:  
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_RaiseJowlEventIrp(bool bRaiseJowl);
		/*******************************************************************************/
		// �������ƣ� CreateSimulateTrigger_PipeCloseEventIrp
		// ���ܣ� ��������ʱ����δ�����¼�Irp
		// ������      
		// ����ֵ:  
		static CEventIrp_SimulateTrigger *CreateSimulateTrigger_PipeCloseEventIrp(bool bPipeClose);
		/*******************************************************************************/
		// �������ƣ� CreateSimulateTrigger_ClearObstructEventIrp
		// ���ܣ� ������������¼�
		// ������      
		// ����ֵ:  
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_ClearObstructEventIrp();
		/*******************************************************************************/
		// �������ƣ� CreateSimulateTrigger_ConsciousEventIrp
		// ���ܣ� ������ʶ�б��¼�
		// ������      
		// ����ֵ:  
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_ConsciousEventIrp();
		/*******************************************************************************/
		// �������ƣ� CreateSimulateTrigger_DefibrEventIrp
		// ���ܣ� ���������¼�
		// ������    
		//           bool bSyncDefibr:      �Ƿ�ͬ������
		//           short sEnergy:         ����������0:��ʾδָ��
		// ����ֵ:  
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_DefibrEventIrp(bool bSyncDefibr, short sEnergy = 0);
		/*******************************************************************************/
		// �������ƣ� CreateSimulateTrigger_AEDEventIrp
		// ���ܣ� ����AED�¼�
		// ������    
		//          bStartupAED:     ture:��ʼ  false: ����  unknow: ����
		// ����ֵ:  
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_AEDEventIrp(boost::tribool bStartupAED = indeterminate);
		/*******************************************************************************/
		// �������ƣ� CreateSimulateTrigger_PulseCheckEventIrp
		// ���ܣ� ������������¼�
		// ������     
		//        short sPosition:      ��λ��������(1),��ɶ���(2),�ҹɶ���(3),�ұ��Ŷ���(4),�ұ��㶯��(5),����Ŷ���(6),����㶯��(7),�����N����(8),���㱳����(9),�����N����(10),���㱳����(11)��
		//        short sAct:           ������0x11�����ƿ���0x10��
		// ����ֵ:  
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_PulseCheckEventIrp(short sAct, short sPosition=1);
		/*******************************************************************************/
		// �������ƣ� CreateSimulateTrigger_IntubateEventIrp
		// ���ܣ� ��������¼�
		// ������      
		//         short sPosition:   ����0x02��֧����0x01��ʳ��0x00
		//         short sAct:        ����0x11���γ�0x10
		// ����ֵ:  
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_IntubateEventIrp(short sPosition, short sAct);
		/*******************************************************************************/
		// �������ƣ� CreateSimulateTrigger_PaceEventIrp
		// ���ܣ� �������¼�
		// ������   
		//         sPaceSign:    �𲫶�Ӧ�¼�
		// ����ֵ: 
		//ע��    ���¼���ʶֵ�����𲫿�ʼ(0x11)���𲫲�׽��ʼ(0x12)���𲫶����޸�����(0x13)���𲫶�����(0x02)���𲫽���(0x01)��
		static CEventIrp_SimulateTrigger * CreateSimulateTrigger_PaceEventIrp(short sPaceSign, short sHeartRate = 0);
		/*******************************************************************************/
		// �������ƣ� UnzipPackage
		// ���ܣ� ��ѹ�������Irp������
		// ������ 
		//        char *lpData��
		//        UINT uNumber��
		// ����ֵ:  
        static CEventIrp_SimulateTrigger * UnzipPackage(char *lpData, unsigned short uNumber);
		//����ģ���˴����¼��������
		static std::string encodeTriggerXMLExpress(const std::string &strTriggerXML);
		//����ģ���˴����¼��������
		static std::string decodeTriggerXMLExpress(const std::string &strEncode);
	private:
		std::string  GetEventSign(const std::string &strTriggerXML);
	public:
		std::string       m_strTriggerEventName;    //ģ���˴����¼�����
		std::string       m_strTriggerXML;          //ģ���˴����¼��������
		bool              m_bAddLog;
	};

}}
