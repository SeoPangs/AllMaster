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
	FName SkillName;
	
public:
	USkill();

	
	UPROPERTY(EditAnywhere)
		AMob* Caster;
	
	UPROPERTY(EditAnywhere)
		UTexture2D* SkillIcon;

	UFUNCTION()
		virtual bool Perform();
		
};
