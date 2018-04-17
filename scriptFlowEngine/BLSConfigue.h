#pragma once
#include <string>
#include ".\scriptflowengine_global.h"

#include "..\common\CommonGlobal.h"


namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	类说明：     配置信息解析类
	创建人：	 hjg
	创建时间：   2018/2/21
	//-----------------------------------------------------------------------------------------------------------------*/
    class SCRIPTFLOWENGINESHARED_EXPORT CBLSConfigue
	{
	public:
		CBLSConfigue(void);
		virtual ~CBLSConfigue(void);
	public:
		/*******************************************************************************/
		//功能：解析场景的配置数据
		//参数：
		//      configueFile： 配置文件信息
		//返回值:  
		void parseBLSConfigue(const std::string &configueFile);
		//判断是否能连接3D仿真演示系统
		bool isCanLink3DSystem();
		/*******************************************************************************/
		//功能：saveBLSConfigueToFile
		//功能： 保存使用者的脚本配置信息
		//参数：
		//返回值: 
		void saveBLSConfigueToFile(const std::string &configueFile);
	public:
		//嗒音提示(0:none; 100bpm:1; 110bpm:2; 120bpm:3)
		inline  short getDidaSoundHint() { return sDidaSoundHint; };
		inline  void setDidaSoundHint( short sDidaSound ) { sDidaSoundHint = sDidaSound; };
		//操作提示音
		inline  bool isHintSound() { return bOpHintSound; };
		inline  void setIsHintSound(bool bHintSound) { bOpHintSound = bHintSound; };
		//是否能除颤
		inline _DefibrEnable getDefibrState() { return eDefibrState; };
		inline void setDefibrState(_DefibrEnable eDefibr) { eDefibrState = eDefibr; };
		inline short  getDefibrSumNumber() { return defibrNum; };
		inline void setDefibrSumNumber(short sNum) { defibrNum = sNum; };
		inline bool getScriptSuccessByQCPR() { return succuQCPR; };
		inline void setIsScriptSuccessByQCPR( bool bQCPR) { succuQCPR = bQCPR; };
		//3D仿真演示系统参数
		inline std::string   get_3DSystemComputerName() { return str3DSystemComputerName; };
		inline void set_3DSystemComputerName(const std::string &strComputerName ) { str3DSystemComputerName = strComputerName; };
		//服务端口号
		inline short  get_3DSystemPort() { return s3DSystemPort; };
	public:
		static std::string get_strDefibrState(_DefibrEnable eDefibr);
		static _DefibrEnable get_eDefibrState(const std::string &strDefibr);
	protected:  //提示音参数
		short                sDidaSoundHint;           //滴嗒音提示(0:none; 100bpm:1; 110bpm:2; 120bpm:3)
		bool                 bOpHintSound;             //操作提示音
	protected: //脚本参数
		_DefibrEnable        eDefibrState;
		short                defibrNum;
		bool                 succuQCPR;
	protected: //3D仿真演示系统参数
		short                s3DSystemPort;            //端口号
		std::string          str3DSystemComputerName;  //计算机名称
	};
}}
