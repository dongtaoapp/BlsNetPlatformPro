#ifndef IDISTRIBUTECPRREALTIMEDATA_H
#define IDISTRIBUTECPRREALTIMEDATA_H

#include ".\cprmoduls_global.h"

#include "..\Common\CommonGlobal.h"


class  CPRMODULSSHARED_EXPORT IDistributeCPRRealTimeData
{
public:
    IDistributeCPRRealTimeData();
public:
    //传递缓存中的cpr数据
    virtual void DistributeCPRDataInMem(_CPRData *lpDataPtr, int nLength) = 0;
    //传递实时cpr数据
    virtual void DistributeCPRData(_CPRData *lpDataPtr, int nLength) = 0;
    //获取显示需要的cpr数据长度
    virtual int GetNeededCPRDataLen() = 0;
    //重置界面
    virtual void AllClear() = 0;
    //加入错误标志
    virtual void AddCPRErrorSign(_eCPRErrorSign eErrorSign) = 0;
};

#endif // IDISTRIBUTECPRREALTIMEDATA_H
