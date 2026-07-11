// Copyright Flavio


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	SpringArm->SetupAttachment(RootComponent);
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
}

/*
 * Initialize Ability Actor Info both on Server and on Client when first Pawn/Character is controlled on server 
 * and then replicated on client
 */
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitAbilityActorInfo(); 	// Server
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	InitAbilityActorInfo(); 	// Client
}

/**
 * Initializes the ability actor information for the AuraCharacter, linking it with the PlayerState,
 * AbilitySystemComponent, and AttributeSet. This method ensures that the character is properly set up
 * with the necessary ability-related components and prepares the HUD overlay if available.
 *
 * Workflow:
 * - Retrieves the AuraPlayerState from the PlayerState and verifies its validity.
 * - Initializes the AbilitySystemComponent's actor information using the PlayerState and this character.
 * - Updates local references to the AbilitySystemComponent and AttributeSet.
 * - Attempts to retrieve the AuraPlayerController and its associated HUD to initialize the overlay
 *   with player-specific data.
 *
 * This method is intended to be called on both the server and client to ensure consistent initialization
 * across the network after possession or PlayerState replication.
 *
 * Preconditions:
 * - The PlayerState must be valid and of type AAuraPlayerState.
 * - The controller (if present) should be of type AAuraPlayerController.
 * - The HUD (if present) should be of type AAuraHUD.
 *
 * Notes:
 * - Ensures that vital ability systems and attributes are initialized properly for gameplay.
 * - Called during possession on the server and OnRep_PlayerState on the client.
 */
void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = Cast<AAuraPlayerState>(GetPlayerState());
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
	
	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
