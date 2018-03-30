#include ".\CPRPhaseStatistic.h"
#include <boost/foreach.hpp>

#include "..\Common\ParseCPRData_Singleton.h"


using namespace boost;
namespace jysoft{  namespace cpr {

	ICPRPhaseStatistic::ICPRPhaseStatistic(void)
	{
		delayTime                  = 0;
		buffTimeEvent              = 0;
		transEvent                 = 0;
		loopBuff.InitializeBuff(30);
		
		m_pEventLogInterface = NULL;
		actCPRDetailShowInterface  = NULL;
	}


	ICPRPhaseStatistic::~ICPRPhaseStatistic(void)
	{
		resetPhaseStatistic();
	}

	//��������
	void ICPRPhaseStatistic::resetPhaseStatistic()
	{
		BOOST_FOREACH(auto x, phaseStatSegs)
		{
			delete x;
		}
		phaseStatSegs.clear();
		loopBuff.Empty();
		delayTime      = 0;
		buffTimeEvent  = 0;
		transEvent     = 0;
	}

	//������ʾ�ӿ�
	void ICPRPhaseStatistic::setShowCPRDetailActInterfacePtr(CShowCPRActUpdateInterface *pInterface)
	{
		if( pInterface != NULL )
		{
			IBedirecteLinksVir *pHeadInterface = pInterface->GetHeaderInterfacePtr();
			while( pHeadInterface )
			{
				if(pHeadInterface != actCPRDetailShowInterface && pHeadInterface->isKindOf("CShowCPRActUpdateInterface") )
				{
					actCPRDetailShowInterface = (CShowCPRActUpdateInterface *)pHeadInterface;
					return;
				}
				pHeadInterface = pHeadInterface->GetNextInterfacePtr();
			}
			actCPRDetailShowInterface = NULL;
		}
	}

	//-------------------------------------------------------------------------------------------
	////��ѹ�׶���
	CPressurePhaseStatistic::CPressurePhaseStatistic()
	{

	}

	CPressurePhaseStatistic::~CPressurePhaseStatistic()
	{

	}

	/*******************************************************************************/
	// �������ƣ� cprPressureRealTimeDataHandle
	// ���ܣ� CPR�������ݴ����� 
	// ������ 
	// ����ֵ:  
	void CPressurePhaseStatistic::cprPressureRealTimeDataHandle(const _CPRData *lptrCPRDatas, int nLength, const CPressureCollate *pPressureColl)
	{//��ѹ���ȣ�0x2X
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		for (int nStep = 0; nStep < nLength; ++nStep)
		{
			if( cCPRParse.isCPRScopeOrder(lptrCPRDatas[nStep], true) && pPressureColl->getLogicalValue(lptrCPRDatas[nStep]) > 2 )
			{//С��2mmʱҲ���޸�m_iDelayTime
				delayTime = 0;
			}
		}
		if(buffTimeEvent == 0 && transEvent == 0)
		{
			if( !cCPRParse.isCPRScopeOrder(lptrCPRDatas[0], true) )
				return;
		}
		loopBuff.WriteData(lptrCPRDatas, nLength);
		if(transEvent == 0 && buffTimeEvent == 0)
		{
			buffTimeEvent = 3; //SetTimer(2,300,NULL);
		}
	}

	/*******************************************************************************/
	// �������ƣ� intervalTicktimeHandle
	// ���ܣ� ���100����ʱ�䴦����
	// ������ 
	//        
	// ����ֵ:  
	void CPressurePhaseStatistic::intervalTicktimeHandle(const CPressureCollate *pPressureColl, const CBreathCollate *pBreathColl)
	{
		CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_mutable_instance();
		if( transEvent == 1 )
		{//��������С��6����ÿ�δ�һ�����ݣ��������ݴ���6��С��10����ÿ�δ��������ݣ��������ݴ���10����ÿ�δ���������
			++delayTime;
			int i = 1;
			if(loopBuff.GetCurrBufferNum() > 6 || loopBuff.GetCurrBufferNum() < 10)
				i = 2;
			else if(loopBuff.GetCurrBufferNum() >= 10)
				i = 3;
			for(;i>0;--i)
			{
				while(1)
				{
					_CPRData  cCPRData[1];
                    short     dwActiveSize = 0;
					if( loopBuff.ReadDataMovePtr(cCPRData, 1, &dwActiveSize) == false)
					{
						dwActiveSize = 0;
					}
					if(delayTime == 15)
					{
						//����Pressure����
						cCPRData[0] = cCPRParse.createPressurePhaseData( false );
						dwActiveSize = 1;
						//--------------------------------------------------------------------
						if( actCPRDetailShowInterface != NULL )
						{
							actCPRDetailShowInterface->OnPressureStateAct( false );
						}
						delayTime += 1;
						transEvent = 0;
					}
					if(dwActiveSize == 1)
					{
						if( cCPRParse.isCPROrder(cCPRData[0]) )
						{//�Է��Ⱥ���������ݼ��뵽m_pwndCPR
							cprRealTimePhaseStatisticHandle(cCPRData[0], pPressureColl);
							break;//������ʵʱ����
						}
					}
					else
					{
						i = 0;
						break;
					}
				}
			}
		}
		if( buffTimeEvent == 3 )
		{//���������
			buffTimeEvent = 0;
			delayTime = 0;   //����Delay������Ϊ0
			transEvent = 1;  //SetTimer(1,100,NULL);
			//����Pressure��ʼ
			_CPRData  cCPRData = cCPRParse.createPressurePhaseData( true );
			cprRealTimePhaseStatisticHandle(cCPRData, pPressureColl);
			//--------------------------------------------------------------------
			if( actCPRDetailShowInterface != NULL )
			{
				actCPRDetailShowInterface->OnPressureStateAct( true );
			}
		}
	}

	/*******************************************************************************/
	// �������ƣ� increaseSecondTickNotify
	// ���ܣ� ÿһ��ʱ���¼�֪ͨ
	// ������ 
	//        scriptRunTime:   ��������ʱ��
	// ����ֵ:
	void CPressurePhaseStatistic::increaseSecondTickNotify(const time_duration &scriptRunTime)
	{
		if( !currentSegStat.bValidate )
		{
			currentSegStat.segBeginTime = scriptRunTime;
			currentSegStat.segPeriod = seconds(0);
		}
		else
		{
			currentSegStat.segPeriod += seconds(1);
		}
		//�ж�ʱ���ж�
		if( !currentSegStat.bValidate && phaseStatSegs.size() > 0)
		{
			interruptTime += seconds(1);
			accumInterruptTime += 1;
		}
		else
		{
			interruptTime = seconds(0);
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnCPRRealTimePhaseStatisticHandle
	// ���ܣ� CPR�׶��Բ���ͳ�ƴ����� 
	// ������ 
	//        const _CPRData &cCPRData: ���Ȼ�����ָ��
	// ����ֵ:  
	void CPressurePhaseStatistic::cprRealTimePhaseStatisticHandle(const _CPRData &cCPRData, const CPressureCollate *pPressureColl)
	{
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		if( cCPRParse.judgeCPRPhaseStartOrFinishOrder(cCPRData, true, indeterminate) )
		{
			if( cCPRParse.judgeCPRPhaseStartOrFinishOrder(cCPRData, true, true) )
			{
				//��ѹ�׶ο�ʼ
				currentSegStat.bValidate = true;
				currentSegStat.segPeriod = seconds(0);
			}
			else
			{
				//��ѹ�׶ν�����������ǰ��ͳ�Ƶ������б�
				if( currentSegStat.sumNum > 0 )
				{
					_StatPressueSeg *pBackupsSegStat = new _StatPressueSeg;
					*pBackupsSegStat = currentSegStat;
					phaseStatSegs.push_back( pBackupsSegStat );
					//��ѹ�׶�ͳ����־
					logPressurePhaseStatistic( pBackupsSegStat, m_pEventLogInterface );
				}
				currentSegStat.reset();
			}
		}
		else if( cCPRParse.isCPRScopeOrder(cCPRData, true) )
		{
			currentSegStat.average += pPressureColl->getLogicalValue(cCPRData);
			//��ѹ����
			if( pPressureColl->judgeIsOver( cCPRData ) )
			{
				currentSegStat.overNum += 1;
			}
			else if( pPressureColl->judgeIsLower( cCPRData ) )
			{
				currentSegStat.lackNum += 1;
			}
		}
		else if( cCPRParse.isRateOrder( cCPRData, true) )
		{
			//��ȷƵ�ʷ�Χ(100~120/����)�ڵĸ���
			int  nRate = 0;
			boost::tie(nRate, boost::tuples::ignore) = cCPRParse.getPressureRateValue( cCPRData );
			if( nRate <= 120 && nRate >= 100 )
			{
				currentSegStat.rateRightSum += 1;
			}
		}
	}

	/*******************************************************************************/
	// �������ƣ� cprPhaseStatisticHandle
	// ���ܣ� CPR�׶��Բ���ͳ�ƴ����� 
	// ������ 
	//       cprData:
	// ����ֵ:  
    void CPressurePhaseStatistic::cprPhaseStatisticHandle(const _CPRData &cprData, _eCPRErrorSign  eErrorSign, short uLackNum, _eCPRErrorSign ePractiseExtendSign, _CPRManageState eState)
	{
		_eCPRErrorSign    eCPRSigns[2];
		eCPRSigns[0]  = eErrorSign;
		eCPRSigns[1]  = ePractiseExtendSign;
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		for ( int nStep = 0; nStep < 2; ++nStep )
		{
			switch( eCPRSigns[nStep] )
			{
			case CS_Pressure_Right:
				{
					currentSegStat.rightNum += 1;
					break;
				}
			case CS_PressureNumOver:
				{
					currentSegStat.sumErrorNum += 1;
					currentSegStat.overSumNum += 1;
					break;
				}
			case CS_PressureNumLack:
				{
					currentSegStat.sumErrorNum += uLackNum;
					currentSegStat.lackSumNum += uLackNum;
					break;
				}
			default:
				{
					if( eCPRSigns[nStep] != CS_None && cCPRParse.isCPRScopeOrder(cprData, true) )
					{
						currentSegStat.sumErrorNum += 1;
					}
					break;
				}
			}
		}
		if( cCPRParse.isCPRScopeOrder(cprData, true) )
		{
			currentSegStat.sumNum += 1;
			//-----------------------------------------------------------------------------
			bool completeRight = true;
			boost::dynamic_bitset<>  pos(_CPR_ORDER_L, 0x00);
			//��ѹλ�ô���
			boost::tie(boost::tuples::ignore, pos, completeRight) = cCPRParse.getPressureScopeValue(cprData);
			if(  !pos.none() )
			{
				currentSegStat.posErrorNum += 1;
				//��ѹλ�õ�
				if( pos[0] )
				{
					//��ѹλ��̫��
					currentSegStat.posErr_left += 1;
				}
				else if( pos[1] )
				{
					//��ѹλ��̫��
					currentSegStat.posErr_right += 1;
				}
				else if( pos[2] )
				{
					//��ѹλ��̫��
					currentSegStat.posErr_high += 1;
				}
				else if( pos[3] )
				{
					//��ѹλ��̫��
					currentSegStat.posErr_low += 1;
				}
			}
			//��ѹδ�ͷ���ȷ
			if( !completeRight )
			{
				currentSegStat.incompleteNum += 1;
			}
		}
	}

	//��������
	void CPressurePhaseStatistic::resetPhaseStatistic()
	{
		accumInterruptTime = 0;
		interruptTime = time_duration(0,0,0);
		currentSegStat.reset();
		__super::resetPhaseStatistic();
	}

	void CPressurePhaseStatistic::logPressurePhaseStatistic(const _StatPressueSeg *pPressureSeg, log::COpLogInterface* pLogInterface)
	{
        /*if( pLogInterface != NULL && pPressureSeg->sumNum > 0 )
		{
			short sRightNum, sErrorNum, sPressureRate, sLogicDepth;
			sRightNum  = pPressureSeg->rightNum;
			sErrorNum  = pPressureSeg->getSumErrorsNum();
			sPressureRate = pPressureSeg->getAverageRate();
			sLogicDepth  = pPressureSeg->getAverageValue();
			pLogInterface->OnPressurePhaseDetailStaticLog((int)sRightNum, (int)sErrorNum, (int)sPressureRate, (int)sLogicDepth);
        }*/
	}

	//��ѹ�ܴ���
	short  CPressurePhaseStatistic::getPressureSumNum()
	{
		short  uSumNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatPressueSeg *pressueSeg = (_StatPressueSeg *)item;
			uSumNum += pressueSeg->sumNum;
		}
		uSumNum += currentSegStat.sumNum;
		return uSumNum;
	}

	//��ѹ��ȷ����
	short  CPressurePhaseStatistic::getPressureSumRightNum()
	{
		short  uSumRightNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatPressueSeg *pressueSeg = (_StatPressueSeg *)item;
			uSumRightNum += pressueSeg->rightNum;
		}
		uSumRightNum += currentSegStat.rightNum;
		return uSumRightNum;
	}

	//��ѹ�������
	short  CPressurePhaseStatistic::getPressureSumErrorsNum()
	{
		short  uSumErrorsNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatPressueSeg *pressueSeg = (_StatPressueSeg *)item;
			uSumErrorsNum += pressueSeg->getSumErrorsNum();
		}
		uSumErrorsNum += currentSegStat.getSumErrorsNum();
		return uSumErrorsNum;
	}

	//��ѹ�ͷŲ�������
	short  CPressurePhaseStatistic::getPressureSumIncomplete()
	{
		short uSumIncomplete = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatPressueSeg *pressueSeg = (_StatPressueSeg *)item;
			uSumIncomplete += pressueSeg->incompleteNum;
		}
		uSumIncomplete += currentSegStat.incompleteNum;
		return uSumIncomplete;
	}

	////��ѹλ�ô������
	short  CPressurePhaseStatistic::getPressurePosErrorNum(short *pos_low/*=NULL*/, short *pos_high/*=NULL*/, short *pos_left/*=NULL*/, short *pos_Right/*=NULL*/)
	{
		short  uPosEorroNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatPressueSeg *pressueSeg = (_StatPressueSeg *)item;
			uPosEorroNum += pressueSeg->posErrorNum;
			//��ѹλ��̫��
			if( pos_low != NULL )
			{
				*pos_low += pressueSeg->posErr_low;
			}
			//��ѹλ��̫��
			if( pos_high != NULL )
			{
				*pos_high += pressueSeg->posErr_high;
			}
			 //��ѹλ��̫��
			if( pos_left != NULL )
			{
				*pos_left += pressueSeg->posErr_left;
			}
			//��ѹλ��̫��
			if( pos_Right != NULL )
			{
				*pos_Right += pressueSeg->posErr_right;
			}
		}
		uPosEorroNum += currentSegStat.posErrorNum;
		//��ѹλ��̫��
		if( pos_low != NULL )
		{
			*pos_low += currentSegStat.posErr_low;
		}
		//��ѹλ��̫��
		if( pos_high != NULL )
		{
			*pos_high += currentSegStat.posErr_high;
		}
		//��ѹλ��̫��
		if( pos_left != NULL )
		{
			*pos_left += currentSegStat.posErr_left;
		}
		//��ѹλ��̫��
		if( pos_Right != NULL )
		{
			*pos_Right += currentSegStat.posErr_right;
		}
		return uPosEorroNum;
	}

	//��ѹ����
	short  CPressurePhaseStatistic::getPressureOverNum()
	{
		short  uOverNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatPressueSeg *pressueSeg = (_StatPressueSeg *)item;
			uOverNum += pressueSeg->overNum;
		}
		uOverNum += currentSegStat.overNum;
		return uOverNum;
	}

	//��ѹ��С
	short  CPressurePhaseStatistic::getPressureLackNum()
	{
		short  uLackNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatPressueSeg *pressueSeg = (_StatPressueSeg *)item;
			uLackNum += pressueSeg->lackNum;
		}
		uLackNum += currentSegStat.lackNum;
		return uLackNum;
	}

	//��ѹ�����ȷ
	short  CPressurePhaseStatistic::getPressureDepthRightNum()
	{
		short  uRightNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatPressueSeg *pressueSeg = (_StatPressueSeg *)item;
			uRightNum += pressueSeg->getRightDepthNum();
		}
		uRightNum += currentSegStat.getRightDepthNum();
		return uRightNum;
	}

	//����ƽ����ѹ���
	short  CPressurePhaseStatistic::getAverageDepth()
	{
		short  uDepthSum = 0, uSumNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			uDepthSum += item->getAverageValue() * item->getSumCount();
			uSumNum += item->getSumCount();
		}
		uDepthSum += currentSegStat.getAverageValue() * currentSegStat.getSumCount();
		uSumNum += currentSegStat.getSumCount();
		return short(uSumNum > 0 ? uDepthSum/uSumNum : 0);
	}

	//����ƽ��Ƶ��
	short  CPressurePhaseStatistic::getAverageRate()
	{
		short   uRates = 0, uNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			uRates += item->getAverageRate();
			uNum += 1;
		}
		return uNum > 0 ? uRates/uNum : 0;
	}
	//--------------------------------------------------------------------------------------------
	////�����׶���
	CBreathPhaseStatistic::CBreathPhaseStatistic()
	{

	}

	CBreathPhaseStatistic::~CBreathPhaseStatistic()
	{

	}

	/*******************************************************************************/
	// �������ƣ� cprBreathRealTimeDataHandle
	// ���ܣ� �����������ݴ����� 
	// ������ 
	// ����ֵ:  
	void CBreathPhaseStatistic::cprBreathRealTimeDataHandle(const _CPRData *lptrCPRDatas, int nLength, const CBreathCollate *pBreathColl)
	{//�������ȣ�0x4X
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		for (int nStep = 0; nStep < nLength; ++nStep)
		{
			if( cCPRParse.isCPRScopeOrder(lptrCPRDatas[nStep], false) && pBreathColl->getLogicalValue(lptrCPRDatas[nStep]) > 10 )
			{//С��2mmʱҲ���޸�m_iDelayTime
				delayTime = 0;
			}
		}
		if(buffTimeEvent == 0 && transEvent == 0)
		{
			if( !cCPRParse.isCPRScopeOrder(lptrCPRDatas[0], false) )
				return;
		}
		loopBuff.WriteData(lptrCPRDatas, nLength);
		if(transEvent == 0 && buffTimeEvent == 0)
		{
			buffTimeEvent = 3; //SetTimer(2,300,NULL);
		}
	}

	/*******************************************************************************/
	// �������ƣ� intervalTicktimeHandle
	// ���ܣ� ���100����ʱ�䴦����
	// ������ 
	//        
	// ����ֵ:  
	void CBreathPhaseStatistic::intervalTicktimeHandle(const CPressureCollate *pPressureColl, const CBreathCollate *pBreathColl)
	{
		CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_mutable_instance();
		if( transEvent == 1 )
		{//��������С��6����ÿ�δ�һ�����ݣ��������ݴ���6��С��10����ÿ�δ��������ݣ��������ݴ���10����ÿ�δ���������
			++delayTime;
			int i = 1;
			if(loopBuff.GetCurrBufferNum() > 6 || loopBuff.GetCurrBufferNum() < 10)
				i = 2;
			else if(loopBuff.GetCurrBufferNum() >= 10)
				i = 3;
			for(;i>0;--i)
			{
				while(1)
				{
					_CPRData cCPRData;
                    short    dwActiveSize = 0;
					if(loopBuff.ReadDataMovePtr(&cCPRData,1,&dwActiveSize) == false)
					{
						dwActiveSize = 0;
					}
					if(delayTime == 30)
					{
						transEvent = 0;
						//����Breath����
						cCPRData = cCPRParse.createBreathPhaseData(false);
						dwActiveSize = 1;
						//--------------------------------------------------------------------
						if( actCPRDetailShowInterface != NULL )
						{
							actCPRDetailShowInterface->OnBreathStateAct( false );
						}
						delayTime += 1;
					}
					if(dwActiveSize == 1)
					{
						if( cCPRParse.isCPROrder(cCPRData) )
						{//�Է��Ⱥ���������ݴ���
							cprRealTimePhaseStatisticHandle(cCPRData, pBreathColl);
							break;//������ʵʱ����
						}
					}
					else
					{
						i = 0;
						break;
					}
				}
			}
		}
		if( buffTimeEvent == 3 )
		{//���������
			buffTimeEvent = 0;
			delayTime = 0;//����Delay������Ϊ0
			transEvent = 1; //SetTimer(1,100,NULL);
			//������ʼ
			_CPRData cCPRData = cCPRParse.createBreathPhaseData(true);
			cprRealTimePhaseStatisticHandle(cCPRData, pBreathColl);
			//--------------------------------------------------------------------
			if( actCPRDetailShowInterface != NULL )
			{
				actCPRDetailShowInterface->OnBreathStateAct( TRUE );
			}
		}
	}


	/*******************************************************************************/
	// �������ƣ� increaseSecondTickNotify
	// ���ܣ� ÿһ��ʱ���¼�֪ͨ
	// ������ 
	//        scriptRunTime:   ��������ʱ��
	// ����ֵ:
	void CBreathPhaseStatistic::increaseSecondTickNotify(const time_duration &scriptRunTime)
	{
		if( !currentSegStat.bValidate )
		{
			currentSegStat.segBeginTime = scriptRunTime;
			currentSegStat.segPeriod = seconds(0);
		}
		else
		{
			currentSegStat.segPeriod += seconds(1);
		}
		//.....
	}

	/*******************************************************************************/
	// �������ƣ� OnCPRRealTimePhaseStatisticHandle
	// ���ܣ� CPR�׶��Բ���ͳ�ƴ����� 
	// ������ 
	//        _CPRData cCPRData:  ���Ȼ�ָ��
	// ����ֵ:  
	void CBreathPhaseStatistic::cprRealTimePhaseStatisticHandle(const _CPRData &cCPRData, const CBreathCollate *pBreathColl)
	{
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		if( cCPRParse.judgeCPRPhaseStartOrFinishOrder(cCPRData, false, indeterminate) )
		{
			if( cCPRParse.judgeCPRPhaseStartOrFinishOrder(cCPRData, false, true) )
			{
				//�����׶ο�ʼ
				currentSegStat.bValidate = true;
				currentSegStat.segPeriod = seconds(0);
			}
			else
			{
				//�����׶ν�����������ǰ��ͳ�Ƶ������б�
				if( currentSegStat.sumNum > 0 )
				{
					_StatBreathSeg *pBackupsSegStat = new _StatBreathSeg;
					*pBackupsSegStat = currentSegStat;
					phaseStatSegs.push_back( pBackupsSegStat );
					//�����׶�ͳ����־
					logBreathPhaseStatistic( pBackupsSegStat, m_pEventLogInterface );
				}
				currentSegStat.reset();
			}
		}
		else if( cCPRParse.isCPRScopeOrder(cCPRData, false) )
		{
			currentSegStat.average += pBreathColl->getLogicalValue(cCPRData);
			//��������
			if( pBreathColl->judgeIsOver( cCPRData ) )
			{
				currentSegStat.overNum += 1;
			}
			else if( pBreathColl->judgeIsOver( cCPRData ) )
			{
				currentSegStat.lackNum += 1;
			}
			//ͨ��ʱ��
			if( pBreathColl->judgeIsRespTimeOver( cCPRData ) )
			{
				currentSegStat.ventiOverTimeNum += 1;
			}
			else if( pBreathColl->judgeIsRespTimeLower( cCPRData ) )
			{
				currentSegStat.ventiLowerTimeNum += 1;
			}
		}
	}

	/*******************************************************************************/
	// �������ƣ� cprPhaseStatisticHandle
	// ���ܣ� CPR�׶��Բ���ͳ�ƴ����� 
	// ������ 
	//       cprData:
	// ����ֵ:  
    void CBreathPhaseStatistic::cprPhaseStatisticHandle(const _CPRData &cprData, _eCPRErrorSign  eErrorSign, short uLackNum, _eCPRErrorSign ePractiseExtendSign, _CPRManageState eState)
	{
		_eCPRErrorSign    eCPRSigns[2];
		eCPRSigns[0]  = eErrorSign;
		eCPRSigns[1]  = ePractiseExtendSign;
		const CParseCPRData_Singleton &cCPRParse = CParseCPRData_Singleton::get_const_instance();
		for ( int nStep = 0; nStep < 2; ++nStep )
		{
			switch( eCPRSigns[nStep] )
			{
			case CS_Breath_Right:
				{
					currentSegStat.rightNum += 1;
					break;
				}
			case CS_BreathNumLack:
				{
					currentSegStat.sumErrorNum += uLackNum;
					currentSegStat.lackSumNum += uLackNum;
					break;
				}
			case CS_BreathNumOver:
				{
					currentSegStat.sumErrorNum += 1;
					currentSegStat.overSumNum += 1;
					break;
				}
			default:
				{
					if( eCPRSigns[nStep] != CS_None && cCPRParse.isCPRScopeOrder(cprData, false) )
					{
						currentSegStat.sumErrorNum += 1;
					}
					break;
				}
			}
		}
		if( cCPRParse.isCPRScopeOrder(cprData, false) )
		{
			currentSegStat.sumNum += 1;
		}
	}

	//��������
	void CBreathPhaseStatistic::resetPhaseStatistic()
	{
		currentSegStat.reset();
		__super::resetPhaseStatistic();
	}

	//ͳ�ƴ����׶��Բ���������
	void CBreathPhaseStatistic::logBreathPhaseStatistic(const _StatBreathSeg *pBreathSeg,  log::COpLogInterface* pLogInterface)
	{
        /*if( pLogInterface != NULL && pBreathSeg->getSumCount() > 0 )
		{
			short sRightNum, sErrorNum, sBreathRate, sLogicDepth;
			sRightNum  = pBreathSeg->rightNum;
			sErrorNum  = pBreathSeg->getSumErrorsNum();
			sBreathRate = pBreathSeg->getAverageRate();
			sLogicDepth  = pBreathSeg->getAverageValue();
			pLogInterface->OnBreathPhaseDetailStaticLog((int)sRightNum, (int)sErrorNum, (float)sBreathRate, (int)sLogicDepth);
        }*/
	}

    //�����ܴ���
	short  CBreathPhaseStatistic::getBreathSumNum()
	{
		short  uSumNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uSumNum += breathSeg->sumNum;
		}
		uSumNum += currentSegStat.sumNum;
		return uSumNum;
	}

	//������ȷ����
	short  CBreathPhaseStatistic::getBreathSumRightNum()
	{
		short  uSumRightNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uSumRightNum += breathSeg->rightNum;
		}
		uSumRightNum += currentSegStat.rightNum;
		return uSumRightNum;
	}

	//�����������
	short  CBreathPhaseStatistic::getBreathSumErrorsNum()
	{
		short uSumErrorsNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uSumErrorsNum += breathSeg->getSumErrorsNum();
		}
		uSumErrorsNum += currentSegStat.getSumErrorsNum();
		return uSumErrorsNum;
	}

	short  CBreathPhaseStatistic::getBreathOverNum()
	{
		short uOverNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uOverNum += breathSeg->overNum;
		}
		uOverNum += currentSegStat.overNum;
		return uOverNum;
	}

	short  CBreathPhaseStatistic::getBreathLackNum()
	{
		short uLackNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uLackNum += breathSeg->lackNum;
		}
		uLackNum += currentSegStat.lackNum;
		return uLackNum;
	}

	short  CBreathPhaseStatistic::getBreathInStomachNum()
	{
		short uInStomachNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uInStomachNum += breathSeg->stomachNum;
		}
		uInStomachNum += currentSegStat.stomachNum;
		return uInStomachNum;
	}

	short  CBreathPhaseStatistic::getBreathPipeCloseNum()
	{
		short uPipeCloseNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uPipeCloseNum += breathSeg->pipeCloseNum;
		}
		uPipeCloseNum += currentSegStat.pipeCloseNum;
		return uPipeCloseNum;
	}

	//����ƽ��������
	short  CBreathPhaseStatistic::getAverageVolume()
	{
		short  uVolumeSum = 0, uSumNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			uVolumeSum += item->getAverageValue() * item->getSumCount();
			uSumNum += item->getSumCount();
		}
		uVolumeSum += currentSegStat.getAverageValue() * currentSegStat.getSumCount();
		uSumNum += currentSegStat.getSumCount();
		return short(uSumNum > 0 ? uVolumeSum/uSumNum : 0);
	}

	//ͨ��ʱ�����
	short CBreathPhaseStatistic::getVentiOverTimeNum()
	{
		short uOverTimeNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uOverTimeNum += breathSeg->ventiOverTimeNum;
		}
		uOverTimeNum += currentSegStat.ventiOverTimeNum;
		return uOverTimeNum;
	}

	//ͨ��ʱ�����
	short CBreathPhaseStatistic::getVentiLowerTimeNum()
	{
		short uLowerTimeNum = 0;
		BOOST_FOREACH(auto item, phaseStatSegs)
		{
			_StatBreathSeg *breathSeg = (_StatBreathSeg *)item;
			uLowerTimeNum += breathSeg->ventiLowerTimeNum;
		}
		uLowerTimeNum += currentSegStat.ventiLowerTimeNum;
		return uLowerTimeNum;
	}
}}
