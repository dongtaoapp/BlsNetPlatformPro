#pragma once
#include "symptomvirtual.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �ɲ�����ز�����������������
	�����ˣ�	 hjg
	����ʱ�䣺   2009/3/31
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORSYMPTOMSHARED_EXPORT CSymptomUnmonitorVirtual : public CSymptomVirtual
	{
	public:
		CSymptomUnmonitorVirtual(void);
		virtual ~CSymptomUnmonitorVirtual(void);
	public:
		//���ݱ�ʾ�����ж���������
		virtual  bool isSymptomCaption(const std::string &strCaption) = 0;
		//�޸Ķ�Ӧ�����Ĳ���
		virtual  void ModifyUnmonitorSymptomValue(IModifiedSymptomsOp *pInterfacePtr, CXActionVirtual *pVirAction) = 0;
	public: 
		/*******************************************************************************/
		// �������ƣ� IsKindOf
		// ���ܣ�   �ж����������
		// ������   const CString &strClassName
		// ����ֵ: 
		virtual  bool isKindOf( const std::string &strClassName );
		/*******************************************************************************/
		// �������ƣ� InitialSymptomValue
		// ���ܣ�   ��ʼ������ֵ
		// ������   IModifiedSymptomsOp *pInterfacePtr
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
		virtual  void InitialSymptomValue( CXActionVirtual *pVirAction, short sTransTime = 0) ;
		// �������ƣ� OnUpdateInterfaceShow
		// ���ܣ�   ���½�����ʾ
		// ������   
		// ����ֵ: 
		virtual  void OnUpdateInterfaceShow() = 0; 
		/*******************************************************************************/
		// �������ƣ� OnLinkWatchBarUpdateInterfaceShow
		// ���ܣ�   ����ģ������ʾ����
		// ������   
		// ����ֵ:
		virtual  void OnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate) = 0;
		// �������ƣ� OnUnLinkWatchBarUpdateInterfaceShow
		// ���ܣ�   �Ͽ���ʾ����
		// ������   
		// ����ֵ:
		virtual  void OnUnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate) = 0;
	};
}}
