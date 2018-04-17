#pragma once
#include "VirBuffer.h"

namespace jysoft{
namespace utility {

//缓冲区特征：初始化后大小不再改变，线性读取数据
template<class DataType>
class  Q_DECL_EXPORT CLineBuffer : public CVirBuffer<DataType>
{
public:
	CLineBuffer(void) : CVirBuffer<DataType>() { };
	virtual ~CLineBuffer(void){};
public://主要功能函数
	//返回目前缓冲区中已填充的数据的大小
    short GetCurrBufferNum()
	{
        return (short)(m_pEndPos - m_pBeginPos);
	};
	//返回目前缓冲区中还没有被读的数据大小
    short GetNoneReadedNum()
	{
        return (short)(m_pEndPos - m_pReadBeginPos);
	};
	//由m_pBeginPos为起点读dNeedCount长度的数据
    bool ReadData(DataType *lpByte, short dNeedCount, short *dActiveSize = NULL)
	{
		if(m_pAllocCurvePtr == NULL)
			return false;
        short dwBuffSize = GetCurrBufferNum(); //缓冲区内的填充的数据大小
		if(dNeedCount > dwBuffSize)
			dNeedCount = dwBuffSize;
		if(dActiveSize != NULL)
			*dActiveSize = dNeedCount;
		::memcpy((void *)lpByte,(void *)m_pBeginPos,dNeedCount*sizeof(DataType));
		return true;
	};
	//由m_pEndPos为起点写入dSize长度的数据
    bool WriteData(const DataType *pInData,short dSize,short *dwActiveNum = NULL)
	{//写入的数据不能跨出数组的边界
		if(m_pAllocCurvePtr == NULL)
			return false;
        short dwBuffSize = GetCurrBufferNum();
		if(dwBuffSize + dSize > m_dwBuffNum)
			dSize = m_dwBuffNum - dwBuffSize;
		if(dwActiveNum != NULL)
			*dwActiveNum = dSize;
		if(dSize == 0)
			return false;
		::memcpy((void *)m_pEndPos,(void *)pInData,dSize * sizeof(DataType));
		m_pEndPos = m_pEndPos + dSize;
		return true;
	};
	//有m_pReadBeginPos为起点读dSize长度的数据，并移动m_pReadBeginPos的位置
    bool ReadDataMovePtr(DataType *pInData, short dSize, short *dwActiveNum = NULL)
	{
        short dwBuff = m_pEndPos - m_pReadBeginPos;
		if(dSize > dwBuff)
			dSize = dwBuff;
		if(dwActiveNum != NULL)
			*dwActiveNum = dSize;
		if(dSize == 0)
			return false;
		::memcpy((void *)pInData,(void *)m_pReadBeginPos,dSize*sizeof(DataType));
		m_pReadBeginPos = m_pReadBeginPos + dSize;
		return true;
	};
};

}}
