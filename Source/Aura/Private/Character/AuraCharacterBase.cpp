//----------------------------------------------------------------------------------------------------
// AuraCharacterBase.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "Character/AuraCharacterBase.h"

#include <AbilitySystemComponent.h>

#include "AbilitySystem/AuraAbilitySystemComponent.h"

//----------------------------------------------------------------------------------------------------
AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;;
}

UAttributeSet* AAuraCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

//----------------------------------------------------------------------------------------------------
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

//----------------------------------------------------------------------------------------------------
void AAuraCharacterBase::InitAbilityActorInfo()
{
}

//----------------------------------------------------------------------------------------------------
void AAuraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> const& GameplayEffectClass,
                                           float const                         Level /* 1.f */) const
{
	check(IsValid(GetAbilitySystemComponent()))
	check(GameplayEffectClass)
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle const SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

//----------------------------------------------------------------------------------------------------
void AAuraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes);
	ApplyEffectToSelf(DefaultSecondaryAttributes);
	ApplyEffectToSelf(DefaultVitalAttributes);
}

//----------------------------------------------------------------------------------------------------
void AAuraCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority()) return;

	UAuraAbilitySystemComponent* AuraAbilitySystemComponent = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);

	AuraAbilitySystemComponent->AddCharacterAbilities(StartupAbilities);
}
