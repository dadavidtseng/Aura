//----------------------------------------------------------------------------------------------------
// AttributeMenuWidgetController.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

//----------------------------------------------------------------------------------------------------
void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo)

	// FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Strength);
	//
	// Info.AttributeValue = AS->GetStrength();
	// AttributeInfoDelegate.Broadcast(Info);		// Widget need to bind to this delegate before `UAttributeMenuWidgetController::BroadcastInitialValues()`

	for (TPair<FGameplayTag, FGameplayAttribute(*)()>& Pair : AS->TagsToAttributesMap)
	{
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);

		FGameplayAttribute Attribute = Pair.Value();
		Info.AttributeValue          = Attribute.GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}
}

//----------------------------------------------------------------------------------------------------
void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
}
