//----------------------------------------------------------------------------------------------------
// AttributeInfo.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "AbilitySystem/Data/AttributeInfo.h"

//----------------------------------------------------------------------------------------------------
FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(FGameplayTag const& AttributeTag,
                                                           bool const          bLogNotFound)
{
	for (FAuraAttributeInfo const& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for AttributeTag (%s), on AttributeInfo (%s)!"), *AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FAuraAttributeInfo();
}
