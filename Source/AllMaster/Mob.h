// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mob.generated.h"

class USkill;

//현재 Mob이 무슨 액션을 취하고 있는지 상태를 표시하게 해주는 enum class;
UENUM(BlueprintType)
enum class EActionState : uint8 { M_Idle UMETA(DisplayName = "Idle"), M_Detect UMETA(DisplayName = "Targeting"), M_Perform UMETA(DisplayName = "Performing") };

UCLASS()
class ALLMASTER_API AMob : public ACharacter
{
	GENERATED_BODY()
protected:
    UPROPERTY(VisibleAnywhere, Category = Mob)
    TSubclassOf<USkill> AppliedSkill;

    UPROPERTY(EditAnywhere, Category = Mob)
    TArray<TSubclassOf<USkill>> SkillList;
    UPROPERTY(EditAnywhere, Category = Mob)
    EActionState State;

    
public:
	// Sets default values for this character's properties
	AMob();

private:

    /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* FollowCamera;
public:
    /** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float BaseTurnRate;

    /** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
    float BaseLookUpRate;

protected:
    /** Called for forwards/backward input */
    void MoveForward(float Value);

    /** Called for side to side input */
    void MoveRight(float Value);

    /**
     * Called via input to turn at a given rate.
     * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
     */
    void TurnAtRate(float Rate);

    /**
     * Called via input to turn look up/down at a given rate.
     * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
     */
    void LookUpAtRate(float Rate);

    /// <summary>
    /// Called via input to zoom in/out at a given rate.
    /// </summary>
    /// <param name="Rate"></param>
    void Zoom(float Rate);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
    /** Returns CameraBoom subobject **/
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    /** Returns FollowCamera subobject **/
    FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
    
    
protected:
    virtual void UseSkill(int index);
    


protected:
    //마우스 좌클릭 매핑;
    UFUNCTION(BlueprintCallable)
    virtual void Act();
    //입력을 받아서 스킬 매핑;
    virtual void UseSkillFirst();
    virtual void UseSkillSecond();
    virtual void UseSkillThird();
    virtual void UseSkillFourth();

public:
    UFUNCTION(BlueprintCallable)
    void GetSkill(TSubclassOf<USkill> gottenSkill);
};
