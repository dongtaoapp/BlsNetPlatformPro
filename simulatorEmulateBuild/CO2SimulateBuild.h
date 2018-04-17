#pragma once
#include ".\simulatoremulatebuild_global.h"
#include ".\CO2CycleData.h"
#include ".\CO2SimulateStateGlobal.h"

#include "..\SimulatorBase\IGetPhysioloySimulateData.h"
#include "..\SimulatorBase\ICO2SimulateSign.h"
#include "..\SimulatorBase\OpEtCO2BuildInterface.h"


namespace jysoft { namespace simulator { namespace etCO2 {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     CO2ģ��ʵʱ����������
	�����ˣ�	 hjg
	����ʱ�䣺   2008/7/30
	//-----------------------------------------------------------------------------------------------------------------*/

	class CCO2SimulateIntubateState;
    class SIMULATOREMULATEBUILDSHARED_EXPORT CCO2SimulateBuild  : public IGetPhysioloySimulateData
											 ,public ICO2SimulateSign
											 ,public base::COpEtCO2BuildInterface
	{
	public:
		CCO2SimulateBuild(void);
		virtual ~CCO2SimulateBuild(void);
	protected:
		CCO2CycleData                 m_cCO2CycleData;
		//------------------------------------------------------------------------------------
		CCO2SimulateAutoRespState     m_cAutoRespState;
		CCO2SimulateNoRespState       m_cNoRespState;
		CCO2SimulateIntubateState *   m_pIntubateState;
	protected:
		std::string       m_strCO2ResourePath;
	private:
		ICO2SimulateState  *          m_pCurrCO2SimulateState;   //��ǰ��״̬
		ICO2SimulateState  *          m_pNextCO2SimulateState;   //��״ָ̬�����ڴ������״̬
	public: //���ຯ������
		/*******************************************************************************/
		//���ܣ���ȡ���������ڵ���������
		//������int iMilliTime:          ʱ�䣨0.1���룩
		//      float *pcBuffer:         ���ص���������
		//����ֵ:  �������ݵĳ���
		virtual unsigned long GetPhysioloySimulateData(int iMilliTime, /*out*/float *pcBuffer = NULL);
		/*******************************************************************************/
		// �������ƣ� OnCO2SimulateSignOp
		// ���ܣ� ����ʱ��������CO2��ģ���źŴ���
		// ������  BOOL bInspiration: ����(TRUE); ����(FALSE)
		//         int nMilliChangeTime: CO2������������ʱ�䣨0.1���룩
		//         int nMilliOtherTime:  �������������������ʱ�䣨0.1���룩
		// ����ֵ:  
		virtual void OnCO2SimulateSignOp(bool bInspiration, int nMilliChangeTime, int nMilliOtherTime);
		/*******************************************************************************/
		// �������ƣ� OnStartAutoRespOp
		// ���ܣ� ����/��ͣ��������
		// ������ 
		//         BOOL bAutoResp:
		// ����ֵ:  
		virtual void OnStartAutoRespOp( bool bAutoResp );
		/*******************************************************************************/
		// �������ƣ� Get_IGetPhysioloySimulateDataPtr
		// ���ܣ� ����IGetPhysioloySimulateData�ӿ�ָ��
		// ������ 
		// ����ֵ: 
		virtual IGetPhysioloySimulateData * Get_IGetPhysioloySimulateDataPtr() { return dynamic_cast<IGetPhysioloySimulateData *>(this); };
	protected:
		//�޸�CO2%
		virtual void ModifyCO2PercentValue( int nCO2Per );
		/*******************************************************************************/
		// �������ƣ� OnIntubateOp
		// ���ܣ� ��/����¼�
		// ������ 
		//         BOOL bIntubate:
		// ����ֵ:  
		virtual void IntubateEventOp( bool bIntubate );
		/*******************************************************************************/
		// �������ƣ� OnOnceBreathEventOp
		// ���ܣ� һ�δ����¼�
		// ������ 
		// ����ֵ:  
		virtual void OnceBreathEventOp();
		/*******************************************************************************/
		// �������ƣ� OnCPREventOp
		// ���ܣ� �׶���CPR�¼�
		// ������ 
		// ����ֵ:  
		virtual void CPREventOp( bool bStop );
	public:
		/*********************************************************************************/
		//���ܣ���ʼ��ģ��CO2������
		//������
		//      int nCO2Per:             CO2%
		//����ֵ:  
		void InitializeBuild(int nCO2Per);
		/*********************************************************************************/
		//���ܣ��޸Ĳ��״̬��EtCO2ֵ
		//������
		//      int nEtCO2Value:             CO2%
		//����ֵ:  
		void ModifyEtCO2ValueIntubationState(int nEtCO2Value);
		void setResouceFilePath(const std::string &resPath) { m_strCO2ResourePath = resPath + "\\CO2SimulateData";};
		//����EtCO2����״̬�������Ƿ���ʾEtCO2����
		bool IsShowEtCO2LinkState();
		//�����Ƿ����EtCO2���Ӽ��
		void Set_IsClearEtCO2WatchLink(bool bClear);
		//����EtCO2���Ӽ��״̬
		void Set_EtCO2WatchLinkState(bool bLinking);
	private:
		bool                     m_bClearWatchLink;  //�Ƿ����EtCO2���Ӽ��
		bool                     m_bLinkWatchEtCO2;

		int                      m_nReflushCalculate;   //��ֵˢ�¼�����
	};
}}}
