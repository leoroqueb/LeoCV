// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LeosCVCharacter.h"
#include "GameManagement/LeoCVSaveGame.h"
#include "GameFramework/GameModeBase.h"
#include "LeosCVGameMode.generated.h"

UCLASS(minimalapi)
class ALeosCVGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

	
	
public:
	ALeosCVGameMode();

	UPROPERTY(Category="Saving")
	ULeoCVSaveGame* SaveGameInstance;

	UPROPERTY(VisibleAnywhere, Category="References")
	ALeosCVCharacter* MainPlayer;
	
	UFUNCTION(BlueprintCallable, Category="SavingSystem")
	void SaveGame(FTransform PlayerPosition);

	UFUNCTION(BlueprintCallable, Category="SavingSystem")
	void LoadGame();

	UFUNCTION(BlueprintCallable, Category="SavingSystem")
	bool CleanSavedSlot();
};



