#pragma once

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FMyDivideModule"

class FMyDivideModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    virtual bool SupportsDynamicReloading() override;
};

#undef LOCTEXT_NAMESPACE
