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
	//���ܣ�������������������
	//������
	//      configueFile�� �����ļ���Ϣ
	//����ֵ:  
	void CBLSConfigue::parseBLSConfigue(const std::string &configueFile)
	{
		ptree   pt;
		ini_parser::read_ini( configueFile, pt);
		//��ʾ������
		sDidaSoundHint = pt.get<short>("simulate.beatSound");
		bOpHintSound = pt.get<short>("simulate.hintSound") ? true : false;
		//�ű�����
		eDefibrState = CBLSConfigue::get_eDefibrState( pt.get<std::string>("scriptConfigue.defibrEnable") );
		defibrNum = pt.get<short>("scriptConfigue.defibrNum");
		succuQCPR =  pt.get<std::string>("scriptConfigue.condition") == "QCPR" ? true : false;
		//3D������ʾϵͳ����
		s3DSystemPort = pt.get<short>("3DSystem.server_port");
		str3DSystemComputerName = pt.get<std::string>("3DSystem.server_host");
	}

	//�ж��Ƿ�������3D������ʾϵͳ
	bool CBLSConfigue::isCanLink3DSystem()
	{
		if( str3DSystemComputerName == "none" )
		{
			return false;
		}
		return true;
	}

	/*******************************************************************************/
	//���ܣ�saveBLSConfigueToFile
	//���ܣ� ����ʹ���ߵĽű�������Ϣ
	//������
	//����ֵ: 
	void CBLSConfigue::saveBLSConfigueToFile(const std::string &configueFile)
	{
		ptree   pt;
		read_ini( configueFile, pt);
		//��ʾ������
		pt.put("simulate.beatSound", sDidaSoundHint);
		pt.put("simulate.hintSound", bOpHintSound ? 1 : 0);
		//�ű�����
		pt.put("scriptConfigue.defibrEnable", CBLSConfigue::get_strDefibrState(eDefibrState) );
		pt.put("scriptConfigue.defibrNum", defibrNum);
		pt.put("scriptConfigue.condition", succuQCPR ? "QCPR" : "defibr");
		//3D������ʾϵͳ����
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
