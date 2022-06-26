#pragma once

#include "K2Node.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "KismetCompiler.h"

#include "K2Node_MyCompareInt.generated.h"

UCLASS(meta = (Keywords = "MyCompareInt CompareInt"))
class UK2Node_MyCompareInt : public UK2Node
{
    GENERATED_BODY()

    virtual void AllocateDefaultPins() override;
    virtual FText GetTooltipText() const override;
    virtual FLinearColor GetNodeTitleColor() const override;
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;

    virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
    virtual FText GetMenuCategory() const override;
    virtual FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;
};