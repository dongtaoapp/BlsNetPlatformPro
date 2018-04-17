#include "cprsamplebufferstate.h"

#include "..\Common\ParseCPRData_Singleton.h"

ICPRSampleBufferState::ICPRSampleBufferState(void)
{

}

ICPRSampleBufferState::~ICPRSampleBufferState(void)
{

}


CCPRSampleEmptyBufferState::CCPRSampleEmptyBufferState(QObject * parent):CCPRSampleEmptyBufferState( parent )
{

}

CCPRSampleEmptyBufferState::~CCPRSampleEmptyBufferState()
{

}

bool CCPRSampleEmptyBufferState::isKindOf(const std::string &className)
{
    if( className == "CCPRSampleEmptyBufferState" )
    {
        return true;
    }
    return false;
}

void CCPRSampleEmptyBufferState::timerEvent(QTimerEvent *event)
{
    const jysoft::cpr::CParseCPRData_Singleton &cParseCPRData = jysoft::cpr::CParseCPRData_Singleton::get_const_instance();
    _CPRData cprZeroData = cParseCPRData.createRealTimeSampleData(0, true);
    cprBuff.push_back(cprZeroData);
}



CCPRSamplingBufferState::CCPRSamplingBufferState()
{

}

CCPRSamplingBufferState::~CCPRSamplingBufferState()
{

}

bool CCPRSamplingBufferState::isKindOf(const std::string &className)
{
    if( className == "CCPRSamplingBufferState" )
    {
        return true;
    }
    return false;
}
