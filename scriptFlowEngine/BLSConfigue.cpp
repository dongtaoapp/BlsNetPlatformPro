#include ".\BLSConfigue.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>


using namespace boost::property_tree;
namespace jysoft { namespace flowEngine 
{
	CBLSConfigue::CBLSConfigue(void)
	{
		sDidaSoundHint = 1;
		bOpHintSound = true;
		eDefibrState = _defibrCan;
		defibrNum = 1;
		succuQCPR = true;
		s3DSystemPort = 8300;
		str3DSystemComputerName = "none";
	}

	CBLSConfigue::~CBLSConfigue(void)
	{
	}

	/*******************************************************************************/
	//功能：解析场景的配置数据
	//参数：
	//      configueFile： 配置文件信息
	//返回值:  
	void CBLSConfigue::parseBLSConfigue(const std::string &configueFile)
	{
		ptree   pt;
		ini_parser::read_ini( configueFile, pt);
		//提示音参数
		sDidaSoundHint = pt.get<short>("simulate.beatSound");
		bOpHintSound = pt.get<short>("simulate.hintSound") ? true : false;
		//脚本参数
		eDefibrState = CBLSConfigue::get_eDefibrState( pt.get<std::string>("scriptConfigue.defibrEnable") );
		defibrNum = pt.get<short>("scriptConfigue.defibrNum");
		succuQCPR =  pt.get<std::string>("scriptConfigue.condition") == "QCPR" ? true : false;
		//3D仿真演示系统参数
		s3DSystemPort = pt.get<short>("3DSystem.server_port");
		str3DSystemComputerName = pt.get<std::string>("3DSystem.server_host");
	}

	//判断是否能连接3D仿真演示系统
	bool CBLSConfigue::isCanLink3DSystem()
	{
		if( str3DSystemComputerName == "none" )
		{
			return false;
		}
		return true;
	}

	/*******************************************************************************/
	//功能：saveBLSConfigueToFile
	//功能： 保存使用者的脚本配置信息
	//参数：
	//返回值: 
	void CBLSConfigue::saveBLSConfigueToFile(const std::string &configueFile)
	{
		ptree   pt;
		read_ini( configueFile, pt);
		//提示音参数
		pt.put("simulate.beatSound", sDidaSoundHint);
		pt.put("simulate.hintSound", bOpHintSound ? 1 : 0);
		//脚本参数
		pt.put("scriptConfigue.defibrEnable", CBLSConfigue::get_strDefibrState(eDefibrState) );
		pt.put("scriptConfigue.defibrNum", defibrNum);
		pt.put("scriptConfigue.condition", succuQCPR ? "QCPR" : "defibr");
		//3D仿真演示系统参数
		pt.put("3DSystem.server_port", s3DSystemPort);
		pt.put("3DSystem.server_host", str3DSystemComputerName);
	}

	std::string CBLSConfigue::get_strDefibrState(_DefibrEnable eDefibr)
	{
		std::string   strDefibr;
		switch( eDefibr )
		{
		case _defibrCan:
			{
				strDefibr = "Enable";
				break;
			}
		case _defibrDia:
			{
				strDefibr = "Disable";
				break;
			}
		case _defibrNone:
			{
				strDefibr = "Ignore";
				break;
			}
		}
		return strDefibr;
	}

	_DefibrEnable CBLSConfigue::get_eDefibrState(const std::string &strDefibr)
	{
		_DefibrEnable  eDefibrState;
		if( strDefibr == "Enable" )
		{
			eDefibrState = _defibrCan;
		}
		else if( strDefibr == "Disable" )
		{
			eDefibrState = _defibrDia;
		}
		else 
		{
			eDefibrState = _defibrNone;
		}
		return eDefibrState;
	}

}}
