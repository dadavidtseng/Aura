//----------------------------------------------------------------------------------------------------
// AuraCharacterBase.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

//----------------------------------------------------------------------------------------------------
// By adding abstract specifier to the class macro,
// it will prevent this class from being able to be dragged into the level.
UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

protected:
	virtual void BeginPlay() override;
};
