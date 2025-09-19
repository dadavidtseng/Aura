//----------------------------------------------------------------------------------------------------
// AuraAbilitySystemLibrary.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include <Kismet/GameplayStatics.h>

#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

//----------------------------------------------------------------------------------------------------
UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(UObject const* WorldContextObject)
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			AAuraPlayerState*        PlayerState            = PlayerController->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* AbilitySystemComponent = PlayerState->GetAbilitySystemComponent();
			UAttributeSet*           AttributeSet           = PlayerState->GetAttributeSet();

			FWidgetControllerParams const WidgetControllerParams = FWidgetControllerParams(PlayerController, PlayerState, AbilitySystemComponent, AttributeSet);

			return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}
