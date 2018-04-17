#include ".\XEvent_CPR.h"

#include "..\ElementParse\SEvent_CPR.h"

#include "..\SimulatorBase\EventIrp_ClockTime.h"
#include "..\SimulatorBase\CPRStatIrp.h"


namespace jysoft { namespace flowEngine 
{
	CXEvent_CPR::CXEvent_CPR(void)
	{
		m_sImplementNum        = 0;
		m_sAccumulateTime      = 0;
		m_pCPMessageCollect    = NULL;
	}

	CXEvent_CPR::~CXEvent_CPR(void)
	{
		m_pCPMessageCollect    = NULL;
	}

	bool CXEvent_CPR::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXEvent_CPR" )
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
	std::string CXEvent_CPR::getEventCaption()
	{
		return CSEvent_CPR::getEvent_CPR_Caption();
	}
	/*******************************************************************************/
	// �������ƣ� Parse_EventFromXml
	// ���ܣ�   ����������������
	// ������   IXMLDOMNode *pXMLShapeNode:
	// ����ֵ: 
	bool CXEvent_CPR::Parse_EventFromXml(pugi::xml_node *pXMLShapeNode, IGetPhysiologyActionObj *pGetActionObj)
	{
		m_sImplementNum  = 0;
		SetEnableCaculateTime( false, true);
		bool bSec = CSEvent_CPR::explainParamsFromXML(pXMLShapeNode, &m_sOpMode, &m_sAccumulateTime, &m_sAccumulateNum);
		//��ȡCPR��Ϣ����ָ��
		m_pCPMessageCollect   = pGetActionObj->Get_CPRMessageCollectPtr();
		return bSec ;
	}

	/*******************************************************************************/
	// ���ܣ�   �Ƿ񴥷��趨���¼�
	// ������   
	// ����ֵ: ����(TRUE)��������(FALSE)
	bool CXEvent_CPR::IsSatisfactionEvent()
	{
		if( m_sAccumulateNum <= m_sImplementNum )
		{
			return true;
		}
		return false;
	}

	/*******************************************************************************/
	// ���ܣ�   ����¼�������ص���Ϣ
	// ������   
	// ����ֵ: 
	void CXEvent_CPR::ClearSatisfactionInfo()
	{
		m_sImplementNum = 0;
		SetEnableCaculateTime( false, true );
	}

	/*******************************************************************************/
	// ���ܣ�   �¼�����
	// ������   
	// ����ֵ: 
	void CXEvent_CPR::DoHandleEventIrp(irp::CVirEventIrp  *pEventIrp)
	{
		if( pEventIrp->isKindOf( "CEventIrp_ClockTime" ) )
		{
			irp::CEventIrp_ClockTime *pClockTimeIrp = (irp::CEventIrp_ClockTime *)pEventIrp;
			//�����ۻ�ʱ��
			AddCaculateTime( pClockTimeIrp->GetValue_ClockEvent() );
		}
		else if( pEventIrp->isKindOf( "CCPRStatIrp" ) )
		{
			irp::CCPRStatIrp *pCPRStatIrp = (irp::CCPRStatIrp *)pEventIrp;
			_CPRManageState  eCPRMode = pCPRStatIrp->Get_eCPRMode();
			//CPR�¼�
			int     nStat  = pCPRStatIrp->GetValue_Stat();
			if( (m_sOpMode == 1 && nStat == 1) || (m_sOpMode == 0 && nStat == 0) )
			{
				m_sImplementNum += 1;
			}
			else if( m_sOpMode == 2 && nStat == 1)
			{
				m_sImplementNum += 1;
			}
			else if( m_sOpMode == 3 && (eCPRMode != eNoneDefine) && nStat == 2 )
			{
				m_sImplementNum += 1;
			}
		}
	}

	//�����ۻ�ʱ��
	void CXEvent_CPR::AddCaculateTime(short sSecond)
	{
		if( m_bEnableCaculateTime )
		{
			m_sCaculateTimeValue += sSecond;
		}
	}

	//�����Ƿ��ܽ����ۻ�ʱ�����
	void CXEvent_CPR::SetEnableCaculateTime(bool bEnable, bool bClearCalcTime)
	{
		m_bEnableCaculateTime  = bEnable;
		if( bClearCalcTime )
		{
			m_sCaculateTimeValue   = 0;
		}
	}
	
}}
