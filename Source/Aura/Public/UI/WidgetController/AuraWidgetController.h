// Copyright Flavio

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class APlayerState;
class APlayerController;

/**
 * @struct FWidgetControllerParams
 * @brief A lightweight data structure that provides parameters required for widget controller initialization.
 *
 * FWidgetControllerParams is used to encapsulate references to critical gameplay systems and
 * state objects necessary for properly configuring a widget controller. This structure provides
 * a convenient way to pass these references in a single object.
 *
 * The struct contains the following key components:
 * - A reference to the player controller.
 * - A reference to the player state.
 * - A reference to the ability system component.
 * - A reference to the attribute set.
 *
 * These references enable the widget controller to interface with core gameplay systems
 * and access player-specific attributes and abilities as needed.
 */
USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	
	FWidgetControllerParams() {}
	
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS) 
	: 
	PlayerController(PC), 
	PlayerState(PS), 
	AbilitySystemComponent(ASC), 
	AttributeSet(AS) {}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

/**
 * @class UAuraWidgetController
 * @brief A base class responsible for controlling widget behavior and interactions in the Aura framework.
 *
 * UAuraWidgetController provides a structured way to interact with widgets by integrating player-specific data
 * and systems. It is designed to manage the communication and updates between gameplay systems and UI elements.
 *
 * Key functionality:
 * - Stores references to critical gameplay systems, including the player controller, player state,
 *   ability system component, and attribute set.
 * - Simplifies the process of injecting dynamic game-related data into UI widgets.
 *
 * This class relies on an external parameter struct, FWidgetControllerParams, to initialize its references
 * to required gameplay objects.
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);
	
protected:
	
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;
	
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;
	
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

};
