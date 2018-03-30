#pragma once
#include <string>

#include ".\IPnPFacility.h"

#include "..\common\criticalMutex.h"

namespace jysoft { namespace pnp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ���弴���豸�ӿڼ��ϣ�ͬ����������
	�����ˣ�	 hjg
	����ʱ�䣺   2013/3/5
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CSyncPnpFacilities
	{
	public:
		CSyncPnpFacilities(void);
		virtual ~CSyncPnpFacilities(void);
	protected:
        IPnPFacility *     m_pPnPFacilities;
	private:
        utility::CCriticalMutex     m_cPnpMutex;
		//------------------------------------------------------------------------
        int                m_nWeepSpeedParam;   //����ģʽ����
        int                m_nSweatSpeedParam;  //����ģʽ����
	public:
		/*******************************************************************************/
		// �������ƣ� SyncAddPnpInstrument
		// ���ܣ�   ͬ����������µ�Pnp�豸
		// ������   
		//      IPnPFacility *pNewPnPFacility: 
		// ����ֵ: 
		void SyncAddPnpInstrument( IPnPFacility *pNewPnPFacility );
		/*******************************************************************************/
		// �������ƣ� SyncRemovePnpInstrument
		// ���ܣ�   ͬ�������Ƴ�Pnp�豸
		// ������   
		//      IPnPFacility *pRmvPnPFacility: 
		// ����ֵ: 
        bool SyncRemovePnpInstrument( IPnPFacility  *pRmvPnPFacility );
		/*******************************************************************************/
		// �������ƣ� SyncRemovePnpInstrument
		// ���ܣ�   ͬ�������Ƴ�Pnp�豸
		// ������   
		//      short sPort: 
		// ����ֵ: 
        bool SyncRemovePnpInstrument( short sPnpID );
		/*******************************************************************************/
		// �������ƣ� SyncModifyTransmitAddress
		// ���ܣ�   ͬ�������޸�ͨѶָ���ת����ַ
		// ������   
		//      /*out*/short &sAddress: 
		// ����ֵ: 
		void SyncModifyTransmitAddress(/*out*/short &sAddress, const std::string &symptomCaption);
		/*******************************************************************************/
		// �������ƣ� RemoveAllPnpInstrument
		// ���ܣ�   ������е�Pnp�豸
		// ������   
		//      
		// ����ֵ: 
		void RemoveAllPnpInstrument();
	public:
		void Set_WaterSpeedParams(int nWeepSpeed, int nSeatSpeed);
		inline int Get_nWeepSpeedParam() { return m_nWeepSpeedParam; };
		inline int Get_nSweatSpeedParam() { return m_nSweatSpeedParam; };
	};

}}
