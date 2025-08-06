//----------------------------------------------------------------------------------------------------
// AuraEffectActor.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include <CoreMinimal.h>
#include <GameplayEffectTypes.h>
#include <GameFramework/Actor.h>
#include <AuraEffectActor.generated.h>

//-Forward-Declaration--------------------------------------------------------------------------------
class UAbilitySystemComponent;
class UGameplayEffect;

//----------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnBeginOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

//----------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

//----------------------------------------------------------------------------------------------------
UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectsToTarget(AActor* TargetActor, TArray<TSubclassOf<UGameplayEffect>> const& EffectClasses);

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	bool bDestroyOnEffectRemoval = false;

	// Instant effects `BaseValue` on `FGameplayAttributeData`
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	// TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	TArray<TSubclassOf<UGameplayEffect>> InstantGameplayEffectClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	// Duration effects `CurrentValue` on `FGameplayAttributeData`
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	// TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	TArray<TSubclassOf<UGameplayEffect>> DurationGameplayEffectClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	// Infinite effects `CurrentValue` on `FGameplayAttributeData`
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	// TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	TArray<TSubclassOf<UGameplayEffect>> InfiniteGameplayEffectClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	float ActorLevel = 1.f;

private:
	void ApplyEffectToTargetInternal(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
};
