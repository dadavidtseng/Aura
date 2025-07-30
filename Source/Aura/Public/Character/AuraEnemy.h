//----------------------------------------------------------------------------------------------------
// AuraEnemy.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include <CoreMinimal.h>

#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"

#include <AuraEnemy.generated.h>

//----------------------------------------------------------------------------------------------------
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	//-Start-of-EnemyInterface----------------------------------------------------------------------------
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	//-End-of-EnemyInterface------------------------------------------------------------------------------

protected:
	virtual void BeginPlay() override;
};
