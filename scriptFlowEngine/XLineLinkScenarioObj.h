#pragma once
#include "xlinelink.h"
#include ".\IAclsFlowStrategy.h"

#include "..\SimulatorBase\FrameFlowIrp.h"


namespace jysoft { namespace flowEngine 
{
	class CXLineLinkScenarioObj : public CXLineLink
	{
	public:
		CXLineLinkScenarioObj();
		virtual ~CXLineLinkScenarioObj(void);
	public:
		virtual bool isKindOf(const std::string &strClassName);
		/*******************************************************************************
		//���ܣ��������Ӷ���
		//������const CString &strAimId:          ���ӵ�Ŀ������ID��
		//      IXMLDOMNode *pScenarioNode:       Ԫ��scenario�ڵ�ָ��
		//����ֵ:  �Ƿ�����ɹ�
		*********************************************************************************/
		virtual bool InitialLineLink(const std::string &strAimId, pugi::xml_node *pScenarioNode, IAclsFlowStrategy  *pFlowStrategy);
	public: //���ຯ������
		//������Ӷ��󵽶����У��Ա���Դ���Irp
		void AddLinkObjToHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect) { };
		//�Ƴ����Ӷ���
		void RemoveLinkObjFromHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect) { };
	public:
		//���س���ת��Irp
		irp::CFrameFlowIrp * GetFrameFlowIrp(eEventSign eEvent);
	};
}}