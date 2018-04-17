#pragma once
#include "XLineLink.h"
#include ".\XVirtualEventFrame.h"


namespace jysoft { namespace flowEngine 
{
	class CXLineLinkEventObj : public CXLineLink
	{
	public:
		CXLineLinkEventObj();
		virtual ~CXLineLinkEventObj(void);
	protected:
		CXVirtualEventFrame    *m_pEventFrame;
	public:
		virtual bool isKindOf(const std::string &strClassName);
		/*******************************************************************************
		//���ܣ��������Ӷ���
		//������const CString &strAimId:          ���ӵ�Ŀ������ID��
		//      pugi::xml_node *pScenarioNode:       Ԫ��scenario�ڵ�ָ��
		//����ֵ:  �Ƿ�����ɹ�
		*********************************************************************************/
		virtual bool InitialLineLink(const std::string &strAimId, pugi::xml_node *pScenarioNode, IAclsFlowStrategy  *pFlowStrategy);
	public: //���ຯ������
		//������Ӷ��󵽶����У��Ա���Դ���Irp
		void AddLinkObjToHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect);
		//�Ƴ����Ӷ���
		void RemoveLinkObjFromHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect);
	};
}}