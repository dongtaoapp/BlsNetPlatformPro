#pragma once
#include <string>
#include <atlconv.h>
#include <objbase.h>
#include <windows.h>
#include ".\simulatorbase_global.h"

/////////////////////////////////////modified hjg/////////////////////////////////////////////////////
namespace jysoft { namespace simulator {

    class SIMULATORBASESHARED_EXPORT CSample
	{
		enum _Heap_Alloc_Type
		{
			Customized,            //����ר���ڴ���������ɴ����ջ�
			ExternalDeliver        //�ⲿ���������ڴ�����������ⲿ�����ջ�
		};
	private:
		unsigned long              m_dwID;//��־��
	public:
		int                m_iSampleSec; //ÿ��Ĳ�����
		int                m_iSampleVolt;//ÿ���صĲ�����
	private:
		HANDLE             m_hHandle;
		_Heap_Alloc_Type   m_eAllocType;
		unsigned long              m_dwGlobalSize; //�ܷ������������
	public:
		float *            m_pPtrData;
		unsigned long              m_dwSize;       //��Ч����
	public:
		CSample(void);
		CSample( HANDLE hAllocHeap, int nAllocSize );
		CSample(unsigned long dwID);
		CSample( HANDLE hAllocHeap, unsigned long dwID, int nAllocSize);
		virtual ~CSample(void);
	public://��Ҫ����
		inline bool  IsEmpty() const { return m_dwGlobalSize == 0 || m_pPtrData == NULL || m_dwSize == 0;};
		inline unsigned long GetSampleID() { return m_dwID;};
		//�����ļ��еĲ�������
        bool CSample::LoadSampleDataFromTxt(const std::string &strPathFile);
		bool LoadSampleDataFromStream(LPSTREAM lpFileSteam);
		void ChangeSampleData(float *fSrcBegin,const int nCount,int nBeginTime);
		//����
		void Clone(CSample *pOrgSample);
		void Clone(CSample *pSrcSample,float *fpBegin,float *fpEnd);
		void ResetSample(void);
		//�������ݿռ�
		void AllocSample(unsigned long  dwGlobalSize);
		//���ز����ε�ʱ��
		int  GetSampleSumTime();
		//����ʱ�䷵�ز������ָ��
		float *GetSamplePtr(int  iTime);
		//����X��ĳ��ȣ����ش˳����������ʱ��
		int GetSampleTime(float fX);
		//����ָ�룬���ش�λ���������ʱ��
		int GetValidTime(float *pfPos,int nBeginTime);
		//����ʱ�䣬���س���
		float GetLength(int nTime);
		//���ز����ĵ��� 
		//int nTime����λ0.1΢��
		inline int   GetSampleNum(int nTime) {return int(nTime * m_iSampleSec*1e-4);};
		//����Y�����ֵ�����ر�ʾ�ĵ�ѹ(��λ������)
		float GetMilliVolt(float fH);
		//���ݵ�ѹ(��λ������)������Y�����ֵ
		float GetYFromMilliVolt(float fMillVolt);
		void  AddSampleData(int nDstBeginTime, int nTime, float fValue);
		void  AddSampleData(int nDstBeginTime, int nTime, float fBeginValue, float fEndValue);
		void  AddSampleData(int nDstBeginTime, CSample *pSrcSample,float *fpBegin,float *fpEnd);
		void  OverlapSampleData(int nDstBeginTime,int nLogicTime,CSample *pSrcSample,float *fpBegin,float *fpEnd);
		void  HoriIntervalLinkSampleData(int nExtendTime, float fValue, bool bHorDirect=true);
		//ˮƽ�ӳ���ָ��ʱ�䳤��
		//int nTime����λ0.1΢��
		void  HoriExtendSampleData(int nTime);
		//����ѹֵת���ɶ�Ӧ��BYTEֵ
        static int  ModifyVoltToLogicValue(const float *pBeginPtr, long uSrcSize,/*out*/unsigned char *pDstPtr, int iRate = 1);
		//������������
		void  AdjustSampleData(float fData);
		//����������ת��Ϊ8bit����������
		void  ChangeSampleDataTo8Big();
		//����
		void  RidSampleYawp(int nBeginTime, int nValidTime);
		//*******************************************************************************************************
		//*********ע�����º����Ŀ�ʼλ�ö�Ϊ��㣬��Чʱ��Ϊ���в�����******************************************/
		//���Ų������ݴ���
		void  ZoomSampleDataHandle(int iChgedTime);
		//�и�������ݴ���
		void  CutSampleDataHandle(int iPosTime, bool bRmvPostion);
		//void  AddDirectSampleData(CSample *pSrcSample);
		//���pSrcSample�е�����
		void  DirectLinkSampleData(CSample *pSrcSample);
		//ˮƽ������Ӳ���
		void  HoriIntervalLinkSampleData(CSample *pSrcSample,int nIntervalTime, float fValue);
		//ֱ�߼�����Ӳ���
		void  LineIntervalLinkSampleData(CSample *pSrcSample,int nIntervalTime);
		//������Ӳ���
		void  OverlapLinkSampleData(CSample *pSrcSample,int nOverlapTime);
		//��ʼλ�õ��Ӳ���
		void  DirectOverlapLinkSampleData(const CSample *pSrcSample);
		//��ʼλ�ø��ǲ���
		void  DirectCoverLinkeSampleData(const CSample *pSrcSample);
	};

}}
