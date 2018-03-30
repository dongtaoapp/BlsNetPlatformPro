#pragma once
#include ".\IGetPhysioloySimulateData.h"

#include "..\common\opinterfacevir.h"
#include "..\common\criticalMutex.h"

namespace jysoft { namespace simulator { namespace base {

	class CShowABPUpdateInterface;
    class SIMULATORBASESHARED_EXPORT COpABPBuildInterface : public COpInterfaceVir
	{
	public:
		COpABPBuildInterface(void);
		virtual ~COpABPBuildInterface(void);
	protected:
		CShowABPUpdateInterface          *m_pShowABPUpdate;
        utility::CCriticalMutex           m_cInterfaceMutex;
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		/*******************************************************************************/
		// �������ƣ� ModifyABPValue
		// ���ܣ� �޸�ABP��ֵ
		// ������  
		// ����ֵ:  
		virtual void ModifyABPValue(int nShrinkValue, int nStretchValue) = 0;
	public:
		//�޸�ABP��ֵ
		void OnModifyABPValue(int nShrinkValue, int nStretchValue);
	public:
		/*******************************************************************************/
		// �������ƣ� SetRelateABPShowInterface
		// ���ܣ� ����ABP��ʾ�ӿ�
		// ������ CShowABPUpdateInterface *pShowInterface:       
		// ����ֵ:  
		//ע�� ͨ��CShowABPUpdateInterface�Ĵ���ָ�룬��������صĶ��ABP��ʾ�ӿ�
		void SetRelateABPShowInterface(CShowABPUpdateInterface *pShowInterface);
		//�Ͽ�ָ����ABP��ʾ�ӿ�
		void RemoveRelateABPShowInterface(CShowABPUpdateInterface *pRmvShowInterface);
	public:
		/*******************************************************************************/
		// �������ƣ� Get_IGetPhysioloySimulateDataPtr
		// ���ܣ� ����IGetPhysioloySimulateData�ӿ�ָ��
		// ������ 
		// ����ֵ: 
		virtual IGetPhysioloySimulateData * Get_IGetPhysioloySimulateDataPtr() = 0;
	};

}}}
