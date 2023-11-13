// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "InteractiveObject.h"


APlayerCharacter::APlayerCharacter()
{
    bIsSprinting = false;
    bIsWalking = false;
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::Sprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::StopSprinting);
    PlayerInputComponent->BindAction("ToggleWalking", IE_Pressed, this, &APlayerCharacter::ToggleWalking);

}

void APlayerCharacter::Sprint()
{
    if (!bIsSprinting)
    {
        bIsSprinting = true;
        bIsWalking = false;
        GetCharacterMovement()->MaxWalkSpeed = 800.0f;
    }
}

void APlayerCharacter::StopSprinting()
{
    if (bIsSprinting)
    {
        bIsSprinting = false;
        bIsWalking = false;
        GetCharacterMovement()->MaxWalkSpeed = 500.0f;
    }

}

void APlayerCharacter::ToggleWalking()
{
    if (bIsWalking)
    {
        bIsWalking = false;
        GetCharacterMovement()->MaxWalkSpeed = 500.0f;
    }

    else if (!bIsWalking)
    {
        bIsWalking = true;
        GetCharacterMovement()->MaxWalkSpeed = 300.0f;
    }
}

void APlayerCharacter::Act()
{
    
}

AInteractiveObject* APlayerCharacter::DetectObject()
{
    //MUST BE DEVELOP
    return NULL;
}

