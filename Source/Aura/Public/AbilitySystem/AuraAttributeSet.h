//----------------------------------------------------------------------------------------------------
// AuraAttributeSet.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include <CoreMinimal.h>
#include <AbilitySystemComponent.h>
#include <AttributeSet.h>
#include <AuraAttributeSet.generated.h>

//----------------------------------------------------------------------------------------------------
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

//----------------------------------------------------------------------------------------------------
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties()
	{
	};

	FGameplayEffectContextHandle EffectContextHandle;
	UPROPERTY()
	UAbilitySystemComponent* SourceAbilitySystemComponent = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;
	UPROPERTY()
	UAbilitySystemComponent* TargetAbilitySystemComponent = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

//----------------------------------------------------------------------------------------------------
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(FGameplayAttribute const& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(FGameplayEffectModCallbackData const& Data) override;


	//-Primary-Attributes---------------------------------------------------------------------------------
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor)
	//----------------------------------------------------------------------------------------------------

	//-Vital-Attributes-----------------------------------------------------------------------------------
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)
	//----------------------------------------------------------------------------------------------------

	UFUNCTION()
	void OnRep_Health(FGameplayAttributeData const& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(FGameplayAttributeData const& OldMaxHealth) const;
	UFUNCTION()
	void OnRep_Mana(FGameplayAttributeData const& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(FGameplayAttributeData const& OldMaxMana) const;
	UFUNCTION()
	void OnRep_Strength(FGameplayAttributeData const& OldStrength) const;
	UFUNCTION()
	void OnRep_Intelligence(FGameplayAttributeData const& OldIntelligence) const;
	UFUNCTION()
	void OnRep_Resilience(FGameplayAttributeData const& OldResilience) const;
	UFUNCTION()
	void OnRep_Vigor(FGameplayAttributeData const& OldVigor) const;

private:
	void SetEffectProperties(FGameplayEffectModCallbackData const& Data, FEffectProperties& EffectProperties) const;
};
