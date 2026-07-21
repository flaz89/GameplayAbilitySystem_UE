// Copyright Flavio


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"


/**
 * Retrieves or creates an instance of UOverlayWidgetController with the specified parameters.
 *
 * @param WCParams A struct containing the necessary parameters required to initialize the widget controller, including PlayerController, PlayerState, AbilitySystemComponent, and AttributeSet.
 * @return A pointer to the instance of UOverlayWidgetController. It returns an existing instance if already created; otherwise, it creates a new one, initializes it with the given parameters, and then returns it.
 */
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController != nullptr) return OverlayWidgetController;
	
	OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
	OverlayWidgetController->SetWidgetControllerParams(WCParams);
	return OverlayWidgetController;
}


/**
 * Initializes and adds the overlay widget to the viewport while configuring its associated widget controller.
 *
 * @param PC The player controller for the local player, used for initializing the widget controller.
 * @param PS The player state for the local player, providing player-specific data for the widget controller.
 * @param ASC The ability system component associated with the player, used for gameplay ability logic in the overlay.
 * @param AS The attribute set containing gameplay-related attributes such as health and mana.
 */
void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is not set in AuraHUD, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not set in AuraHUD, please fill out BP_AuraHUD"));
	
	// create a new widget from OverlayWidgetClass and set the OverlayWidget casting to the widget just created
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	
	// create a new OverlayWidgetController passing in the structure WidgetControllerParams
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
}

