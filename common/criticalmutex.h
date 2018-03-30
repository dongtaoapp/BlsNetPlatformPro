#ifndef CRITICALMUTEX_H
#define CRITICALMUTEX_H

#include <Windows.h>
#include ".\common_global.h"


namespace jysoft{
namespace utility {
    //临界资源访问控制  2018.3
    class AFX_EXT_CLASS CCriticalMutex
    {
    public:
        CCriticalMutex();
        virtual ~CCriticalMutex();
    protected:
        CRITICAL_SECTION     lockMutex;
    public:
        void Lock();
        void Unlock();
    };
}}

#endif // CRITICALMUTEX_H
