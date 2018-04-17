#pragma once
#include <pugixml.hpp>
#include "xvirtuallink.h"
#include ".\IAclsFlowStrategy.h"
#include ".\IGetPhysiologyActionObj.h"


namespace jysoft { namespace flowEngine 
{
	class IAclsFlowStrategy;
	class CXLineLink : public CXVirtualLink
	{
	public:
		CXLineLink();
		virtual ~CXLineLink(void);
	protected:
		IAclsFlowStrategy          *m_pFlowStrategy;
	public:
		virtual bool isKindOf(const std::string &strClassName);
		/*******************************************************************************
		//���ܣ��������Ӷ���
		//������const std::string &strAimId:          ���ӵ�Ŀ������ID��
		//      pugi::xml_node *pScenarioNode:       Ԫ��scenario�ڵ�ָ��
		//����ֵ:  �Ƿ�����ɹ�
		*********************************************************************************/
		virtual bool InitialLineLink(const std::string &strAimId, pugi::xml_node *pScenarioNode, IAclsFlowStrategy  *pFlowStrategy) = 0;
	public: //���ຯ������
		//������Ӷ��󵽶����У��Ա���Դ���Irp
		virtual void AddLinkObjToHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect) = 0;
		//�Ƴ����Ӷ���
		virtual void RemoveLinkObjFromHandleIrpCollect(IHandleIrpsCollect *pHandleIrpsCollect) = 0;
	};
}}