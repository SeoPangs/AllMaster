// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveObject.generated.h"

UCLASS()
class ALLMASTER_API AInteractiveObject : public AActor
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UBoxComponent* box;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
    class UStaticMeshComponent* mesh;


public:

	// Sets default values for this actor's properties
	AInteractiveObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void Interact(class AMob* Interactor);
    virtual void Interact_Implementation(class AMob* Interactor);

    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
            class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
            bool bFromSweep, const FHitResult& SweepResult);
    
};
