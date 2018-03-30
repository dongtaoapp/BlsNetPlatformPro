#pragma once
#include ".\Collates.h"
#include ".\CPRSimulateJudgeOp.h"
#include ".\CPRConfigue.h"
#include ".\CPRStatisticImplement.h"

#include "..\Common\EventHandleClockIrpOp.h"
#include "..\Common\RealTimeDataHandleIrpOp.h"

#include "..\SimulatorBase\OpLogInterface.h"
#include "..\SimulatorBase\CPRShowInterfacesAggregate.h"
#include "..\SimulatorBase\ITransportOrderIrpToSimulator.h"


namespace jysoft{  namespace cpr {
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �ķθ�����Ϣ���ݼ�����
	�����ˣ�	 hjg
	����ʱ�䣺   2017/5/22
	//-----------------------------------------------------------------------------------------------------------------*/
    class CPRMODULSSHARED_EXPORT CCPRMessageCollect : public irp::CRealTimeDataHandleIrpOp
							 , public irp::CEventHandleClockIrpOp
	{
	public:
		CCPRMessageCollect(void);
		virtual ~CCPRMessageCollect(void);
	protected:
		CCPRSimulateJudgeOp*           m_pCPRJudgeOp;         //CPR�����ж���
		CCPRStatisticImplement*        m_pStatisticImpl;      //����ͳ�Ƽ�����
		CCPRConfigue*                  m_pCPRConfigue;        //CPR�������ý�����
		log::COpLogInterface*          m_pEventLogInterface;  //��־�¼��ӿ�
	public:
		CPressureCollate                          m_cPressureCollate;    //��ѹ�߼����ֶ��ձ�
		CBreathCollate                            m_cBreathCollate;      //�����߼����ֶ��ձ�
	private:
		transLayer::ITransportOrderIrpToUp*   m_pTransportUpOrderInterface;
		CCPRRealTimeUpdateInterface*          m_pShowCPRRealTimeInteface;
		CShowCPRActUpdateInterface*           m_pShowCPRDetailActInterface;
	private:
		bool                                      m_bEnableCompleteJudge;  //���CPR��������жϵı�ʶ
		_CPRManageState                           m_eNextPhaseCPRState;    //�½׶�CPR����ģʽ
	protected: //�ӿ�CRealTimeDataHandleIrpOp��������
		/*******************************************************************************/
		//���ܣ���������ת��IRP����
		//������
		//      CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool doHandleRealTimeDataIrpOp(irp::CVirtualIrp *pCurrIrp);
	protected:
		/*******************************************************************************/
		//���ܣ�����ʱ���¼�IRP����
		//������
		//      CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool doHandleClockIrpOp(irp::CVirtualIrp *pCurrIrp);
	public:
		//����CPR�����жϽӿ�ָ��
		inline CCPRSimulateJudgeOp * getCPRSimulateJudgeOp() { return m_pCPRJudgeOp; };
	public:
		/*******************************************************************************/
		// �������ƣ� initialCPR
		// ���ܣ�    ��ʼ��
		// ������  
		// ����ֵ:  
		void initialCPR(CCPRConfigue *pCPRConfigue, transLayer::ITransportOrderIrpToUp *pTransUpInterface, log::COpLogInterface *pEventLogInterface = NULL);
		/*******************************************************************************/
		// �������ƣ� ResetCPROperatorMessage
		// ���ܣ�    ����CPR����ͳ��
		// ������  
		// ����ֵ:  
		void resetCPROperatorMessage(_CPRManageState  eCPRState);
		/*******************************************************************************/
		// �������ƣ� restatisticByDefibrEventHandle
		// ���ܣ�    �����¼���������CPR����ͳ��
		// ������  
		// ����ֵ:  
		void restatisticByDefibrEventHandle();
		/*******************************************************************************/
		// �������ƣ� StartLinkCPRShowInterfaces
		// ���ܣ� ��ʼ����CPR��ʾ�������ʾ�ӿ�
		// ������ CCPRShowInterfacesAggregate *pShowAggregate:        
		// ����ֵ:  
		void startLinkCPRShowInterfaces(CCPRShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// �������ƣ� UnLinkCPRShowInterfaces
		// ���ܣ� �Ͽ�CPR��ʾ�������ʾ�ӿ�
		// ������ CCPRShowInterfacesAggregate *pShowAggregate:        
		// ����ֵ:
		void unLinkCPRShowInterfaces(CCPRShowInterfacesAggregate *pShowAggregate);
		/*******************************************************************************/
		// �������ƣ� DoModifyCPRJudgeRange
		// ���ܣ� �޸��ķθ��ղ���ʱ�������밴ѹ�ķ�Χ
		// ������     
		// ����ֵ:  
		void modifyCPRJudgeRange(int nLowerDepth, int nOverDepth, int nLowerVolume, int nOverVolume);
	public:
		//�����½׶ε�CPR����ģʽ
		void setNextPhaseCPROperatorMode(_CPRManageState  eCPRState);
		//�����ķθ���������
		inline CCPRConfigue * getCPRConfiguePtr() { return m_pCPRConfigue;};
		inline CCPRStatisticImplement * getCPRStatisticImplement() { return m_pStatisticImpl; };
		//�����δ���
		void startTickSound();
		//ֹͣ�δ���
		void stopTickSound();
	private:
		//CPR����ָ���
		_eCPRErrorSign doCPROrderHandle(const _CPRData &cprOrder);
		//CPR������ɴ���
		void doCPRCompleteHandle();
		//CPR������������
		void doCPROperatorFinishHandle(_CPRManageState  eCPRState);
		//���ؽű���ǰʱ��
		UINT getScriptRunTime();
	};

}}
