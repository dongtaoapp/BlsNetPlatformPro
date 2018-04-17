#include ".\CardiogramVFibrParam_I12.h"


namespace jysoft { namespace simulator { namespace ecg {

	CCardiogramVFibrParam_I12::CCardiogramVFibrParam_I12(IStorage *pRootStorage )
							: CVirCardiogramParam()
	{
		m_sExtendParam  = 0;
		m_pStorages     = pRootStorage;
	}

	CCardiogramVFibrParam_I12::~CCardiogramVFibrParam_I12(void)
	{
	}

	//���ز���ֵ
    void CCardiogramVFibrParam_I12::LoadCardiogramParam(QRS eQRS, BasicRhythm eRhythm,int uHR, short sConduct/*=0*/, short sExtendParam/*=0*/)
	{
		//�����ƣ�ʱ��
		static std::string strParams[][2] = {
			//----------------------------------------------------------------------
            {"VFibr.txt","40875"}
		};
		std::string *pAimPtr = strParams[0];
		//����ˢ�����ݵķ�Χ
		if(m_eQRS == QRS_None)
		{
			m_setParams.clear();//�Ƴ����еĲ���
			m_eRefurbishDataRange = RD_LoadConfigFile;
			m_setParams["ConfigFileName"] = "MakeFile.txt";
		}
		else if(m_sExtendParam != sExtendParam || m_eQRS != eQRS)
		{
			m_eRefurbishDataRange = RD_AllData;
		}
		m_sExtendParam  = sExtendParam;

		if( m_uHR != uHR || m_eQRS != eQRS )
		{
			m_setParams["HR"] = "0";
		}

		m_setParams["Seg_FileName"] = pAimPtr[0];
		m_setParams["CycleTime"] = pAimPtr[1];
		m_setParams["ZoomTime"] = pAimPtr[1];
		m_eQRS = eQRS;
		m_eRhythm = eRhythm;
		m_uHR     = uHR;
		//end hjg 2006/3/29
	}
}}}
