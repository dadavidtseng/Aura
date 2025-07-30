


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* In_WidgetController)
{
WidgetController = In_WidgetController;
	WidgetControllerSet();
}
