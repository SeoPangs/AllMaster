// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObject.h"
#include "Components/BoxComponent.h"
#include "../Mob/Mob.h"

// Sets default values
AInteractiveObject::AInteractiveObject()
{
    mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));;
    RootComponent = mesh;

    box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));;
    box->SetupAttachment(RootComponent);
   
    box->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveObject::OnOverlapBegin);
    
}

// Called when the game starts or when spawned
void AInteractiveObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractiveObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractiveObject::Interact_Implementation(AMob* Interactor)
{
    if (Interactor)
    {
        UE_LOG(LogTemp, Log, TEXT("Yes Interactor"));
    }
    else 
    {
        UE_LOG(LogTemp, Log, TEXT("Not Implement IINNTTEERRAACCTT"));
    }
    
}


void AInteractiveObject::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Log, TEXT("Interactive Object Overlap Begining"))
    AMob* interactor = Cast<AMob>(OtherActor);
    if (interactor)
    {
        Interact(interactor);
    }
    
}