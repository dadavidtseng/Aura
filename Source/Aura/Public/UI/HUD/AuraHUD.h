//----------------------------------------------------------------------------------------------------
// AuraHUD.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include <CoreMinimal.h>
#include <GameFramework/HUD.h>
#include <AuraHUD.generated.h>

//-Forward-Declaration--------------------------------------------------------------------------------
class UAbilitySystemComponent;
class UAttributeMenuWidgetController;
class UAttributeSet;
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
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UFUNCTION()
	UOverlayWidgetController* GetOverlayWidgetController(FWidgetControllerParams const& WidgetControllerParams);

	UFUNCTION()
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(FWidgetControllerParams const& WidgetControllerParams);

private:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
