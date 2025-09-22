//----------------------------------------------------------------------------------------------------
// AuraHUD.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

//----------------------------------------------------------------------------------------------------
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(FWidgetControllerParams const& WidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}

	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(FWidgetControllerParams const& WidgetControllerParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}

	return AttributeMenuWidgetController;
}

//----------------------------------------------------------------------------------------------------
void AAuraHUD::InitOverlay(APlayerController*       PC,
                           APlayerState*            PS,
                           UAbilitySystemComponent* ASC,
                           UAttributeSet*           AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is not initialized, please fill out BP_AuraHUD!"))
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not initialized, please fill out BP_AuraHUD!"))

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget       = Cast<UAuraUserWidget>(Widget);

	FWidgetControllerParams const WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController*     WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();

	Widget->AddToViewport();
}
