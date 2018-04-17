#pragma once
#include <list>
#include <string>
#include ".\SymptomVirtual.h"
#include ".\XActionVirtual.h"

#include "..\Common\CommonGlobal.h"

#include "..\SimulatorBase\OpECGBuildInterface.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ģ���˵ĵ�ǰ����
	�����ˣ�	 hjg
	����ʱ�䣺   2008/10/17
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORSYMPTOMSHARED_EXPORT CSymptom_Ecg :  public CSymptomVirtual
	{
	public:
		CSymptom_Ecg(void);
		virtual ~CSymptom_Ecg(void);
	public: //���ຯ������
		/*******************************************************************************/
		// �������ƣ� IsKindOf
		// ���ܣ�   �ж����������
		// ������   const CString &strClassName
		// ����ֵ: 
		virtual  bool isKindOf( const std::string &strClassName );
		//���ݱ�ʾ�����ж���������
		virtual  bool isSymptomCaption(const std::string &strCaption);
		/*******************************************************************************/
		// �������ƣ� InitialSymptomValue
		// ���ܣ�   ��ʼ������ֵ
		// ������   IModifiedSymptomsOp *pInterfacePtr
		//          tag_TrendValue *pDefaultTrendValue:  ��Ӧ�����޸ĵ�ֵ����
		// ����ֵ: 
		virtual  void InitialSymptomValue( IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType);
		/*******************************************************************************/
		// �������ƣ� InitialSymptomValue
		// ���ܣ�   ��ʼ���ĵ�ͼ
		// ������   /*out*/tag_TrendValue *pTrendValue: 
		//          CXActionVirtual *pEcgAction:
		//          short sTransTime:                    ת��ʱ�䣨��λ���룩
		// ����ֵ: 
		void InitialSymptomValue( CXActionVirtual *pVirAction, short sTransTime = 0);
		/*******************************************************************************/
		// �������ƣ� isTransmitAEDState
		// ���ܣ�   �Ƿ�AED״̬�ı�
		// ������   
		//          /*in,out*/unsigned char *sAEDState:        AED״̬
		// ����ֵ: 
		virtual  bool isTransmitAEDState(/*in,out*/unsigned char *sAEDState);
		// �������ƣ� OnUpdateInterfaceShow
		// ���ܣ�   ���½�����ʾ
		// ������   
		// ����ֵ: 
		virtual  void OnUpdateInterfaceShow();
		/*******************************************************************************/
		// �������ƣ� OnLinkSimulatorBarUpdateInterfaceShow
		// ���ܣ�   �Ͽ�ģ���������ʾ����
		// ������   
		// ����ֵ:
		virtual  void OnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate );
		/*******************************************************************************/
		// �������ƣ� OnUnLinkSimulatorBarUpdateInterfaceShow
		// ���ܣ�   �Ͽ�ģ���������ʾ����
		// ������   
		// ����ֵ:
		virtual  void OnUnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate );
	public:
		//��ʼ���ĵ�ͼģ�����߹�����
		void InitialEcgBuild(SimulatePatientType ePatientType);
		//�޸��ĵ�ͼģ�����߹�����
		void ModifyEcgBuild(eEventSign eEventValue);
		//ֱ���޸��ĵ�ͼģ�����߹�����
		void DirectEcgBuild();
		//�����ĵ�ͼģ���������ӿ�
		inline void SetECGBuildInterface(base::COpECGBuildInterface *pInterface) { m_pECGBuildInterface = pInterface; };
		inline base::COpECGBuildInterface * GetECGBuildInterface() { return m_pECGBuildInterface; };
		//��������
		inline int  GetValue_HR() { return m_iHR; };
	public:
		//��ʼ�𲫶��
		void StartPaceCapture();
		//�޸��𲫶��������
		void ModifyPaceCaptureHR(int nCaptureHR);
		//�����𲫶��
		void StopPaceCapture();
	public:
		std::string getBasicRmShowText();
	protected:
		QRS                    m_eQRS;           //�������   PM_QRS = 0x00000004
		BasicRhythm            m_eBasicRm;       //��������   PM_BASICRHYTHM = 0x00000008
		Extrasys               m_eExtrasys;      //�����������粫�� PM_EXTRASYS = 0x00000010
		int                    m_iHR;            //��������   PM_HR = 0x00000020
		BOOL                   m_bEMD;           //           PM_EMD   = 0x00000100
		short                  m_sConduct;       //����       PM_CONDUCT = 0x00000200
		short                  m_sExtendParam;   //��չ����   PM_EXTEND  = 0x00000800
		Artifact               m_eArtifact;      //           PM_ARTIFACT = 0x00000001
		int                    m_iExtrasysRate;  //�粫�ı��� PM_EXTRASYSRATE = 0x00000002
		int                    m_nPaceCaptureHR; //�𲫶�������ֵ
	private:
        unsigned long                  m_dwFields;  //����λָ����Щ�������޸ģ���Ҫ���¶�Ӧ�Ľ���
		SimulatePatientType    m_ePatientType;
		base::COpECGBuildInterface  *m_pECGBuildInterface; //�ĵ�ͼģ���������ӿ�
		//-------------------------------------------------------------------------------------------
		base::CShowECGUpdateInterface *m_pEcgShowInterface;//�ĵ�ͼ��ʾ�ӿ���
	};
}}
