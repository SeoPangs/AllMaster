// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Skill.generated.h"

class AMob;

/// <summary>
/// Skill Class
/// </summary>
UCLASS(Blueprintable)
class ALLMASTER_API USkill : public UObject
{
	GENERATED_BODY()
		
protected:
	FName SkillType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SkillName;
	
public:
	USkill();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		AMob* Caster;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* SkillIcon;

public:

    UFUNCTION(BlueprintCallable)
    FName GetName() { return SkillName; }

	UFUNCTION(BlueprintNativeEvent)
	bool Perform();


    virtual bool Perform_Implementation();
	
    
};
