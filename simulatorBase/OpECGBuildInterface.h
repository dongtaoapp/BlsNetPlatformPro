#pragma once
#include ".\SyncPnpFacilities.h"
#include ".\IGetPhysioloySimulateData.h"

#include "..\common\opinterfacevir.h"
#include "..\common\criticalMutex.h"
#include "..\Common\ECGParams.h"

namespace jysoft { namespace simulator { namespace base {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �����ĵ�ͼ���ݲ������Ľӿ���
	�����ˣ�	 hjg
	����ʱ�䣺   2016/8/5
	//-----------------------------------------------------------------------------------------------------------------*/

	class CShowECGUpdateInterface;
    class SIMULATORBASESHARED_EXPORT COpECGBuildInterface : public COpInterfaceVir
	{
	public:
		COpECGBuildInterface(void);
		virtual ~COpECGBuildInterface(void);
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		CShowECGUpdateInterface          *m_pShowECGUpdate;
        utility::CCriticalMutex           m_cInterfaceMutex;
	private:
		pnp::CSyncPnpFacilities*          m_pSyncPnPFacilities;
	protected:
		/*******************************************************************************/
		// �������ƣ� ModifyECGHandle
		// ���ܣ� �޸��ĵ�ͼ
		// ������ CECGParams *pECGParams:       
		// ����ֵ:  
		virtual void ModifyECGHandle(CECGParams *pECGParams) = 0;
		/*******************************************************************************/
		// �������ƣ� DirectModifyECGHandle
		// ���ܣ� ֱ���޸��ĵ�ͼ
		// ������ CECGParams *pECGParams
		//ע�� ���ĵ�ͼBuild��ʼ������ʱҲ�ô˺���
		// ����ֵ:  
		virtual void DirectModifyECGHandle(CECGParams *pECGParams) = 0;
		/*******************************************************************************/
		// �������ƣ� ManualBuildExtrasystHandle
		// ���ܣ� �ֶ�����һ���粨
		// ������       
		// ����ֵ:  
		virtual void ManualBuildExtrasystHandle() = 0;
		/*******************************************************************************/
		// �������ƣ� ModifyECGInDefibrEventHandle
		// ���ܣ� ��Ϊ�������޸Ĳ���
		// ������ CECGParams *pECGParams
		// ����ֵ:  
		virtual void ModifyECGInDefibrEventHandle(CECGParams *pECGParams) = 0;
		/*******************************************************************************/
		// �������ƣ� StartPacingHandle
		// ���ܣ� ������
		// ������ 
		// ����ֵ:  
		virtual void StartPacingHandle(short sPaceHR) = 0;
		/*******************************************************************************/
		// �������ƣ� ModifyPacingRateHandle
		// ���ܣ� �޸���Ƶ��
		// ������ 
		// ����ֵ:  
		virtual void ModifyPacingRateHandle(long nPaceRate) = 0;
		/*******************************************************************************/
		// �������ƣ� StopPacingHandle
		// ���ܣ� ֹͣ��
		// ������ 
		// ����ֵ: 
		virtual void StopPacingHandle() = 0;
	public:
		/*******************************************************************************/
		// �������ƣ� Get_IGetEcgLeadSimulateDataPtr
		// ���ܣ� ����IGetEcgSimulateData�ӿ�ָ��
		// ������ 
		// ����ֵ: 
		virtual IGetEcgSimulateData * Get_IGetEcgLeadSimulateDataPtr() = 0;
		/*******************************************************************************/
		// �������ƣ� OnInitializeBuild
		// ���ܣ� ��ʼ���ĵ�ͼ������
		// ������ CECGParams *pECGParams:       
		// ����ֵ:  
		virtual bool OnInitializeBuild(const CECGParams *ptrParam, SimulatePatientType ePatientType) = 0;
		/*******************************************************************************/
		// �������ƣ� OnModifyPnPFacility
		// ���ܣ� �ı��Ȳ���豸
		// ������ 
		//         CSyncPnpFacilities *pSyncPnPFacilities:
		// ����ֵ:  
		virtual void OnModifyPnPFacility(pnp::CSyncPnpFacilities *pSyncPnPFacilities);
	public:
		/*******************************************************************************/
		// �������ƣ� SetRelateECGShowInterface
		// ���ܣ� �����ĵ�ͼ��ʾ�ӿ�
		// ������ CShowECGUpdateInterface *pShowECGInterface:       
		// ����ֵ:  
		//ע�� ͨ��CShowECGUpdateInterface�Ĵ���ָ�룬��������صĶ���ĵ�ͼ��ʾ�ӿ�
		void SetRelateECGShowInterface(CShowECGUpdateInterface *pShowECGInterface);
		//�Ͽ�ָ�����ĵ�ͼ��ʾ�ӿ�
		void RemoveRelateECGShowInterface(CShowECGUpdateInterface *pRmvShowECGInterface);
	public:
		//�޸��ĵ�ͼ
		void OnModifyECGHandle(CECGParams *pECGParams);
		//ֱ���޸��ĵ�ͼ
		void OnDirectModifyECGHandle(CECGParams *pECGParams);
		//�ֶ�����һ���粨
		void OnManualBuildExtrasystHandle();
		//��Ϊ�������޸Ĳ���
		void OnModifyECGInDefibrEventHandle(CECGParams *pECGParams);
		//������  
		void OnStartPacingHandle(short sPaceHR);
		//�޸���Ƶ�� 
		void OnModifyPacingRateHandle(long nPaceRate);
		//ֹͣ��
		void OnStopPacingHandle() ;
	protected:
		void ModifyTransmitAddress(/*out*/short &sAddress);
	};

}}}
