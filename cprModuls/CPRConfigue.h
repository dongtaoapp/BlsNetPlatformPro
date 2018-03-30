#pragma once
#include <string>
#include <boost/optional.hpp>
#include ".\cprmoduls_global.h"

#include "..\common\CommonGlobal.h"

using namespace boost;
namespace jysoft{  namespace cpr 
{
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     CPR参数配置类
	创建人：	 hjg
	创建时间：   2009/5/22               修改日期：2018/3/19
	XML格式定义： 
	        <?xml version="1.0" encoding="utf-8"?>
	        <QCPRConfig opMode="practise">
	           <!--脚本操作时间 enable="" /-->
	           <scriptTime enable="true">120</scriptTime>
	           <!--QCPR条件 enable="" /-->
	           <interruptTime enable="true">20</interruptTime>
	           <CCF enable="true">60</CCF>
	           <PRightPce enable="true">70</PRightPce>
	           <BRightPce enable="true">70</BRightPce>
	           <PRatePce enable="true">70</PRatePce>
	           <CPRRule type="speciality">
	              <cycleOpNumber value="5"/>
	              <parameters>
	                 <pressureRule>
	                    <depthRange lower="50" over="60"/>
	                    <rateRange lower="100" over="120"/>
	                 </pressureRule>
	               <breathRule>
	                  <volumeRange lower="500" over="1000"/>
	                  <ventiTimeRange lower="500" over="1500"/>
	               </breathRule>
	             </parameters>
	           </CPRRule>
	          </QCPRConfig>
	//-----------------------------------------------------------------------------------------------------------------*/
    class CPRMODULSSHARED_EXPORT CCPRConfigue
	{
	public:
		CCPRConfigue(void);
		virtual ~CCPRConfigue(void);
	public:
		/*******************************************************************************/
		//功能：加载心肺复苏配置信息
		//参数：
		//      const std::string &configueFile： 个人配置文件信息
		//返回值:  
		void loadCPRConfigue(const std::string &configueFile);
		/*******************************************************************************/
		//功能：SaveCPRConfigueToFile
		//功能： 保存使用者的CPR配置信息（用于BLS脚本操作）
		//参数：
		//返回值: 
		void saveCPRConfigueToFile(const std::string &strUserConfigueFile, _CPRManageState eCPRMode);
		//保存
		void copyConfigue(CCPRConfigue  *pCPRConfigue);
	public:
		//按压最小值
		inline  int getLowerPressureDepth() { return lowerPressureDepth; };
		inline  void set_LowerPressureDepth(int nDepth) { lowerPressureDepth = nDepth; };
		//按压最大值
		int getOverPressureDepth(bool bPresets = false) ;
		inline  void setOverPressureDepth(int nDepth) { overPressureDepth = nDepth; };
		inline  bool isOverPressureDepthValidate() { return bOverPressureValidate; };
		inline  void setOverPressureDepthValidate(bool bValidate) { bOverPressureValidate = bValidate; };
		//吹气量最小值
		inline  int getLowerBreathVolume() { return lowerBreathVolume; };
		inline void setLowerBreathVolume( int nBreathVolume ) { lowerBreathVolume = nBreathVolume; };
		//吹气量最大值
		inline  int getOverBreathVolume() { return overBreathVolume; };
		inline void setOverBreathVolume( int nBreathVolume ) { overBreathVolume = nBreathVolume; };
		//通气时间
		inline int getLowerRespTime() { return lowerRespTime; };
		inline int getOverRespTime() { return overRespTime; }
		//五个循环操作模式
		inline  _CPRManageState getFiveCycleMode() { return eFiveCycleMode; };
		//是否五个循环CPR操作
		inline  bool isFiveCycleRule() { return cycleNumber == 3 ? false : true; };
		void setIsFiveCycleRule(bool bFiveCycleRule) 
		{ 
			if( bFiveCycleRule )
				cycleNumber  = 5;
			else
				cycleNumber  = 3;
		};
		//是否为专业操作类型
		inline  bool isSpecialityMemberOp() { return bSpecialityMemberOp; };
		inline void setIsSpecialityMemberOp(bool bSpecialityOp)  { bSpecialityMemberOp = bSpecialityOp; };
		//非专业人员操作: 按压总数
		inline  int  getSumPressureNumber() { return sumPressureNumber; };
		inline  void setSumPressureNumber(int nNumber) { sumPressureNumber = nNumber; };
	public://QCPR条件
		//脚本允许时间
		inline optional<short> getScriptSumTime() { return scriptTime; };
		//中断时间
		inline optional<short> getInterruptTime() { return interruptTime; };
		//按压占比
		inline optional<short> getCCFPecent() { return CCF; };
		//按压正确占比
		inline optional<short> getPRightPecent() { return rightPPce; };
		//吹气正确占比
		inline optional<short> getBRightPecent() { return rightBPce; };
		//按压频率正确占比
		inline optional<short> getPRatePecent() { return ratePPce; };
	public:
		//设置五个循环操作模式
		void setFiveCycleMode(_CPRManageState eMode) { eFiveCycleMode = eMode; };
		//设置默认的参数值
		void setDefaultParams(_CPRManageState eMode);
	protected:
		int                  lowerPressureDepth;      //按压最小值
		int                  overPressureDepth;       //按压最大值
		int                  lowerBreathVolume;       //吹气量最小值
		int                  overBreathVolume;        //吹气量最大值
		//最小、最大通气时间(单位：ms)
		int                  lowerRespTime;
		int                  overRespTime;
		_CPRManageState      eFiveCycleMode;           //五个循环操作模式
		bool                 bSpecialityMemberOp;      //是否为专业操作类型  hjg 2011.4 add
		bool                 bOverPressureValidate;    //是否限制最大按压深度 hjg 2014.3 add
	protected://QCPR条件
		//脚本允许时间
		optional<short>      scriptTime;
		//中断时间
		optional<short>      interruptTime;
		//按压占比
		optional<short>      CCF;
		//按压正确占比
		optional<short>      rightPPce;
		//吹气正确占比
		optional<short>      rightBPce;
		//按压频率正确占比
		optional<short>      ratePPce;
	private:
		int                  cycleNumber;             //专业人员操作:   循环CPR操作次数
		int                  sumPressureNumber;       //非专业人员操作: 按压总数
	};
}}
