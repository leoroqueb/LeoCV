// Copyright Epic Games, Inc. All Rights Reserved.

#include "LeosCVGameMode.h"
#include "GameManagement/LeoCVSaveGame.h"
#include "Characters/MainPlayer.h"
#include "Kismet/GameplayStatics.h"
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

void ALeosCVGameMode::SaveGame(FTransform PlayerPosition)
{
	if(UGameplayStatics::DoesSaveGameExist("Slot_1", 0) && MainPlayer)
	{
		// Saving Data
		SaveGameInstance->PlayerHealth = MainPlayer->Health;
		SaveGameInstance->PlayerLifes = MainPlayer->CurrentLifes;
		SaveGameInstance->PlayerPosition = PlayerPosition;
		
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, "Slot_1", 0);
	}else if(MainPlayer){
		SaveGameInstance =
			Cast<ULeoCVSaveGame>(UGameplayStatics::CreateSaveGameObject(ULeoCVSaveGame::StaticClass()));
		
		/**
		 * Basicamente esta parte es un dispatcher. Si consigo definir algún metodo abstracto en una clase generica
		 * que pueda usar cada vez que quiera guardar, es descomentar y bindear.
		 * 
			// Set up the (optional) delegate.
			FAsyncSaveGameToSlotDelegate SavedDelegate;
			// USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
			SavedDelegate.BindUObject(SomeUObjectPointer, &USomeUObjectClass::SaveGameDelegateFunction);
		*/
		
		// Set data on the savegame object.
		SaveGameInstance->PlayerHealth = MainPlayer->Health;
		SaveGameInstance->PlayerLifes = MainPlayer->CurrentLifes;
		SaveGameInstance->PlayerPosition = PlayerPosition;

		// Start async save process.
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, "Slot_1", 0);
	}
}


bool ALeosCVGameMode::LoadGame()
{
	if(UGameplayStatics::DoesSaveGameExist("Slot_1", 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("SI EXISTE GAME SAVE"));
		// TODO: Synchronous load. This will need to be changed to asynchronous at some point
		if (ULeoCVSaveGame* LoadedGame = Cast<ULeoCVSaveGame>(UGameplayStatics::LoadGameFromSlot("Slot_1", 0)))
		{
			UE_LOG(LogTemp, Warning, TEXT("ENTRA AL LOAD %s"), *LoadedGame->GetName());
			if(!MainPlayer)
			{
				MainPlayer = Cast<AMainPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
			}
			UE_LOG(LogTemp, Warning, TEXT("ENTRA AL LOAD %s"), *MainPlayer->GetName());
			MainPlayer->SetActorLocation(LoadedGame->PlayerPosition.GetLocation());
			MainPlayer->SetActorRotation(LoadedGame->PlayerPosition.GetRotation());

			// Successful load
			return true;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("NO EXISTE GAME SAVE"));
	return false;
}

bool ALeosCVGameMode::CleanSavedSlot()
{
	if(UGameplayStatics::DoesSaveGameExist("Slot_1", 0))
	{
		UGameplayStatics::DeleteGameInSlot("Slot_1", 0);
		return true;
	}
	return false;
}


void ALeosCVGameMode::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("%d"), CleanSavedSlot());
	MainPlayer = Cast<AMainPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
}


