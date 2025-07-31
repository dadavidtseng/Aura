//----------------------------------------------------------------------------------------------------
// AuraWidgetController.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "UI/WidgetController/AuraWidgetController.h"

//----------------------------------------------------------------------------------------------------
void UAuraWidgetController::SetWidgetControllerParams(FWidgetControllerParams const& WidgetControllerParams)
{
	PlayerController       = WidgetControllerParams.PlayerController;
	PlayerState            = WidgetControllerParams.PlayerState;
	AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;
	AttributeSet           = WidgetControllerParams.AttributeSet;
}
