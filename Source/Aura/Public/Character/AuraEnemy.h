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

	//-Start-of-EnemyInterface------------------------------------------------------------------------
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	//-End-of-EnemyInterface--------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------
	//-Start-of-CombatInterface-----------------------------------------------------------------------
	virtual int32 GetPlayerLevel() override;
	//-End-of-CombatInterface-------------------------------------------------------------------------

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	// The reason that we are not making this `replicated` is because
	// we are only to be concerned with checking the level on the server for AI controlled enemies.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Default")
	int32 Level = 1;
};
