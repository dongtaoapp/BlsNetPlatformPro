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
		//断开显示后通知
		cutLinkCPRStatisticUpdateShow();
	}

	void CShowCPRStatisticUpdateInterface::LinkUpdateShow()
	{
		//对接显示后通知
		doLinkCPRStatisticUpdateShow();
	}

	//重置统计
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

	//更新统计次数
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

	//操作时间、按压中断时间通知、按压时间占比
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

	//循环统计：按压:吹气、循环次数
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

	//按压位置统计(包括进胃)：
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

	//进胃统计
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

	//按压统计：正确百分比、中断时间、平均深度、平均频率、位置正确百分比、释放正确百分比、按压过大、按压过小
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

	//吹气统计：正确百分比、平均吹气量、平均吹气频率、总吹气数、过大、过小、通气多长、通气多短
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
