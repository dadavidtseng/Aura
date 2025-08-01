//----------------------------------------------------------------------------------------------------
// OverlayWidgetController.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

//----------------------------------------------------------------------------------------------------
void UOverlayWidgetController::BroadcastInitialValues()
{
	// Make sure to call `BroadcastInitialValues` after `UAuraAttributeSet` is initialized.
	UAuraAttributeSet const* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

//----------------------------------------------------------------------------------------------------
void UOverlayWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet const* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

//----------------------------------------------------------------------------------------------------
void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

//----------------------------------------------------------------------------------------------------
void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

//----------------------------------------------------------------------------------------------------
void UOverlayWidgetController::ManaChanged(FOnAttributeChangeData const& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

//----------------------------------------------------------------------------------------------------
void UOverlayWidgetController::MaxManaChanged(FOnAttributeChangeData const& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
