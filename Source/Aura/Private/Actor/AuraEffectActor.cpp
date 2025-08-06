//----------------------------------------------------------------------------------------------------
// AuraEffectActor.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "Actor/AuraEffectActor.h"

#include <AbilitySystemBlueprintLibrary.h>

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

//----------------------------------------------------------------------------------------------------
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));

	// Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	// SetRootComponent(Mesh);
	//
	// Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	// Sphere->SetupAttachment(GetRootComponent());
}

//----------------------------------------------------------------------------------------------------
// void AAuraEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
//                                       AActor*              OtherActor,
//                                       UPrimitiveComponent* OtherComp,
//                                       int32                OtherBodyIndex,
//                                       bool                 bFromSweep,
//                                       FHitResult const&    SweepResult)
// {
// 	// TODO: Change this to apply a `Gameplay Effect`. For now, use `const_cast` for a hack.
// 	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OtherActor);
//
// 	if (AbilitySystemInterface != nullptr)
// 	{
// 		UAuraAttributeSet const* AuraAttributeSet = Cast<UAuraAttributeSet>(AbilitySystemInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
//
// 		UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
// 		MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
// 		MutableAuraAttributeSet->SetMana(AuraAttributeSet->GetMana() + 10.f);
// 		Destroy();
// 	}
// }
//
// //----------------------------------------------------------------------------------------------------
// void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
//                                     AActor*              OtherActor,
//                                     UPrimitiveComponent* OtherComp,
//                                     int32                OtherBodyIndex)
// {
// }

//----------------------------------------------------------------------------------------------------
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	// Go to `OnComponentXXXXX's` definition and go to `FComponentXXXXXSignature`'s definition.
	// That's the place where you can find `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_XXXXXParams` for its signature.
	// Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnBeginOverlap);
	// Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverlap);
}

//----------------------------------------------------------------------------------------------------
void AAuraEffectActor::ApplyEffectsToTarget(AActor*                                     TargetActor,
                                            TArray<TSubclassOf<UGameplayEffect>> const& EffectClasses)
{
	for (TSubclassOf<UGameplayEffect> const& EffectClass : EffectClasses)
	{
		if (EffectClass)
		{
			ApplyEffectToTargetInternal(TargetActor, EffectClass);
		}
	}
}

//----------------------------------------------------------------------------------------------------
void AAuraEffectActor::OnBeginOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectsToTarget(TargetActor, InstantGameplayEffectClasses);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectsToTarget(TargetActor, DurationGameplayEffectClasses);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectsToTarget(TargetActor, InfiniteGameplayEffectClasses);
	}
}

//----------------------------------------------------------------------------------------------------
void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectsToTarget(TargetActor, InstantGameplayEffectClasses);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectsToTarget(TargetActor, DurationGameplayEffectClasses);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectsToTarget(TargetActor, InfiniteGameplayEffectClasses);
	}
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetAbilitySystemComponent)) return;

		// Store `FActiveGameplayEffectHandle` in this array and remove it in the next for-loop so that we don't crash.
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;

		for (TPair const HandlePair : ActiveEffectHandles)
		{
			if (TargetAbilitySystemComponent == HandlePair.Value)
			{
				// Remove a single stack.
				TargetAbilitySystemComponent->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}

		for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}

//----------------------------------------------------------------------------------------------------
void AAuraEffectActor::ApplyEffectToTargetInternal(AActor*                            TargetActor,
                                                   TSubclassOf<UGameplayEffect> const GameplayEffectClass)
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetAbilitySystemComponent == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle const   TargetGameplayEffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	FActiveGameplayEffectHandle const ActiveEffectHandle             = TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*TargetGameplayEffectSpecHandle.Data.Get());

	bool const bIsInfinite = TargetGameplayEffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;

	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetAbilitySystemComponent);
	}
}
