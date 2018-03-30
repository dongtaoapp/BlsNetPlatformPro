#include <boost/format.hpp>
#include ".\cprstatirp.h"

using namespace jysoft::simulator::base;

namespace jysoft { namespace irp {

	CCPRStatIrp::CCPRStatIrp(void)
	{
	}

	CCPRStatIrp::~CCPRStatIrp(void)
	{
	}

	bool CCPRStatIrp::isKindOf(const std::string &strClass)
	{
		if( strClass == "CCPRStatIrp" )
		{
			return true;
		}
		return CVirEventIrp::isKindOf( strClass );
	}

	/*******************************************************************************/
	// �������ƣ� doPackageIrp
	// ���ܣ�  ���Irp������
	// ������ 
	// ����ֵ: 
	std::string CCPRStatIrp::doPackageIrp()
	{
		boost::format fmt("<CPRStatIrp><Mode>%d</Mode><State>%d</State></CPRStatIrp>");
		fmt % (int)m_eCPRMode % m_nStat;
		return fmt.str();
	}

	/*******************************************************************************/
	// �������ƣ� CreateEvent_CPRIrp
	// ���ܣ� ����CPR�¼�Irp��
	// ������ 
	//       _CPRManageState eCPRMode: CPRģʽ
	//       int nStat:               ״̬
	// ����ֵ:  
	CCPRStatIrp * CCPRStatIrp::CreateEvent_CPRIrp(_CPRManageState eCPRMode, int nStat)
	{
		CCPRStatIrp  *pCPRStatIrp = new CCPRStatIrp();
		//����CPRģʽ
		pCPRStatIrp->Set_eCPRMode( eCPRMode );
		//���ô�ģʽ�µ��¼�
		pCPRStatIrp->Set_OperatorStat( nStat );
		return pCPRStatIrp;
	}

	/*******************************************************************************/
	// �������ƣ� UnzipPackage
	// ���ܣ� ��ѹ�������Irp������
	// ������ 
	//        char *lpData��
	//        UINT uNumber��
	// ����ֵ:  
    CCPRStatIrp * CCPRStatIrp::UnzipPackage(char *lpData, unsigned short uNumber)
	{
		CCPRStatIrp  *pCPRStateIrp = NULL;
		/*CMessMemory   cMessMemory;
		if( cMessMemory.ParseContext(lpData, (DWORD)uNumber, NULL) != -1 )
		{
			if( cMessMemory.m_eStyle == CMessMemory::aComposite )
			{
				pCPRStateIrp   = new CCPRStatIrp();
				POSITION  pos = cMessMemory.m_LeafList.GetHeadPosition();
				while( pos )
				{
					CMessMemory  *pLeafMess = cMessMemory.m_LeafList.GetNext( pos );
					CString   strTxt((char *)pLeafMess->m_pPtr, pLeafMess->GetLeafMSize());
					if( pLeafMess->m_strCaption == _T("Mode") )
					{
						pCPRStateIrp->m_eCPRMode = (_CPRManageState)::atoi( strTxt.operator LPCTSTR() );
					}
					else if( pLeafMess->m_strCaption == _T("EventSign") )
					{
						pCPRStateIrp->m_nStat = ::atoi( strTxt.operator LPCTSTR() );
					}
				}
			}
		}*/
		return pCPRStateIrp;
	}

	/*******************************************************************************/
	// �������ƣ� UpdateEventSignShow
	// ���ܣ�  ��ʾ�¼�����
	// ������ 
	// ����ֵ: 
	void CCPRStatIrp::UpdateEventSignShow(CShowEventSignUpdateInterface  *pInterface )
	{
		//------------------------------------------------------------------------
		//0:    CPR��������
		//1:    CPR������ʼ
		//2:    �ڱ�׼ģʽ��ʵսģʽ�£����5��ѭ����CPR����
		if( m_nStat == 1 )
		{
			pInterface->OnAddNewEventSign( ES_CPREvent );
		}
		else if( m_nStat == 0 )
		{
			pInterface->OnRemoveEventSign( ES_CPREvent );
		}
	}

}}
