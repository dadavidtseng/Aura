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
	GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Red,TEXT("EffectApplied"));
}
