#include "MyDivideModule.h"

#define LOCTEXT_NAMESPACE "FMyDivideModule"

void FMyDivideModule::StartupModule()
{
}

void FMyDivideModule::ShutdownModule()
{
}

bool FMyDivideModule::SupportsDynamicReloading()
{
    return true;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMyDivideModule, MyDivideModule);