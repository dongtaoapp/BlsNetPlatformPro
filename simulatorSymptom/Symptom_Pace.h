#pragma once
#include "symptomvirtual.h"

#include "..\SimulatorBase\ShowPaceUpdateInterface.h"

namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ������
	�����ˣ�	 hjg
	����ʱ�䣺   2009/4/1
	//-----------------------------------------------------------------------------------------------------------------*/
	class CSymptom_Pace : public CSymptomVirtual
	{
	public:
		CSymptom_Pace(void);
		virtual ~CSymptom_Pace(void);
	public: 
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
		// ������   
		//          IModifiedSymptomsOp *pInterfacePtr
		//          tag_TrendValue *pDefaultTrendValue:  ��Ӧ�����޸ĵ�ֵ����
		// ����ֵ: 
		virtual  void InitialSymptomValue(IModifiedSymptomsOp *pInterfacePtr, SimulatePatientType ePatientType);
		/*******************************************************************************/
		// �������ƣ� InitialSymptomValue
		// ���ܣ�   ��ʼ������ֵ
		// ������   
		//          tag_TrendValue *pDefaultTrendValue:  ��Ӧ�����޸ĵ�ֵ����
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
	protected:
		bool                         m_bEnablePace;  //�Ƿ�����
		short                        m_sData;        //�𲫵�����mA��
	protected:
		base::CShowPaceUpdateInterface    *m_pShowPaceInterface;
	};
}}