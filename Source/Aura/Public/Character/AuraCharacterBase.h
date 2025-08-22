//----------------------------------------------------------------------------------------------------
// AuraCharacterBase.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include <CoreMinimal.h>
#include <AbilitySystemInterface.h>
#include <GameFramework/Character.h>

#include "Interaction/CombatInterface.h"

#include <AuraCharacterBase.generated.h>

//-Forward-Declaration--------------------------------------------------------------------------------
class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;

//----------------------------------------------------------------------------------------------------
// By adding abstract specifier to the class macro,
// it will prevent this class from being able to be dragged into the level.
UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet*                   GetAttributeSet() const;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	void         ApplyEffectToSelf(TSubclassOf<UGameplayEffect> const& GameplayEffectClass, float Level = 1.f) const;
	void         InitializeDefaultAttributes() const;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;
};
