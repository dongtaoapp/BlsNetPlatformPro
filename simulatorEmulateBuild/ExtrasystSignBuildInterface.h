#pragma once
#include ".\simulatoremulatebuild_global.h"

#include  "..\common\criticalmutex.h"

namespace jysoft { namespace simulator { namespace ecg {

	//�粫�ź�������
    class SIMULATOREMULATEBUILDSHARED_EXPORT CExtrasystSignBuildInterface
	{
	public:
		CExtrasystSignBuildInterface(void);
		virtual ~CExtrasystSignBuildInterface(void);
	private:
		int         m_nSigns[60];
		long        m_nCurrentTime;      //��ǰʱ�䣬��λ��0.1����
		int         m_nExtrasystRate;
	private:
		utility::CCriticalMutex      m_cMutex;
	protected:
		void RandonExtrasystSignBuildTime(int nExtrasystRate);
	public:
		//�޸��粫����������
		void  ModifyExtrasystRate(int  nExtrasystRate);
		//�����Ƿ�Ҫ�����粫����λ��0.1���룩
		bool  AddMilliterTime( int iMilliTime );
	};
}}}
