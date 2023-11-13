// Fill out your copyright notice in the Description page of Project Settings.


#include "Mob.h"
#include "Skill.h"
#include "TargetingSkill.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMob::AMob()
{
    State = EActionState::M_Idle;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    // set our turn rates for input
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;

    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 500.0f; // The camera follows at this distance behind the character	
    CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
    FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

    // Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
    // are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

// Called when the game starts or when spawned
void AMob::BeginPlay()
{
    Super::BeginPlay();

    SkillList.Emplace(USkill::StaticClass());
    SkillList.Emplace(UTargetingSkill::StaticClass());


    AppliedSkill = NULL;
    //MUST
    SkillList[0].GetDefaultObject()->Caster = this;
    SkillList[1].GetDefaultObject()->Caster = this;
	
}

// Called every frame
void AMob::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMob::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

    PlayerInputComponent->BindAxis("MoveForward", this, &AMob::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMob::MoveRight);

    // We have 2 versions of the rotation bindings to handle different kinds of devices differently
    // "turn" handles devices that provide an absolute delta, such as a mouse.
    // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &AMob::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookUpRate", this, &AMob::LookUpAtRate);
    PlayerInputComponent->BindAxis("Zoom", this, &AMob::Zoom);

    PlayerInputComponent->BindAction("Act", IE_Pressed, this, &AMob::Act);

    PlayerInputComponent->BindAction("SkillFirst", IE_Pressed, this, &AMob::UseSkillFirst);
    PlayerInputComponent->BindAction("SkillSecond", IE_Pressed, this, &AMob::UseSkillSecond);
    PlayerInputComponent->BindAction("SkillThird", IE_Pressed, this, &AMob::UseSkillThird);
    PlayerInputComponent->BindAction("SkillFourth", IE_Pressed, this, &AMob::UseSkillFourth);
    
}

void AMob::TurnAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMob::LookUpAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMob::Zoom(float Rate)
{
    this->CameraBoom->TargetArmLength += Rate;
    if (CameraBoom->TargetArmLength > 700)
    {
        CameraBoom->TargetArmLength = 700;
    }
    else if (CameraBoom->TargetArmLength < 100)
    {
        CameraBoom->TargetArmLength = 100;
    }

    
}

void AMob::MoveForward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void AMob::MoveRight(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        // find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get right vector 
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        // add movement in that direction
        AddMovementInput(Direction, Value);
    }
}

void AMob::UseSkill(int index)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Skill Use %d"), index+1));
    if (SkillList.IsValidIndex(index))
    {
        SkillList[index].GetDefaultObject()->Perform();
        AppliedSkill = SkillList[index];
    }
    else GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Skill %d Not Perform"), index + 1));
}

void AMob::Act() 
{
    //MUST
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Mob Act, Set Act Plz")));
}

void AMob::UseSkillFirst()
{
    UseSkill(0);
}

void AMob::UseSkillSecond()
{
    UseSkill(1);
}

void AMob::UseSkillThird()
{
    UseSkill(2);
}
void AMob::UseSkillFourth()
{
    UseSkill(3);
}

void AMob::GetSkill(TSubclassOf<USkill> gottenSkill)
{
    SkillList.Add(gottenSkill);
}