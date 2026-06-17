// Copyright Flavio

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
	
public:
	AAuraCharacter();
	
	/** Init AbilityActorInfo of ASC after the controller possesed the pawn, we need to override 2 functions from APawn*/
	virtual void PossessedBy(AController* NewController) override; // server
	virtual void OnRep_PlayerState() override; // client
	
protected:
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Camera")
	TObjectPtr<USpringArmComponent> SpringArm;
	
	UPROPERTY(EditDefaultsOnly, Category="Camera")
	TObjectPtr<UCameraComponent> Camera;
	
	void InitAbilityActorInfo();
	
};
