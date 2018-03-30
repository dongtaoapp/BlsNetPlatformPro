#include ".\showcprstatisticupdateinterface.h"

namespace jysoft{  namespace cpr {

	CShowCPRStatisticUpdateInterface::CShowCPRStatisticUpdateInterface(void)
	{
	}

	CShowCPRStatisticUpdateInterface::~CShowCPRStatisticUpdateInterface(void)
	{
	}

	bool CShowCPRStatisticUpdateInterface::isKindOf(const std::string &className)
	{
		if( className == "CShowCPRStatisticUpdateInterface" )
		{
			return true;
		}
		return IUpdateShowVir::isKindOf( className );
	}

	void CShowCPRStatisticUpdateInterface::UnLinkUpdateShow()
	{
		//�Ͽ���ʾ��֪ͨ
		cutLinkCPRStatisticUpdateShow();
	}

	void CShowCPRStatisticUpdateInterface::LinkUpdateShow()
	{
		//�Խ���ʾ��֪ͨ
		doLinkCPRStatisticUpdateShow();
	}

	//����ͳ��
	void CShowCPRStatisticUpdateInterface::OnResetCPRStatistic(_CPRManageState  eState)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowCPRStatisticUpdateInterface" ) )
			{
				CShowCPRStatisticUpdateInterface *pShowCPRStatisticInterface = (CShowCPRStatisticUpdateInterface *)pInterface;
				pShowCPRStatisticInterface->ResetCPRStatistic( eState );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	//����ͳ�ƴ���
	void CShowCPRStatisticUpdateInterface::OnUpdateStatistic(boost::optional<int> calcGradePec, int nPressureSumNum, int nPressureRightNum, int nBreathSumNum, int nBreathRightNum)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowCPRStatisticUpdateInterface" ) )
			{
				CShowCPRStatisticUpdateInterface *pShowCPRStatisticInterface = (CShowCPRStatisticUpdateInterface *)pInterface;
				pShowCPRStatisticInterface->UpdateCPRStatistic(calcGradePec, nPressureSumNum, nPressureRightNum, nBreathSumNum, nBreathRightNum);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	//����ʱ�䡢��ѹ�ж�ʱ��֪ͨ����ѹʱ��ռ��
	void CShowCPRStatisticUpdateInterface::OnUpdateCPRTimeStatic(int cprPeriodTime, boost::optional<int> interruptTime,  boost::optional<int> pressureTimePercent)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowCPRStatisticUpdateInterface" ) )
			{
				CShowCPRStatisticUpdateInterface *pShowCPRStatisticInterface = (CShowCPRStatisticUpdateInterface *)pInterface;
				pShowCPRStatisticInterface->UpdateCPRTimeStatic( cprPeriodTime,  interruptTime, pressureTimePercent );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	//ѭ��ͳ�ƣ���ѹ:������ѭ������
	void CShowCPRStatisticUpdateInterface::OnUpdateCPRCycle(int pressureNum, int breathNum, boost::optional<int> cycleNum)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowCPRStatisticUpdateInterface" ) )
			{
				CShowCPRStatisticUpdateInterface *pShowCPRStatisticInterface = (CShowCPRStatisticUpdateInterface *)pInterface;
				pShowCPRStatisticInterface->UpdateCPRCycle( pressureNum,  breathNum, cycleNum );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	//��ѹλ��ͳ��(������θ)��
	void CShowCPRStatisticUpdateInterface::OnUpdatePositionStatic(short pos_low, short pos_high, short pos_left, short pos_Right)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowCPRStatisticUpdateInterface" ) )
			{
				CShowCPRStatisticUpdateInterface *pShowCPRStatisticInterface = (CShowCPRStatisticUpdateInterface *)pInterface;
				pShowCPRStatisticInterface->UpdatePositionStatic( pos_low,  pos_high, pos_left, pos_Right);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	//��θͳ��
	void CShowCPRStatisticUpdateInterface::OnUpdateInStomachNumber( short sInStomachNum)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowCPRStatisticUpdateInterface" ) )
			{
				CShowCPRStatisticUpdateInterface *pShowCPRStatisticInterface = (CShowCPRStatisticUpdateInterface *)pInterface;
				pShowCPRStatisticInterface->UpdateInStomachNumber( sInStomachNum );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	//��ѹͳ�ƣ���ȷ�ٷֱȡ��ж�ʱ�䡢ƽ����ȡ�ƽ��Ƶ�ʡ�λ����ȷ�ٷֱȡ��ͷ���ȷ�ٷֱȡ���ѹ���󡢰�ѹ��С
	void CShowCPRStatisticUpdateInterface::OnUpdatePressureStatic(int calcGradePec, int interruptTime, int nAvergeDepth, int nAvergeRate, int sumNum, int posRightPec, int releasRightPec, int depthOverNum, int depthLowerNum)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowCPRStatisticUpdateInterface" ) )
			{
				CShowCPRStatisticUpdateInterface *pShowCPRStatisticInterface = (CShowCPRStatisticUpdateInterface *)pInterface;
				pShowCPRStatisticInterface->UpdatePressureStatic( calcGradePec, interruptTime, nAvergeDepth, nAvergeRate, sumNum, posRightPec, releasRightPec, depthOverNum, depthLowerNum );
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	//����ͳ�ƣ���ȷ�ٷֱȡ�ƽ����������ƽ������Ƶ�ʡ��ܴ����������󡢹�С��ͨ���೤��ͨ�����
	void CShowCPRStatisticUpdateInterface::OnUpdateBreathStatic(int calGradePec, int nAvergeVolume, int nAvergeRate, int sumNum, int volumeOverNum, int volumeLowerNum, int ventiOverTimeNum, int ventiLowerTimeNum)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface != NULL )
		{
			if( pInterface->isKindOf( "CShowCPRStatisticUpdateInterface" ) )
			{
				CShowCPRStatisticUpdateInterface *pShowCPRStatisticInterface = (CShowCPRStatisticUpdateInterface *)pInterface;
				pShowCPRStatisticInterface->UpdateBreathStatic(calGradePec, nAvergeVolume, nAvergeRate, sumNum,  volumeOverNum, volumeLowerNum, ventiOverTimeNum, ventiLowerTimeNum);
			}
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}
}}
