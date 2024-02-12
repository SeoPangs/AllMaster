// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObject.h"
#include "SkillBox.generated.h"

/**
 * 
 */

class USkill;

//이 클래스는 닿으면 스킬이 얻도록 생긴 클래스입니다.

UCLASS()
class ALLMASTER_API ASkillBox : public AInteractiveObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USkill> SetSkill;
	
public:
    virtual void Interact_Implementation(class AMob* Interactor);

};
