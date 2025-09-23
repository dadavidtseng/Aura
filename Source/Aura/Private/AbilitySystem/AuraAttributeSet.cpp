//----------------------------------------------------------------------------------------------------
// AuraAttributeSet.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "AbilitySystem/AuraAttributeSet.h"

#include <GameplayEffectExtension.h>
#include <GameFramework/Character.h>
#include <Net/UnrealNetwork.h>

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"

//----------------------------------------------------------------------------------------------------
UAuraAttributeSet::UAuraAttributeSet()
{
	FAuraGameplayTags const& GameplayTags = FAuraGameplayTags::Get();

	// https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Core/Misc/TAttribute/BindStatic?application_version=5.6
	// FAttributeSignature StrengthDelegate;
	// StrengthDelegate.BindStatic(GetStrengthAttribute);
	// TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Strength, StrengthDelegate);

	// Primary Attribute
	TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Resilience, GetResilienceAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Primary_Vigor, GetVigorAttribute);

	// Secondary Attribute
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_Armor, GetArmorAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_BlockChance, GetBlockChanceAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributesMap.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);
}

//----------------------------------------------------------------------------------------------------
/// @brief Register `FGameplayAttributeData` variables for replication.
/// @param OutLifetimeProps Array that stores the properties to be replicated.
void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// COND_None means it should always replicate; no condition
	// `REPNOTIFY_Always` means the OnRep function will always be triggered when replication happens

	//-Primary-Attributes---------------------------------------------------------------------------------
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always)

	//-Secondary-Attributes-------------------------------------------------------------------------------
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockChance, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always)

	//-Vital-Attributes-----------------------------------------------------------------------------------
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always)
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

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_Strength(FGameplayAttributeData const& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_Intelligence(FGameplayAttributeData const& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldIntelligence)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_Resilience(FGameplayAttributeData const& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldResilience)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_Vigor(FGameplayAttributeData const& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldVigor)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_Armor(FGameplayAttributeData const& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldArmor)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_ArmorPenetration(FGameplayAttributeData const& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, OldArmorPenetration)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_BlockChance(FGameplayAttributeData const& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockChance, OldBlockChance)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_CriticalHitChance(FGameplayAttributeData const& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitChance, OldCriticalHitChance)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_CriticalHitDamage(FGameplayAttributeData const& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldCriticalHitDamage)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_CriticalHitResistance(FGameplayAttributeData const& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitResistance, OldCriticalHitResistance)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_HealthRegeneration(FGameplayAttributeData const& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegeneration, OldHealthRegeneration)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_ManaRegeneration(FGameplayAttributeData const& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegeneration, OldManaRegeneration)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_MaxHealth(FGameplayAttributeData const& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_MaxMana(FGameplayAttributeData const& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_Health(FGameplayAttributeData const& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth)
}

//----------------------------------------------------------------------------------------------------
void UAuraAttributeSet::OnRep_Mana(FGameplayAttributeData const& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana)
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
