// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillBox.h"
#include "Mob.h"

void ASkillBox::Interact_Implementation(AMob* Interactor)
{
    Interactor->GetSkill(SetSkill);

    Destroy();
}