#pragma once
#include "xvirtualeventframe.h"


namespace jysoft { namespace flowEngine 
{
	class CXSelEventsFrame : public CXVirtualEventFrame
	{
	public:
		CXSelEventsFrame(IAclsFlowStrategy   *pFlowStrategy);
		virtual ~CXSelEventsFrame(void);
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