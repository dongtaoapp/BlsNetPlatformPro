#pragma once
#include <string>
#include <boost/optional.hpp>
#include ".\cprmoduls_global.h"

#include "..\common\CommonGlobal.h"

using namespace boost;
namespace jysoft{  namespace cpr 
{
	/*-----------------------------------------------------------------------------------------------------------------
	��˵����     CPR����������
	�����ˣ�	 hjg
	����ʱ�䣺   2009/5/22               �޸����ڣ�2018/3/19
	XML��ʽ���壺 
	        <?xml version="1.0" encoding="utf-8"?>
	        <QCPRConfig opMode="practise">
	           <!--�ű�����ʱ�� enable="" /-->
	           <scriptTime enable="true">120</scriptTime>
	           <!--QCPR���� enable="" /-->
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
		//���ܣ������ķθ���������Ϣ
		//������
		//      const std::string &configueFile�� ���������ļ���Ϣ
		//����ֵ:  
		void loadCPRConfigue(const std::string &configueFile);
		/*******************************************************************************/
		//���ܣ�SaveCPRConfigueToFile
		//���ܣ� ����ʹ���ߵ�CPR������Ϣ������BLS�ű�������
		//������
		//����ֵ: 
		void saveCPRConfigueToFile(const std::string &strUserConfigueFile, _CPRManageState eCPRMode);
		//����
		void copyConfigue(CCPRConfigue  *pCPRConfigue);
	public:
		//��ѹ��Сֵ
		inline  int getLowerPressureDepth() { return lowerPressureDepth; };
		inline  void set_LowerPressureDepth(int nDepth) { lowerPressureDepth = nDepth; };
		//��ѹ���ֵ
		int getOverPressureDepth(bool bPresets = false) ;
		inline  void setOverPressureDepth(int nDepth) { overPressureDepth = nDepth; };
		inline  bool isOverPressureDepthValidate() { return bOverPressureValidate; };
		inline  void setOverPressureDepthValidate(bool bValidate) { bOverPressureValidate = bValidate; };
		//��������Сֵ
		inline  int getLowerBreathVolume() { return lowerBreathVolume; };
		inline void setLowerBreathVolume( int nBreathVolume ) { lowerBreathVolume = nBreathVolume; };
		//���������ֵ
		inline  int getOverBreathVolume() { return overBreathVolume; };
		inline void setOverBreathVolume( int nBreathVolume ) { overBreathVolume = nBreathVolume; };
		//ͨ��ʱ��
		inline int getLowerRespTime() { return lowerRespTime; };
		inline int getOverRespTime() { return overRespTime; }
		//���ѭ������ģʽ
		inline  _CPRManageState getFiveCycleMode() { return eFiveCycleMode; };
		//�Ƿ����ѭ��CPR����
		inline  bool isFiveCycleRule() { return cycleNumber == 3 ? false : true; };
		void setIsFiveCycleRule(bool bFiveCycleRule) 
		{ 
			if( bFiveCycleRule )
				cycleNumber  = 5;
			else
				cycleNumber  = 3;
		};
		//�Ƿ�Ϊרҵ��������
		inline  bool isSpecialityMemberOp() { return bSpecialityMemberOp; };
		inline void setIsSpecialityMemberOp(bool bSpecialityOp)  { bSpecialityMemberOp = bSpecialityOp; };
		//��רҵ��Ա����: ��ѹ����
		inline  int  getSumPressureNumber() { return sumPressureNumber; };
		inline  void setSumPressureNumber(int nNumber) { sumPressureNumber = nNumber; };
	public://QCPR����
		//�ű�����ʱ��
		inline optional<short> getScriptSumTime() { return scriptTime; };
		//�ж�ʱ��
		inline optional<short> getInterruptTime() { return interruptTime; };
		//��ѹռ��
		inline optional<short> getCCFPecent() { return CCF; };
		//��ѹ��ȷռ��
		inline optional<short> getPRightPecent() { return rightPPce; };
		//������ȷռ��
		inline optional<short> getBRightPecent() { return rightBPce; };
		//��ѹƵ����ȷռ��
		inline optional<short> getPRatePecent() { return ratePPce; };
	public:
		//�������ѭ������ģʽ
		void setFiveCycleMode(_CPRManageState eMode) { eFiveCycleMode = eMode; };
		//����Ĭ�ϵĲ���ֵ
		void setDefaultParams(_CPRManageState eMode);
	protected:
		int                  lowerPressureDepth;      //��ѹ��Сֵ
		int                  overPressureDepth;       //��ѹ���ֵ
		int                  lowerBreathVolume;       //��������Сֵ
		int                  overBreathVolume;        //���������ֵ
		//��С�����ͨ��ʱ��(��λ��ms)
		int                  lowerRespTime;
		int                  overRespTime;
		_CPRManageState      eFiveCycleMode;           //���ѭ������ģʽ
		bool                 bSpecialityMemberOp;      //�Ƿ�Ϊרҵ��������  hjg 2011.4 add
		bool                 bOverPressureValidate;    //�Ƿ��������ѹ��� hjg 2014.3 add
	protected://QCPR����
		//�ű�����ʱ��
		optional<short>      scriptTime;
		//�ж�ʱ��
		optional<short>      interruptTime;
		//��ѹռ��
		optional<short>      CCF;
		//��ѹ��ȷռ��
		optional<short>      rightPPce;
		//������ȷռ��
		optional<short>      rightBPce;
		//��ѹƵ����ȷռ��
		optional<short>      ratePPce;
	private:
		int                  cycleNumber;             //רҵ��Ա����:   ѭ��CPR��������
		int                  sumPressureNumber;       //��רҵ��Ա����: ��ѹ����
	};
}}
