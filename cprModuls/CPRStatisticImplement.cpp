#include ".\CPRStatisticImplement.h"

#include "..\Common\ParseCPRData_Singleton.h"


using namespace boost;
BOOST_TRIBOOL_THIRD_STATE(freezed)
namespace jysoft{  namespace cpr {

	//=======================�̺߳���======================================
	//100����ʱ���߳�
	UINT CCPRStatisticImplement::ThrdCPRMicroSecondTimeFunc(LPVOID lpVoid)
	{
        /*CCPRStatisticImplement  *pCPRAggregate = (CCPRStatisticImplement *)lpVoid;
		::ResetEvent(pCPRAggregate->m_hThrdFinish);
		HANDLE  pHandles[2];
		pHandles[0] = pCPRAggregate->m_hThrdOut;
		pHandles[1] = pCPRAggregate->m_hRun;
		while(1)
		{
			DWORD dwRtn = ::WaitForMultipleObjects(2,pHandles,false,INFINITE);
			if(dwRtn == WAIT_OBJECT_0)
			{
				break;
			}
			HANDLE pHandles2[2];
			pHandles2[0] = pCPRAggregate->m_hThrdOut;
			pHandles2[1] = pCPRAggregate->m_hPause;
			dwRtn = ::WaitForMultipleObjects(2,pHandles2,false,100);
			switch(dwRtn)
			{
			case WAIT_TIMEOUT://����100����ʱ��
				{
					pCPRAggregate->increaseMillisecTimeTick();
					break;
				}
			case WAIT_OBJECT_0:
				{//�˳�
					::SetEvent(pCPRAggregate->m_hThrdFinish);
					return 0;
				}
			}
		}
        ::SetEvent(pCPRAggregate->m_hThrdFinish);*/
		return 0;
	}

	CCPRStatisticImplement::CCPRStatisticImplement(CPressureCollate *pPressureCollate, CBreathCollate *pBreathCollate)
	{
		cprResetStating    = true;
		bCPROperatoring    = false;
		pressureCollate   = pPressureCollate;
		breathCollate     = pBreathCollate;
		cycleNum   = boost::none;
		cprGradePec = boost::none;
		interruptTime = boost::none;
		pressurePeriodNum = 0;
		breathPeriodNum = 0;
		//-------------------------------------------------------------------------------------
		m_hRun        = NULL;//��ͣ
		m_hPause      = NULL;//��ͣ
		m_hThrdOut    = NULL;
		m_hThrdFinish = NULL;

		cprStatisticShowInterface  = NULL;
	}

	CCPRStatisticImplement::~CCPRStatisticImplement(void)
	{
		resetStatisticImpl();
		//�˳�ʱ���߳�
		if(m_hThrdOut)
		{
			::SetEvent(m_hThrdOut);
			::WaitForSingleObject(m_hThrdFinish,INFINITE);
		}
		//ɾ���¼����
		if(m_hRun)
			CloseHandle(m_hRun);
		if(m_hPause)
			CloseHandle(m_hPause);
		if(m_hThrdOut)
			CloseHandle(m_hThrdOut);
		if(m_hThrdFinish)
			CloseHandle(m_hThrdFinish);
		cprStatisticShowInterface  = NULL;
	}

	/*******************************************************************************/
	// �������ƣ� initialCPRStaticImpl
	// ���ܣ� ��ʼ�����ݣ�����ʱ���¼��߳�
	// ������   
	// ����ֵ:  
	void CCPRStatisticImplement::initialCPRStaticImpl(void)
	{
		bCPROperatoring    = false;
		cycleNum   = boost::none;
		cprGradePec = boost::none;
		interruptTime = boost::none;
		pressurePeriodNum = 0;
		breathPeriodNum = 0;
		//�����¼����
		m_hRun = ::CreateEvent(NULL,true,false,NULL);//��ͣ
		m_hPause = ::CreateEvent(NULL,true,true,NULL);//��ͣ
		m_hThrdOut = ::CreateEvent(NULL,true,false,NULL);
		m_hThrdFinish = ::CreateEvent(NULL,true,true,NULL);
		//�����߳�
        //::AfxBeginThread((AFX_THREADPROC)CCPRStatisticImplement::ThrdCPRMicroSecondTimeFunc,(LPVOID)this,THREAD_PRIORITY_ABOVE_NORMAL);
	}

	/*******************************************************************************/
	// �������ƣ� acceptAndStatisticImp
	// ���ܣ� ͨ�����յ��ķ�����ֵ�ж�CPR��������ȷ�Լ�����ԭ��
	// ������ cprData: ��ѹ/�����ķ���ֵ
	// ����ֵ:  CPR����״̬��ʾ
	void CCPRStatisticImplement::acceptAndStatisticImp(const _CPRData &cprData, _eCPRErrorSign  eErrorSign, UINT uLackNum, _eCPRErrorSign ePractiseExtendSign, boost::optional<int> cycleNewNum, _CPRManageState eState, CCPRConfigue* pCPRConfigue)
	{
		bool   bEnableRefresh  = false;
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		if( !cCPRParse.judgeCPRPhaseStartOrFinishOrder(cprData, indeterminate) )
		{
			if( cCPRParse.judgeCPRStartOrStopOrder(cprData, true) )
			{
				CPRStartHandle();
			}
			else if( cCPRParse.judgeCPRStartOrStopOrder(cprData, false) )
			{
				CPRStopHandle();
			}
			else
			{
				bEnableRefresh = true;
			}
			pressurePhaseStat.cprPhaseStatisticHandle(cprData, eErrorSign, uLackNum, ePractiseExtendSign, eState);
			breathPhaseStat.cprPhaseStatisticHandle(cprData, eErrorSign, uLackNum, ePractiseExtendSign, eState);
			//��ʾ�����־����
			cprGradePec = calcCPRGradePecent(eState, pCPRConfigue);
			//����ѭ��ͳ�ƣ���ѹ:������ѭ������
			calcCPRCycleStatistic(cprData, cycleNewNum);
			if( bEnableRefresh && cprStatisticShowInterface != NULL )
			{
				//���㲢ͬ������ͳ����ֵ
				calcAndUpdateStatisticValues( cprStatisticShowInterface, cCPRParse.isCPRScopeOrder(cprData, true) );
			}
		}
	}

	void CCPRStatisticImplement::loadCPRData(const _CPRData *lptrCPRData, int nLength)
	{
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		if( nLength > 0 && !cCPRParse.judgeCPRStartOrStopOrder(lptrCPRData[0]) && !cCPRParse.judgeCPRPhaseStartOrFinishOrder(lptrCPRData[0], indeterminate) )
		{
			//CPR�������ݴ����� 
			pressurePhaseStat.cprPressureRealTimeDataHandle(lptrCPRData, nLength, pressureCollate);
			breathPhaseStat.cprBreathRealTimeDataHandle(lptrCPRData, nLength, breathCollate);
		}
	}

	//��������
	void CCPRStatisticImplement::resetStatisticImpl(bool bUpdateStatistics/*=false*/)
	{
		//��ͣʱ���߳�
		if( m_hRun != NULL )
			::ResetEvent( m_hRun );
		if( m_hPause != NULL )
			::SetEvent( m_hPause );
		//-----------------------------------------------------------
		cprResetStating  = true;
		cycleNum   = boost::none;
		cprGradePec = boost::none;
		interruptTime = boost::none;
		pressurePeriodNum = 0;
		breathPeriodNum = 0;
		accumulateSec    = seconds(0);
		bCPROperatoring  = false;
		pressurePhaseStat.resetPhaseStatistic();
		breathPhaseStat.resetPhaseStatistic();
		//ͬ������ͳ����ֵ
		if( bUpdateStatistics && cprStatisticShowInterface )
		{
			calcAndUpdateStatisticValues( cprStatisticShowInterface, indeterminate );
		}
	}

	//�������¿�ʼͳ��
	void CCPRStatisticImplement::allowRestatisticImpl(const time_duration &scriptRunTime)
	{
		if( cprResetStating == true)
		{
			cprResetStating  = false;
			cprCycleInitiateTime = scriptRunTime;
			accumulateSec    = seconds(0);
			//ѭ��ͳ�ƣ���ѹ:������ѭ������
			cycleNum = boost::none;
			pressurePeriodNum = 0;
			breathPeriodNum = 0;
			//CPR�ܼ�Чֵ%
			cprGradePec = boost::none;
			interruptTime = boost::none;
		}
		else if( freezed(cprResetStating) )
		{
			//����״̬ʱ���ָ�ʱ�����
			cprResetStating = false;
		}
	}

	//����ʱ��
	void CCPRStatisticImplement::freezedStatisticImpl()
	{
		cprResetStating = freezed;
	}

	//ʱ���¼�������λ��1�룩
	void CCPRStatisticImplement::doHandleSecondClockTick()
	{
		if( !cprResetStating || freezed(cprResetStating) )
		{
			if( cprResetStating == false )
			{
				accumulateSec += seconds(1);
				//ÿһ��ʱ���¼�֪ͨ
				time_duration scriptRunTime = cprCycleInitiateTime + accumulateSec;
				pressurePhaseStat.increaseSecondTickNotify( scriptRunTime );
				breathPhaseStat.increaseSecondTickNotify( scriptRunTime );
			}
			else
			{
				pressurePhaseStat.increaseSecondTickNotify( cprCycleInitiateTime );
			}
			//�ж�ʱ������
			//if( interruptTime.is_initialized() )
			//{
			interruptTime = pressurePhaseStat.interruptTime.total_seconds();
			//}
			//����ʱ�䡢��ѹ�ж�ʱ��֪ͨ����ѹʱ��ռ��
			if( cprStatisticShowInterface != NULL )
			{
				cprStatisticShowInterface->OnUpdateCPRTimeStatic(accumulateSec.total_seconds(), interruptTime, boost::none);
			}
		}
	}

	//����100����ʱ���¼�����
	void CCPRStatisticImplement::increaseMillisecTimeTick()
	{
		//���ʱ�䴦������100���룩
		pressurePhaseStat.intervalTicktimeHandle(pressureCollate, breathCollate);
		breathPhaseStat.intervalTicktimeHandle(pressureCollate, breathCollate);
	}

	//CPR��ʼ����
	void CCPRStatisticImplement::CPRStartHandle()
	{
		//�����¼�����
		if( m_hPause != NULL )
			::ResetEvent( m_hPause );
		if( m_hRun != NULL )
			::SetEvent( m_hRun );
		//--------------------------------------------------------------------------
		bCPROperatoring = true;
	}

	//CPR��������
	void CCPRStatisticImplement::CPRStopHandle()
	{
		bCPROperatoring = false;
		//��ͣ�¼�����
		if( m_hRun != NULL )
			::ResetEvent( m_hRun );
		if( m_hPause != NULL )
			::SetEvent( m_hPause );
	}

	/*******************************************************************************/
	// �������ƣ� StartLinkCPRShowInterfaces
	// ���ܣ� ��ʼ����CPR��ʾ�������ʾ�ӿ�
	// ������ CCPRShowInterfacesAggregate *pShowAggregate:        
	// ����ֵ:  
	void CCPRStatisticImplement::startLinkCPRShowInterfaces(CCPRShowInterfacesAggregate *pShowAggregate)
	{
		CShowCPRStatisticUpdateInterface *pShowCPRStatisticInterface = pShowAggregate->Get_ShowCPRStatisticUpdateInterface();
		if( cprStatisticShowInterface == NULL )
		{
			cprStatisticShowInterface = pShowCPRStatisticInterface;
		}
		else if( pShowCPRStatisticInterface != NULL )
		{
			cprStatisticShowInterface->SetNextInterfacePtr( pShowCPRStatisticInterface );
		}
		if( pShowCPRStatisticInterface != NULL )
		{
			pShowCPRStatisticInterface->LinkUpdateShow();
			//ͬ������ͳ����ֵ
			calcAndUpdateStatisticValues( pShowCPRStatisticInterface, indeterminate);
		}
		//�趨CPR����ϸ����ʾ�ӿ�
		CShowCPRActUpdateInterface  *pShowCPRDetailActInterface = pShowAggregate->Get_ShowCPRDetailActUpdateInterface();
		pressurePhaseStat.setShowCPRDetailActInterfacePtr( pShowCPRDetailActInterface );
		breathPhaseStat.setShowCPRDetailActInterfacePtr( pShowCPRDetailActInterface );
	}

	/*******************************************************************************/
	// �������ƣ� UnLinkCPRShowInterfaces
	// ���ܣ� �Ͽ�CPR��ʾ�������ʾ�ӿ�
	// ������ CCPRShowInterfacesAggregate *pShowAggregate:        
	// ����ֵ:
	void CCPRStatisticImplement::unLinkCPRShowInterfaces(CCPRShowInterfacesAggregate *pShowAggregate)
	{
		CShowCPRStatisticUpdateInterface *pShowCPRStatisticInterface = pShowAggregate->Get_ShowCPRStatisticUpdateInterface();
		if( pShowCPRStatisticInterface != NULL )
		{
			cprStatisticShowInterface = (CShowCPRStatisticUpdateInterface *)IBedirecteLinksVir::RemoveInterfacePtr(cprStatisticShowInterface, pShowCPRStatisticInterface);
			pShowCPRStatisticInterface->UnLinkUpdateShow();
		}
		//�Ƴ�CPR����ϸ����ʾ�ӿ�
		CShowCPRActUpdateInterface  *pShowCPRDetailActInterface = pShowAggregate->Get_ShowCPRDetailActUpdateInterface();
		pressurePhaseStat.setShowCPRDetailActInterfacePtr( pShowCPRDetailActInterface );
		breathPhaseStat.setShowCPRDetailActInterfacePtr( pShowCPRDetailActInterface );
	}

	//���ý׶�CPRͳ����־�ӿ�
	void  CCPRStatisticImplement::setPhaseCPRLogInterfacePtr(log::COpLogInterface *pLogInterface)
	{
		pressurePhaseStat.setLogInterfacePtr( pLogInterface );
		breathPhaseStat.setLogInterfacePtr( pLogInterface );
	}

	/*******************************************************************************/
	// �������ƣ� StatisticOtherCPRValues
	// ���ܣ� ͳ������������
	// ������ DWORD  dwData:        ��ѹ/�����ķ���ֵ
	//        _eCPRErrorSign eSign: CPR����״̬��ʾ
	// ����ֵ:  
	void CCPRStatisticImplement::statisticOtherCPRValues(const _CPRData &cprData, _eCPRErrorSign eSign)
	{

	}

	//���㲢ͬ������ͳ����ֵ
	//bScopeJudge�� true:��ѹ���ȣ�false:�������ȣ� unknown:����ָ��
	void CCPRStatisticImplement::calcAndUpdateStatisticValues(CShowCPRStatisticUpdateInterface *pShowInterface, tribool bScopeJudge)
	{
		short nBSumRight = breathPhaseStat.getBreathSumRightNum();
		short nBSumError = breathPhaseStat.getBreathSumErrorsNum();
		short nPSumRight = pressurePhaseStat.getPressureSumRightNum();
		short nPSumError = pressurePhaseStat.getPressureSumErrorsNum();
		pShowInterface->OnUpdateStatistic(cprGradePec, nPSumRight, nPSumError, nBSumRight, nBSumError);
		//ѭ��ͳ�ƣ���ѹ:������ѭ������
		pShowInterface->OnUpdateCPRCycle(pressurePeriodNum, breathPeriodNum, cycleNum);
		//��ѹ
		if( bScopeJudge == true || indeterminate(bScopeJudge) )
		{
			//��ѹλ��ͳ��
			short pos_low, pos_high, pos_left, pos_Right;
			pressurePhaseStat.getPressurePosErrorNum(&pos_low, &pos_high, &pos_left, &pos_Right);
			pShowInterface->OnUpdatePositionStatic(pos_low, pos_high, pos_left, pos_Right);

			//��ѹͳ�ƣ���ȷ�ٷֱȡ��ж�ʱ�䡢ƽ����ȡ�ƽ��Ƶ�ʡ�λ����ȷ�ٷֱȡ��ͷ���ȷ�ٷֱȡ���ѹ���󡢰�ѹ��С...

		}
		//����
		if( bScopeJudge == false || indeterminate(bScopeJudge) )
		{
			//��θͳ��
			short sInStomachNum = breathPhaseStat.getBreathInStomachNum();
			pShowInterface->OnUpdateInStomachNumber( sInStomachNum );
			//����ͳ�ƣ���ȷ�ٷֱȡ�ƽ����������ƽ������Ƶ�ʡ��ܴ����������󡢹�С��ͨ���೤��ͨ�����...

		}
		if( indeterminate(bScopeJudge) )
		{
			//����ʱ�䡢��ѹ�ж�ʱ��֪ͨ����ѹʱ��ռ��...
			pShowInterface->OnUpdateCPRTimeStatic(accumulateSec.total_seconds(), interruptTime, boost::none);
		}
	}

	//���㲢���ذ�ѹ��ֵ(%)
	boost::optional<int>  CCPRStatisticImplement::calcPressureGradePecent()
	{
		boost::optional<int> gradePec = boost::none;
		if( pressurePhaseStat.getPressureSumNum() != 0 )
		{
			gradePec = 100 * pressurePhaseStat.getPressureSumRightNum() / pressurePhaseStat.getPressureSumNum();
		}
		return gradePec;
	}

	//���㲢���ذ�ѹ�ͷ���ȷ��ֵ(%)
	boost::optional<int>  CCPRStatisticImplement::calcPressureReleaseGradePecent()
	{
		boost::optional<int> gradePec = boost::none;
		if( pressurePhaseStat.getPressureSumNum() != 0 )
		{
			gradePec = 100 - 100 * pressurePhaseStat.getPressureSumIncomplete() / pressurePhaseStat.getPressureSumNum();
		}
		return gradePec;
	}

	//���㲢���ذ�ѹλ����ȷ��ֵ(%)
	boost::optional<int>  CCPRStatisticImplement::calcPressurePosGradePecent()
	{
		boost::optional<int> gradePec = boost::none;
		if( pressurePhaseStat.getPressureSumNum() != 0 )
		{
			gradePec = 100 - 100 * pressurePhaseStat.getPressurePosErrorNum() / pressurePhaseStat.getPressureSumNum();
		}
		return gradePec;
	}

	//������ȷ��ѹ��Χ�ٷֱ�
	boost::optional<int>  CCPRStatisticImplement::calcPressureDepthRightPecent()
	{
		boost::optional<int> rightPec = boost::none;
		if( pressurePhaseStat.getPressureSumNum() > 0 )
		{
			rightPec = 100 * pressurePhaseStat.getPressureDepthRightNum() / pressurePhaseStat.getPressureSumNum();
		}
		return rightPec;
	}

	//���㲢���ش�����ֵ(%)
	boost::optional<int>  CCPRStatisticImplement::calcBreathGradePecent()
	{
		boost::optional<int> gradePec = boost::none;
		if( breathPhaseStat.getBreathSumNum() != 0 )
		{
			gradePec = 100 * breathPhaseStat.getBreathSumRightNum() / breathPhaseStat.getBreathSumNum();
		}
		return gradePec;
	}

	//���㲢�����ܷ�ֵ(%)
	boost::optional<int>  CCPRStatisticImplement::calcCPRGradePecent(_CPRManageState eState, CCPRConfigue* pCPRConfigue)
	{
		short  uPressureSumNum = pressurePhaseStat.getPressureSumNum();
		short  uBreathSumNum = breathPhaseStat.getBreathSumNum();
		boost::optional<int>  cprGradePec = boost::none;
		if( uPressureSumNum != 0  || uBreathSumNum != 0 )
		{
			//��ѹ��Чֵ(%)
			boost::optional<int>  PGradePec = calcPressureGradePecent();
			//������Чֵ(%)
			boost::optional<int>  BGradePec = calcBreathGradePecent();
			//����CPR��Чֵ(%): ��ѹ/����ռ�ȣ�3:1
			switch( eState )
			{
			case aCPRPopularMode:
			case aCPRPractiseMode:
				{
					int  nRulePSum  = 150;
					int  nRuleBSum = 10;
					if( pCPRConfigue->isSpecialityMemberOp() )
					{
						if( !pCPRConfigue->isFiveCycleRule() )
						{
							nRulePSum = 90;
							nRuleBSum = 6;
						}
					}
					else
					{
						nRuleBSum = 0;
						nRulePSum = pCPRConfigue->getSumPressureNumber();
					}
					float  fPNumAcc = pressurePhaseStat.getPressureSumNum() * 1.0f / nRulePSum;
					float  fBNumAcc =  nRuleBSum == 0 ? 1.0f : (breathPhaseStat.getBreathSumNum() * 1.0f / nRuleBSum);
					//����: ��ѹռ��*��ѹ��Чֵ*0.75 + ����ռ��*������Чֵ*0.25
					int nPGradePec = PGradePec.is_initialized() ? PGradePec.get() : 0;
					int nBGradePec = BGradePec.is_initialized() ? BGradePec.get() : 0;
					if( pCPRConfigue->isSpecialityMemberOp() && eState == aCPRPractiseMode )
					{
						cprGradePec = int((fPNumAcc >= 1.0f ? 1.0f : fPNumAcc) * nPGradePec * 0.75 + (fBNumAcc >= 1.0f ? 1.0f : fBNumAcc) * nBGradePec * 0.25);
					}
					else
					{
						cprGradePec = int((fPNumAcc >= 1.0f ? 1.0f : fPNumAcc) * nPGradePec);
					}
					break;
				}
			}
		}
		return cprGradePec;
	}

	//����ѭ��ͳ�ƣ���ѹ:������ѭ������
	void CCPRStatisticImplement::calcCPRCycleStatistic(const _CPRData &cprData, boost::optional<int> cycleNewNum)
	{
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		//����ѭ��ͳ��
		if( cycleNewNum == boost::none || cycleNum == boost::none || cycleNum == cycleNewNum )
		{
			if( cCPRParse.isCPRScopeOrder( cprData, true) )
			{
				pressurePeriodNum += 1;
			}
			else if( cCPRParse.isCPRScopeOrder( cprData, false) )
			{
				breathPeriodNum += 1;
			}
			if( cycleNewNum != boost::none )
			{
				cycleNum = cycleNewNum;
			}
		}
		else
		{
			if( cCPRParse.isCPRScopeOrder( cprData, true) )
			{
				pressurePeriodNum = 1;
				breathPeriodNum = 0;
			}
			else if( cCPRParse.isCPRScopeOrder( cprData, false) )
			{
				breathPeriodNum = 1;
				pressurePeriodNum = 0;
			}
			cycleNum = cycleNewNum;
		}
	}

	//��ѹƽ��Ƶ��
	int CCPRStatisticImplement::GetPressureRate()
	{
		return pressurePhaseStat.getAverageRate();
	}
	//ƽ����ѹ����  nSumSecond: �ܲ���ʱ��(��)
	int CCPRStatisticImplement::GetPressureAverageCount(int nOpSumSecond)
	{
		int  nSumNumber = pressurePhaseStat.getPressureSumNum();
		return nOpSumSecond > 0 ? int( nSumNumber * 60.0f / nOpSumSecond) : 0;
	}

	int CCPRStatisticImplement::GetPressureAverageDepth()
	{
		return pressurePhaseStat.getAverageDepth();
	}

	int CCPRStatisticImplement::GetPressurePosErrorNum()
	{
		return pressurePhaseStat.getPressurePosErrorNum();
	}

	int CCPRStatisticImplement::GetPressureSumRightNum()
	{
		return pressurePhaseStat.getPressureSumRightNum();
	}

	int CCPRStatisticImplement::GetPressureSumIncomplete()
	{
		return pressurePhaseStat.getPressureSumIncomplete();
	}

	int CCPRStatisticImplement::GetPressureSumErrorsNum()
	{
		return pressurePhaseStat.getPressureSumErrorsNum();
	}

	int CCPRStatisticImplement::GetPressureOverNum()
	{
		return pressurePhaseStat.getPressureOverNum();
	}
	//��ѹ��С
	int CCPRStatisticImplement::GetPressureLackNum()
	{
		return pressurePhaseStat.getPressureLackNum();
	}

	//����
	int CCPRStatisticImplement::GetBreathAverageVol()
	{
		return breathPhaseStat.getAverageVolume();
	}

	int CCPRStatisticImplement::GetBreathAverageVolInMinute(int nOpSumSecond)
	{
		int nAverageVol = GetBreathAverageVol();
		return nAverageVol * GetBreathAverageCountInMinute( nOpSumSecond );
	}

	int CCPRStatisticImplement::GetBreathAverageCountInMinute(int nOpSumSecond)
	{
		int nSumNumber = breathPhaseStat.getBreathSumNum();
		return nOpSumSecond > 0 ? int( nSumNumber * 60.0f / nOpSumSecond) : 0;
	}

	int CCPRStatisticImplement::GetBreathSumRightNum()
	{
		return breathPhaseStat.getBreathSumRightNum();
	}

	int CCPRStatisticImplement::GetBreathSumErrorsNum()
	{
		return breathPhaseStat.getBreathSumErrorsNum();
	}

	int CCPRStatisticImplement::GetBreathOverNum()
	{
		return breathPhaseStat.getBreathOverNum();
	}

	int CCPRStatisticImplement::GetBreathLackNum()
	{
		return breathPhaseStat.getBreathLackNum();
	}

	int CCPRStatisticImplement::GetBreathInStomachNum()
	{
		return breathPhaseStat.getBreathInStomachNum();
	}

	int CCPRStatisticImplement::GetBreathPipeCloseNum()
	{
		return breathPhaseStat.getBreathPipeCloseNum();
	}
}}
