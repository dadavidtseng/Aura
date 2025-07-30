//----------------------------------------------------------------------------------------------------
// AuraEffectActor.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "Actor/AuraEffectActor.h"

#include <AbilitySystemInterface.h>
#include <AbilitySystem/AuraAttributeSet.h>
#include <Components/SphereComponent.h>

//----------------------------------------------------------------------------------------------------
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

//----------------------------------------------------------------------------------------------------
void AAuraEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                      AActor*              OtherActor,
                                      UPrimitiveComponent* OtherComp,
                                      int32                OtherBodyIndex,
                                      bool                 bFromSweep,
                                      FHitResult const&    SweepResult)
{
	// TODO: Change this to apply a `Gameplay Effect`. For now, use `const_cast` for a hack.
	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OtherActor);

	if (AbilitySystemInterface != nullptr)
	{
		UAuraAttributeSet const* AuraAttributeSet = Cast<UAuraAttributeSet>(AbilitySystemInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));

		UAuraAttributeSet* MutableAuraAttributeSet = const_cast<UAuraAttributeSet*>(AuraAttributeSet);
		MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

//----------------------------------------------------------------------------------------------------
void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
                                    AActor*              OtherActor,
                                    UPrimitiveComponent* OtherComp,
                                    int32                OtherBodyIndex)
{
}

//----------------------------------------------------------------------------------------------------
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	// Go to `OnComponentXXXXX's` definition and go to `FComponentXXXXXSignature`'s definition.
	// That's the place where you can find `DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_XXXXXParams` for its signature.
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverlap);
}
