/*****************************************************************************
 *            Copyright (C) - InfinyTech3D - All Rights Reserved             *
 *                                                                           *
 * Unauthorized copying of this file, via any medium is strictly prohibited  *
 * Proprietary and confidential.                                             *
 *                                                                           *
 * Written by Erik Pernod <erik.pernod@infinytech3d.com>, October 2019       *
 ****************************************************************************/

#include <InteractionTools/config.h>

namespace sofa
{

namespace component
{

//Here are just several convenient functions to help user to know what contains the plugin

extern "C" {
    SOFA_INTERACTIONTOOLS_API void initExternalModule();
    SOFA_INTERACTIONTOOLS_API const char* getModuleName();
    SOFA_INTERACTIONTOOLS_API const char* getModuleVersion();
    SOFA_INTERACTIONTOOLS_API const char* getModuleLicense();
    SOFA_INTERACTIONTOOLS_API const char* getModuleDescription();
    SOFA_INTERACTIONTOOLS_API const char* getModuleComponentList();
}

void initExternalModule()
{
    static bool first = true;
    if (first)
    {
        first = false;
    }
}

const char* getModuleName()
{
    return "InteractionTools";
}

const char* getModuleVersion()
{
    return "0.1";
}

const char* getModuleLicense()
{
    return "";
}


const char* getModuleDescription()
{
    return "plugin to interact with Sleeve tool.";
}

const char* getModuleComponentList()
{
    return "W3CDriver";
}

}

}

SOFA_LINK_CLASS(PliersToolManager)
SOFA_LINK_CLASS(PliersPositionsMapper)
