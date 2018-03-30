#include ".\iheartstartsign.h"

namespace jysoft { namespace simulator {

	IHeartStartSign::IHeartStartSign(void)
	{
	}

	IHeartStartSign::~IHeartStartSign(void)
	{
	}

	bool IHeartStartSign::isKindOf(const std::string &className)
	{
		if( className == "IHeartStartSign" ) 
		{
			return true;
		}
		return false;
	}

	/*******************************************************************************/
	// �������ƣ� OnHeartStartSignHandle
	// ���ܣ�   ���࿪ʼ����һ�����ڵ��������ź�
	// ������
	//        BasicRhythm eRhythm:  ��������
	//        int  nCycleTime:      ��������ʱ�䣨��λ��0.1���룩
	// ����ֵ:  
	void IHeartStartSign::OnHeartStartSignHandle(BasicRhythm eRhythm, int  nCycleTime, bool bHaveHeartSign)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface )
		{
			IHeartStartSign *pHeartStartSign = (IHeartStartSign *)pInterface;
			pHeartStartSign->HeartStartSignHandle(eRhythm, nCycleTime, bHaveHeartSign);
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

	/*******************************************************************************/
	// �������ƣ� OnWatchHeartStartSign
	// ���ܣ�   
	// ������
	//        BOOL bWatching:  
	// ����ֵ:  
	void IHeartStartSign::OnWatchHeartStartSign(bool bWatching)
	{
		IBedirecteLinksVir *pInterface = GetHeaderInterfacePtr();
		while( pInterface )
		{
			IHeartStartSign *pHeartStartSign = (IHeartStartSign *)pInterface;
			pHeartStartSign->WatchHeartStartSign( bWatching );
			pInterface = pInterface->GetNextInterfacePtr();
		}
	}

}}
