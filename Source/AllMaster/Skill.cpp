// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill.h"
#include "Mob.h"

bool USkill::Perform()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Execute USkill::Perform")));
	if (Caster)
	{
		UE_LOG(LogTemp, Log, TEXT("Skill Caster Name: %s"), *Caster->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Skill.cpp 1 Error"));
	}
	
	return true;
	
}

USkill::USkill()
{
	
}