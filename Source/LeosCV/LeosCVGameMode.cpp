// Copyright Epic Games, Inc. All Rights Reserved.

#include "LeosCVGameMode.h"
#include "LeosCVCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALeosCVGameMode::ALeosCVGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
