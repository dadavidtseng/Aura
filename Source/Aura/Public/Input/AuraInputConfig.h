//----------------------------------------------------------------------------------------------------
// AuraInputConfig.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include <CoreMinimal.h>
#include <GameplayTagContainer.h>
#include <Engine/DataAsset.h>
#include <AuraInputConfig.generated.h>

//-Forward-Declaration--------------------------------------------------------------------------------
class UInputAction;

//----------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	UInputAction const* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

//----------------------------------------------------------------------------------------------------
UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UInputAction const* FindAbilityInputActionForTag(FGameplayTag const& InputTag, bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraInputAction> AbilityInputActions;
};
