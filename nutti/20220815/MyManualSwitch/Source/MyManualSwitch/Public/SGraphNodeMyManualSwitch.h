#pragma once

#include "KismetNodes/SGraphNodeK2Base.h"

class UK2Node_MyManualSwitch;

class SGraphNodeMyManualSwitch : public SGraphNodeK2Base
{
    SLATE_BEGIN_ARGS(SGraphNodeMyManualSwitch)
    {
    }
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs, UK2Node_MyManualSwitch* InNode);

    virtual void CreatePinWidgets() override;
};