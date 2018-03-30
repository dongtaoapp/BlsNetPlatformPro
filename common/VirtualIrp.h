#pragma once
#include <string>
#include ".\CommonGlobal.h"

namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ����Irp��װ��
	�����ˣ�	 hjg
	����ʱ�䣺   2009/4/8
	//-----------------------------------------------------------------------------------------------------------------*/
	class AFX_EXT_CLASS CVirtualIrp
	{
	public:
		CVirtualIrp(void);
		virtual ~CVirtualIrp(void);
	public:
		//����Irp�����
		virtual _IrpType Get_eIrpType() = 0;
		virtual bool isKindOf(const std::string &strClass) = 0;
	public:
		/*******************************************************************************/
		// �������ƣ� doPackageIrp
		// ���ܣ�  ���Irp������
		// ������ 
		// ����ֵ: 
		virtual std::string doPackageIrp() = 0;
	};
}}

