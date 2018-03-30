#pragma once
#include ".\VirBuffer.h"

#include <boost/assert.hpp>

namespace jysoft{
namespace utility {

template<class DataType>
class Q_DECL_EXPORT CLoopBuffer : public CVirBuffer<DataType>
{
public:
	CLoopBuffer(void) : CVirBuffer<DataType>(){ } ;
	virtual ~CLoopBuffer(void) { };
protected:
    DataType * MoveLogicPtr(DataType *pPtr,short dwMoveSize)
	{
		DataType *pRtn = NULL;
		DataType *pTmpEnd = (DataType *)m_pAllocCurvePtr + m_dwBuffNum + 1;//����Ľ�����
		if(pPtr + dwMoveSize >= pTmpEnd)
			pRtn = (DataType *)m_pAllocCurvePtr + (pPtr + dwMoveSize - pTmpEnd);
		else
			pRtn = pPtr + dwMoveSize;
		return pRtn;
	};
public://��Ҫ���ܺ���
	//����Ŀǰ�����������������ݵĴ�С
    short GetCurrBufferNum()
	{
        short nReturn;
		if(m_pBeginPos <= m_pEndPos)
            nReturn = short(m_pEndPos - m_pBeginPos);
		else
		{
			DataType *pTmpEnd = (DataType *)m_pAllocCurvePtr + m_dwBuffNum + 1;//����Ľ�����
            nReturn = short(pTmpEnd - m_pBeginPos);
            nReturn += (short)(m_pEndPos - (DataType *)m_pAllocCurvePtr);
		}
		return nReturn;
	};
	//����Ŀǰ�������л�û�б��������ݴ�С
    short GetNoneReadedNum()
	{
        short nReturn;
		if(m_pReadBeginPos <= m_pEndPos)
            nReturn = short(m_pEndPos - m_pReadBeginPos);
		else
		{
			DataType *pTmpEnd = (DataType *)m_pAllocCurvePtr + m_dwBuffNum + 1;//����Ľ�����
            nReturn = short(pTmpEnd - m_pReadBeginPos);
            nReturn += (short)(m_pEndPos - (DataType *)m_pAllocCurvePtr);
		}
		return nReturn;
	};
	//����Ŀǰ�������л�û�б��������ݴ�С
    void SetCurrNoneReadedNum( short dwSize )
	{
        BOOST_ASSERT(dwSize < ( m_dwBuffNum - 1));//��Ҫ���󻺳����Ĵ�С
		if(m_pAllocCurvePtr == NULL)
			return ;
		DataType *pTmpBeginPos = m_pReadBeginPos;
		DataType *pTmpEnd = (DataType *)m_pAllocCurvePtr + m_dwBuffNum + 1;//����Ľ�����
		if((pTmpBeginPos + dwSize) >= pTmpEnd)
		{//Ҫ��ȡ������������
            short utmpSize = pTmpEnd - pTmpBeginPos;
			pTmpBeginPos = (DataType *)m_pAllocCurvePtr;
			dwSize -= utmpSize;
		}
		if(dwSize != 0)
			pTmpBeginPos = pTmpBeginPos + dwSize;
		m_pEndPos = pTmpBeginPos;
	}
	//��m_pBeginPosΪ����dNeedCount���ȵ�����
    bool ReadData(DataType *lpByte,short dNeedCount,short *dActiveSize = NULL)
	{
		if(m_pAllocCurvePtr == NULL)
			return false;
		DataType *pTmpBeginPos = m_pBeginPos;
        short dwBuffSize = GetCurrBufferNum(); //�������ڵ��������ݴ�С
		if(dwBuffSize < dNeedCount)
			dNeedCount = dwBuffSize;
		if(dActiveSize != NULL)
			*dActiveSize = dNeedCount;
		DataType *pTmpEnd = (DataType *)m_pAllocCurvePtr + m_dwBuffNum + 1;//����Ľ�����
		if((pTmpBeginPos + dNeedCount) >= pTmpEnd)
		{//Ҫ��ȡ������������
            short utmpSize = short(pTmpEnd - pTmpBeginPos);
			::memcpy((void *)lpByte,(void *)pTmpBeginPos,utmpSize*sizeof(DataType));
			pTmpBeginPos = (DataType *)m_pAllocCurvePtr;
			dNeedCount -= utmpSize;
			lpByte = lpByte + utmpSize;
		}
		else
		{
			::memcpy((void *)lpByte,(void *)pTmpBeginPos,dNeedCount*sizeof(DataType));
			dNeedCount = 0;
		}
		if(dNeedCount != 0)
			::memcpy((void *)lpByte,(void *)pTmpBeginPos,dNeedCount*sizeof(DataType));
		return true;
	};
	//��m_pEndPosΪ���д��dSize���ȵ�����
    bool WriteData(const DataType *pInData,short dSize,short *dwActiveNum = NULL)
	{
		if(m_pAllocCurvePtr == NULL)
			return false;
		if(dSize > m_dwBuffNum)
			dSize = m_dwBuffNum;
		if(dwActiveNum != NULL)
			*dwActiveNum = dSize;
        short dwBuffSize = GetCurrBufferNum(); //�������ڵ��������ݴ�С
		DataType *pTmpEnd = (DataType *)m_pAllocCurvePtr + m_dwBuffNum + 1;//����Ľ�����
		if(dSize + dwBuffSize > m_dwBuffNum)
		{//����ӵ����ݽ�����������������
            short dwMoveSize = dSize + dwBuffSize - m_dwBuffNum;//����ƶ��ľ���
			DataType *pBeginPos = MoveLogicPtr(m_pBeginPos,dwMoveSize);
			if(pBeginPos < m_pBeginPos)
				pBeginPos += m_dwBuffNum + 1;
			if(m_pReadBeginPos >= m_pBeginPos && m_pReadBeginPos <= pBeginPos)
				m_pReadBeginPos = m_pBeginPos = MoveLogicPtr(m_pBeginPos,dwMoveSize);
			else
				m_pBeginPos = MoveLogicPtr(m_pBeginPos,dwMoveSize);
			
		}
		//����ӵ�������ӵ�ĩ��������
		if(m_pEndPos + dSize <= pTmpEnd)
		{
			::memcpy((void *)m_pEndPos,(void *)pInData,dSize*sizeof(DataType));
			if(m_pEndPos + dSize == pTmpEnd)
				m_pEndPos = (DataType *)m_pAllocCurvePtr;
			else
				m_pEndPos = m_pEndPos + dSize;
			dSize = 0;
		}
		else
		{
            short utmpSize = short(pTmpEnd - m_pEndPos);
			::memcpy((void *)m_pEndPos,(void *)pInData,utmpSize*sizeof(DataType));
			dSize -= utmpSize;
			m_pEndPos = (DataType *)m_pAllocCurvePtr;
			pInData = pInData + utmpSize;
		}
		if(dSize != 0)
		{
			::memcpy((void *)m_pEndPos,(void *)pInData,dSize*sizeof(DataType));
			m_pEndPos = m_pEndPos + dSize;
		}
		return true;
	};
	//�ڵ�ǰ�����ݵ�λ��д��������
    bool WriteDataFromCurrReadPos(DataType *pInData,short dSize,short *dwActiveNum = NULL)
	{
		if(m_pAllocCurvePtr == NULL)
			return false;
		DataType *pTmpBeginPos = m_pReadBeginPos;
		DataType *pTmpEnd = (DataType *)m_pAllocCurvePtr + m_dwBuffNum + 1; ///����Ľ�����
        short dwBuffSize ; //�������ڵ��������ݴ�С
		if(pTmpBeginPos <= m_pEndPos)
			dwBuffSize = m_pEndPos - pTmpBeginPos;
		else
		{
            dwBuffSize = (short)(pTmpEnd - pTmpBeginPos);
            dwBuffSize += (short)(m_pEndPos - (DataType *)m_pAllocCurvePtr);
		}
        short dwWriteSize = dSize;
		if(dwBuffSize < dSize)
		{
			dSize = (dSize-dwBuffSize);
			//����ӵ�������ӵ�ĩ��������
			if(m_pEndPos + dSize <= pTmpEnd)
			{
				if(m_pEndPos + dSize == pTmpEnd)
					m_pEndPos = (DataType *)m_pAllocCurvePtr;
				else
					m_pEndPos = m_pEndPos + dSize;
				dSize = 0;
			}
			else
			{
                short utmpSize = pTmpEnd - m_pEndPos;
				dSize -= utmpSize;
				m_pEndPos = (DataType *)m_pAllocCurvePtr;
			}
			if(dSize != 0)
			{
				m_pEndPos = m_pEndPos + dSize;
			}
		}
		dSize = dwWriteSize;
		if( dwActiveNum != NULL)
		{
			*dwActiveNum = dSize;
		}
		if((pTmpBeginPos + dSize) >= pTmpEnd)
		{//Ҫ��ȡ������������
            short utmpSize = pTmpEnd - pTmpBeginPos;
			::memcpy((void *)pTmpBeginPos,(void *)pInData,utmpSize*sizeof(DataType));
			pTmpBeginPos = (DataType *)m_pAllocCurvePtr;
			dSize -= utmpSize;
			pInData = pInData + utmpSize;
		}
		else
		{
			::memcpy((void *)pTmpBeginPos,(void *)pInData,dSize*sizeof(DataType));
			dSize = 0;
		}
		if(dSize != 0)
			::memcpy((void *)pTmpBeginPos,(void *)pInData,dSize*sizeof(DataType));
		return true;
		
	};
	//��m_pReadBeginPosΪ����dSize���ȵ����ݣ����ƶ�m_pReadBeginPos��λ��
    bool ReadDataMovePtr(DataType *pInData, short dSize, short *dActiveSize = NULL)
	{
		if(m_pAllocCurvePtr == NULL)
			return false;
		DataType *pTmpBeginPos = m_pReadBeginPos;
		DataType *pTmpEnd = (DataType *)m_pAllocCurvePtr + m_dwBuffNum + 1;//����Ľ�����
        short dwBuffSize ; //�������ڵ��������ݴ�С

		if(pTmpBeginPos <= m_pEndPos)
            dwBuffSize = short(m_pEndPos - pTmpBeginPos);
		else
		{
            dwBuffSize = (short)(pTmpEnd - pTmpBeginPos);
            dwBuffSize += (short)(m_pEndPos - (DataType *)m_pAllocCurvePtr);
		}
	
		if(dwBuffSize < dSize)
			dSize = dwBuffSize;
		if(dActiveSize != NULL)
			*dActiveSize = dSize;

		if((pTmpBeginPos + dSize) >= pTmpEnd)
		{//Ҫ��ȡ������������
            short utmpSize = (short)(pTmpEnd - pTmpBeginPos);
			::memcpy((void *)pInData,(void *)pTmpBeginPos,utmpSize*sizeof(DataType));
			m_pReadBeginPos = pTmpBeginPos = (DataType *)m_pAllocCurvePtr;
			dSize -= utmpSize;
			pInData = pInData + utmpSize;
		}
		else
		{
			::memcpy((void *)pInData,(void *)pTmpBeginPos,dSize*sizeof(DataType));
			m_pReadBeginPos = pTmpBeginPos + dSize;
			dSize = 0;
		}
		if(dSize != 0)
		{
			::memcpy((void *)pInData,(void *)pTmpBeginPos,dSize*sizeof(DataType));
			m_pReadBeginPos = pTmpBeginPos + dSize;
		}
		return true;
	};
	//����ָ�����ȵ�����
    bool PopupDataFromEndPos(DataType *pInData, short dSize, short *dActiveSize = NULL)
	{
		if(m_pAllocCurvePtr == NULL)
			return false;
		//*dActiveSize = GetCurrBufferNum() > dSize ? dSize : GetCurrBufferNum();
		return false;
	};
};
}}
