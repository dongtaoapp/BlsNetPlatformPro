#pragma once
#include <boost/thread.hpp>
#include ".\IGetPhysioloySimulateData.h"

#include "..\common\opinterfacevir.h"

namespace jysoft { namespace simulator { namespace base {

	class CShowSpO2UpdateInterface;
    class SIMULATORBASESHARED_EXPORT COpSpO2BuildInterface : public COpInterfaceVir
	{
	public:
		COpSpO2BuildInterface(void);
		virtual ~COpSpO2BuildInterface(void);
	protected:
		CShowSpO2UpdateInterface          *m_pShowSpO2Update;
		boost::mutex                      m_cInterfaceMutex;
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		/*******************************************************************************/
		// �������ƣ� ModifySpO2ValuePrecent
		// ���ܣ� �޸�Ѫ���İٷֱ�Ũ��
		// ������  int nSpO2Value:            Ѫ���ٷֱ�Ũ��ֵ
		// ����ֵ:  
		virtual void ModifySpO2ValuePrecent( int nSpO2Value ) = 0;
	public:
		//�޸�Ѫ���İٷֱ�Ũ��
		void OnModifySpO2ValuePrecent( int nSpO2Value );
	public:
		/*******************************************************************************/
		// �������ƣ� SetRelateSpO2ShowInterface
		// ���ܣ� ����SpO2��ʾ�ӿ�
		// ������ CShowSpO2UpdateInterface *pShowInterface:       
		// ����ֵ:  
		//ע�� ͨ��CShowSpO2UpdateInterface�Ĵ���ָ�룬��������صĶ��SpO2��ʾ�ӿ�
		void SetRelateSpO2ShowInterface(CShowSpO2UpdateInterface *pShowInterface);
		//�Ͽ�ָ����SpO2��ʾ�ӿ�
		void RemoveRelateSpO2ShowInterface(CShowSpO2UpdateInterface *pRmvShowInterface);
	public:
		/*******************************************************************************/
		// �������ƣ� Get_IGetPhysioloySimulateDataPtr
		// ���ܣ� ����IGetPhysioloySimulateData�ӿ�ָ��
		// ������ 
		// ����ֵ: 
		virtual IGetPhysioloySimulateData * Get_IGetPhysioloySimulateDataPtr() = 0;
	};

}}}
