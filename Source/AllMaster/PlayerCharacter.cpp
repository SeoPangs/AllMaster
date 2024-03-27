// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Skill/Skill.h"
#include "Object/InteractiveObject.h"



APlayerCharacter::APlayerCharacter()
{

    Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
    if (WeaponSocket.IsValid())
    {
        Weapon->SetupAttachment(GetMesh(), WeaponSocket);
        Weapon->SetRelativeLocation(FVector(-10, 2, 2));
        Weapon->SetRelativeRotation(FRotator(0.f, 0.0f, -90.0f));
    }
   
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

void APlayerCharacter::Act_Implementation()
{
    AnimPlay(0);

}

AInteractiveObject* APlayerCharacter::DetectObject()
{
    //MUST BE DEVELOP
    return NULL;
}


void APlayerCharacter::AnimPlay_Implementation(int number)
{
    // Default implementation
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("None AnimPlay")));
}

void APlayerCharacter::UseSkill(int index)
{
    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("%d Hotkey Pressed"), index + 1));
    if (HotkeySkill.IsValidIndex(index))
    {
        HotkeySkill[index].GetDefaultObject()->Perform();
        AppliedSkill = HotkeySkill[index];
    }
    else GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d Hotkey Not Used Pressed"), index + 1));
}
