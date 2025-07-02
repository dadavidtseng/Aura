//----------------------------------------------------------------------------------------------------
// AuraPlayerState.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

//----------------------------------------------------------------------------------------------------
AAuraPlayerState::AAuraPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	// NetUpdateFrequency = 100.f;	// Deprecated
	// As changes are made on the server, every single update, the server sends data down to the client
	// so they can be informed on that change
	SetNetUpdateFrequency(100.f);	// updates on client 100 times per second as long as the server can manage that
	// And this behavior of data transmitting from server to client is called `Replication`
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AAuraPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
