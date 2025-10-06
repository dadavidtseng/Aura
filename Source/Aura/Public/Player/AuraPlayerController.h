//----------------------------------------------------------------------------------------------------
// AuraPlayerController.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------
#include <CoreMinimal.h>
#include <GameFramework/PlayerController.h>
#include <AuraPlayerController.generated.h>

//-Forward-Declaration--------------------------------------------------------------------------------
class IEnemyInterface;
class UAuraAbilitySystemComponent;
class UAuraInputConfig;
class UInputAction;
class UInputMappingContext;
class USplineComponent;
struct FGameplayTag;
struct FInputActionValue;

//----------------------------------------------------------------------------------------------------
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(FInputActionValue const& InputActionValue);
	void CursorTrace();

	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent();

	FVector CachedDestination   = FVector::ZeroVector;
	float   FollowTime          = 0.f;
	float   ShortPressThreshold = 0.5f;
	bool    bAutoRunning        = false;
	bool    bTargeting          = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USplineComponent> Spline;

	void AutoRun();
};
