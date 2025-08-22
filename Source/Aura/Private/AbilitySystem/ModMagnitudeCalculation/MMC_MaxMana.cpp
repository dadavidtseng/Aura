//----------------------------------------------------------------------------------------------------
// MMC_MaxMana.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "AbilitySystem/ModMagnitudeCalculation/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

//----------------------------------------------------------------------------------------------------
UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDefinition.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDefinition.AttributeSource    = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDefinition.bSnapshot          = false;

	RelevantAttributesToCapture.Add(IntelligenceDefinition);
}

//----------------------------------------------------------------------------------------------------
float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(FGameplayEffectSpec const& Spec) const
{
	// Gather tags from source and target.
	FGameplayTagContainer const* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	FGameplayTagContainer const* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDefinition, Spec, EvaluateParameters, Intelligence);
	Intelligence = FMath::Max<float>(Intelligence, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	int32 const       PlayerLevel     = CombatInterface->GetPlayerLevel();

	return 50.f + 2.5f * Intelligence + 15.f * PlayerLevel;
}
