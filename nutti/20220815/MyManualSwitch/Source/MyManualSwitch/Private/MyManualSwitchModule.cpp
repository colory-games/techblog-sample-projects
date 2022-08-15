#include "MyManualSwitchModule.h"

#include "EdGraphUtilities.h"
#include "K2Node_MyManualSwitch.h"
#include "SGraphNodeMyManualSwitch.h"

#define LOCTEXT_NAMESPACE "FMyManualSwitchModule"

class FGraphPanelNodeFactory_MyManualSwitch : public FGraphPanelNodeFactory
{
    virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* Node) const override
    {
        if (UK2Node_MyManualSwitch* MyManualSwitch = Cast<UK2Node_MyManualSwitch>(Node))
        {
            return SNew(SGraphNodeMyManualSwitch, MyManualSwitch);
        }

        return nullptr;
    }
};

void FMyManualSwitchModule::StartupModule()
{
    GraphPanelNodeFactory_MyManualSwitch = MakeShareable(new FGraphPanelNodeFactory_MyManualSwitch());
    FEdGraphUtilities::RegisterVisualNodeFactory(GraphPanelNodeFactory_MyManualSwitch);
}

void FMyManualSwitchModule::ShutdownModule()
{
    if (GraphPanelNodeFactory_MyManualSwitch.IsValid())
    {
        FEdGraphUtilities::UnregisterVisualNodeFactory(GraphPanelNodeFactory_MyManualSwitch);
        GraphPanelNodeFactory_MyManualSwitch.Reset();
    }
}

bool FMyManualSwitchModule::SupportsDynamicReloading()
{
    return true;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMyManualSwitchModule, MyManualSwitchModule);