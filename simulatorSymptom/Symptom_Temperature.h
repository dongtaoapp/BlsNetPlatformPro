#pragma once
#include ".\symptomvirtual.h"
#include ".\XActionVirtual.h"

#include "..\SimulatorBase\ShowTempUpdateInterface.h"


namespace jysoft { namespace simulator {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ģ���˵����£����������¶Ⱥ���Χ�¶�
	�����ˣ�	 hjg
	����ʱ�䣺   2008/10/22
	//-----------------------------------------------------------------------------------------------------------------*/
	class CSymptom_Temperature : public CSymptomVirtual
	{
	public:
		CSymptom_Temperature(void);
		virtual ~CSymptom_Temperature(void);
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
		virtual  void InitialSymptomValue( CXActionVirtual *pVirAction, short sTransTime = 0);
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
		// ���ܣ�   �Ͽ���ʾ����
		// ������   
		// ����ֵ:
		virtual  void OnUnLinkWatchBarUpdateInterfaceShow(CWatchBarsShowInterfacesAggregate *pShowAggregate) ;
	public:
		void SetShowTemperatureValueInterface(base::CShowTempUpdateInterface *ptemp);
	public:
		inline float GetValue_PTemperator() { return m_fP_TempValue; };
	protected:
		float       m_fP_TempValue;   //��Χ�¶�
		base::CShowTempUpdateInterface*  m_pShowPTempValueInterface;
	};
}}