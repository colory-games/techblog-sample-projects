#include "MyManualSwitchModule.h"

#define LOCTEXT_NAMESPACE "FMyManualSwitchModule"

void FMyManualSwitchModule::StartupModule()
{
}

void FMyManualSwitchModule::ShutdownModule()
{
}

bool FMyManualSwitchModule::SupportsDynamicReloading()
{
    return true;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMyManualSwitchModule, MyManualSwitchModule);