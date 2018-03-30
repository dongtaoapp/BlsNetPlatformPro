#pragma once
#include <list>
#include ".\simulatorbase_global.h"

#include "..\Common\CommonGlobal.h"

enum _SIMULATECOMMANDTYPE
{
	CT_NONE = 0,
	CT_SIMULATE_LINK,      //模拟人连接指令
	CT_CPR_DATA,            //CPR数据
	CT_CPR_EVENT,          //CPR事件
	CT_CARDIOGRAM_DATA,    //心电图数据
	CT_AIRWAY_SET,         //气道设置
	CT_PACE_SET,           //起博设置
	CT_BLOODPRESS_SET,     //血压设置
	CT_BREATH_SET,         //呼吸设置
	CT_ECGRATE_SET,        //心率设置
	CT_PUPIL_SET,          //瞳孔设置
	CT_SPILE_EVENT,        //插管事件
	CT_UNSPILE_EVENT,      //取消插管事件
	CT_SCENARIORESET_EVENT,   //脚本重置事件
	CT_CONTROL_EVENT,      //控制指令
	CT_EVENT               //事件
};

//---------------------------------------------------------------------------------------------------
//心肺复苏操作统计数据结构
struct  SIMULATORBASESHARED_EXPORT _CPRStatisticCollectStruct
{
	//按压
	int                     m_uPressureRate;
	int                     m_uPressureAverageCount; //每分钟的次数
	int                     m_uPressureAverageDepth; //平均深度
	int                     m_uPressureRightNum;  //正确次数
	int                     m_uPressureErrSumNum;
	int                     m_uPressureOverNum;   //过大
	int                     m_uPressureLackNum;   //不足
	int                     m_uPressureIncompleteNum;    //按压时非完全释放
	int                     m_uPressurePositionErrorNum; //按压位置总错误
	int                     m_uPressureOtherNum;   //其他
	//吹气
	int                     m_uBreathAverageVol;            //平均吹气量[ml]
	int                     m_uBreathAverageVolInMinute;    //每1分钟的吹气量[ml]
	int                     m_uBreathAverageCountInMinute;  //每分钟的次数
	int                     m_uBreathRightNum; //正确次数
	int                     m_uBreathErrSumNum;
	int                     m_uBreathOverNum;  //过大
	int                     m_uBreathLackNum;  //不足
	int                     m_uBreathStomachNum; //进胃
	int                     m_uBreathPipeCloseNum;//气道关闭
	int                     m_uBreathOtherNum; //其它
public:
	_CPRStatisticCollectStruct();
};
