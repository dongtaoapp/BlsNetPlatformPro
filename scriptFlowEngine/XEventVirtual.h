#pragma once
#include <pugixml.hpp>
#include ".\IGetPhysiologyActionObj.h"

#include "..\SimulatorBase\VirEventIrp.h"

#include "..\SimulatorSymptom\XVirtualComponent.h"


namespace jysoft { namespace flowEngine
{
    class CXEventVirtual : public simulator::CXVirtualComponent
    {
    public:
        CXEventVirtual(void);
        virtual ~CXEventVirtual(void);
    public:
        virtual bool isKindOf(const std::string &strClassName);
    public:
        /*******************************************************************************/
        // ????????? GetEventCaption
        // ?????   ?????????????
        // ??????
        // ?????:
        virtual std::string getEventCaption() = 0;
        /*******************************************************************************/
        // ????????? Parse_EventFromXml
        // ?????   ????????????????
        // ??????   IXMLDOMNode *pXMLShapeNode:
        // ?????:
        virtual bool Parse_EventFromXml(pugi::xml_node *pXMLShapeNode, IGetPhysiologyActionObj *pGetActionObj) = 0;
        /*******************************************************************************/
        // ?????   ??????څ?????
        // ??????
        // ?????: ????(TRUE)????????(FALSE)
        virtual bool IsSatisfactionEvent() = 0;
        /*******************************************************************************/
        // ?????   ?????????????????????
        // ??????
        // ?????:
        virtual void ClearSatisfactionInfo() = 0;
        /*******************************************************************************/
        // ?????   ???????
        // ??????
        // ?????:
        virtual void DoHandleEventIrp(irp::CVirEventIrp  *pEventIrp) = 0;
    public:
        bool isEventNameOf(const std::string &caption);
    };
}}
