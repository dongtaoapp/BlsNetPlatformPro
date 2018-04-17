#pragma once
#include ".\SimulatorOrderIrp.h"

#include "..\Common\VirtualIrp.h"

namespace jysoft { namespace transLayer {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ��ģ���˷���ָ��Ľӿ���
	�����ˣ�	 hjg
	����ʱ�䣺   2016/7/31
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT ITransportOrderIrpToSimulator
	{
	public:
		ITransportOrderIrpToSimulator(void);
		virtual ~ITransportOrderIrpToSimulator(void);
	public:
		/*******************************************************************************/
		// �������ƣ� OnTransportDownOrderToSimulater
		// ���ܣ�  ��ģ���˷���ָ��
		// ������ 
		// ����ֵ:  
		virtual void OnTransportDownOrderToSimulater(irp::CSimulatorOrderIrp *pOrderIrp) = 0;
		/*******************************************************************************/
		// �������ƣ� GetCommunicateVersion
		// ���ܣ�  ����ͨ�Ű汾
		// ������ 
		// ����ֵ:  
		virtual short GetCommunicateVersion() = 0;
	};

	/*-------------------------------------------------------------------------------------------------------------------
	��˵����     �ϴ�����ָ��Ľӿ���
	�����ˣ�	 hjg
	����ʱ�䣺   2009/5/13
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT ITransportOrderIrpToUp
	{
	public:
		ITransportOrderIrpToUp();
		virtual ~ITransportOrderIrpToUp();
	public:
		//----------------------------------------------------------------------------------
		// �������ƣ� TranslateUpIrp
		// ���ܣ�  ͨ����������ϴ���Irp
		// ������ 
		// ����ֵ:  
		virtual void OnTranslateUpIrp( irp::CVirtualIrp * pUpIrp ) = 0;
		//-----------------------------------------------------------------------------------
		// �������ƣ� TranslateUpIrpNoNetwork
		// ���ܣ�  �����Irp�ɱ���������
		// ������ 
		// ����ֵ:  
		virtual void OnTranslateUpIrpNoNetwork( irp::CVirtualIrp * pUpIrp ) = 0;
	};

}}
