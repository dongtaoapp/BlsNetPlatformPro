#pragma once
#include <boost/thread.hpp>
#include ".\simulatoremulatebuild_global.h"
#include ".\EcgLeadSamples.h"
#include ".\EcgCycleLeadsBuild.h"
#include ".\ExtrasystSignBuildInterface.h"
#include ".\SpO2SignBuildInterface.h"

#include "..\Common\VirBuffer.h"
#include "..\Common\LoopBuffer.h"
#include "..\Common\ECGParams.h"

#include "..\SimulatorBase\IPhysiologyStartSign.h"
#include "..\SimulatorBase\IGetPhysioloySimulateData.h"
#include "..\SimulatorBase\VirCardiogramParaFactory.h"
#include "..\SimulatorBase\ITransportOrderIrpToSimulator.h"
#include "..\SimulatorBase\OpECGBuildInterface.h"
#include "..\SimulatorBase\SimulatorOrderIrp.h"
#include "..\SimulatorBase\IHeartStartSign.h"
#include "..\SimulatorBase\ICardiogramLeads.h"


namespace jysoft { namespace simulator { namespace ecg {

    class SIMULATOREMULATEBUILDSHARED_EXPORT CCardiogramBuild : public IGetEcgSimulateData
										 , public base::COpECGBuildInterface
	{
	protected:
		enum _NEXTCYCLESTATE
		{//��һ���ڵ�״̬
			NC_Rhythm = 0,  //��һ����Ϊԭ����״̬
			NC_Change      //��һ���ڸ�Ϊ����״̬
		};
	public:
		CCardiogramBuild( );
		~CCardiogramBuild(void);
	protected: //COpECGBuildInterface���ຯ������
		/*******************************************************************************/
		// �������ƣ� DirectModifyECGHandle
		// ���ܣ� ֱ���޸��ĵ�ͼ
		// ������ CECGParams *pECGParams
		//ע�� ���ĵ�ͼBuild��ʼ������ʱҲ�ô˺���
		// ����ֵ:  
		virtual void DirectModifyECGHandle(const CECGParams &cECGParams);
		/*******************************************************************************/
		// �������ƣ� ModifyECGInDefibrEventHandle
		// ���ܣ� ��Ϊ�������޸Ĳ���
		// ������ CECGParams *pECGParams
		// ����ֵ:  
		virtual void ModifyECGInDefibrEventHandle(const CECGParams *pECGParams);
		/*******************************************************************************/
		// �������ƣ� ModifyECGHandle
		// ���ܣ� �޸��ĵ�ͼ
		// ������ CECGParams *pECGParams:       
		// ����ֵ:  
		virtual void ModifyECGHandle(const CECGParams &cECGParams);
	public:
		/*******************************************************************************/
		// �������ƣ� getIGetEcgLeadSimulateDataPtr
		// ���ܣ� ����IGetEcgSimulateData�ӿ�ָ��
		// ������ 
		// ����ֵ: 
		virtual simulator::IGetEcgSimulateData * getIGetEcgLeadSimulateDataPtr() { return dynamic_cast<simulator::IGetEcgSimulateData *>(this); };
		/*******************************************************************************/
		// �������ƣ� OnInitializeBuild
		// ���ܣ� ��ʼ���ĵ�ͼ������
		// ������ CECGParams *pECGParams:       
		// ����ֵ:  
		virtual bool OnInitializeBuild(const CECGParams &cECGParams);
	public: //�ӿ�IGetEcgSimulateData��������
		/*******************************************************************************/
		//���ܣ���ȡ���������ڵĸ�������������
		//������int iMilliTime:             ʱ�䣨0.1���룩
		//      I12LeadSample *pcBuffer:    ���صĸ�������������
		//����ֵ:  �������ݵĳ���
		virtual unsigned long GetI12LeadEcgSimulateData(int iMilliTime, /*out*/I12LeadSample *pcBuffer = NULL);
	public:
		/*******************************************************************************/
		// �������ƣ� SetEcgBuildRelateInterfacesPtr
		// ���ܣ� �����ĵ�ͼ�������ָ��
		// ������ 
		//        ITransportOrderIrpToSimulator *pPtrTransportLayer:
		//        IPhysiologyStartSign *pSpO2SignPtr:  
		//        SimulatePatientType ePateintType:    ģ�������
		// ����ֵ: 
		void SetEcgBuildRelateInterfacesPtr(IPhysiologyStartSign *pSpO2SignPtr, const std::string &resPath, transLayer::ITransportOrderIrpToSimulator *pPtrTransportLayer, SimulatePatientType ePateintType);
		// ���Ի��ĵ�ͼ������
		bool InitializeBuild(const CECGParams &cECGParams);
		//�������������źŽӿ�
		void InsertHeartStartSignPtr(IHeartStartSign  *pInterface);
		void RemoveHeartStartSignPtr(IHeartStartSign  *pInterface);
		//�����Ƿ�����ĵ����Ӽ��
		void Set_IsClearEcgWatchLink(bool bClear);
		//�����ĵ����Ӽ��״̬
		void Set_EcgWatchLinkState(bool bLinking);
		//�ر��ĵ�ͼ������
		void CloseCardiogramBuild();
		//�����¸����ڵ�����
		void BuildNextCycleCardiogram();
		bool CreateCardiogram(const CECGParams *ptrParam, /*out*/CEcgLeadSamples *pDestLeadsSample);
		bool CreateExtrasyst(Extrasys eExtrasyst, /*out*/CEcgLeadSamples *pDestLeadsSample);
		//��ȡ�ĵ�ͼ�����ݻ�����������
		template<class T> void GetBufferData(utility::CVirBuffer<T> *pcBuffer, short dwReadNum)
		{
			boost::mutex::scoped_lock  lock(muEcgData);
			m_DataBuffer.ReadDataToBuffer(pcBuffer,dwReadNum);
		};
	public:
		// ��������ˢ�µ��ٶȣ��������ƶ����ٶȣ���λ������/�룩
		int GetMoveSpeed(void);
		//�����Ƿ��ѳ�ʼ��
		inline bool IsInitialCardiogramBuild() { return m_bInitialed;};
		//�����ĵ�����״̬�������Ƿ���ʾ�ĵ�����
		bool IsShowEcgByLinkState();
		//���ص�ǰ����ʱ��(��λ��0.1����)
		inline int Get_nCycleTime() { return m_iCycleTime; };
	protected:
		/*******************************************************************************
		//���ܣ���������ڵ�����
		//����ֵ:  ���ݵĳ���
		*********************************************************************************/
		short CombinNextCycleCurveData(bool changeInDefibr = false);
		//��Ӽ�����50/60HZʱ������
		void  CombineArtifactData(Artifact eArtiface, float *fptrBegin, float *fptrEnd);
		//�жϼ�����Ѫ�����ź�; int iMilliTime:   ʱ�䣨0.1���룩
		void  JudgeSpO2Sign(ICardiogramLeads  *pVirEcgLeads, int  iMilliTime);
	public:
		//���س�������ĵ�������ʱ��
		int   GetDefibrillateActDelayTime();
protected:
		//�����������ڵ�Yֵ
		static float* GetTriangleCycleData(int nFrequent, unsigned int &uCycleNum);
		//ʵʩ��һ�γ���
		void DefibrillateAct();
		//���ڳ�����������ĵ�ͼ�����޸�
		void DirectModifyCardiogramInDefibrState(const CECGParams * ptrParam);
		//ֱ���޸��ĵ�ͼ���� 2006/11/2 hjg ���
		void DirectModifyCardiogram(const CECGParams * ptrParam);
		//��������
		void UpdateShowHR(ICardiogramLeads  *pVirEcgLeads);
		//���������źŷ���
		void SendHeartStartSign(bool   bHaveHeartSign);
	private:
		bool CreateCardiogram(ICardiogramLeads *pVirEcgLeads, /*out*/CEcgLeadSamples *pDestLeadsSample);
	private:
		bool                                     m_bInitialed;        //�Ƿ��Ѿ���ʼ��������
		CSpO2SignBuildInterface                  m_cSpO2SignBuildInterface;
		IPhysiologyStartSign *                   m_pPhysiologyStartSignPtr;
		bool                                     m_bClearWatchLink;    //�Ƿ�����ĵ����Ӽ��
		bool                                     m_bLinkWatchEcg;
	protected:
		CExtrasystSignBuildInterface             m_cExtrasystSignInterface;
		IHeartStartSign *                        m_pHeartStartSignAgg;
	protected:
		transLayer::ITransportOrderIrpToSimulator *m_pPtrTransportLayer;
		CVirCardiogramParaFactory *                m_pParamFactory;
		CEcgCycleLeadsBuild                        m_cCycleLeadsBuild;
		_NEXTCYCLESTATE                            m_eNextCycleState;
		CECGParams                                 m_cParams;
		CEcgLeadSamples                            m_cLeadsSampleBuff[2];
		bool                                       m_bCardiogramModifyed[2];
		int                                        m_iCycleTime; //����ʱ�� 
		//�¼����
		utility::CLoopBuffer<I12LeadSample>      m_DataBuffer;        //�ĵ�ͼ�����ݻ�����
		boost::mutex                             muEcgData;
		boost::mutex                             muHeartStartSign;
		boost::mutex                             muSwapMutex;
		boost::mutex                             muCardiogramParamMutex;
		boost::mutex                             muDirectEcgModifyMutex;
		//-----------------------------------------------------------------------------------------
		unsigned short                           m_uArtifactNum;       //����ʱ��ȡ����
	};
}}}
