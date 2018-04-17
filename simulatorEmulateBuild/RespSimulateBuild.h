#pragma once
#include ".\RespCycleDataCollects.h"
#include ".\simulatoremulatebuild_global.h"

#include "..\SimulatorBase\IGetPhysioloySimulateData.h"
#include "..\SimulatorBase\ITransportOrderIrpToSimulator.h"
#include "..\SimulatorBase\OpRespBuildInterface.h"
#include "..\SimulatorBase\ICO2SimulateSign.h"
#include "..\SimulatorBase\ShowRespRateUpdateInterface.h"

#include "..\Common\CommonGlobal.h"



namespace jysoft { namespace simulator { namespace resp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ����ģ��ʵʱ����������
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/22
	//-----------------------------------------------------------------------------------------------------------------*/
	class CRespCycleData;
	class IRespBuildTypeState;
    class SIMULATOREMULATEBUILDSHARED_EXPORT CRespSimulateBuild : public IGetRespSimulateData
											,public base::COpRespBuildInterface
	{
	public:
		CRespSimulateBuild();
		virtual ~CRespSimulateBuild(void);
	private:
		SimulatePatientType             m_ePatientType;
	protected:
		IRespBuildTypeState            *m_pRespBuildState;
		CRespCycleData                 *m_pCurrentRespData[2];
		CRespCycleDataCollects          m_cRespDeletedCollects; //���ݰ������ռ���
	protected:
		int                             m_nRespRate;            //��ǰ�ĺ�������
		int                             m_nRemainTime;          //��λ: 0.1ms
		ICO2SimulateSign               *m_pCO2SimulateSignInterface;
		transLayer::ITransportOrderIrpToSimulator  *m_pTransportOrderToSimulatorInterface; 
		std::string          respResourcePath;
	private:
		bool                            m_bClearWatchLink;  //�Ƿ����RR���Ӽ��
		bool                            m_bLinkWatchResp;
		int                            m_bSynchronizeSignSend;  //ͬ���ź��Ƿ��ѷ���
	public:
		//����RR����״̬�������Ƿ���ʾResp����
		bool IsShowRespLinkState();
		//�����Ƿ����RR���Ӽ��
		void Set_IsClearRespWatchLink(bool bClear);
		//����RR���Ӽ��״̬
		void Set_RespWatchLinkState(bool bLinking);
	public: //IGetPhysioloySimulateData�ӿڻ��ຯ������
		/*******************************************************************************/
		//���ܣ���ȡ���������ڵ���������
		//������int iMilliTime:          ʱ�䣨0.1���룩
		//      float *pcBuffer:         ���ص���������
		//����ֵ:  �������ݵĳ���
		virtual unsigned long GetRespSimulateData(int iMilliTime, /*out*/float *pcLeftBuffer = NULL, /*out*/float *pcRightBuffer = NULL);
	protected://COpRespBuildInterface�ӿڻ��ຯ������
		/*******************************************************************************/
		// �������ƣ� ModifyRespRate
		// ���ܣ� �޸ĺ�������
		// ������  int nBreathRate:            ������������λ����/���ӣ�
		// ����ֵ:  
		virtual void ModifyRespRate(int nBreathRate);
		/*******************************************************************************/
		// �������ƣ� ModifyRespBuildType
		// ���ܣ� �޸����ͼ�����
		// ������  eRespMode eMode:            ��������
		//         int nBreathRate:                       ������������λ����/���ӣ�
		// ����ֵ:  
		virtual void ModifyRespBuildType(eRespMode eMode, int nBreathRate);
	public:
		/*******************************************************************************/
		// �������ƣ� Get_IGetPhysioloySimulateDataPtr
		// ���ܣ� ����IGetRespSimulateData�ӿ�ָ��
		// ������ 
		// ����ֵ: 
		virtual IGetRespSimulateData * Get_IGetPhysioloySimulateDataPtr() { return dynamic_cast<IGetRespSimulateData *>(this); };
	public:
		/*********************************************************************************/
		//���ܣ���ʼ��ģ�����������
		//������eRespMode eMode:             ģʽ����
		//      int nBreathRate:             ��������
		//����ֵ:  
		virtual void InitializeBuild(eRespMode eMode, int nBreathRate);
		/*******************************************************************************/
		// �������ƣ� OnModifyPnPFacility
		// ���ܣ� �ı��Ȳ���豸
		// ������ 
		//         CSyncPnpFacilities *pSyncPnPFacilities:
		// ����ֵ:  
		virtual void OnModifyPnPFacility(pnp::CSyncPnpFacilities *pSyncPnPFacilities);
		/*******************************************************************************/
		// �������ƣ� SetRespBuildRelateInterfacesPtr
		// ���ܣ� ���ú����������ָ��
		// ������ 
		//        ICO2SimulateSign *pInterface:
		//        ITransportOrderIrpToSimulator *pTransportInterface:  
		//        SimulatePatientType ePateintType:    ģ�������
		// ����ֵ: 
		void SetRespBuildRelateInterfacesPtr(ICO2SimulateSign *pInterface, const std::string &resPath, transLayer::ITransportOrderIrpToSimulator *pTransportInterface = NULL, SimulatePatientType eType = SPT_Adult);
		/*********************************************************************************/
		//���ܣ���֯�����ڵĺ�������
		//������
		//����ֵ:  
		void CombineNextCycleSimulateData();
		//�رպ���������
		void CloseRespSimulateBuild();
	protected:
		/*********************************************************************************/
		//���ܣ� �޸�Ӱ���������Ϊ
		//������
		//����ֵ:  
		void ModifyInfluentRespBehaviors();
	};
}}}
