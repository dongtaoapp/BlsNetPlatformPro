#pragma once
#include ".\simulatorbase_global.h"

#include "..\Common\CommonGlobal.h"
#include "..\Common\VirtualIrp.h"


namespace jysoft { namespace irp {

	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ʵʱ����Irp
	�����ˣ�	 hjg
	����ʱ�䣺   2017/2/8
	//-----------------------------------------------------------------------------------------------------------------*/
    class SIMULATORBASESHARED_EXPORT CRealTimeDataIrp : public CVirtualIrp
	{
	public:
		CRealTimeDataIrp(void);
		virtual ~CRealTimeDataIrp(void);
	public:
		virtual _IrpType Get_eIrpType() { return eRealTimeData; };
		virtual bool isKindOf(const std::string &strClass);
		/*******************************************************************************/
		// �������ƣ� doPackageIrp
		// ���ܣ�  ���Irp������
		// ������ 
		// ����ֵ: 
		virtual std::string doPackageIrp();
	public:
		/*******************************************************************************/
		// �������ƣ� CreateRealTimeData_CPRIrp
		// ���ܣ� ����CPRʵʱ����Irp��
		// ������ 
		//        const _CPRData *ptrCPRDatas��
		//        int nLength��
		// ����ֵ:  
		static CRealTimeDataIrp * CreateRealTimeData_CPRIrp(const _CPRData *ptrCPRDatas, int nLength);
		/*******************************************************************************/
		// �������ƣ� UnzipPackage
		// ���ܣ� ��ѹ�������Irp������
		// ������ 
		//        const char *lpstrPackage��
		//        UINT uNumber��
		// ����ֵ:  
        static CRealTimeDataIrp * UnzipPackage(const char *lpstrPackage, short uNumber);
	public:
		//����CPRʵʱ��������
		void SetCPR_RealTimeData(/*in*/const _CPRData *ptrCPRDatas, int nLength);
		//��ȡCPRʵʱ��������
		int GetCPR_RealTimeData(/*out*/_CPRData *ptrCPRDatas);
	public:
		_CPRData*       m_ptrCPRDatas;
		int             m_nLength;
	};

}}
