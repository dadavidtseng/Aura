//----------------------------------------------------------------------------------------------------
// AuraCharacter.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "Character/AuraCharacter.h"

#include <AbilitySystemComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

//----------------------------------------------------------------------------------------------------  
AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate              = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane         = true;
	GetCharacterMovement()->bSnapToPlaneAtStart       = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll  = false;
	bUseControllerRotationYaw   = false;
}

//----------------------------------------------------------------------------------------------------
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the server
	InitAbilityActorInfo();
	// This could be  called on both client and server side.
	// But it's okay to just call it on server, and it will be replicated to clients afterward.
	InitializeDefaultAttributes();
	AddCharacterAbilities();
}

//----------------------------------------------------------------------------------------------------
void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the client
	InitAbilityActorInfo();
}

//----------------------------------------------------------------------------------------------------
int32 AAuraCharacter::GetPlayerLevel()
{
	AAuraPlayerState const* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetPlayerLevel();
}

//----------------------------------------------------------------------------------------------------
void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet           = AuraPlayerState->GetAttributeSet();

	// Only server has all PlayerController valid.
	// In this scenario, AuraPlayerController can and will be null in a multiplayer game.
	AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController());

	if (AuraPlayerController != nullptr)
	{
		AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD());
		if (AuraHUD != nullptr)
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
