// Copyright Epic Games, Inc. All Rights Reserved.

#include "AllMasterGameMode.h"
#include "AllMasterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAllMasterGameMode::AAllMasterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
