//----------------------------------------------------------------------------------------------------
// AuraAttributeSet.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "AbilitySystem/AuraAttributeSet.h"

#include <Net/UnrealNetwork.h>

//----------------------------------------------------------------------------------------------------
UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(200.f);
	InitMana(300.f);
	InitMaxMana(400.f);
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
