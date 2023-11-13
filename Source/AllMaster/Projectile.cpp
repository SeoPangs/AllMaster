// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
    RootComponent = arrow;
    mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));;
    mesh->SetupAttachment(RootComponent);
    
    sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    sphere->SetupAttachment(RootComponent);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
    ProjectileMovement->InitialSpeed = 1500.f;
    ProjectileMovement->ProjectileGravityScale = 0;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
    this->SetLifeSpan(1.0f);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

