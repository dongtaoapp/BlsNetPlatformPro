#pragma once
#include ".\simulatorbase_global.h"
#include <list>
#include <string>
#include <boost/assert.hpp>
#include ".\SimulateBaseGlobal.h"

#include "..\Common\VirtualIrp.h"

namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ģ����ָ���
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/9
	ע��  �޸ĳ�֧��for_each�������ѯ(ĩ���)
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CSimulatorOrderIrp : public CVirtualIrp
	{
	public:
		CSimulatorOrderIrp(_SIMULATECOMMANDTYPE  eCmdType);
		virtual ~CSimulatorOrderIrp(void);
	public:
		/*******************************************************************************/
		// �������ƣ� createSimulatorOrderIrp
		// ���ܣ� ����ģ����ָ��Irp
		// ������      
		// ����ֵ:  
		static CSimulatorOrderIrp * createSimulatorOrderIrp(byte param1, byte param2);
	public:
		//����Irp�����
		virtual _IrpType Get_eIrpType() { return eSimulateOrder; };
		virtual bool isKindOf(const std::string &strClass);
		/*******************************************************************************/
		// �������ƣ� doPackageIrp
		// ���ܣ�  ���Irp������
		// ������ 
		// ����ֵ: 
		virtual std::string doPackageIrp() { BOOST_ASSERT( 0 ); return ""; };
	public:
		inline _SIMULATECOMMANDTYPE Get_eSimulateCommandType() { return m_eCommandType; };
	protected:
		std::list<std::string>         m_lstOrderDecodes;        //�����ͨ��ָ���б�
		_SIMULATECOMMANDTYPE           m_eCommandType;
	public:
		void addOrderDecode(const std::string &orderDecode);
		void clearOrderDecode() { m_lstOrderDecodes.clear(); };
	public:
		//��ʼ����
		std::list<std::string>::iterator StartUnDecode();
		//�����¸�ָ��
		long NextUnDecode(std::list<std::string>::iterator &pos, byte *lpbyteData);
	};

}}
