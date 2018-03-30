#pragma once
#include <windows.h>
#include ".\common_global.h"


namespace jysoft{
namespace utility {

template<class DataType>
class  Q_DECL_EXPORT CVirBuffer
{
public:
	CVirBuffer(void) 
	{
		m_pBeginPos = m_pEndPos = m_pReadBeginPos  = NULL;
		m_dwBuffNum = 0;
		m_pAllocCurvePtr = NULL;
		m_hCurveHeap = HeapCreate(HEAP_NO_SERIALIZE,2*1024,0);
	};
	virtual ~CVirBuffer(void) 
	{
		if(!m_pAllocCurvePtr)
			::HeapFree(m_hCurveHeap,HEAP_NO_SERIALIZE,m_pAllocCurvePtr);
		::HeapDestroy(m_hCurveHeap);
		m_hCurveHeap = NULL;
	};
public://主要功能函数
	//初始化缓冲区的大小
    virtual bool InitializeBuff(short dwSize)
	{
		if(m_pAllocCurvePtr != 0)
			HeapFree(m_hCurveHeap,HEAP_NO_SERIALIZE,m_pAllocCurvePtr);
		m_dwBuffNum = dwSize;
		m_pAllocCurvePtr	= ::HeapAlloc(m_hCurveHeap,HEAP_NO_SERIALIZE|HEAP_ZERO_MEMORY,sizeof(DataType)*(dwSize+1));
		if(m_pAllocCurvePtr == NULL)
		{
			m_pBeginPos = m_pEndPos = NULL;
			return false;
		}
		m_pBeginPos = m_pEndPos = (DataType *)m_pAllocCurvePtr;
		m_pReadBeginPos  = m_pBeginPos;
		return true;
	};
	//由m_pBeginPos为起点读dNeedCount长度的数据
    virtual bool ReadData(DataType *lpByte,short dNeedCount,short *dActiveSize = NULL) {return false;};
	//由m_pEndPos为起点写入dSize长度的数据
    virtual bool WriteData(const DataType *pInData,short dSize,short *dwActiveNum = NULL) {return false;};
	//有m_pReadBeginPos为起点读dSize长度的数据，并移动m_pReadBeginPos的位置
    virtual bool ReadDataMovePtr(DataType *pInData, short dSize, short *dwActiveNum = NULL) {return false;};
	//重制m_pReadBeginPos指针，使其指向起点m_pBeginPos
	inline void ResetReadBeginPosPtr() { m_pReadBeginPos = m_pBeginPos;};
	//设置起点m_pBeginPos为m_pReadBeginPos指针
	inline void ResetBeginPosToReadBeginPos() {m_pBeginPos = m_pReadBeginPos; };
	//设为空
	virtual void Empty() 
	{
		m_pEndPos = m_pBeginPos;
		m_pReadBeginPos  = m_pBeginPos;
	};
	//返回目前缓冲区中已填充的数据的大小
    virtual short GetCurrBufferNum() { return 0;};
	//返回起始指针
	inline DataType * GetBeginPosPtr() { return m_pBeginPos;};
	//返回结束指针
	inline DataType * GetEndPosPtr() { return m_pEndPos;};
	//返回目前缓冲区中还没有被读的数据大小
    virtual short GetNoneReadedNum() = 0;
	//读数据;注：需要考虑同步问题
    void ReadDataToBuffer(CVirBuffer<DataType> *pAimBuff, short dReadNum, short *dActiveSize = 0)
	{
		DataType tmpBuff[512];
		if(dActiveSize != NULL)
			*dActiveSize = 0;

		DataType *pReadBeginPos = m_pReadBeginPos;
		ResetReadBeginPosPtr();
		while(dReadNum > 0)
		{
            short dwRead = dReadNum > 512 ? 512 : dReadNum;
            short dwActiveNum = 0;
			ReadDataMovePtr(tmpBuff,dwRead,&dwActiveNum);//有m_pReadBeginPos为起点读数据
			if(dwActiveNum == 0)
				break;
			pAimBuff->WriteData(tmpBuff,dwActiveNum,&dwRead);
			dReadNum -= dwRead;
			if(dActiveSize != NULL)
				*dActiveSize += dwRead;
			if(dwActiveNum > dwRead)
				break;//无法再写入
		}
		m_pReadBeginPos = pReadBeginPos;
	};
	//返回内存缓冲区的大小
    inline short GetAllocateBuffNum() { return m_dwBuffNum;};
protected:
	DataType    *m_pBeginPos;
	DataType    *m_pEndPos;
	DataType    *m_pReadBeginPos;
    short        m_dwBuffNum; //内存缓冲区的大小
	//=====================================================
    void *       m_hCurveHeap;
    void *       m_pAllocCurvePtr;
};

}}
