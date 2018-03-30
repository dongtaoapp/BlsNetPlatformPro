#include <algorithm>
#include <iterator>
#include <boost/foreach.hpp>
#include ".\simulatebaseglobal.h"


using namespace std;
//---------------------------------------------------------------------------------------------------
//�ķθ��ղ���ͳ�����ݽṹ
_CPRStatisticCollectStruct::_CPRStatisticCollectStruct()
{
	//��ѹ
	m_uPressureRate             = 0;
	m_uPressureAverageCount     = 0; //ÿ���ӵĴ���
	m_uPressureAverageDepth     = 0; //ƽ�����
	m_uPressureRightNum         = 0;  //��ȷ����
	m_uPressureErrSumNum        = 0;
	m_uPressureOverNum          = 0;   //����
	m_uPressureLackNum          = 0;   //����
	m_uPressureIncompleteNum    = 0;    //��ѹʱ����ȫ�ͷ�
	m_uPressurePositionErrorNum = 0;   //��ѹλ���ܴ���
	m_uPressureOtherNum         = 0;   //����
	//����
	m_uBreathAverageVol         = 0;   //ƽ��������[ml]
	m_uBreathAverageVolInMinute = 0;    //ÿ1���ӵĴ�����[ml]
	m_uBreathAverageCountInMinute = 0;  //ÿ���ӵĴ���
	m_uBreathRightNum           = 0;    //��ȷ����
	m_uBreathErrSumNum          = 0;
	m_uBreathOverNum            = 0;     //����
	m_uBreathLackNum            = 0;     //����
	m_uBreathStomachNum         = 0;     //��θ
	m_uBreathPipeCloseNum       = 0;      //�����ر�
	m_uBreathOtherNum           = 0;     //����
}	

