#include ".\igetphysiologyactionobj.h"


using namespace jysoft::simulator;
namespace jysoft { namespace flowEngine 
{
	IGetPhysiologyActionObj::IGetPhysiologyActionObj(void)
	{
		m_pCPRMessageCollect  = NULL;
	}

	IGetPhysiologyActionObj::~IGetPhysiologyActionObj(void)
	{
	}

	//��ȡѪ������
	CXAction_Osat * IGetPhysiologyActionObj::getAction_OsatPtr()
	{
        CXAction_Osat  *pSpO2Action = (CXAction_Osat *)getPhysiologyActionPtr( "CXAction_Osat" );
		return pSpO2Action;
	}

	//��ȡ��������
	CXAction_ECG * IGetPhysiologyActionObj::getAction_ECGPtr()
	{
        CXAction_ECG  *pEcgAction = (CXAction_ECG *)getPhysiologyActionPtr( "CXAction_ECG" );
		return pEcgAction;
	}

	//��ȡѪѹ����
	CXAction_ABP * IGetPhysiologyActionObj::getAction_ABPPtr()
	{
        CXAction_ABP  *pABPAction = (CXAction_ABP *)getPhysiologyActionPtr( "CXAction_ABP" );
		return pABPAction;
	}

	//��ȡ��������
	CXAction_Temperature * IGetPhysiologyActionObj::getAction_TemperaturePtr()
	{
        CXAction_Temperature  *pTempAction = (CXAction_Temperature *)getPhysiologyActionPtr( "CXAction_Temperature" );
		return pTempAction;
	}

	//��ȡEtCO2����
	CXAction_etCO2 * IGetPhysiologyActionObj::getAction_EtCO2Ptr()
	{
        CXAction_etCO2  *pEtCo2Action = (CXAction_etCO2 *)getPhysiologyActionPtr( "CXAction_etCO2" );
		return pEtCo2Action;
	}

	CXAction_Pupil * IGetPhysiologyActionObj::getAction_PupilPtr()
	{
        CXAction_Pupil  *pAction = (CXAction_Pupil *)getPhysiologyActionPtr( "CXAction_Pupil" );
		return pAction;
	}

	CXAction_Resp * IGetPhysiologyActionObj::getAction_Resp()
	{
        CXAction_Resp *pRespSound = (CXAction_Resp *)getPhysiologyActionPtr( "CXAction_Resp" );
		return	pRespSound;
	}
}}
