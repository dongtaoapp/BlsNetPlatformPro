#pragma once
#include "xvirtualeventframe.h"


namespace jysoft { namespace flowEngine 
{
	class CXSingleEventFrame : public CXVirtualEventFrame
	{
	public:
		CXSingleEventFrame(IAclsFlowStrategy   *pFlowStrategy);
		virtual ~CXSingleEventFrame(void);
	public:
		virtual bool isKindOf(const std::string &strClassName);
		/*******************************************************************************/
		//���ܣ������¼�IRP�����麯��
		//������
		//      CVirEventIrp *pCurrEventIrp��
		//����ֵ:  �¼����Ƿ���������(TURE:���㣻FALSE:������)
		virtual bool DoHandleEventIrp(irp::CVirEventIrp *pCurrEventIrp);
	};
}}