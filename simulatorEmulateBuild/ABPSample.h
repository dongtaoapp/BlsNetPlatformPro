#pragma once
#include "..\SimulatorBase\Sample.h"


namespace jysoft { namespace simulator { namespace bp {

	class CABPSample : public CSample
	{
	public:
		CABPSample(void);
		virtual ~CABPSample(void);
	public:
        bool CutBefore(int pos);
        bool CutAfter(int pos);
	};
}}}
