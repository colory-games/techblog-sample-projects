#pragma once

#include "K2Node.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "KismetCompiler.h"

#include "K2Node_MyDivide.generated.h"

UCLASS(meta = (Keywords = "MyDivide Divide"))
class UK2Node_MyDivide : public UK2Node
{
    GENERATED_BODY()

    // クラスUEdGraphNodeからオーバーライドしたメンバ関数
    virtual void AllocateDefaultPins() override;
    virtual FText GetTooltipText() const override;
    virtual FLinearColor GetNodeTitleColor() const override;
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;

    // クラスUK2Nodeからオーバーライドしたメンバ関数
    virtual bool IsNodePure() const override;
    virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
    virtual FText GetMenuCategory() const override;
    void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
};