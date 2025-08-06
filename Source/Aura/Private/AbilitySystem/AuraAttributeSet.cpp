//----------------------------------------------------------------------------------------------------
// AuraAttributeSet.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "AbilitySystem/AuraAttributeSet.h"

#include <GameplayEffectExtension.h>
#include <GameFramework/Character.h>
#include <Net/UnrealNetwork.h>

#include "AbilitySystemBlueprintLibrary.h"

//----------------------------------------------------------------------------------------------------
UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(10.f);
	InitMaxHealth(100.f);
	InitMana(30.f);
	InitMaxMana(40.f);
}

//----------------------------------------------------------------------------------------------------
/// @brief Register `FGameplayAttributeData` variables for replication.
/// @param OutLifetimeProps Array that stores the properties to be replicated.
void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// COND_None means it should always replicate; no condition
	// `REPNOTIFY_Always` means the OnRep function will always be triggered when replication happens
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::PreAttributeChange(FGameplayAttribute const& Attribute,
                                           float&                    NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::PostGameplayEffectExecute(FGameplayEffectModCallbackData const& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties EffectProperties;
	SetEffectProperties(Data, EffectProperties);
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_Health(FGameplayAttributeData const& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_MaxHealth(FGameplayAttributeData const& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_Mana(FGameplayAttributeData const& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_MaxMana(FGameplayAttributeData const& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana)
}

//----------------------------------------------------------------------------------------------------
// Source = causer of the effect, Target = target of the effect (owner of AbilitySystemComponent)
void UAuraAttributeSet::SetEffectProperties(FGameplayEffectModCallbackData const& Data,
                                            FEffectProperties&                    EffectProperties) const
{
	EffectProperties.EffectContextHandle          = Data.EffectSpec.GetContext();
	EffectProperties.SourceAbilitySystemComponent = EffectProperties.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (!IsValid(EffectProperties.SourceAbilitySystemComponent)) return;
	if (!EffectProperties.SourceAbilitySystemComponent->AbilityActorInfo.IsValid()) return;
	if (!EffectProperties.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.IsValid()) return;

	EffectProperties.SourceAvatarActor = EffectProperties.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
	EffectProperties.SourceController  = EffectProperties.SourceAbilitySystemComponent->AbilityActorInfo->PlayerController.Get();

	// If `SourceController` is nullptr but `SourceAvatarActor` is not nullptr,
	// we can get `AController` by casting `SourceAvatarActor` to `APawn`.
	if (EffectProperties.SourceController == nullptr && EffectProperties.SourceAvatarActor != nullptr)
	{
		if (APawn const* Pawn = Cast<APawn>(EffectProperties.SourceAvatarActor))
		{
			EffectProperties.SourceController = Pawn->GetController();
		}
		if (EffectProperties.SourceController != nullptr)
		{
			ACharacter* SourceCharacter = Cast<ACharacter>(EffectProperties.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.TargetAvatarActor            = Data.Target.AbilityActorInfo->AvatarActor.Get();
		EffectProperties.TargetController             = Data.Target.AbilityActorInfo->PlayerController.Get();
		EffectProperties.TargetCharacter              = Cast<ACharacter>(EffectProperties.TargetAvatarActor);
		EffectProperties.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectProperties.TargetAvatarActor);
	}
}
