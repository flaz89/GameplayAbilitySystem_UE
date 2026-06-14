// Copyright Flavio


#include "Player/AuraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	CursorTrace();
}


void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor(); // using TScriptInterface<> no need to cast
	
	/*
	 * Trace Scenario each frame:
	 * A - LastActor == nullptr && ThisActor == nullptr		---> do nothing
	 * C - LastActor == nullptr && ThisActor is valid		---> ThisActor Highlight()
	 * C - LastActor is valid && ThisActor == nullptr		---> LastActor UnHighlight()
	 * D - LastActor is valid && ThisActor is valid:
	 *					LastActor != ThisActor				---> LastActor UnHighlight() && ThisActor Highlight()
	 *					LastActor == ThisActor				---> do nothing
	 */
	
	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr) ThisActor->HighlightActor();
	}
	else
	{
		if (ThisActor == nullptr)
		{
			LastActor->UnHighlight();
		} 
		else
		{
			if (LastActor != ThisActor)
			{
				LastActor->UnHighlight();
				ThisActor->HighlightActor();
			}
		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	check(AuraContext); // if no AuraContext set, it's gonna crash
	
	// set the Subsystem & added Mapping Context
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	// set input mode
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	// define the vertical rotation of controller
	const FRotator YawRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	// extract the forward and right vectors from rotation
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
