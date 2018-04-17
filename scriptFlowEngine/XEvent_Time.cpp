#include ".\XEvent_Time.h"

#include "..\ElementParse\SEvent_Time.h"

#include "..\simulatorBase\EventIrp_ClockTime.h"


namespace jysoft { namespace flowEngine 
{
	CXEvent_Time::CXEvent_Time(void)
	{
		m_sImplementNum           = 0;
		m_pGetActionObjInterface  = NULL;
	}

	CXEvent_Time::~CXEvent_Time(void)
	{
	}

	bool CXEvent_Time::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXEvent_Time" )
		{
			return true;
		}
		return CXEventVirtual::isKindOf( strClassName );
	}

	/*******************************************************************************/
	// �������ƣ� GetEventCaption
	// ���ܣ�   ����������ʶ��
	// ������   
	// ����ֵ: 
	std::string CXEvent_Time::getEventCaption()
	{
		return CSEvent_Time::getEvent_Time_Caption();
	}

	/*******************************************************************************/
	// �������ƣ� Parse_EventFromXml
	// ���ܣ�   ����������������
	// ������   IXMLDOMNode *pXMLShapeNode:
	// ����ֵ: 
	bool CXEvent_Time::Parse_EventFromXml(pugi::xml_node *pXMLShapeNode, IGetPhysiologyActionObj *pGetActionObj)
	{
		bool  bSec = CSEvent_Time::explainParamsFromXML(pXMLShapeNode, &m_bTimeType, &m_sTimeValue);
		m_sImplementNum = 0;
		m_pGetActionObjInterface  = pGetActionObj;
		return bSec ;
	}

	/*******************************************************************************/
	// ���ܣ�   �Ƿ񴥷��趨���¼�
	// ������   
	// ����ֵ: ����(TRUE)��������(FALSE)
	bool CXEvent_Time::IsSatisfactionEvent()
	{
		if( m_sImplementNum > 0 )
		{
			return true;
		}
		return false;
	}

	/*******************************************************************************/
	// ���ܣ�   ����¼�������صļ�¼��Ϣ
	// ������   
	// ����ֵ: 
	void CXEvent_Time::ClearSatisfactionInfo()
	{
		m_sImplementNum = 0;
	}

	/*******************************************************************************/
	// ���ܣ�   �¼�����
	// ������   
	// ����ֵ: 
	void CXEvent_Time::DoHandleEventIrp(irp::CVirEventIrp  *pEventIrp)
	{
		if( pEventIrp->isKindOf( "CEventIrp_ClockTime" ) && !IsSatisfactionEvent())
		{
			irp::CEventIrp_ClockTime *pClockTimeIrp = (irp::CEventIrp_ClockTime *)pEventIrp;
			if( m_bTimeType == true )
			{
				//���ʱ���ж�
				simulator::CSymptom_FrameTime  *pFrameTime = m_pGetActionObjInterface->getFrameTimeSymptomPtr();
				if( pFrameTime != NULL && pFrameTime->GetValue_FrameTime() > m_sTimeValue )
				{
					m_sImplementNum += 1;
				}
			}
		}
	}
}}
