#pragma once
#include <list>
#include <pugixml.hpp>
#include ".\IAclsFlowStrategy.h"
#include ".\XEventVirtual.h"

#include "..\Common\CommonGlobal.h"
#include "..\Common\EventHandleClockIrpOp.h"
#include "..\Common\EventHandleCustomIrpOp.h"

#include "..\simulatorsymptom\xvirtualcomponent.h"


namespace jysoft { namespace flowEngine 
{
	class CXVirtualEventFrame : public simulator::CXVirtualComponent
								,public irp::CEventHandleCustomIrpOp
								,public irp::CEventHandleClockIrpOp
	{
	public:
		CXVirtualEventFrame(IAclsFlowStrategy   *pFlowStrategy);
		virtual ~CXVirtualEventFrame(void);
	protected:
		IAclsFlowStrategy*               m_pAlcsFlowStrategy;
		std::list<CXEventVirtual *>      m_lstEvents;
		eEventSign                       m_eEventSign;
		pugi::xml_node                   m_xmlEventFrameDOMNode;
	public: //��������
		/*******************************************************************************/
		//���ܣ��������¼�IRP����
		//������
		//      CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool doHandleCustomEventIrpOp(irp::CVirtualIrp *pCurrIrp);
		/*******************************************************************************/
		//���ܣ�����ʱ���¼�IRP����
		//������
		//      CVirtualIrp *pCurrIrp��
		//����ֵ:  �������ٴ���FALSE);
		virtual bool doHandleClockIrpOp(irp::CVirtualIrp *pCurrIrp);
	public:
		virtual bool isKindOf(const std::string &strClassName);
		virtual eEventSign Get_eEventSign();
		/*******************************************************************************/
		//���ܣ������¼�IRP�����麯��
		//������
		//      CVirEventIrp *pCurrEventIrp��
		//����ֵ:  �¼����Ƿ���������(TURE:���㣻FALSE:������)
		virtual bool DoHandleEventIrp(irp::CVirEventIrp *pCurrEventIrp) = 0;
	public:
		//�����¼���
		bool ParseEvents(const pugi::xml_node &eventFrameNode);
	};
}}