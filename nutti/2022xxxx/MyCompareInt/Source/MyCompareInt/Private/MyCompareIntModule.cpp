#include "MyCompareIntModule.h"

#define LOCTEXT_NAMESPACE "FMyCompareIntModule"

void FMyCompareIntModule::StartupModule()
{
}

void FMyCompareIntModule::ShutdownModule()
{
}

bool FMyCompareIntModule::SupportsDynamicReloading()
{
    return true;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMyCompareIntModule, MyCompareIntModule);