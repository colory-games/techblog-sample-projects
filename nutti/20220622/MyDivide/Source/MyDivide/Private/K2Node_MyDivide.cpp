#include "K2Node_MyDivide.h"

#include "BlueprintNodeSpawner.h"
#include "EdGraphSchema_K2.h"
#include "EditorCategoryUtils.h"
#include "GraphEditorSettings.h"
#include "K2Node_CallFunction.h"
#include "Kismet/KismetMathLibrary.h"

#define LOCTEXT_NAMESPACE "K2Node"

namespace
{
static const FName APinName(TEXT("A"));
static const FName BPinName(TEXT("B"));
static const FName QuotientPinName(TEXT("Quotient"));
static const FName RemainderPinName(TEXT("Remainder"));
}

void UK2Node_MyDivide::AllocateDefaultPins()
{
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Int, APinName);
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Int, BPinName);
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Int, QuotientPinName);
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Int, RemainderPinName);
}

FText UK2Node_MyDivide::GetTooltipText() const
{
    // Tooltipで表示するテキストを返す
    return LOCTEXT("MyDivide_Tooltip", "MyDivide\nGet quotient and remainder from dividing two integer");
}

FLinearColor UK2Node_MyDivide::GetNodeTitleColor() const
{
    // 整数型（Integer）のピンと同じ色をタイトル部の色とする
    return GetDefault<UGraphEditorSettings>()->IntPinTypeColor;
}

FText UK2Node_MyDivide::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    // タイトル部に表示するテキストを返す
    return LOCTEXT("MyDivide", "MyDivide");
}

FSlateIcon UK2Node_MyDivide::GetIconAndTint(FLinearColor& OutColor) const
{
    // 関数アイコンをタイトル部に表示するアイコンとする
    static FSlateIcon Icon("EditorStyle", "Kismet.AllClasses.FunctionIcon");
    return Icon;
}

bool UK2Node_MyDivide::IsNodePure() const
{
    return true;
}

void UK2Node_MyDivide::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    UClass* ActionKey = GetClass();
    if (ActionRegistrar.IsOpenForRegistration(ActionKey))
    {
        UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
        check(NodeSpawner != nullptr);

        ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
    }
}

FText UK2Node_MyDivide::GetMenuCategory() const
{
    // カテゴリ「Math」に登録する
    return FEditorCategoryUtils::GetCommonCategory(FCommonEditorCategory::Math);
}

void UK2Node_MyDivide::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
    // 「/」ノードの配置
    UK2Node_CallFunction* CallDivideFunction = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
    CallDivideFunction->SetFromFunction(UKismetMathLibrary::StaticClass()->FindFunctionByName(GET_MEMBER_NAME_CHECKED(UKismetMathLibrary, Divide_IntInt)));
    CallDivideFunction->AllocateDefaultPins();
    CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(QuotientPinName), *CallDivideFunction->GetReturnValuePin());
    CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(APinName), *CallDivideFunction->FindPinChecked(TEXT("A")));
    CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(BPinName), *CallDivideFunction->FindPinChecked(TEXT("B")));

    // 「%」ノードの配置
    UK2Node_CallFunction* CallPercentFunction = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
    CallPercentFunction->SetFromFunction(UKismetMathLibrary::StaticClass()->FindFunctionByName(GET_MEMBER_NAME_CHECKED(UKismetMathLibrary, Percent_IntInt)));
    CallPercentFunction->AllocateDefaultPins();
    CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(RemainderPinName), *CallPercentFunction->GetReturnValuePin());
    CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(APinName), *CallPercentFunction->FindPinChecked(TEXT("A")));
    CompilerContext.MovePinLinksToIntermediate(*FindPinChecked(BPinName), *CallPercentFunction->FindPinChecked(TEXT("B")));
}

#undef LOCTEXT_NAMESPACE