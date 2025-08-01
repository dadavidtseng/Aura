//----------------------------------------------------------------------------------------------------
// OverlayWidgetController.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include <CoreMinimal.h>

#include "UI/WidgetController/AuraWidgetController.h"

#include <OverlayWidgetController.generated.h>

//-Forward-Declaration--------------------------------------------------------------------------------
struct FOnAttributeChangeData;

//----------------------------------------------------------------------------------------------------
/// @brief Type declaration.
/// Dynamic -> Supports Unreal's reflection system, so you can bind it in Blueprint.
/// Multicast -> Allows multiple listeners to be bound at the same time.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);

//----------------------------------------------------------------------------------------------------
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	/// @brief Event instances that Blueprint can bind to.
	/// These multicast delegates broadcast attribute changes to Blueprint UI or other listeners.
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;

protected:
	/// @brief Callback functions bound to attribute change events.
	/// These functions receive data from the ability system and broadcast it to Blueprint via delegates.
	void HealthChanged(FOnAttributeChangeData const& Data) const;
	void MaxHealthChanged(FOnAttributeChangeData const& Data) const;
	void ManaChanged(FOnAttributeChangeData const& Data) const;
	void MaxManaChanged(FOnAttributeChangeData const& Data) const;
};
