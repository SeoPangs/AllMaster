// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mob/Mob.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */


enum class EWeaponStyle : uint8 { Sword UMETA(DisplayName = "Sword"), Wand UMETA(DisplayName = "Wand"), Bow UMETA(DisplayName = "Bow") };

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

    FName WeaponSocket = "hand_rSocket";

    UPROPERTY(EditAnywhere)
    class UStaticMeshComponent* Weapon;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Skill)
    TArray<TSubclassOf<USkill>> HotkeySkill;


protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
    APlayerCharacter();

private:


protected:
    void Sprint();
    void StopSprinting();
    void ToggleWalking();

    virtual void UseSkill(int index) override;
    
    virtual void Act_Implementation() override;

    AInteractiveObject* DetectObject(); //Find Near Interactive Object;

    UFUNCTION(BlueprintNativeEvent)
    void AnimPlay(int number);
    virtual void AnimPlay_Implementation(int number);
};
