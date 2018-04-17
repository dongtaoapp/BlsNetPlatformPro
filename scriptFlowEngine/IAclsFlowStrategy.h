#pragma once
#include <list>
#include <pugixml.hpp>
#include ".\xvirtuallink.h"
#include ".\IHandleIrpsCollect.h"
#include ".\IGetPhysiologyActionObj.h"


namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     �ű�������Խӿ���
	�����ˣ�	 hjg
	����ʱ�䣺   2009/3/27
	//-----------------------------------------------------------------------------------------------------------------*/
	class CXLineLink;
	class CXLineLinkScenarioObj;
    class SCRIPTFLOWENGINESHARED_EXPORT IAclsFlowStrategy
	{
	public:
		IAclsFlowStrategy(pugi::xml_node *pxmlRootElement, IHandleIrpsCollect *pHandleIrpsCollect, IGetPhysiologyActionObj *pGetActionObj);
		virtual ~IAclsFlowStrategy(void);
	protected:
		pugi::xml_node                            m_xmlRootElement;
		IHandleIrpsCollect*                       m_pHandleIrpsCollect;
		IGetPhysiologyActionObj*                  m_pGetPhysiologyActionObj;
		std::list<CXVirtualLink *>                m_lstLineLinks;
	private:
		std::list<CXVirtualLink *>                m_lstDeletedLineLinks; //ɾ��������
	protected:
		//���ؽű����ݽڵ�
		pugi::xml_node getScenarioXMLDOMNodePtr();
		//�������������Ӷ���
		CXLineLink * CreateLineLink(pugi::xml_node *pLinkNodePtr);
		//��ձ�ɾ��������
		void EmptyDeletedLineLinks();
	public:
		IHandleIrpsCollect * GetHandleIrpsCollectPtr() { return m_pHandleIrpsCollect; };
		inline IGetPhysiologyActionObj * GetPhysiologyActionObjInterface() { return m_pGetPhysiologyActionObj; };
		//�������е����Ӷ���
		void CreateLineLinks(pugi::xml_node *pFrameElement);
		//ɾ���������ɵ����Ӷ��󣬲�ת�Ƶ���ʱ�б���
		void DeleteAllLineLinks();
	public:
		/*******************************************************************************/
		//���ܣ����ݲ��ԣ���������
		//������
		//      IXMLDOMNode *pFrameElement��
		//      eEventSign eEvent:
		//����ֵ:  �������ٴ����¼���FALSE);
		virtual bool OnFlowStrategy(pugi::xml_node *pFrameElement, eEventSign eEvent=ES_Normal) = 0;
		//���ݲ���ѡ������ת���������¸�����
		virtual CXLineLinkScenarioObj * SelectNextScenarioFromStrategy() = 0;
	};
}}
