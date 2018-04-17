#ifndef IDISTRIBUTECPRREALTIMEDATA_H
#define IDISTRIBUTECPRREALTIMEDATA_H

#include ".\cprmoduls_global.h"

#include "..\Common\CommonGlobal.h"


class  CPRMODULSSHARED_EXPORT IDistributeCPRRealTimeData
{
public:
    IDistributeCPRRealTimeData();
public:
    //���ݻ����е�cpr����
    virtual void DistributeCPRDataInMem(_CPRData *lpDataPtr, int nLength) = 0;
    //����ʵʱcpr����
    virtual void DistributeCPRData(_CPRData *lpDataPtr, int nLength) = 0;
    //��ȡ��ʾ��Ҫ��cpr���ݳ���
    virtual int GetNeededCPRDataLen() = 0;
    //���ý���
    virtual void AllClear() = 0;
    //��������־
    virtual void AddCPRErrorSign(_eCPRErrorSign eErrorSign) = 0;
};

#endif // IDISTRIBUTECPRREALTIMEDATA_H
