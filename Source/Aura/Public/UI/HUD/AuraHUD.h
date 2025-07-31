//----------------------------------------------------------------------------------------------------
// AuraHUD.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include <CoreMinimal.h>
#include <GameFramework/HUD.h>
#include <AuraHUD.generated.h>

class UAttributeSet;
class UAbilitySystemComponent;
//-Forward-Declaration--------------------------------------------------------------------------------
class UAuraUserWidget;
class UOverlayWidgetController;
struct FWidgetControllerParams;

//----------------------------------------------------------------------------------------------------
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION()
	UOverlayWidgetController* GetOverlayWidgetController(FWidgetControllerParams const& WidgetControllerParams);

	UFUNCTION()
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
