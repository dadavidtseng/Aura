//----------------------------------------------------------------------------------------------------
// AttributeMenuWidgetController.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

//----------------------------------------------------------------------------------------------------
void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet const* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	if (!IsValid(AttributeInfo))
	{
		UE_LOG(LogTemp, Error, TEXT("(UAttributeMenuWidgetController::BroadcastInitialValues) AttributeInfo is not valid!"));
		return;
	}

	// FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Strength);
	//
	// Info.AttributeValue = AS->GetStrength();
	// AttributeInfoDelegate.Broadcast(Info);		// Widget need to bind to this delegate before `UAttributeMenuWidgetController::BroadcastInitialValues()`

	for (TPair<FGameplayTag, FGameplayAttribute(*)()> const& Pair : AS->TagsToAttributesMap)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

//----------------------------------------------------------------------------------------------------
void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet const* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	if (!IsValid(AttributeInfo))
	{
		UE_LOG(LogTemp, Error, TEXT("(UAttributeMenuWidgetController::BindCallbacksToDependencies) AttributeInfo is not valid!"));
		return;
	}

	for (auto& Pair : AS->TagsToAttributesMap)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](FOnAttributeChangeData const& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			});
	}
}

//----------------------------------------------------------------------------------------------------
void UAttributeMenuWidgetController::BroadcastAttributeInfo(FGameplayTag const&       AttributeTag,
                                                            FGameplayAttribute const& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue     = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
