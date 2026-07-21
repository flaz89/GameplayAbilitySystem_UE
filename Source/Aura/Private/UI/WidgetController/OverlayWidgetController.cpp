// Copyright Flavio


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

/**
 * Broadcasts the initial values of health and max health to their respective listeners.
 *
 * This method gets the attribute set from the associated AttributeSet property, extracts
 * the current health and max health values, and broadcasts these values via the OnHealthChanged
 * and OnMaxHealthChanged delegates.
 *
 * It is primarily used to initialize the UI or other systems that rely on receiving initial
 * attribute states.
 *
 * Note:
 * - The method expects the AttributeSet property to be properly set and castable to UAuraAttributeSet.
 * - The OnHealthChanged and OnMaxHealthChanged delegates must be bound appropriately to handle the broadcasts.
 */
void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
}
