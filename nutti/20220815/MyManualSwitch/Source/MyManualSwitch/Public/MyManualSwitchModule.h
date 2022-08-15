#pragma once

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FMyManualSwitchModule"

class FGraphPanelNodeFactory_MyManualSwitch;

class FMyManualSwitchModule : public IModuleInterface
{
    TSharedPtr<FGraphPanelNodeFactory_MyManualSwitch> GraphPanelNodeFactory_MyManualSwitch;

public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    virtual bool SupportsDynamicReloading() override;
};

#undef LOCTEXT_NAMESPACE
