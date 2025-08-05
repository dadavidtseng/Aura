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
void AAuraEffectActor::ApplyEffectToTarget(AActor*                            TargetActor,
                                           TSubclassOf<UGameplayEffect> const GameplayEffectClass)
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetAbilitySystemComponent == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle const   TargetGameplayEffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContextHandle);
	FActiveGameplayEffectHandle const ActiveEffectHandle             = TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*TargetGameplayEffectSpecHandle.Data.Get());

	bool const bIsInfinite = TargetGameplayEffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;

	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetAbilitySystemComponent);
	}
}

//----------------------------------------------------------------------------------------------------
void AAuraEffectActor::OnBeginOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

//----------------------------------------------------------------------------------------------------
void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
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
