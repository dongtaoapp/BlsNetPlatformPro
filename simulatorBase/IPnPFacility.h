#pragma once
#include ".\simulatorbase_global.h"
#include <string>

namespace jysoft { namespace pnp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ���弴���豸�ӿ���
	�����ˣ�	 hjg
	����ʱ�䣺   2009/4/30
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT IPnPFacility
	{
	public:
		IPnPFacility(short sPnpID, short sPort);
		virtual ~IPnPFacility(void);
	protected:
		IPnPFacility            *m_pNextInterface;    //�¸��ӿ�
		IPnPFacility            *m_pPreInterface;     //�ϸ��ӿ�
	protected:
		short                    m_sPnpID;     //�豸��
		short                    m_sPnPAddress;
	public:
		//�����¸����弴���豸�ӿ���
		void SetNextInterfacePtr(IPnPFacility *pNextInterface);
		//�����ϸ��ӿ�
		inline void SetPreviouInterfacePtr(IPnPFacility *pPreInterface) { m_pPreInterface = pPreInterface;};
		//�����¸��ӿ�
		inline IPnPFacility * GetNextInterfacePtr() { return m_pNextInterface;};
		//�����ϸ��ӿ�
		inline IPnPFacility * GetPreviouInterfacePtr() { return m_pPreInterface;};
		//�����豸���ӵĵ�ַ��
		inline short Get_PnPId() { return m_sPnpID; };
	public:
		//���ؽӿ������ͷ
		IPnPFacility * GetHeaderInterfacePtr();
		//�Ƴ��ƶ��Ľӿ�
		static IPnPFacility * RemoveInterfacePtr(IPnPFacility *pOrgInterfacePtr, IPnPFacility *pRmvInterface);
	public:
		/*******************************************************************************/
		// �������ƣ� OnModifyTransmitAddress
		// ���ܣ�   �޸�ͨѶָ���ת����ַ
		// ������   
		//      /*out*/BYTE &byteAddress: 
		// ����ֵ: 
		virtual  void OnModifyTransmitAddress(/*out*/short &sAddress, const std::string &symptomCaption) ;
	public:
		/*******************************************************************************/
		// �������ƣ� isModifyTransmitAddress
		// ���ܣ�   �ж��Ƿ��޸�ͨѶָ���ת����ַ
		// ������   
		//      const std::string &symptomCaption: 
		// ����ֵ: 
		virtual bool isModifyTransmitAddress( const std::string &symptomCaption ) = 0;
	};

}}
