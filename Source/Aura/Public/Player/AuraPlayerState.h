//----------------------------------------------------------------------------------------------------
// AuraPlayerState.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

//-Forward-Declaration--------------------------------------------------------------------------------
class UAttributeSet;
class UAbilitySystemComponent;

//----------------------------------------------------------------------------------------------------
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet*                   GetAttributeSet() const;

protected:
	/* The core ActorComponent for interfacing with the GameplayAbilities System */
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	/*
	1. Defines the set of all GameplayAttributes for your game
	2. Games should subclass this and add FGameplayAttributeData properties to represent attributes like health, damage, etc
	3. AttributeSets are added to the actors as subobjects, and then registered with the AbilitySystemComponent
	4. It is often desired to have several sets per project that inherit from each other
	5. You could make a base health set, then have a player set that inherits from it and adds more attributes
	*/
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
