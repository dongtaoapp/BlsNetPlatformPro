#pragma once
#include <list>
#include ".\SymptomVirtual.h"
#include ".\XActionVirtual.h"

#include "..\Common\CommonGlobal.h"

#include "..\SimulatorBase\OpRespBuildInterface.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ģ���˵ĵ�ǰ����
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/17
	//-----------------------------------------------------------------------------------------------------------------*/
	class  CSymptom_Resp : public CSymptomVirtual
	{
	public:
		CSymptom_Resp(void);
		virtual ~CSymptom_Resp(void);
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
		/*******************************************************************************/
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
		//��ʼ������ģ�����߹�����
		void InitialRespBuild(SimulatePatientType ePatientType);
		//�޸ĺ���ģ�����߹�����
		void ModifyRespBuild();
	public:
		inline eRespMode GetRespMode() { return m_eRespMode; };
		inline int GetValue_RespRate() { return m_nRespRate; };
		//���ú���ģ�⹹���������ӿ�
		inline void SetRespBuildInterface(base::COpRespBuildInterface *pInterface) { m_pRespBuildInterface = pInterface; };
		inline base::COpRespBuildInterface * GetRespBuildInterface() { return m_pRespBuildInterface; };
	protected:
		base::COpRespBuildInterface           *m_pRespBuildInterface;   //����ģ�⹹���������ӿ�
		//����ģʽ��ʾ�ӿ�
		base::CShowRespRateUpdateInterface    *m_pShowRespInterface;
	protected:
		eRespMode                        m_eRespMode;             //����ģʽ
		int                              m_nRespRate;             //��������
	};
}}