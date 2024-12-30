//----------------------------------------------------------------------------------------------------
// AuraPlayerController.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"

//----------------------------------------------------------------------------------------------------
AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	// Call the parent class's BeginPlay method to ensure base initialization logic is executed
	Super::BeginPlay();
    
	// Ensure that AuraContext is valid (non-null)
	check(AuraContext);

	// Retrieve the UEnhancedInputLocalPlayerSubsystem from the local player and ensure it is valid
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	// Add the input mapping context to the subsystem
	Subsystem->AddMappingContext(AuraContext, 0);

	// Enable the mouse cursor and set the default cursor style
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// Set up the input mode to allow both game and UI input
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // Do not lock the mouse to the viewport
	InputModeData.SetHideCursorDuringCapture(false); // Do not hide the cursor during input capture
	SetInputMode(InputModeData); // Apply the input mode settings to the player controller
}
