#pragma once
#include <string>

#include "..\Common\CommonGlobal.h"

#include "..\SimulatorBase\Sample.h"


namespace jysoft { namespace simulator { namespace ecg {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     12�ֵ����ĵ�ͼ���������ݴ�����
	�����ˣ�	 hjg
	����ʱ�䣺   2013/5/16
	//-----------------------------------------------------------------------------------------------------------------*/
	class CEcgLeadSamples
	{
	public:
		CEcgLeadSamples(void);
		virtual ~CEcgLeadSamples(void);
	public:
		/*******************************************************************************/
		// �������ƣ� DirectOverlapLinkSampleData
		// ���ܣ� ��ʼλ�õ��Ӳ���
		// ������  
		//        const CEcgLeadSamples &cSrcLeadSamples:
		// ����ֵ: 
		void DirectOverlapLinkSampleData( CEcgLeadSamples &cSrcLeadSamples );
		/*******************************************************************************/
		// �������ƣ� GetEcgLeadSample
		// ���ܣ� ����ָ�������ĵ�����
		// ������ 
		//        RhythmLead  eEcgLeadType:  
		// ����ֵ:  
		CSample * GetEcgLeadSample(RhythmLead  eEcgLeadType) { return &m_cLeadSample[(int)eEcgLeadType]; };
		/*******************************************************************************/
		// �������ƣ� CombineArtifactData
		// ���ܣ� ��Ӽ�����50/60HZʱ������
		// ������ 
		//        Artifact eArtiface:  
		//        int iCycleTime:  
		//        UINT uArtifactNum:         
		// ����ֵ:  
		UINT  CombineArtifactData(Artifact eArtiface, int iCycleTime, UINT uArtifactNum);
		/*******************************************************************************/
		// �������ƣ� CombineLeadSamples
		// ���ܣ� ���ϸ����������ݵ����ݽ�������أ��������
		// ������ 
		//        int nMiliCycleTime:          ����ʱ��(0.1ms)
		// ����ֵ:  
		I12LeadSample * CombineLeadSamples(int nMiliCycleTime);
		/*******************************************************************************/
		// �������ƣ� ClearEcgLeadCycleData
		// ���ܣ� �������������ʱ���ڵ��ĵ�ͼ���ݣ�������ʣ������
		// ������ 
		//        int nMiliCycleTime:          ����ʱ��(0.1ms)
		// ����ֵ:  
		void ClearEcgLeadCycleData(int nMiliCycleTime);
		/*******************************************************************************/
		// �������ƣ� CutEcgLeadCycleExtendData
		// ���ܣ� �г��������ڲ��ֵ����� 
		// ������ 
		//        int nMiliCycleTime:          ����ʱ��(0.1ms)
		// ����ֵ:  
		bool CutEcgLeadCycleExtendData(int nMiliCycleTime);
		/*******************************************************************************/
		// �������ƣ� GetBuildEcgLeadSampleNum
		// ���ܣ� ���ع������ĵ�ͼ��������
		// ������ 
		//        
		// ����ֵ: 
		UINT GetBuildEcgLeadSampleNum();
	public:
		/*******************************************************************************/
		// �������ƣ� GetSampleNum
		// ���ܣ� ���ز����ĵ���
		// ������  
		//        int nMiliTime��     ��λ0.1ms
		// ����ֵ: 
		inline unsigned int  GetSampleNum(int nMiliTime) {return unsigned int(nMiliTime * 400*1e-4);};
		//��ո��������ĵ�ͼ����
		void EmptyEcgLeadSamples();
	protected:
		//�����������ڵ�Yֵ
		static float* GetTriangleCycleData(int nFrequent, UINT &uCycleNum);
		//������ʱ���ݽ�������ش�С
		void ResetTempBuffSize(DWORD dwSize);
	protected:
		//�����ĵ����ݣ�����Ϊ��I, II, III, aVR, aVL, aVF, V2, V3, V4, V5, V6
		CSample             m_cLeadSample[12];  
	private:
		I12LeadSample *     m_pTempBuff;          //���������
		DWORD               m_dwTempBuffSize;
	};

}}}
