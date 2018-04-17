#pragma once
#include ".\symptomvirtual.h"


namespace jysoft { namespace simulator {

    class SIMULATORSYMPTOMSHARED_EXPORT CSymptom_FrameTime : public CSymptomVirtual
	{
	public:
		CSymptom_FrameTime(void);
		virtual ~CSymptom_FrameTime(void);
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
		// ������   IModifiedSymptomsOp *pInterfacePtr
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
	public:
		inline long  GetValue_FrameTime() { return m_lFrameTime; };
		//���ó�����ʱ��Ϊ0
		void ResetFrameTimeToZero();
		//���ӳ��������ʱ��
		void IncreaseFrameTime(long  lAddTime);
	protected:
		long                            m_lFrameTime;
	};
}}
