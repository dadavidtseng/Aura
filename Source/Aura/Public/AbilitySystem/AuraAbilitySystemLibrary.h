//----------------------------------------------------------------------------------------------------
// AuraAbilitySystemLibrary.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>
#include <AuraAbilitySystemLibrary.generated.h>

class UOverlayWidgetController;
//----------------------------------------------------------------------------------------------------
UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// static function can not access anything that existed in the world.
	// In order to access things in the world, it needs `WorldContext`.
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary | WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(UObject const* WorldContextObject);
};
