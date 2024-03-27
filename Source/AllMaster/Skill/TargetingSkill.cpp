// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetingSkill.h"
#include "../Mob/Mob.h"
#include "EngineUtils.h"

//스킬 버튼을 눌렀을 때
bool UTargetingSkill::Perform_Implementation()
{
    //State가 Idle이면 스킬 시전
    //State가 Targeting이면 
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Execute UTargetingSkill::Perform")));
    Target = DetectTarget();
    if (Target)
    {
        Affect();
        return true;
    }
    return false;
    
}

AMob* UTargetingSkill::DetectTarget()
{
    AActor* ReferenceActor = Caster; // 기준이 되는 액터
    AMob* ReturnMob = NULL;
    float SearchRadius = 100.0f; // 검색 반경
    UWorld* World = GetWorld();
    if (World)
    {
        for (TActorIterator<AActor> ActorItr(World); ActorItr; ++ActorItr) {
            AActor* OtherActor = *ActorItr;

            // 기준 액터와의 거리 계산
            float Distance = (OtherActor->GetActorLocation() - ReferenceActor->GetActorLocation()).Size();

            if (Distance <= SearchRadius) {
                // 검색 반경 내에 있는 액터를 추가
                AMob* AddMob = Cast<AMob>(OtherActor);
                if (AddMob)
                {
                    FoundMobs.Add(AddMob);
                }
            }
        }
    }
    

    //return Cast<AMob>(FoundMobs.Pop());

    return NULL;
}

AMob* UTargetingSkill::AutoDetectTarget()
{
    AActor* ReferenceActor = Caster; // 기준이 되는 액터
    AMob* ReturnMob = NULL;
    float SearchRadius = 100.0f; // 검색 반경
    UWorld* World = GetWorld();
    if (World)
    {
        for (TActorIterator<AActor> ActorItr(World); ActorItr; ++ActorItr) {
            AActor* OtherActor = *ActorItr;

            // 기준 액터와의 거리 계산
            float Distance = (OtherActor->GetActorLocation() - ReferenceActor->GetActorLocation()).Size();

            if (Distance <= SearchRadius) {
                // 검색 반경 내에 있는 액터를 추가
                AMob* AddMob = Cast<AMob>(OtherActor);
                if (AddMob)
                {
                    FoundMobs.Add(AddMob);
                }
            }
        }
    }
    return NULL;
}

void UTargetingSkill::Affect()
{
    UE_LOG(LogTemp, Log, TEXT("Affect::Caster Name: %s"), *Caster->GetName());
    if (Target)
    {
        UE_LOG(LogTemp, Log, TEXT("Skill User Name: %s"), *Target->GetName());
    }
    
}