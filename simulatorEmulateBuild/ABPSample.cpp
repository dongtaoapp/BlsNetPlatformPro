#include ".\abpsample.h"

namespace jysoft { namespace simulator { namespace bp {

	CABPSample::CABPSample(void)
	{
	}

	CABPSample::~CABPSample(void)
	{
	}

    bool CABPSample::CutBefore(int pos)
	{
		if(pos>=m_dwSize)
            return false;
		for(int i=0;i<(m_dwSize-pos);i++)
		{
			*(m_pPtrData+i)=*(m_pPtrData+pos+i);
		}
		m_dwSize=m_dwSize-pos;
        return true;
	}

    bool CABPSample::CutAfter(int pos)
	{
        if(pos >= m_dwSize)
            return false;
		m_dwSize=pos+1;
        return true;
	}
}}}
