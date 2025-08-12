//----------------------------------------------------------------------------------------------------
// AuraAbilitySystemComponent.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include <CoreMinimal.h>
#include <AbilitySystemComponent.h>
#include <AuraAbilitySystemComponent.generated.h>

//----------------------------------------------------------------------------------------------------
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, FGameplayTagContainer const& /*AssetTags*/);

//----------------------------------------------------------------------------------------------------
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void             AbilityActorInfoSet();
	FEffectAssetTags EffectAssetTags;

protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, FGameplayEffectSpec const& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
