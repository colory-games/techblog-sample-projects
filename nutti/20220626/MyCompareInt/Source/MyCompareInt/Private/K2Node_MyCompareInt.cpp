#include "K2Node_MyCompareInt.h"

#include "BlueprintNodeSpawner.h"
#include "EdGraphSchema_K2.h"
#include "EditorCategoryUtils.h"
#include "GraphEditorSettings.h"
#include "K2Node_CallFunction.h"
#include "Kismet/KismetMathLibrary.h"
#include "EdGraphUtilities.h"

#define LOCTEXT_NAMESPACE "K2Node"

namespace
{
static const FName APinName(TEXT("A"));
static const FName BPinName(TEXT("B"));
static const FName GreaterPinName(TEXT("Greater"));
static const FName EqualPinName(TEXT("Equal"));
static const FName LessPinName(TEXT("Less"));
}

class FKCHandler_MyCompareInt : public FNodeHandlingFunctor
{
    TMap<FName, FBPTerminal*> BoolTermMap;
public:
    FKCHandler_MyCompareInt(FKismetCompilerContext& InCompilerContext) : FNodeHandlingFunctor(InCompilerContext)
    {
    }

    virtual void RegisterNets(FKismetFunctionContext& Context, UEdGraphNode* Node) override
    {
        FNodeHandlingFunctor::RegisterNets(Context, Node);

        {
            // ライブラリ関数「UKismetMathLibrary::GreaterEqual_IntInt」の実行結果を格納する
            // Boolean型の一時変数を作成する
            FBPTerminal* BoolTerm = Context.CreateLocalTerminal();
            BoolTerm->Type.PinCategory = UEdGraphSchema_K2::PC_Boolean;
            BoolTerm->Source = Node;
            BoolTerm->Name = Context.NetNameMap->MakeValidName(Node, TEXT("IsGreaterEqual"));
            BoolTermMap.Add(TEXT("IsGreaterEqual"), BoolTerm);
        }
        {
            // ライブラリ関数「UKismetMathLibrary::LessEqual_IntInt」の実行結果を格納する
            // Boolean型の一時変数を作成する
            FBPTerminal* BoolTerm = Context.CreateLocalTerminal();
            BoolTerm->Type.PinCategory = UEdGraphSchema_K2::PC_Boolean;
            BoolTerm->Source = Node;
            BoolTerm->Name = Context.NetNameMap->MakeValidName(Node, TEXT("IsLessEqual"));
            BoolTermMap.Add(TEXT("IsLessEqual"), BoolTerm);
        }
    }

    virtual void Compile(FKismetFunctionContext& Context, UEdGraphNode* Node) override
    {
        UK2Node_MyCompareInt* MyCompareIntNode = CastChecked<UK2Node_MyCompareInt>(Node);

        // 出力側の実行ピンを取得する
        UEdGraphPin* GreaterPin = MyCompareIntNode->FindPin(GreaterPinName);
        UEdGraphPin* EqualPin = MyCompareIntNode->FindPin(EqualPinName);
        UEdGraphPin* LessPin = MyCompareIntNode->FindPin(LessPinName);

        // 一時変数を取得する
        FBPTerminal* IsGreaterEqualTerm = BoolTermMap.FindRef(TEXT("IsGreaterEqual"));
        FBPTerminal* IsLessEqualTerm = BoolTermMap.FindRef(TEXT("IsLessEqual"));

        // 入力ピン「A」の変数を取得する
        UEdGraphPin* APin = MyCompareIntNode->FindPin(APinName);
        UEdGraphPin* ANet = FEdGraphUtilities::GetNetFromPin(APin);
        FBPTerminal* ATerm = Context.NetMap.FindRef(ANet);

        // 入力ピン「B」の変数を取得する
        UEdGraphPin* BPin = MyCompareIntNode->FindPin(BPinName);
        UEdGraphPin* BNet = FEdGraphUtilities::GetNetFromPin(BPin);
        FBPTerminal* BTerm = Context.NetMap.FindRef(BNet);

        {
            // ライブラリ関数「UKismetMathLibrary::GreaterEqual_IntInt」のUFunctionを取得する
            UEdGraphPin* FunctionPin = MyCompareIntNode->FindPin(TEXT("GreaterEqual_IntInt"));
            FBPTerminal* FunctionContext = Context.NetMap.FindRef(FunctionPin);
            UClass* FunctionClass = Cast<UClass>(FunctionPin->PinType.PinSubCategoryObject.Get());
            UFunction* FunctionPtr = FindUField<UFunction>(FunctionClass, FunctionPin->PinName);

            // ライブラリ関数を呼び出すステートメントを作成する
            FBlueprintCompiledStatement& CallFuncStatement = Context.AppendStatementForNode(MyCompareIntNode);
            CallFuncStatement.Type = KCST_CallFunction;
            CallFuncStatement.FunctionToCall = FunctionPtr;
            CallFuncStatement.FunctionContext = FunctionContext;
            CallFuncStatement.bIsParentContext = false;
            CallFuncStatement.LHS = IsGreaterEqualTerm;
            CallFuncStatement.RHS.Add(ATerm);
            CallFuncStatement.RHS.Add(BTerm);

            // ライブラリ関数の呼び出し結果ががFalseのときに、実行ピン「LessPin」に実行制御が移るステートメントを作成する
            FBlueprintCompiledStatement& GotoStatement = Context.AppendStatementForNode(MyCompareIntNode);
            GotoStatement.Type = KCST_GotoIfNot;
            GotoStatement.LHS = IsGreaterEqualTerm;
            Context.GotoFixupRequestMap.Add(&GotoStatement, LessPin);
        }

        {
            // ライブラリ関数「UKismetMathLibrary::LessEqual_IntInt」のUFunctionを取得する
            UEdGraphPin* FunctionPin = MyCompareIntNode->FindPin(TEXT("LessEqual_IntInt"));
            FBPTerminal* FunctionContext = Context.NetMap.FindRef(FunctionPin);
            UClass* FunctionClass = Cast<UClass>(FunctionPin->PinType.PinSubCategoryObject.Get());
            UFunction* FunctionPtr = FindUField<UFunction>(FunctionClass, FunctionPin->PinName);

            // ライブラリ関数を呼び出すステートメントを作成する
            FBlueprintCompiledStatement& CallFuncStatement = Context.AppendStatementForNode(MyCompareIntNode);
            CallFuncStatement.Type = KCST_CallFunction;
            CallFuncStatement.FunctionToCall = FunctionPtr;
            CallFuncStatement.FunctionContext = FunctionContext;
            CallFuncStatement.bIsParentContext = false;
            CallFuncStatement.LHS = IsLessEqualTerm;
            CallFuncStatement.RHS.Add(ATerm);
            CallFuncStatement.RHS.Add(BTerm);

            // ライブラリ関数の呼び出し結果がFalseのときに、実行ピン「GreaterPin」に実行制御が移るステートメントを作成する
            FBlueprintCompiledStatement& GotoStatement = Context.AppendStatementForNode(MyCompareIntNode);
            GotoStatement.Type = KCST_GotoIfNot;
            GotoStatement.LHS = IsLessEqualTerm;
            Context.GotoFixupRequestMap.Add(&GotoStatement, GreaterPin);
        }

        // いずれの条件も満たさない場合は、無条件で実行ピン「EqualPin」に実行制御が移るステートメントを作成する
        GenerateSimpleThenGoto(Context, *MyCompareIntNode, EqualPin);
    }
};

void UK2Node_MyCompareInt::AllocateDefaultPins()
{
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Int, APinName);
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Int, BPinName);
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, GreaterPinName);
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, EqualPinName);
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, LessPinName);

    {
        // ライブラリ関数「UKismetMathLibrary::GreaterEqual_IntInt」
        UEdGraphPin* FunctionPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UKismetMathLibrary::StaticClass(), TEXT("GreaterEqual_IntInt"));
        FunctionPin->bDefaultValueIsReadOnly = true;
        FunctionPin->bNotConnectable = true;
        FunctionPin->bHidden = true;
        UFunction* Function = FindUField<UFunction>(UKismetMathLibrary::StaticClass(), TEXT("GreaterEqual_IntInt"));
        if (Function != nullptr && Function->HasAllFunctionFlags(FUNC_Static))
        {
            UBlueprint* Blueprint = GetBlueprint();
            if (Blueprint != nullptr)
            {
                UClass* FunctionOwnerClass = Function->GetOuterUClass();
                if (!Blueprint->SkeletonGeneratedClass->IsChildOf(FunctionOwnerClass))
                {
                    FunctionPin->DefaultObject = FunctionOwnerClass->GetDefaultObject();
                }
            }
        }
    }

    {
        UEdGraphPin* FunctionPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UKismetMathLibrary::StaticClass(), TEXT("LessEqual_IntInt"));
        FunctionPin->bDefaultValueIsReadOnly = true;
        FunctionPin->bNotConnectable = true;
        FunctionPin->bHidden = true;
        UFunction* Function = FindUField<UFunction>(UKismetMathLibrary::StaticClass(), TEXT("LessEqual_IntInt"));
        if (Function != nullptr && Function->HasAllFunctionFlags(FUNC_Static))
        {
            UBlueprint* Blueprint = GetBlueprint();
            if (Blueprint != nullptr)
            {
                UClass* FunctionOwnerClass = Function->GetOuterUClass();
                if (!Blueprint->SkeletonGeneratedClass->IsChildOf(FunctionOwnerClass))
                {
                    FunctionPin->DefaultObject = FunctionOwnerClass->GetDefaultObject();
                }
            }
        }
    }
}

FText UK2Node_MyCompareInt::GetTooltipText() const
{
    return LOCTEXT("MyCompareInt_Tooltip", "MyCompareInt\nCompare one integer to another and indicate if it is greater, less than or the same.");
}

FLinearColor UK2Node_MyCompareInt::GetNodeTitleColor() const
{
    return GetDefault<UGraphEditorSettings>()->IntPinTypeColor;
}

FText UK2Node_MyCompareInt::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    return LOCTEXT("MyCompareInt", "MyCompareInt");
}

FSlateIcon UK2Node_MyCompareInt::GetIconAndTint(FLinearColor& OutColor) const
{
    static FSlateIcon Icon("EditorStyle", "Kismet.AllClasses.FunctionIcon");
    return Icon;
}

void UK2Node_MyCompareInt::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    UClass* ActionKey = GetClass();
    if (ActionRegistrar.IsOpenForRegistration(ActionKey))
    {
        UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
        check(NodeSpawner != nullptr);

        ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
    }
}

FText UK2Node_MyCompareInt::GetMenuCategory() const
{
    return FEditorCategoryUtils::GetCommonCategory(FCommonEditorCategory::FlowControl);
}

FNodeHandlingFunctor* UK2Node_MyCompareInt::CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const
{
    return new FKCHandler_MyCompareInt(CompilerContext);
}

#undef LOCTEXT_NAMESPACE