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
void UAuraAbilitySystemComponent::AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>> const& StartupAbilities)
{
	for (TSubclassOf AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		// GiveAbility(AbilitySpec);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
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
