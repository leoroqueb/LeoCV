// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MainPlayer.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Saving")
	ULeoCVSaveGame* SaveGameInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="References")
	AMainPlayer* MainPlayer;
	
	UFUNCTION(BlueprintCallable, Category="SavingSystem")
	void SaveGame(FTransform PlayerPosition);
	
	/**
	 * @returns bool. True if loaded was successful
	 */
	UFUNCTION(BlueprintCallable, Category="SavingSystem")
	bool LoadGame();

	UFUNCTION(BlueprintCallable, Category="SavingSystem")
	bool CleanSavedSlot();
};



