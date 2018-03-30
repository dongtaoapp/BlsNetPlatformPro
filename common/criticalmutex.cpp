#include "criticalmutex.h"


namespace jysoft{  namespace utility
{
    CCriticalMutex::CCriticalMutex()
    {
        ::InitializeCriticalSection(&lockMutex);
    }

    CCriticalMutex::~CCriticalMutex()
    {
        ::DeleteCriticalSection(&lockMutex);
    }

    void CCriticalMutex::Lock()
    {
        ::EnterCriticalSection(&lockMutex);
    }

    void CCriticalMutex::Unlock()
    {
        ::LeaveCriticalSection(&lockMutex);
    }
}}
