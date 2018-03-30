#pragma once
#include ".\translayer_global.h"

#include "..\common\VirtualIrp.h"

namespace jysoft { namespace transLayer 
{
	class CFilterUp;
    class TRANSLAYERSHARED_EXPORT CVirtualCommunicate
	{
	public:
		CVirtualCommunicate(void);
		virtual ~CVirtualCommunicate(void);
	protected:
		CFilterUp        *m_pFilterUpPtr;
	public:
		inline void SetFilterUpPtr(CFilterUp *pFilterUp) { m_pFilterUpPtr = pFilterUp;};
		// 初始化通信接口，使其能正常的收发数据
		virtual bool InitializeCommunicate(void) = 0;
		//将内容传给下位机
		virtual void TransDownData(irp::CVirtualIrp * pDownIrp) = 0;
		//数据传到程序中
        virtual void TransUpData(void *lpData, short uNumber) = 0 ;
	public:
		//传输CPR数据
		virtual void TransUpCPRDataFromBuffer(const _CPRData *ptrdwCPRData, int nLength) = 0;
		//上传CPR开始命令
		virtual void TransUpCPRStartOrder() = 0;
		//上传CPR结束命令
		virtual void TransUpCPRStopOrder() = 0; 
	};
}}
