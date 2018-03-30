#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\IBedirecteLinksVir.h"

namespace jysoft { namespace simulator {

	//�����źŽӿ���
    class SIMULATORBASESHARED_EXPORT IPhysiologyStartSign : public IBedirecteLinksVir
	{
	public:
		IPhysiologyStartSign(void);
		virtual ~IPhysiologyStartSign(void);
	public:
		virtual bool isKindOf(const std::string &className);
	public:
		/*******************************************************************************
		//���ܣ�Ѫ���������ݼ���
		//������int nDifferMilliTime:          ʱ�䣨0.1���룩
		//      int nQtoSMilliTime:            Q����S����ʱ�䣨0.1���룩
		//      int nStoTMilliTime:            S����T����ʱ�䣨0.1���룩
		//      int nCycleTime:                ����ʱ�䣨0.1���룩
		//����ֵ:  
		*********************************************************************************/
		void OnStartPhysiologySimpleLoad(int nDifferMilliTime, int nQtoSMilliTime, int nStoTMilliTime, int nCycleTime);
	protected:
		//Ѫ���������ݼ���
		virtual void StartPhysiologySimpleLoad(int nDifferMilliTime, int nQtoSMilliTime, int nStoTMilliTime, int nCycleTime) = 0;
	};
}}
