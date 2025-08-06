//----------------------------------------------------------------------------------------------------
// AuraAbilitySystemComponent.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "AbilitySystem/AuraAbilitySystemComponent.h"

//----------------------------------------------------------------------------------------------------
void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

//----------------------------------------------------------------------------------------------------
void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent*    AbilitySystemComponent,
                                                FGameplayEffectSpec const&  GameplayEffectSpec,
                                                FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	GameplayEffectSpec.GetAllAssetTags(TagContainer);
	for (FGameplayTag const& Tag : TagContainer)
	{
		FString const Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
		//TODO: Broadcast the tag to the WidgetController
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red, Msg);
	}
}
