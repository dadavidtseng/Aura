//----------------------------------------------------------------------------------------------------
// MMC_MaxMana.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include <CoreMinimal.h>
#include <GameplayModMagnitudeCalculation.h>
#include <MMC_MaxMana.generated.h>

//----------------------------------------------------------------------------------------------------
UCLASS()
class AURA_API UMMC_MaxMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_MaxMana();

	virtual float CalculateBaseMagnitude_Implementation(FGameplayEffectSpec const& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition IntelligenceDefinition;
};
