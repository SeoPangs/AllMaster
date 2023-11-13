// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/ArrowComponent.h"
#include "Projectile.generated.h"


UCLASS()
class ALLMASTER_API AProjectile : public AActor
{
	GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere)
        UArrowComponent* arrow;
    UPROPERTY(EditAnywhere)
        UStaticMeshComponent* mesh;
    UPROPERTY(EditAnywhere)
        class USphereComponent* sphere;
    UPROPERTY(EditAnywhere)
        class UProjectileMovementComponent* ProjectileMovement;

public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    

};
