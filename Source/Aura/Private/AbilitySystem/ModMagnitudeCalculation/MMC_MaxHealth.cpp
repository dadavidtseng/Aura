//----------------------------------------------------------------------------------------------------
// MMC_MaxHealth.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "AbilitySystem/ModMagnitudeCalculation/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

//----------------------------------------------------------------------------------------------------
UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDefinition.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDefinition.AttributeSource    = EGameplayEffectAttributeCaptureSource::Target;
	VigorDefinition.bSnapshot          = false;

	RelevantAttributesToCapture.Add(VigorDefinition);
}

//----------------------------------------------------------------------------------------------------
float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(FGameplayEffectSpec const& Spec) const
{
	// Gather tags from source and target.
	FGameplayTagContainer const* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	FGameplayTagContainer const* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDefinition, Spec, EvaluateParameters, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	int32 const       PlayerLevel     = CombatInterface->GetPlayerLevel();

	return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;
}
