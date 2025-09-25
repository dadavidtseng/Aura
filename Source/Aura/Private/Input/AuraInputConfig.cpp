//----------------------------------------------------------------------------------------------------
// AuraInputConfig.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "Input/AuraInputConfig.h"

//----------------------------------------------------------------------------------------------------
UInputAction const* UAuraInputConfig::FindAbilityInputActionForTag(FGameplayTag const& InputTag,
                                                                   bool const          bLogNotFound) const
{
	for (FAuraInputAction const& Action : AbilityInputActions)
	{
		if (Action.InputAction == nullptr) continue;
		if (Action.InputTag != InputTag) continue;

		return Action.InputAction;
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]"),
		       *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
