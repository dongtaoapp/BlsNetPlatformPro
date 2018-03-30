#pragma once
#include ".\simulatorbase_global.h"

#include ".\ShowCPRActUpdateInterface.h"
#include ".\ShowCPRStatisticUpdateInterface.h"
#include ".\CPRRealTimeUpdateInterface.h"

namespace jysoft{  namespace cpr {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����    �ķθ�����ʾ�ӿڼ�����
	//-----------------------------------------------------------------------------------------------------------------*/

    class SIMULATORBASESHARED_EXPORT CCPRShowInterfacesAggregate
	{
	public:
		CCPRShowInterfacesAggregate(void);
		virtual ~CCPRShowInterfacesAggregate(void);
	protected:
		CShowCPRActUpdateInterface    *m_pShowCPRDetailActInterface;
		CShowCPRStatisticUpdateInterface    *m_pShowCPRStatisticInterface;
		CCPRRealTimeUpdateInterface     *m_pShowCPRRealTimeInteface;
	public:
		//����CPR������⶯����ʾ�ӿ�
		inline CShowCPRActUpdateInterface *Get_ShowCPRDetailActUpdateInterface() { return m_pShowCPRDetailActInterface; };
		//����CPRͳ����ʾ�ӿ�
		inline CShowCPRStatisticUpdateInterface *Get_ShowCPRStatisticUpdateInterface() { return m_pShowCPRStatisticInterface; };
		//����CPRʵʩ������ʾ�ӿ�
		inline CCPRRealTimeUpdateInterface *Get_ShowCPRRealTimeUpdateInterface() { return m_pShowCPRRealTimeInteface; };
		//-----------------------------------------------------------------------------------------------------------------------
		//����CPR������⶯����ʾ�ӿ�
		void Set_ShowCPRDetailActUpdateInterface(CShowCPRActUpdateInterface *pInterface);
		//����CPRͳ����ʾ�ӿ�
		void Set_ShowCPRStatisticUpdateInterface(CShowCPRStatisticUpdateInterface *pInterface);
		//����CPRʵʩ������ʾ�ӿ�
		void Set_ShowCPRRealTimeUpdateInterface(CCPRRealTimeUpdateInterface *pInterface);
	public:
		//�Ƴ�CPR������⶯����ʾ�ӿ�
		void Remove_ShowCPRDetailActUpdateInterface(CShowCPRActUpdateInterface *pRmvInterface);
	};
}}
