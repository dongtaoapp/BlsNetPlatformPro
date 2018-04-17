#pragma once
#include <string>
#include ".\scriptflowengine_global.h"

#include "..\common\CommonGlobal.h"


namespace jysoft { namespace flowEngine 
{
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     ������Ϣ������
	�����ˣ�	 hjg
	����ʱ�䣺   2018/2/21
	//-----------------------------------------------------------------------------------------------------------------*/
    class SCRIPTFLOWENGINESHARED_EXPORT CBLSConfigue
	{
	public:
		CBLSConfigue(void);
		virtual ~CBLSConfigue(void);
	public:
		/*******************************************************************************/
		//���ܣ�������������������
		//������
		//      configueFile�� �����ļ���Ϣ
		//����ֵ:  
		void parseBLSConfigue(const std::string &configueFile);
		//�ж��Ƿ�������3D������ʾϵͳ
		bool isCanLink3DSystem();
		/*******************************************************************************/
		//���ܣ�saveBLSConfigueToFile
		//���ܣ� ����ʹ���ߵĽű�������Ϣ
		//������
		//����ֵ: 
		void saveBLSConfigueToFile(const std::string &configueFile);
	public:
		//�����ʾ(0:none; 100bpm:1; 110bpm:2; 120bpm:3)
		inline  short getDidaSoundHint() { return sDidaSoundHint; };
		inline  void setDidaSoundHint( short sDidaSound ) { sDidaSoundHint = sDidaSound; };
		//������ʾ��
		inline  bool isHintSound() { return bOpHintSound; };
		inline  void setIsHintSound(bool bHintSound) { bOpHintSound = bHintSound; };
		//�Ƿ��ܳ���
		inline _DefibrEnable getDefibrState() { return eDefibrState; };
		inline void setDefibrState(_DefibrEnable eDefibr) { eDefibrState = eDefibr; };
		inline short  getDefibrSumNumber() { return defibrNum; };
		inline void setDefibrSumNumber(short sNum) { defibrNum = sNum; };
		inline bool getScriptSuccessByQCPR() { return succuQCPR; };
		inline void setIsScriptSuccessByQCPR( bool bQCPR) { succuQCPR = bQCPR; };
		//3D������ʾϵͳ����
		inline std::string   get_3DSystemComputerName() { return str3DSystemComputerName; };
		inline void set_3DSystemComputerName(const std::string &strComputerName ) { str3DSystemComputerName = strComputerName; };
		//����˿ں�
		inline short  get_3DSystemPort() { return s3DSystemPort; };
	public:
		static std::string get_strDefibrState(_DefibrEnable eDefibr);
		static _DefibrEnable get_eDefibrState(const std::string &strDefibr);
	protected:  //��ʾ������
		short                sDidaSoundHint;           //�������ʾ(0:none; 100bpm:1; 110bpm:2; 120bpm:3)
		bool                 bOpHintSound;             //������ʾ��
	protected: //�ű�����
		_DefibrEnable        eDefibrState;
		short                defibrNum;
		bool                 succuQCPR;
	protected: //3D������ʾϵͳ����
		short                s3DSystemPort;            //�˿ں�
		std::string          str3DSystemComputerName;  //���������
	};
}}
