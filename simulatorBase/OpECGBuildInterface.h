#pragma once
#include ".\IGetPhysioloySimulateData.h"

#include "..\common\opinterfacevir.h"
#include "..\Common\ECGParams.h"
#include "..\common\CriticalMutex.h"

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
		CShowECGUpdateInterface*          m_pShowECGUpdate;
		utility::CCriticalMutex           m_cInterfaceMutex;
	protected:
		/*******************************************************************************/
		// �������ƣ� ModifyECGHandle
		// ���ܣ� �޸��ĵ�ͼ
		// ������ cECGParams:        
		// ����ֵ:  
		virtual void ModifyECGHandle(const CECGParams &cECGParams) = 0;
		/*******************************************************************************/
		// �������ƣ� DirectModifyECGHandle
		// ���ܣ� ֱ���޸��ĵ�ͼ
		// ������ cECGParams: 
		//ע�� ���ĵ�ͼBuild��ʼ������ʱҲ�ô˺���
		// ����ֵ:  
		virtual void DirectModifyECGHandle(const CECGParams &cECGParams) = 0;
		/*******************************************************************************/
		// �������ƣ� ModifyECGInDefibrEventHandle
		// ���ܣ� ��Ϊ�������޸Ĳ���
		// ������ cECGParams: 
		// ����ֵ:  
		virtual void ModifyECGInDefibrEventHandle(const CECGParams *pECGParams) = 0;
	public:
		/*******************************************************************************/
		// �������ƣ� getIGetEcgLeadSimulateDataPtr
		// ���ܣ� ����IGetEcgSimulateData�ӿ�ָ��
		// ������ 
		// ����ֵ: 
		virtual IGetEcgSimulateData * getIGetEcgLeadSimulateDataPtr() = 0;
		/*******************************************************************************/
		// �������ƣ� OnInitializeBuild
		// ���ܣ� ��ʼ���ĵ�ͼ������
		// ������ CECGParams *pECGParams:       
		// ����ֵ:  
		virtual bool OnInitializeBuild(const CECGParams &cECGParams) = 0;
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
		void OnModifyECGHandle(const CECGParams &cECGParams);
		//ֱ���޸��ĵ�ͼ
		void OnDirectModifyECGHandle(const CECGParams &cECGParams);
		//��Ϊ�������޸Ĳ���
		void OnModifyECGInDefibrEventHandle(const CECGParams *pECGParams);
	};

}}}
