//----------------------------------------------------------------------------------------------------
// AuraPlayerController.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "Player/AuraPlayerController.h"
//----------------------------------------------------------------------------------------------------
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"
//----------------------------------------------------------------------------------------------------
#include <AbilitySystemBlueprintLibrary.h>
#include <EnhancedInputSubsystems.h>
#include <GameplayTagContainer.h>
#include <Components/SplineComponent.h>

#include "AuraGameplayTags.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"

//----------------------------------------------------------------------------------------------------
AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

//----------------------------------------------------------------------------------------------------
void AAuraPlayerController::PlayerTick(float const DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();

	AutoRun();
}

//----------------------------------------------------------------------------------------------------
void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	/**
	 *	Line trace from cursor. There are several scenerios:
	 *	A. LastActor is null && ThisActor is null
	 *		- Do nothing
	 *	B. LastActor is null && ThisActor is valid
	 *		- Highlight ThisActor
	 *	C. LastActor is valid && ThisActor is null
	 *		- UnHighlight LastActor
	 *	D. Both actors are valid, but LastActor != ThisActor
	 *		- UnHighlight LastActor, and Highlight ThisActor
	 *	E. Both actors are valid, and are the same actor
	 *		- Do nothing
	 */

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case B
			ThisActor->HighlightActor();
		}
		else
		{
			// Case A - both are null, do nothing
		}
	}
	else  // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnHighlightActor();
		}
		else  // both actors are valid
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case E - do nothing
			}
		}
	}
}

//----------------------------------------------------------------------------------------------------
void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bTargeting   = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

//----------------------------------------------------------------------------------------------------
void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetAuraAbilitySystemComponent() != nullptr)
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
		}

		return;
	}

	if (bTargeting)
	{
		if (GetAuraAbilitySystemComponent() != nullptr)
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
		}
	}
	else
	{
		APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold)
		{
			UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination);

			if (NavPath != nullptr)
			{
				Spline->ClearSplinePoints();

				for (FVector const& PointLocation : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLocation, ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(), PointLocation, 8.f, 8, FColor::Green, false, 5.f);
				}
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
				bAutoRunning      = true;
			}
		}

		FollowTime = 0;
		bTargeting = false;
	}
}

//----------------------------------------------------------------------------------------------------
void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetAuraAbilitySystemComponent() != nullptr)
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		}

		return;
	}

	if (bTargeting)
	{
		if (GetAuraAbilitySystemComponent() != nullptr)
		{
			GetAuraAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			CachedDestination = Hit.ImpactPoint;	// or Hit.Location
		}

		if (APawn* ControlledPawn = GetPawn())
		{
			FVector const WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

//----------------------------------------------------------------------------------------------------
UAuraAbilitySystemComponent* AAuraPlayerController::GetAuraAbilitySystemComponent()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}

	return AuraAbilitySystemComponent;
}


//----------------------------------------------------------------------------------------------------
void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();		// Call the parent class's BeginPlay method to ensure base initialization logic is executed
	check(AuraContext);		// Ensure that AuraContext is valid (non-null)

	// Retrieve the UEnhancedInputLocalPlayerSubsystem from the local player and ensure it is valid
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	// check(Subsystem);
	if (Subsystem != nullptr)
	{
		// Add the input mapping context to the subsystem
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	// Enable the mouse cursor and set the default cursor style
	bShowMouseCursor   = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// Set up the input mode to allow both game and UI input
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);	// Do not lock the mouse to the viewport
	InputModeData.SetHideCursorDuringCapture(false);							// Do not hide the cursor during input capture
	SetInputMode(InputModeData);												// Apply the input mode settings to the player controller
}

//----------------------------------------------------------------------------------------------------
void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);

	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);

	AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

//----------------------------------------------------------------------------------------------------
void AAuraPlayerController::Move(FInputActionValue const& InputActionValue)
{
	FVector2D const InputAxisVector = InputActionValue.Get<FVector2D>();	// Extract the 2D input vector (e.g., WASD keys or joystick input).
	FRotator const  Rotation        = GetControlRotation();							// Get the controller's rotation (e.g., camera rotation).
	FRotator const  YawRotation(0.f, Rotation.Yaw, 0.0f);			// Create a rotation that only considers the Yaw (horizontal rotation).

	FVector const ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);	// Calculate the forward direction vector based on the Yaw rotation.
	FVector const RightDirection   = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);		// Calculate the right direction vector based on the Yaw rotation.

	// Check if the controller is currently possessing a pawn.
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);		// Add movement input in the forward direction scaled by the Y-axis input.
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);		// Add movement input in the right direction scaled by the X-axis input.		
	}
}

//----------------------------------------------------------------------------------------------------
void AAuraPlayerController::AutoRun()
{
	if (!bAutoRunning) return;		// Only auto run when we should auto run.
	if (APawn* ControlledPawn = GetPawn())
	{
		FVector const LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		FVector const Direction        = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);

		ControlledPawn->AddMovementInput(Direction);

		float const DistanceToDestination = (LocationOnSpline - CachedDestination).Length();

		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}
