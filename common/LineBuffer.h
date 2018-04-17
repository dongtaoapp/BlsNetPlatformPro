#pragma once
#include "VirBuffer.h"

namespace jysoft{
namespace utility {

//��������������ʼ�����С���ٸı䣬���Զ�ȡ����
template<class DataType>
class  Q_DECL_EXPORT CLineBuffer : public CVirBuffer<DataType>
{
public:
	CLineBuffer(void) : CVirBuffer<DataType>() { };
	virtual ~CLineBuffer(void){};
public://��Ҫ���ܺ���
	//����Ŀǰ�����������������ݵĴ�С
    short GetCurrBufferNum()
	{
        return (short)(m_pEndPos - m_pBeginPos);
	};
	//����Ŀǰ�������л�û�б��������ݴ�С
    short GetNoneReadedNum()
	{
        return (short)(m_pEndPos - m_pReadBeginPos);
	};
	//��m_pBeginPosΪ����dNeedCount���ȵ�����
    bool ReadData(DataType *lpByte, short dNeedCount, short *dActiveSize = NULL)
	{
		if(m_pAllocCurvePtr == NULL)
			return false;
        short dwBuffSize = GetCurrBufferNum(); //�������ڵ��������ݴ�С
		if(dNeedCount > dwBuffSize)
			dNeedCount = dwBuffSize;
		if(dActiveSize != NULL)
			*dActiveSize = dNeedCount;
		::memcpy((void *)lpByte,(void *)m_pBeginPos,dNeedCount*sizeof(DataType));
		return true;
	};
	//��m_pEndPosΪ���д��dSize���ȵ�����
    bool WriteData(const DataType *pInData,short dSize,short *dwActiveNum = NULL)
	{//д������ݲ��ܿ������ı߽�
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
	//��m_pReadBeginPosΪ����dSize���ȵ����ݣ����ƶ�m_pReadBeginPos��λ��
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
