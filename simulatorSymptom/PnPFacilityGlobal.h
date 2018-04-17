#pragma once

#include "..\SimulatorBase\IPnPFacility.h"


namespace jysoft { namespace pnp { 
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ���弴���豸Ѫѹ����ѵ������
	�����ˣ�	 hjg
	����ʱ�䣺   2009/4/30
	//-----------------------------------------------------------------------------------------------------------------*/
	class CSphygmomanometerFacility : public IPnPFacility
	{
	public:
		CSphygmomanometerFacility(short sPnpID, short sPort);		
		virtual ~CSphygmomanometerFacility();
	public:
		/*******************************************************************************/
		// �������ƣ� isModifyTransmitAddress
		// ���ܣ�   �ж��Ƿ��޸�ͨѶָ���ת����ַ
		// ������   
		//      const std::string &strSymptomCaption: 
		// ����ֵ: 
		virtual bool isModifyTransmitAddress( const std::string &symptomCaption );
	};
	
	//--------------------------------------------------------------------------------------------------------------------
	//ģ�����ѵ����: �豸�ţ�0xB0
	class CSimulateDefibrillatorFacility : public IPnPFacility
	{
	public:
		CSimulateDefibrillatorFacility(short sPnpID, short sPort);
		virtual ~CSimulateDefibrillatorFacility();
	public:
		/*******************************************************************************/
		// �������ƣ� isModifyTransmitAddress
		// ���ܣ�   �ж��Ƿ��޸�ͨѶָ���ת����ַ
		// ������   
		//      const std::string &strSymptomCaption: 
		// ����ֵ: 
		virtual bool isModifyTransmitAddress( const std::string &symptomCaption );
	};

	//--------------------------------------------------------------------------------------------------------------------
	//�ֶ���������ģ�鰲װ: �豸�ţ�0xD4
	class  CManualRespInstrumentFacility : public IPnPFacility
	{
	public:
		CManualRespInstrumentFacility(short sPnpID, short sPort);
		virtual ~CManualRespInstrumentFacility();
	public:
		/*******************************************************************************/
		// �������ƣ� IsModifyTransmitAddress
		// ���ܣ�   �ж��Ƿ��޸�ͨѶָ���ת����ַ
		// ������   
		//      const CString &strSymptomCaption: 
		// ����ֵ: 
		virtual  bool isModifyTransmitAddress( const std::string &symptomCaption );
	};
}}