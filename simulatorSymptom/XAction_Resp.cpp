#include ".\XAction_Resp.h"
#include <boost/format.hpp>

#include "..\ElementParse\SAction_Resp.h"

#include "..\Common\PatientTypeFactory.h"
#include "..\Common\PatientRuleInterfaceGlobal.h"


namespace jysoft { namespace simulator 
{
	CXAction_Resp::CXAction_Resp(void)
	{
		m_bRelatePercent  = false;
	}

	CXAction_Resp::CXAction_Resp(eRespMode enumRespMode, long nRespRate)
	{
		m_eRespMode  = enumRespMode;
		m_lBreathRate = nRespRate;
		m_bRelatePercent  = false;
	}

	CXAction_Resp::~CXAction_Resp(void)
	{
	}

	bool CXAction_Resp::isKindOf(const std::string &strClassName)
	{
		if( strClassName == "CXAction_Resp")
		{
			return true;
		}
		return CXActionVirtual::isKindOf(strClassName);
	}

	/*******************************************************************************/
	// 函数名称： GetActionCaption
	// 功能：   返回体征标识名
	// 参数：   
	// 返回值: 
	std::string CXAction_Resp::getActionCaption() const
	{
		return CSAction_Resp::getAction_Resp_Caption();
	}

	bool CXAction_Resp::Parse_ActionFromXml(pugi::xml_node* pXMLShapeNode)
	{
		std::string  strRespMode;
		bool bParseSec = CSAction_Resp::explainParamsFromXML(pXMLShapeNode, /*out*/&strRespMode, /*out*/&m_lBreathRate);
		if( bParseSec )
		{
			m_eRespMode = IRespRule::Get_eRespMode( strRespMode );
		}
		return bParseSec ;
	}

	/*******************************************************************************/
	// 函数名称： CombineActionParam
	// 功能：   整合体征设置参数
	// 参数：   CXActionVirtual *pDstActionVir:
	// 返回值: 
	void CXAction_Resp::CombineActionParam(CXActionVirtual *pDstActionVir)
	{
	#ifdef  _DEBUG
		if( getActionCaption() != pDstActionVir->getActionCaption() )
			BOOST_ASSERT( 0 );
	#endif
		CXAction_Resp *pDestAction_Breath = (CXAction_Resp *)pDstActionVir;
		//呼吸模式
		m_eRespMode   = pDestAction_Breath->GetRespMode();
		//呼吸次数
		m_lBreathRate = pDestAction_Breath->GetBreathRate();
		//百分比增减
		m_bRelatePercent = pDestAction_Breath->Get_bRelatePercent();
	}

	/*******************************************************************************/
	// 函数名称： CloneAction
	// 功能：   拷贝体征参数
	// 参数：   
	// 返回值: 
	CXActionVirtual * CXAction_Resp::CloneAction()
	{
		CXAction_Resp *pNewAction = new CXAction_Resp(m_eRespMode, m_lBreathRate);
		pNewAction->Set_bRelatePercent( m_bRelatePercent );
		return pNewAction;
	}

	long  CXAction_Resp::GetValue_AbsoluteRR(long lSrcRR)
	{
		long   lRRValue  = m_lBreathRate;
		if( m_bRelatePercent == true )
		{
			lRRValue  = (1+m_lBreathRate/100.0f) * lSrcRR;
		}
		return lRRValue;
	}
}}
