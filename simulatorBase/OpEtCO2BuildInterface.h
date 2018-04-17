#pragma once
#include <boost/thread.hpp>
#include ".\IGetPhysioloySimulateData.h"

#include "..\common\opinterfacevir.h"

namespace jysoft { namespace simulator { namespace base {

	class CShowEtCO2UpdateInterface;
    class SIMULATORBASESHARED_EXPORT COpEtCO2BuildInterface : public COpInterfaceVir
	{
	public:
		COpEtCO2BuildInterface(void);
		virtual ~COpEtCO2BuildInterface(void);
	protected:
		CShowEtCO2UpdateInterface*        m_pShowEtCO2Update;
		boost::mutex                      m_cInterfaceMutex;
	public:
		virtual bool isKindOf(const std::string &className);
	protected:
		//�޸�CO2%
		virtual void ModifyCO2PercentValue( int nCO2Per ) = 0;
		/*******************************************************************************/
		// �������ƣ� OnIntubateOp
		// ���ܣ� ��/����¼�
		// ������ 
		//         BOOL bIntubate:
		// ����ֵ:  
		virtual void IntubateEventOp( bool bIntubate ) = 0;
		/*******************************************************************************/
		// �������ƣ� OnOnceBreathEventOp
		// ���ܣ� һ�δ����¼�
		// ������ 
		// ����ֵ:  
		virtual void OnceBreathEventOp() = 0;
		/*******************************************************************************/
		// �������ƣ� OnCPREventOp
		// ���ܣ� �׶���CPR�¼�
		// ������ 
		// ����ֵ:  
		virtual void CPREventOp( bool bStop ) = 0;
	public:
		//�޸�CO2%
		void OnModifyCO2PercentValue( int nCO2Per );
		// ��/����¼�
		void OnIntubateEventOp( bool bIntubate );
		//һ�δ����¼�
		void OnOnceBreathEventOp();
		//�׶���CPR�¼�
		void OnCPREventOp( bool bStop );
	public:
		/*******************************************************************************/
		// �������ƣ� SetRelateEtCO2ShowInterface
		// ���ܣ� ����EtCO2��ʾ�ӿ�
		// ������ CShowEtCO2UpdateInterface *pShowInterface:       
		// ����ֵ:  
		//ע�� ͨ��CShowEtCO2UpdateInterface�Ĵ���ָ�룬��������صĶ��EtCO2��ʾ�ӿ�
		void SetRelateEtCO2ShowInterface(CShowEtCO2UpdateInterface *pShowInterface);
		//�Ͽ�ָ����EtCO2��ʾ�ӿ�
		void RemoveRelateEtCO2ShowInterface(CShowEtCO2UpdateInterface *pRmvShowEtCO2Interface);
	public:
		/*******************************************************************************/
		// �������ƣ� Get_IGetPhysioloySimulateDataPtr
		// ���ܣ� ����IGetPhysioloySimulateData�ӿ�ָ��
		// ������ 
		// ����ֵ: 
		virtual IGetPhysioloySimulateData * Get_IGetPhysioloySimulateDataPtr() = 0;
		/*********************************************************************************/
		//���ܣ���ʼ��ģ��CO2������
		//������
		//      int nCO2Per:             CO2%
		//����ֵ:  
		virtual void InitializeBuild(int nCO2Per) = 0;
	};

}}}
