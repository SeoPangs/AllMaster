// Fill out your copyright notice in the Description page of Project Settings.

/*
Seqeunce:
    Use Skill -> Detecting Target -> Affect -> Return Success Value
    
Defualt Mechanism:
    Detecting Target: Find the nearest target in 30 scalar value, 
    Affect: Print caster's name and target's name;
    Return Success Value: Return true value if succeed in finding target;
*/

#pragma once

#include "CoreMinimal.h"
#include "Skill.h"
#include "TargetingSkill.generated.h"

class AMob;

/// <summary>
/// Skill by Targeting
/// </summary>
UCLASS()
class ALLMASTER_API UTargetingSkill : public USkill
{
	GENERATED_BODY()
	
private:
    bool isTargeting;
    AMob* Target;
    TArray<AActor*> FoundMobs;
    
protected:
    virtual AMob* DetectTarget();
    virtual AMob* AutoDetectTarget();
    virtual void Affect();

public:
    virtual bool Perform() override;
};
