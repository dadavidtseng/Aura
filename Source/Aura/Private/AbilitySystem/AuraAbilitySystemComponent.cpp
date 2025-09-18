//----------------------------------------------------------------------------------------------------
// AuraAbilitySystemComponent.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"

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
	EffectAssetTags.Broadcast(TagContainer);
}
