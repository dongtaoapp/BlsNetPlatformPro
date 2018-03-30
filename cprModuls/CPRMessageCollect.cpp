#include ".\CPRMessageCollect.h"

#include "..\Common\ParseCPRData_Singleton.h"

#include "..\SimulatorBase\CPRStatIrp.h"
#include "..\SimulatorBase\RealTimeDataIrp.h"
#include "..\SimulatorBase\EventIrp_ClockTime.h"

namespace jysoft{  namespace cpr 
{

	CCPRMessageCollect::CCPRMessageCollect(void)
	{
		m_pCPRConfigue        = NULL;
		m_pEventLogInterface  = NULL;
		m_pCPRJudgeOp   = new CCPRSimulateJudgeOp( aCPRPractiseMode );
		m_pStatisticImpl = new CCPRStatisticImplement(&m_cPressureCollate, &m_cBreathCollate);
		//--------------------------------------------------------------------
		m_pShowCPRRealTimeInteface   = NULL;
		m_pShowCPRDetailActInterface = NULL;
		m_pTransportUpOrderInterface = NULL;

		m_bEnableCompleteJudge       = false;
		m_eNextPhaseCPRState         = eNoneDefine;
	}


	CCPRMessageCollect::~CCPRMessageCollect(void)
	{
		delete  m_pCPRJudgeOp;
		delete  m_pStatisticImpl;
		//----------------------------------------------------
		m_pShowCPRRealTimeInteface  = NULL;
		m_pCPRConfigue              = NULL;
		m_pEventLogInterface        = NULL;
	}

	/*******************************************************************************/
	//���ܣ���������ת��IRP����
	//������
	//      CVirtualIrp *pCurrIrp��
	//����ֵ:  �������ٴ���false);
	bool CCPRMessageCollect::doHandleRealTimeDataIrpOp(irp::CVirtualIrp *pCurrIrp)
	{
        if( !pCurrIrp->isKindOf( "CRealTimeDataIrp" ) )
			return true;
		irp::CRealTimeDataIrp *pRealTimeIrp = (irp::CRealTimeDataIrp *)pCurrIrp;
		//CPR�����ж�
		const CParseCPRData_Singleton *pCPRParse = &CParseCPRData_Singleton::get_const_instance();
		for (int nStep = 0; nStep < pRealTimeIrp->m_nLength; ++nStep)
		{
			const _CPRData &cprData = pRealTimeIrp->m_ptrCPRDatas[nStep];
			if( pCPRParse->isCPROrder(cprData) )
			{
				_eCPRErrorSign eErrorSign = doCPROrderHandle( cprData );
				//��ʾ�����ʾ
				if( m_pShowCPRRealTimeInteface != NULL )
				{
					m_pShowCPRRealTimeInteface->OnAddCPRErrorSign( eErrorSign );
				}
				if( pCPRParse->judgeCPRStartOrStopOrder(cprData, true) )
				{
					//������ʾ��
					startTickSound();
					if( !m_pCPRJudgeOp->isCompleteCurrentCPR() )
					{
						m_bEnableCompleteJudge  = true;
					}
				}
				else if( pCPRParse->judgeCPRStartOrStopOrder(cprData, false) )
				{
					//�ر�������ʾ
					stopTickSound();
				}
				if( m_pCPRJudgeOp->isCompleteCurrentCPR() && m_bEnableCompleteJudge )
				{
					//CPR������ɴ���
					doCPRCompleteHandle();
					m_bEnableCompleteJudge  = false;
				}
			}
		}
		m_pStatisticImpl->loadCPRData(pRealTimeIrp->m_ptrCPRDatas, pRealTimeIrp->m_nLength);
		//ʵʱCPR����������ʾ
		if( m_pShowCPRRealTimeInteface != NULL )
		{
			m_pShowCPRRealTimeInteface->OnLoadCPRSample(pRealTimeIrp->m_ptrCPRDatas, pRealTimeIrp->m_nLength);
		}
		return true;
	}

	/*******************************************************************************/
	//���ܣ�����ʱ���¼�IRP����
	//������
	//      CVirtualIrp *pCurrIrp��
	//����ֵ:  �������ٴ���FALSE);
	bool CCPRMessageCollect::doHandleClockIrpOp(irp::CVirtualIrp *pCurrIrp)
	{
        if( pCurrIrp && pCurrIrp->isKindOf( "CEventIrp_ClockTime" ) )
		{
			irp::CEventIrp_ClockTime *pClockTimeIrp = (irp::CEventIrp_ClockTime *)pCurrIrp;
			//ʱ�����
			m_pStatisticImpl->doHandleSecondClockTick();
		}
		return true;
	}

	/*******************************************************************************/
	// �������ƣ� initialCPR
	// ���ܣ�    ��ʼ��
	// ������  
	// ����ֵ:  
	void CCPRMessageCollect::initialCPR(CCPRConfigue *pCPRConfigue,  transLayer::ITransportOrderIrpToUp *pTransUpInterface, log::COpLogInterface *pEventLogInterface/*=NULL*/)
	{
		m_pTransportUpOrderInterface  = pTransUpInterface;
		m_pEventLogInterface          = pEventLogInterface;
		//��ȡCPRϵͳ����
		m_pCPRConfigue                = pCPRConfigue;
		m_cPressureCollate.changeJudgeRange(pCPRConfigue->getOverPressureDepth(), pCPRConfigue->getLowerPressureDepth());
		m_cBreathCollate.changeJudgeRange( pCPRConfigue->getOverBreathVolume(), pCPRConfigue->getLowerBreathVolume() );
		//����ʱ���߳�
		m_pStatisticImpl->setPhaseCPRLogInterfacePtr(pEventLogInterface);
		m_pStatisticImpl->initialCPRStaticImpl( );
	}

	/*******************************************************************************/
	// �������ƣ� resetCPROperatorMessage
	// ���ܣ�    ����CPR����ͳ��
	// ������  
	// ����ֵ:  
	void CCPRMessageCollect::resetCPROperatorMessage(_CPRManageState  eCPRState)
	{
		m_bEnableCompleteJudge  = false;
		//����CPR�����ж���
		doCPROperatorFinishHandle( eCPRState );
		//��������
		m_pStatisticImpl->resetStatisticImpl();
	}

	/*******************************************************************************/
	// �������ƣ� restatisticByDefibrEventHandle
	// ���ܣ�    �����¼���������CPR����ͳ��
	// ������  
	// ����ֵ:  
	void CCPRMessageCollect::restatisticByDefibrEventHandle()
	{
		////���浱ǰ��ͳ��....

		//�������¿�ʼͳ��
		m_pStatisticImpl->allowRestatisticImpl(seconds(getScriptRunTime()));
		//����CPR�����ж���
		doCPROperatorFinishHandle( m_eNextPhaseCPRState );
		m_bEnableCompleteJudge  = true;
	}

	/*******************************************************************************/
	// �������ƣ� StartLinkCPRShowInterfaces
	// ���ܣ� ��ʼ����CPR��ʾ�������ʾ�ӿ�
	// ������ CCPRShowInterfacesAggregate *pShowAggregate:        
	// ����ֵ:  
	void CCPRMessageCollect::startLinkCPRShowInterfaces(CCPRShowInterfacesAggregate *pShowAggregate)
	{
		m_pShowCPRRealTimeInteface = pShowAggregate->Get_ShowCPRRealTimeUpdateInterface();
		if( m_pShowCPRRealTimeInteface != NULL )
		{
			m_pShowCPRRealTimeInteface->LinkUpdateShow();
		}
		//�趨CPR����ϸ����ʾ�ӿ�
		CShowCPRActUpdateInterface  *pShowCPRDetailActInterface = pShowAggregate->Get_ShowCPRDetailActUpdateInterface();
		if( m_pShowCPRDetailActInterface == NULL )
		{
			m_pShowCPRDetailActInterface = pShowCPRDetailActInterface;
		}
		else if( pShowCPRDetailActInterface != NULL )
		{
			m_pShowCPRDetailActInterface->SetNextInterfacePtr( pShowCPRDetailActInterface );
		}
		if( pShowCPRDetailActInterface != NULL )
		{
			pShowCPRDetailActInterface->LinkUpdateShow();
		}
		m_pStatisticImpl->startLinkCPRShowInterfaces( pShowAggregate );
	}

	/*******************************************************************************/
	// �������ƣ� UnLinkCPRShowInterfaces
	// ���ܣ� �Ͽ�CPR��ʾ�������ʾ�ӿ�
	// ������ CCPRShowInterfacesAggregate *pShowAggregate:        
	// ����ֵ:
	void CCPRMessageCollect::unLinkCPRShowInterfaces(CCPRShowInterfacesAggregate *pShowAggregate)
	{
		CCPRRealTimeUpdateInterface *pShowCPRRealTimeInterface = pShowAggregate->Get_ShowCPRRealTimeUpdateInterface();
		if( m_pShowCPRRealTimeInteface && pShowCPRRealTimeInterface )
		{
			m_pShowCPRRealTimeInteface = (CCPRRealTimeUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowCPRRealTimeInteface, pShowCPRRealTimeInterface);
			//�Ͽ���ʾ����
			pShowCPRRealTimeInterface->UnLinkUpdateShow();
		}
		m_pStatisticImpl->unLinkCPRShowInterfaces( pShowAggregate );
		//�Ƴ�CPR����ϸ����ʾ�ӿ�
		CShowCPRActUpdateInterface  *pShowCPRDetailActInterface = pShowAggregate->Get_ShowCPRDetailActUpdateInterface();
		if( pShowCPRDetailActInterface != NULL )
		{
			m_pShowCPRDetailActInterface = (CShowCPRActUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(m_pShowCPRDetailActInterface, pShowCPRDetailActInterface);
			pShowCPRDetailActInterface->UnLinkUpdateShow();
		}
	}

	//CPR����ָ���
	_eCPRErrorSign CCPRMessageCollect::doCPROrderHandle(const _CPRData &cprOrder)
	{
		_eCPRErrorSign eSign  = CS_None;
		_eCPRErrorSign ePractiseExtendSign  = CS_None;
		//���ݷ���ָ��ж�CPR����ͳ��
        short uLackNum  = 0;
		boost::optional<int> cycleNum = m_pStatisticImpl->getCPRCycleNum();
		eSign = m_pCPRJudgeOp->judgeCPRData(cprOrder, &m_cPressureCollate, &m_cBreathCollate, /*out*/uLackNum, /*out*/ePractiseExtendSign, /*in,out*/cycleNum);
		m_pStatisticImpl->acceptAndStatisticImp(cprOrder, eSign, uLackNum, ePractiseExtendSign, cycleNum, m_pCPRJudgeOp->get_eCPRState(), m_pCPRConfigue);
		return eSign;
	}

	//CPR������ɴ���
	void CCPRMessageCollect::doCPRCompleteHandle()
	{
		_CPRManageState   eCPRMode = m_pCPRJudgeOp->get_eCPRState();
		//1. �ϴ����ѭ���������ָ��[ע��/2:    �ڱ�׼ģʽ��ʵսģʽ�£����5��ѭ����CPR����]
		if( m_pTransportUpOrderInterface != NULL )
		{	
			irp::CCPRStatIrp  *pCPRStatIrp = irp::CCPRStatIrp::CreateEvent_CPRIrp(eCPRMode, 2);
			m_pTransportUpOrderInterface->OnTranslateUpIrpNoNetwork( pCPRStatIrp );
		}
		//2. ��ʾ����
		if( m_pShowCPRDetailActInterface != NULL )
		{
			m_pShowCPRDetailActInterface->OnFiveCycleCompleteAct();
		}
	}

	//CPR������������
	void CCPRMessageCollect::doCPROperatorFinishHandle(_CPRManageState  eCPRState)
	{
		//�ж��Ƿ���Ҫ�趨�´�CPR�����Ĺ���[ע��m_eNextPhaseCPRStateΪeNoneDefine���޸Ĺ���]
		if( eCPRState != eNoneDefine )
		{
			//����ͳ�Ƽ�¼
			m_pStatisticImpl->resetStatisticImpl(true);
			///�����´�CPR�����Ĺ���
			_CPRRuleStruct *pCPRRule  = NULL;
			switch( eCPRState )
			{
			case aCPRPopularMode:
			case aCPRPractiseMode:
				{
					pCPRRule  = new _CPRRuleStruct();
					if( m_pCPRConfigue->isSpecialityMemberOp() )
					{
						pCPRRule->setDefaultCPRRule( m_pCPRConfigue->isFiveCycleRule() ? 5 : 3 );
					}
					else
					{
						//��ѹ����
						pCPRRule->setOnlyPressure( m_pCPRConfigue->getSumPressureNumber() );
					}
					break;
				}
			default:
				{
					pCPRRule  = NULL;
					break;
				}
			}
			m_pCPRJudgeOp->resetSimulateParam( eCPRState, pCPRRule );
			m_eNextPhaseCPRState  = eNoneDefine;
		}
		else 
		{
			m_pCPRJudgeOp->resetSimulateParam();
			m_pStatisticImpl->resetStatisticImpl();
		}
	}

	//�����½׶ε�CPR����ģʽ
	void CCPRMessageCollect::setNextPhaseCPROperatorMode(_CPRManageState  eCPRState)
	{
		if( m_pStatisticImpl->isCPROperatoring() )
		{
			m_eNextPhaseCPRState  = eCPRState;
		}
		else
		{
			doCPROperatorFinishHandle(eCPRState);
		}
	}

	/*******************************************************************************/
	// �������ƣ� DoModifyCPRJudgeRange
	// ���ܣ� �޸��ķθ��ղ���ʱ�������밴ѹ�ķ�Χ
	// ������     
	// ����ֵ:  
	void CCPRMessageCollect::modifyCPRJudgeRange(int nLowerDepth, int nOverDepth, int nLowerVolume, int nOverVolume)
	{
		m_cPressureCollate.changeJudgeRange( nOverDepth,  nLowerDepth);
		m_cBreathCollate.changeJudgeRange( nOverVolume, nLowerVolume );
	}

	//�����δ���
	void CCPRMessageCollect::startTickSound()
	{
		
	}

	//ֹͣ�δ���
	void CCPRMessageCollect::stopTickSound()
	{
		
	}

	//���ؽű���ǰʱ��
	UINT CCPRMessageCollect::getScriptRunTime()
	{
		UINT  uScriptTime = 0;
		if( m_pEventLogInterface != 0 )
		{
			uScriptTime = m_pEventLogInterface->GetScriptRunTime();
		}
		return uScriptTime;
	}

}}
