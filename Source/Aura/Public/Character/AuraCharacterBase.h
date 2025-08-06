//----------------------------------------------------------------------------------------------------
// AuraCharacterBase.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include <CoreMinimal.h>
#include <AbilitySystemInterface.h>
#include <GameFramework/Character.h>
#include <AuraCharacterBase.generated.h>

//-Forward-Declaration--------------------------------------------------------------------------------
class UAbilitySystemComponent;
class UAttributeSet;

//----------------------------------------------------------------------------------------------------
// By adding abstract specifier to the class macro,
// it will prevent this class from being able to be dragged into the level.
UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet*                   GetAttributeSet() const;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
