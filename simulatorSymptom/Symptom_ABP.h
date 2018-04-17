#pragma once
#include ".\symptomvirtual.h"
#include ".\XActionVirtual.h"

#include "..\common\EmulateTimer.h"

#include "..\SimulatorBase\OpABPBuildInterface.h"
#include "..\SimulatorBase\ShowNIBPUpdateInterface.h"
#include "..\SimulatorBase\SimulatorOrderIrp.h"
#include "..\SimulatorBase\SymptomsShowInterfacesAggregate.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ģ���˵��д�Ѫѹ�� �޴�ѪѹΪ1�����ڵ��д�Ѫѹֵ
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/22
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORSYMPTOMSHARED_EXPORT CSymptom_ABP : public CSymptomVirtual
	{
	public:
		CSymptom_ABP(void);
		virtual ~CSymptom_ABP(void);
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
		// ����ֵ: 
		virtual  void InitialSymptomValue( IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType);
		/*******************************************************************************/
		// �������ƣ� InitialSymptomValue
		// ���ܣ�   ��ʼ������ֵ
		// ������   
		//          CXActionVirtual *pVirAction:         ��Ӧ����ֵ
		//          short sTransTime:                    ת��ʱ�䣨��λ���룩
		// ����ֵ: 
		virtual  void InitialSymptomValue(CXActionVirtual *pVirAction, short sTransTime = 0);
		// �������ƣ� OnUpdateInterfaceShow
		// ���ܣ�   ���½�����ʾ
		// ������   
		// ����ֵ: 
		virtual  void OnUpdateInterfaceShow();
		/*******************************************************************************/
		// �������ƣ� OnLinkWatchBarUpdateInterfaceShow
		// ���ܣ�   ����ģ������ʾ����
		// ������   
		// ����ֵ:
		virtual  void OnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// �������ƣ� OnUnLinkWatchBarUpdateInterfaceShow
		// ���ܣ�   �Ͽ�ģ������ʾ����
		// ������   
		// ����ֵ:
		virtual  void OnUnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// �������ƣ� OnLinkSimulatorBarUpdateInterfaceShow
		// ���ܣ�   ����ģ���������ʾ����
		// ������   
		// ����ֵ:
		virtual  void OnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate );
		/*******************************************************************************/
		// �������ƣ� OnUnLinkSimulatorBarUpdateInterfaceShow
		// ���ܣ�   �Ͽ�ģ���������ʾ����
		// ������   
		// ����ֵ:
		virtual  void OnUnLinkSimulatorBarUpdateInterfaceShow(CSymptomsShowInterfacesAggregate *pShowAggregate );
		/*******************************************************************************/
		// �������ƣ� ResetFlag
		// ���ܣ�   �����޸ĵı�ʶ
		// ������   
		// ����ֵ:
		virtual  void ResetFlag() { m_bModifyNIBPValue = false; };
	public:
		//��ʼ��Ѫѹģ�����߹�����
		void InitialABPBuild(SimulatePatientType ePatientType);
		//�޸�Ѫѹģ�����߹�����
		void ModifyABPBuild();
		//����ABP����ֵ����ȡNIBP(1����)
		void   Set_NIBPCurrentValue();
	public:
		//�����д�Ѫѹģ�⹹���������ӿ�
		inline void SetABPBuildInterface(base::COpABPBuildInterface *pInterface) { m_pABPBuildInterface = pInterface; };
		inline int  GetValue_SBP() { return m_nShrinkValue_ABP; };
		inline int  GetValue_DBP() { return m_nStretchValue_ABP; };
	public:
		void SetShowNIBPInterface(base::CShowNIBPUpdateInterface *pShowInterface);
		//���ô���NIBPָ��
		void SetEnableTranslateNIBPOrder();
	protected:
		int                       m_nShrinkValue_ABP;        //�д�����ѹ
		int                       m_nStretchValue_ABP;       //�д�����ѹ
		//----------------------------------------------------------------------------------------------------------
		int                       m_nShrinkValue_NIBP;       //�޴�����ѹ
		int                       m_nStretchValue_NIBP;      //�޴�����ѹ
	protected:
		base::COpABPBuildInterface     *m_pABPBuildInterface;      //�д�Ѫѹģ�⹹���������ӿ�
		base::CShowNIBPUpdateInterface *m_pShowNIBPInterface;      //�޴�Ѫѹ��ʾ�ӿ�
	private:
		utility::CEmulateTimer    m_cNIBPTimer;
		bool                      m_bModifyNIBPValue;        //�Ƿ��޸���NIBP��ֵ
	};
}}
