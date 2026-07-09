// Copyright Flavio


#include "UI/Widget/AuraUserWidget.h"


/*
 * It's like a "beginPlay" made blueprint callable, 
 * in order to set the controller and call teh function "WidgetCOntrollerSet()" implemented in blueprint
 */
void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
