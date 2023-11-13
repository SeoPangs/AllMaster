// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mob.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */

class AInteractiveObject;

UCLASS()
class ALLMASTER_API APlayerCharacter : public AMob
{
    GENERATED_BODY()
	
private:
    //Bool to control if we are sprinting. Failsafe
    bool bIsSprinting;
    //Bool to control if we are walking. By toggle with Walking and Runnig
    bool bIsWalking;

protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
    APlayerCharacter();

protected:
    void Sprint();
    void StopSprinting();
    void ToggleWalking();
    void Act() override;
    AInteractiveObject* DetectObject(); //Find Near Interactive Object;
};
