#pragma once
#include ".\SyncPnpFacilities.h"
#include ".\IGetPhysioloySimulateData.h"
#include ".\ShowRespRateUpdateInterface.h"

#include "..\common\criticalMutex.h"
#include "..\common\opinterfacevir.h"
#include "..\Common\CommonGlobal.h"


namespace jysoft { namespace simulator { namespace base {

    class SIMULATORBASESHARED_EXPORT COpRespBuildInterface : public COpInterfaceVir
	{
	public:
		COpRespBuildInterface(void);
		virtual ~COpRespBuildInterface(void);
	protected:
		CShowRespRateUpdateInterface          *m_pShowRespUpdate;
        utility::CCriticalMutex                m_cInterfaceMutex;
	private:
		pnp::CSyncPnpFacilities *                   m_pSyncPnPFacilities;
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		/*******************************************************************************/
		// �������ƣ� ModifyRespRate
		// ���ܣ� �޸ĺ�������
		// ������  int nBreathRate:            ������������λ����/���ӣ�
		// ����ֵ:  
		virtual void ModifyRespRate(int nBreathRate) = 0;
		/*******************************************************************************/
		// �������ƣ� ModifyRespBuildType
		// ���ܣ� �޸����ͼ�����
		// ������  eRespMode eMode:            ��������
		//         int nBreathRate:                       ������������λ����/���ӣ�
		// ����ֵ:  
		virtual void ModifyRespBuildType(eRespMode eMode, int nBreathRate) = 0;
	public:
		/*******************************************************************************/
		// �������ƣ� OnModifyRespRate
		// ���ܣ� �޸ĺ�������
		// ������  int nBreathRate:            ������������λ����/���ӣ�
		// ����ֵ:  
		void OnModifyRespRate(int nBreathRate);
		/*******************************************************************************/
		// �������ƣ� OnModifyRespBuildType
		// ���ܣ� �޸����ͼ�����
		// ������  eRespMode eMode:            ��������
		//         int nBreathRate:                       ������������λ����/���ӣ�
		// ����ֵ:  
		void OnModifyRespBuildType(eRespMode eMode, int nBreathRate);
		/*******************************************************************************/
		// �������ƣ� OnModifyPnPFacility
		// ���ܣ� �ı��Ȳ���豸
		// ������ 
		//         CSyncPnpFacilities *pSyncPnPFacilities:
		// ����ֵ:  
		virtual void OnModifyPnPFacility(pnp::CSyncPnpFacilities *pSyncPnPFacilities);
	public:
		/*******************************************************************************/
		// �������ƣ� Get_IGetPhysioloySimulateDataPtr
		// ���ܣ� ����IGetRespSimulateData�ӿ�ָ��
		// ������ 
		// ����ֵ: 
		virtual IGetRespSimulateData * Get_IGetPhysioloySimulateDataPtr() = 0;
		/*********************************************************************************/
		//���ܣ���ʼ��ģ�����������
		//������eRespMode eMode:  ģʽ����
		//      int nBreathRate:             ��������
		//����ֵ:  
		virtual void InitializeBuild(eRespMode eMode, int nBreathRate) = 0;
	public:
		/*******************************************************************************/
		// �������ƣ� SetRelateRespRateShowInterface
		// ���ܣ� ���Ӻ���������ʾ�ӿ�
		// ������ CShowRespRateUpdateInterface *pShowInterface:       
		// ����ֵ:  
		//ע�� ͨ��CShowRespRateUpdateInterface�Ĵ���ָ�룬��������صĶ������������ʾ�ӿ�
		void SetRelateRespRateShowInterface(CShowRespRateUpdateInterface *pShowInterface);
		//�Ͽ�ָ���ĺ���������ʾ�ӿ�
		void RemoveRelateRespRateShowInterface(CShowRespRateUpdateInterface *pRmvShowInterface);
	protected:
		void ModifyTransmitAddress(/*out*/short &sAddress);
	};

}}}
