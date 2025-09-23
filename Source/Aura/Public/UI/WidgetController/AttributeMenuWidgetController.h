//----------------------------------------------------------------------------------------------------
// AttributeMenuWidgetController.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include <CoreMinimal.h>

#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/WidgetController/AuraWidgetController.h"

#include <AttributeMenuWidgetController.generated.h>

//-Forward-Declaration--------------------------------------------------------------------------------
class UAttributeInfo;
struct FAuraAttributeInfo;

//----------------------------------------------------------------------------------------------------
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, FAuraAttributeInfo const&, Info);


//----------------------------------------------------------------------------------------------------
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS | Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

private:
	void BroadcastAttributeInfo(FGameplayTag const& AttributeTag, FGameplayAttribute const& Attribute) const;
};
