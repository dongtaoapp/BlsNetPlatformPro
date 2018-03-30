#include <algorithm>
#include <iterator>
#include <boost/foreach.hpp>
#include ".\simulatebaseglobal.h"


using namespace std;
//---------------------------------------------------------------------------------------------------
//心肺复苏操作统计数据结构
_CPRStatisticCollectStruct::_CPRStatisticCollectStruct()
{
	//按压
	m_uPressureRate             = 0;
	m_uPressureAverageCount     = 0; //每分钟的次数
	m_uPressureAverageDepth     = 0; //平均深度
	m_uPressureRightNum         = 0;  //正确次数
	m_uPressureErrSumNum        = 0;
	m_uPressureOverNum          = 0;   //过大
	m_uPressureLackNum          = 0;   //不足
	m_uPressureIncompleteNum    = 0;    //按压时非完全释放
	m_uPressurePositionErrorNum = 0;   //按压位置总错误
	m_uPressureOtherNum         = 0;   //其他
	//吹气
	m_uBreathAverageVol         = 0;   //平均吹气量[ml]
	m_uBreathAverageVolInMinute = 0;    //每1分钟的吹气量[ml]
	m_uBreathAverageCountInMinute = 0;  //每分钟的次数
	m_uBreathRightNum           = 0;    //正确次数
	m_uBreathErrSumNum          = 0;
	m_uBreathOverNum            = 0;     //过大
	m_uBreathLackNum            = 0;     //不足
	m_uBreathStomachNum         = 0;     //进胃
	m_uBreathPipeCloseNum       = 0;      //气道关闭
	m_uBreathOtherNum           = 0;     //其它
}	

